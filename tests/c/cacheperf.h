#ifndef CACHEPERF_H
#define CACHEPERF_H

#include "env/encoding.h"

#define UART_THR (*((volatile uint8_t *)(UARTBASE + 0x00)))
#define UART_FCR (*((volatile uint8_t *)(UARTBASE + 0x02)))
#define UART_LSR (*((volatile uint8_t *)(UARTBASE + 0x05)))

#define LSR_THR_EMPTY 0x20
#define FCR_FIFO_EN   0x01

#define CACHE_LINESZ  64ULL
#define CACHE_LINES   2048ULL
#define CACHE_BYTES   (CACHE_LINESZ * CACHE_LINES) // 128 KiB

extern void trapvec();

// trapvec.S dispatches here; nothing to do for these compute-only tests.
void trap_handler() {
  uint64_t mcause;
  csrr(mcause, mcause);
  (void)mcause;
}

static void putc(char c) {
  while ((UART_LSR & LSR_THR_EMPTY) == 0);
  UART_THR = c;
}

static void puts(const char *s) {
  while (*s) putc(*s++);
}

static void put_dec(uint64_t v) {
  char buf[21];
  int i = 0;
  if (v == 0) { putc('0'); return; }
  while (v) { buf[i++] = '0' + (char)(v % 10); v /= 10; }
  while (i) putc(buf[--i]);
}

// print num/den to 3 decimals using integer math (no FP on this core)
static void put_ratio(uint64_t num, uint64_t den) {
  if (den == 0) { puts("n/a"); return; }
  put_dec(num / den);
  putc('.');
  uint64_t frac = ((num % den) * 1000) / den;
  int i;
  for (i = 100; i > 1; i /= 10)
    if (frac < (uint64_t)i) putc('0');
  put_dec(frac);
}

// single hot sink: store final result here once so the compiler can't dead-
// code the measured loop, without adding per-iteration memory traffic.
static volatile uint64_t sink_out;

typedef struct {
  uint64_t ic_hits, ic_acc, dc_hits, dc_acc;
} perf_t;

static void perf_read(perf_t *p) {
  csrr(mhpmcounter4, p->ic_acc);   // read acc first, then hits: keeps the
  csrr(mhpmcounter3, p->ic_hits);  // window tight and consistent
  csrr(mhpmcounter6, p->dc_acc);
  csrr(mhpmcounter5, p->dc_hits);
}

static void perf_init() {
  UART_FCR = FCR_FIFO_EN;
  csrw(mtvec, trapvec);
}

// print a "hits / acc  (rate%)" line for one cache
static void perf_line(const char *tag, uint64_t hits, uint64_t acc) {
  puts(tag);
  put_dec(hits); putc('/'); put_dec(acc);
  puts("  rate ");
  put_ratio(hits * 100, acc);
  puts("%\n");
}

static void perf_report(const char *name, const perf_t *a, const perf_t *b) {
  uint64_t ich = b->ic_hits - a->ic_hits;
  uint64_t ica = b->ic_acc  - a->ic_acc;
  uint64_t dch = b->dc_hits - a->dc_hits;
  uint64_t dca = b->dc_acc  - a->dc_acc;

  puts("\n=== "); puts(name); puts(" ===\n");
  perf_line("  I$ ", ich, ica);
  perf_line("  D$ ", dch, dca);
}

#endif
