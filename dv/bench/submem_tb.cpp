// driver for the submem+amc+axi_slave bench.
// plays the mmu/pipeline role faithfully:
//   - presents an op and holds it until busy drops (hard_stall protocol),
//     including holding it through the completion cycle like ex_mem_reg does
//   - randomly aborts ops mid-transaction (__wb_trap_taken model): en drops,
//     addr/data/bw churn with garbage every cycle, then the op is either
//     re-issued (sret re-execution) or abandoned (squashed)
//   - runs fence.i-style flushes (hold flush until flush_done) and then
//     compares the entire slave RAM against the reference model via backdoor
//   - checks every completed read against the reference model
//   - watchdogs every wait so a wedged FSM reports instead of hanging
#include <verilated.h>
#include "Vsubmem_tb.h"
#include "Vsubmem_tb___024root.h"
#if VM_TRACE
#include <verilated_vcd_c.h>
#endif
#include <cstdio>
#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

static const uint32_t MEM_BYTES = 1048576;
static const uint32_t MEM_WORDS = MEM_BYTES / 8;

static Vsubmem_tb *top;
static uint64_t cycles = 0;
#if VM_TRACE
static VerilatedVcdC *tfp = nullptr;
#endif

static uint64_t f_init(uint64_t i) {
  return (i * 0x9E3779B97F4A7C15ULL) ^ 0xA5A5DEADBEEF5A5AULL;
}

/* xorshift64 rng */
static uint64_t rng_state;
static uint64_t rnd64() {
  uint64_t x = rng_state;
  x ^= x << 13; x ^= x >> 7; x ^= x << 17;
  rng_state = x;
  return x;
}
static uint32_t rnd(uint32_t n) { return (uint32_t)(rnd64() % n); }

/* event history for failure reports */
struct Event { uint64_t cycle; char text[96]; };
static Event hist[64];
static int hist_n = 0;
static void record(const char *fmt, ...) {
  Event &e = hist[hist_n++ % 64];
  e.cycle = cycles;
  va_list ap; va_start(ap, fmt);
  vsnprintf(e.text, sizeof e.text, fmt, ap);
  va_end(ap);
}
static void dump_history() {
  fprintf(stderr, "--- last events ---\n");
  int n = hist_n < 64 ? hist_n : 64;
  int start = hist_n < 64 ? 0 : hist_n % 64;
  for (int i = 0; i < n; i++) {
    Event &e = hist[(start + i) % 64];
    fprintf(stderr, "  cyc %8lu  %s\n", (unsigned long)e.cycle, e.text);
  }
}

static void fail(const char *fmt, ...) {
  va_list ap; va_start(ap, fmt);
  fprintf(stderr, "FAIL @ cycle %lu: ", (unsigned long)cycles);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  va_end(ap);
  dump_history();
#if VM_TRACE
  if (tfp) tfp->close();
#endif
  exit(1);
}

static void spy_after_edge();

static void step() {
  top->clk = 0; top->eval();
#if VM_TRACE
  if (tfp) tfp->dump(cycles * 10);
#endif
  top->clk = 1; top->eval();
#if VM_TRACE
  if (tfp) tfp->dump(cycles * 10 + 5);
#endif
  cycles++;
  spy_after_edge();
}

/* reference model, byte granular */
static std::vector<uint8_t> ref;

static void ref_init() {
  ref.resize(MEM_BYTES);
  for (uint32_t w = 0; w < MEM_WORDS; w++) {
    uint64_t v = f_init(w);
    memcpy(&ref[w * 8], &v, 8);
  }
}

static int bw_bytes(int bw) { return 1 << bw; } // BW_BYTE=0 .. BW_DBLWORD=3

static uint64_t ref_read(uint32_t addr, int bw) {
  uint64_t v = 0;
  memcpy(&v, &ref[addr], bw_bytes(bw)); // zero-extended (sign_extend tied 0)
  return v;
}
static void ref_write(uint32_t addr, int bw, uint64_t data) {
  memcpy(&ref[addr], &data, bw_bytes(bw));
}

struct Op { bool is_write; uint32_t addr; int bw; uint64_t data; };

/* watchpoint: architectural value of one dblword (cache line if tag hits,
 * else slave DRAM) compared against ref at every op boundary. WATCH_ADDR env,
 * hex. only valid while submem is IDLE. */
static int64_t watch_addr = -1;
static uint64_t watch_ops = 0;

/* per-cycle spy: prints every change of the watched word's BRAM copy, DRAM
 * copy, and its line's meta entry, with the submem state. SPY=1 env. */
static bool spy_on = false;
static void spy_after_edge() {
  if (!spy_on || watch_addr < 0) return;
  static uint64_t last_bram = 0, last_dram = 0;
  static uint32_t last_meta = 0xFFFFFFFF;
  static uint8_t last_state = 0xFF;
  auto *r = top->rootp;
  uint32_t a = (uint32_t)watch_addr;
  uint32_t index = (a >> 6) & 0x7FF;
  uint64_t bram =
    r->submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[a >> 3];
  uint32_t meta = index & 1
    ? r->submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd[index >> 1]
    : r->submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even[index >> 1];
  top->bd_addr = a & ~7u;
  top->eval();
  uint64_t dram = top->bd_data;
  uint8_t st = r->submem_tb__DOT__dut__DOT__state;
  if (bram != last_bram || dram != last_dram || meta != last_meta) {
    fprintf(stderr,
            "spy cyc %8lu st=%x meta{v=%d d=%d tag=%03x} bram=%016lx dram=%016lx\n",
            (unsigned long)cycles, st, (meta >> 11) & 1, (meta >> 10) & 1,
            meta & 0x3FF, (unsigned long)bram, (unsigned long)dram);
    last_bram = bram; last_dram = dram; last_meta = meta; last_state = st;
  }
  (void)last_state;
}
static void watch_check(const char *where) {
  if (watch_addr < 0) return;
  auto *r = top->rootp;
  if (r->submem_tb__DOT__dut__DOT__state != 0) return; // not IDLE: defer
  uint32_t a = (uint32_t)watch_addr;
  uint32_t index = (a >> 6) & 0x7FF;
  uint32_t tag = a >> 17;
  uint32_t meta = index & 1
    ? r->submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd[index >> 1]
    : r->submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even[index >> 1];
  int valid = (meta >> 11) & 1;
  int dirty = (meta >> 10) & 1;
  uint32_t mtag = meta & 0x3FF;
  uint64_t got;
  const char *src;
  if (valid && mtag == tag) {
    got = r->submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[a >> 3];
    src = dirty ? "cache-dirty" : "cache-clean";
  } else {
    top->bd_addr = a & ~7u;
    top->eval();
    got = top->bd_data;
    src = "dram";
  }
  uint64_t want;
  memcpy(&want, &ref[a & ~7u], 8);
  if (got != want)
    fail("WATCH %06x diverged (%s, after %s, op#%lu): want=%016lx got=%016lx "
         "meta{v=%d d=%d tag=%03x}",
         a, src, where, (unsigned long)watch_ops, (unsigned long)want,
         (unsigned long)got, valid, dirty, mtag);
}

static uint64_t aborts = 0, ops_done = 0, ops_abandoned = 0, flushes = 0;

static void garbage_inputs() {
  top->mem_read = 0;
  top->mem_write = 0;
  top->addr = rnd64() & 0x7FFFFFF; // full 27-bit churn, like a moving pipeline
  top->data_in = rnd64();
  top->bw = rnd(4);
}

static void set_op_inputs(const Op &op) {
  top->addr = op.addr;
  top->mem_read = !op.is_write;
  top->mem_write = op.is_write;
  top->bw = op.bw;
  top->data_in = op.data;
}

// returns true if the op completed, false if abandoned by an abort.
// on completion of a read, *rdata holds data_out.
static bool drive_op(const Op &op, uint64_t *rdata, bool allow_abort) {
  set_op_inputs(op);
  uint64_t guard = 0;
  while (true) {
    step();
    if (++guard > 100000)
      fail("watchdog: busy never dropped (op %s addr=%06x bw=%d)",
           op.is_write ? "W" : "R", op.addr, op.bw);

    if (!top->busy) {
      // completion cycle: data_out valid now; hold the op through it,
      // exactly like ex_mem_reg holds MEM-stage inputs
      if (rdata) *rdata = top->data_out;
      step();
      return true;
    }

    if (allow_abort && rnd(128) == 0) {
      // trap taken: en drops combinationally, pipeline churns for a while
      aborts++;
      record("abort during %s addr=%06x", op.is_write ? "W" : "R", op.addr);
      int churn = 1 + rnd(16);
      for (int i = 0; i < churn; i++) {
        garbage_inputs();
        step();
      }
      if (rnd(2)) {
        set_op_inputs(op); // sret: re-execute the squashed op
      } else {
        ops_abandoned++;
        top->mem_read = 0;
        top->mem_write = 0;
        return false;
      }
    }
  }
}

static void verify_ram(const char *when) {
  for (uint32_t w = 0; w < MEM_WORDS; w++) {
    top->bd_addr = w * 8;
    top->eval();
    uint64_t want;
    memcpy(&want, &ref[w * 8], 8);
    if (top->bd_data != want)
      fail("%s: DRAM mismatch @%06x want=%016lx got=%016lx",
           when, w * 8, (unsigned long)want, (unsigned long)top->bd_data);
  }
}

static void do_flush() {
  flushes++;
  record("flush #%lu", (unsigned long)flushes);
  top->mem_read = 0;
  top->mem_write = 0;
  step(); step();
  if (spy_on)
    fprintf(stderr, "spy cyc %8lu flush #%lu entry: state=%x flush_line=%03x\n",
            (unsigned long)cycles, (unsigned long)flushes,
            top->rootp->submem_tb__DOT__dut__DOT__state,
            top->rootp->submem_tb__DOT__dut__DOT__flush_line);
  top->flush = 1;
  uint64_t guard = 0;
  while (true) {
    step();
    if (top->flush_done) break;
    if (++guard > 1000000) fail("watchdog: flush_done never asserted");
  }
  // mmu (a reg FSM) holds flush through the whole cycle it samples done in;
  // submem self-clears flush_done at that same edge. one more edge with
  // flush still high, THEN drop it — dropping combinationally in the same
  // cycle leaves flush_done stale and the next flush no-ops.
  step();
  top->flush = 0;
  step(); step();
  verify_ram("post-flush");
}

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  uint64_t seed = 1, nops = 50000;
  bool noabort = false;
  for (int i = 1; i < argc; i++) {
    if (!strncmp(argv[i], "+seed=", 6)) seed = strtoull(argv[i] + 6, 0, 0);
    if (!strncmp(argv[i], "+ops=", 5)) nops = strtoull(argv[i] + 5, 0, 0);
    if (!strcmp(argv[i], "+noabort")) noabort = true;
  }
  rng_state = seed * 0x2545F4914F6CDD1DULL + 1;
  if (const char *w = getenv("WATCH_ADDR"))
    watch_addr = (int64_t)strtoull(w, 0, 16);
  spy_on = getenv("SPY") != nullptr;

  top = new Vsubmem_tb;
#if VM_TRACE
  if (getenv("BENCH_TRACE")) {
    Verilated::traceEverOn(true);
    tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("bench.vcd");
  }
#endif

  ref_init();

  top->rng_seed = (uint32_t)(seed ^ (seed >> 32)) | 1;
  top->rst = 1;
  top->flush = 0;
  top->mem_read = 0;
  top->mem_write = 0;
  top->addr = 0;
  top->bw = 3;
  top->data_in = 0;
  top->bd_addr = 0;
  for (int i = 0; i < 5; i++) step();
  top->rst = 0;
  step();

  for (uint64_t n = 0; n < nops; n++) {
    if (n && n % 2000 == 0) {
      do_flush();
      if (rnd(4) == 0) do_flush(); // flush must be idempotent
    }

    Op op;
    // size distribution: mostly dblword like real kernel traffic
    uint32_t r = rnd(100);
    op.bw = (r < 50) ? 3 : (r < 70) ? 2 : (r < 85) ? 1 : 0;
    int sz = bw_bytes(op.bw);
    op.addr = (rnd(MEM_BYTES / 8) * 8 + rnd(8 / sz) * sz) % MEM_BYTES;
    op.is_write = rnd(2);
    op.data = rnd64();

    uint64_t rdata = 0;
    watch_ops = n;
    if (!drive_op(op, op.is_write ? nullptr : &rdata, !noabort)) {
      watch_check("abandon");
      continue;
    }
    ops_done++;

    if (op.is_write) {
      ref_write(op.addr, op.bw, op.data);
      record("W addr=%06x bw=%d data=%016lx", op.addr, op.bw,
             (unsigned long)op.data);
    } else {
      uint64_t want = ref_read(op.addr, op.bw);
      record("R addr=%06x bw=%d got=%016lx", op.addr, op.bw,
             (unsigned long)rdata);
      if (rdata != want)
        fail("read mismatch addr=%06x bw=%d want=%016lx got=%016lx",
             op.addr, op.bw, (unsigned long)want, (unsigned long)rdata);
    }
    watch_check(op.is_write ? "write" : "read");
  }

  do_flush(); // final: writeback everything and compare full DRAM image

  printf("PASS seed=%lu ops=%lu aborts=%lu abandoned=%lu flushes=%lu cycles=%lu\n",
         (unsigned long)seed, (unsigned long)ops_done, (unsigned long)aborts,
         (unsigned long)ops_abandoned, (unsigned long)flushes,
         (unsigned long)cycles);
#if VM_TRACE
  if (tfp) tfp->close();
#endif
  delete top;
  return 0;
}
