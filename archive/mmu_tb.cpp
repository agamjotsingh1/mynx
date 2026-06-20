// TODO! non AI-fy this code
#include "Vmmu.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>
#include <iomanip>
#include <cstdint>

// Memory access width definitions (from defs.vh)
#define BW_BYTE     0x0
#define BW_HALFWORD 0x1
#define BW_WORD     0x2
#define BW_DBLWORD  0x3

// MMU & Sv39 definitions
#define SATP_MODE_SV39 0x8ULL
#define MEMBASE        0x80000000ULL

// PTE Flags (from defs.vh)
#define PTEF_V 0x01
#define PTEF_R 0x02
#define PTEF_W 0x04
#define PTEF_X 0x08
#define PTEF_U 0x10

int main(int argc, char **argv)
{
  Verilated::commandArgs(argc, argv);
  Vmmu *dut = new Vmmu;

  Verilated::traceEverOn(true);
  VerilatedVcdC *tfp = new VerilatedVcdC;

  dut->trace(tfp, 99); 
  tfp->open("vcd/mmu_trace.vcd");

  int time = 0;
  int fails = 0;

  auto tick = [&]() {
    dut->clk = 0;
    dut->eval();
    tfp->dump(time++);
    
    dut->clk = 1;
    dut->eval();
    tfp->dump(time++);
  };

  auto run_test = [&](uint64_t got, uint64_t expected, const char *name)
  {
    if (got != expected)
    {
      std::cerr << "[FAILED] " << name
                << "\n         Expected: 0x" << std::hex << expected
                << "\n         Got:      0x" << got << std::dec << "\n";
      fails++;
    }
    else
    {
      std::cout << "[PASSED] " << name << "\n";
    }
  };

  std::cout << "====== Starting MMU (Sv39) Tests ======\n";

  // Reset sequence
  dut->rst = 1;
  dut->satp = 0;
  dut->addr_a = 0; dut->mem_read_a = 0; dut->mem_write_a = 0; dut->bw_a = 0; dut->data_in_a = 0; dut->sign_extend_a = 0;
  dut->addr_b = 0; dut->mem_read_b = 0; dut->mem_write_b = 0; dut->bw_b = 0; dut->data_in_b = 0; dut->sign_extend_b = 0;
  tick();
  dut->rst = 0;
  tick();

  // --- TEST 1: Baremetal mode bypass ---
  dut->satp = 0; // SATP_MODE_BAREMETAL
  dut->mem_write_a = 1;
  dut->bw_a = BW_DBLWORD;
  dut->addr_a = MEMBASE + 0x100;
  dut->data_in_a = 0x1122334455667788ULL;
  tick();
  dut->mem_write_a = 0;

  dut->mem_read_a = 1;
  dut->eval();
  run_test(dut->data_out_a, 0x1122334455667788ULL, "Baremetal Doubleword Write/Read (No Translation)");
  dut->mem_read_a = 0;

  // --- TEST 2: Setup Sv39 Page Tables ---
  // We will map Virtual Address: 0x12345000 -> Physical Address: 0x80003000
  // VPN[2] = 0, VPN[1] = 0x91, VPN[0] = 0x145, Offset = 0x000
  
  // 1. Write Root PTE (Level 2 Table)
  // Base at MEMBASE (PA 0x80000000). VPN[2]=0 -> Offset 0.
  dut->mem_write_a = 1; dut->bw_a = BW_DBLWORD;
  dut->addr_a = MEMBASE; 
  // Point to PA 0x80001000 (PPN 0x80001). Set Valid flag.
  dut->data_in_a = (0x80001ULL << 10) | PTEF_V; 
  tick();

  // 2. Write Level 1 PTE
  // Base at PA 0x80001000. VPN[1] = 0x91 -> Entry offset = 0x91 * 8 = 0x488.
  dut->addr_a = MEMBASE + 0x1000 + 0x488;
  // Point to PA 0x80002000 (PPN 0x80002). Set Valid flag.
  dut->data_in_a = (0x80002ULL << 10) | PTEF_V;
  tick();

  // 3. Write Leaf PTE (Level 0 Table)
  // Base at PA 0x80002000. VPN[0] = 0x145 -> Entry offset = 0x145 * 8 = 0xA28.
  dut->addr_a = MEMBASE + 0x2000 + 0xA28;
  // Point to Target PA 0x80003000 (PPN 0x80003). Set Valid, Read, Write flags.
  dut->data_in_a = (0x80003ULL << 10) | PTEF_V | PTEF_R | PTEF_W;
  tick();

  // 4. Write Actual Target Data at mapped Physical Address 0x80003000
  dut->addr_a = MEMBASE + 0x3000;
  dut->data_in_a = 0xCAFEBABE11223344ULL;
  tick();
  dut->mem_write_a = 0;

  // --- TEST 3: Sv39 Page Table Walk ---
  // Setup satp register (Mode SV39, PPN of root table = PA 0x80000000 >> 12 = 0x80000)
  dut->satp = (SATP_MODE_SV39 << 60) | 0x80000ULL;
  
  // Issue translation request for Virtual Address 0x12345000
  dut->addr_a = 0x12345000ULL;
  dut->mem_read_a = 1;
  dut->bw_a = BW_DBLWORD;

  dut->eval();
  if (!dut->hard_stall) std::cerr << "[FAILED] MMU did not assert hard_stall on PT walk start!\n";

  // Simulate processor pipeline waiting for the MMU's hard_stall to drop
  int cycles = 0;
  while (dut->hard_stall && cycles < 10) {
    tick(); // lvl: 3 -> 2 -> 1 -> 0
    dut->eval();
    cycles++;
  }

  // At this point hard_stall should be 0, and data_out_a contains the translated memory fetch
  run_test(cycles, 3, "Sv39 Walk exactly 3 stall cycles");
  run_test(dut->data_out_a, 0xCAFEBABE11223344ULL, "Sv39 Page Table Translated Fetch");

  // Keep read high for one more tick to gracefully cycle lvl counter back to PGTBL_LVLS
  tick();
  dut->mem_read_a = 0;

  // --- TEST 4: Simultaneous Dual-Port Page Walks ---
  // Reset lvl state just in case
  dut->rst = 1; tick(); dut->rst = 0; tick(); 
  
  // We will configure Port B to read a different VA that maps to the same target PA
  // Mapping VA 0x2000_0000 -> PA 0x80003000
  // VPN[2] = 0, VPN[1] = 0x100, VPN[0] = 0x0
  
  dut->satp = 0; // Go to baremetal briefly to setup Port B's tables
  
  // Level 1 PTE for Port B (Root is same because VPN[2] is 0)
  // PA 0x80001000 + (0x100 * 8) = 0x80001800
  dut->mem_write_a = 1; dut->bw_a = BW_DBLWORD;
  dut->addr_a = MEMBASE + 0x1000 + 0x800;
  dut->data_in_a = (0x80004ULL << 10) | PTEF_V; // Points to PA 0x80004000
  tick();

  // Leaf PTE for Port B
  // PA 0x80004000 + (0 * 8) = 0x80004000
  dut->addr_a = MEMBASE + 0x4000;
  dut->data_in_a = (0x80003ULL << 10) | PTEF_V | PTEF_R | PTEF_W; // Points to same PA 0x80003000
  tick();
  dut->mem_write_a = 0;

  // Re-enable SV39
  dut->satp = (SATP_MODE_SV39 << 60) | 0x80000ULL;

  // Fire both ports simultaneously
  dut->addr_a = 0x12345000ULL;
  dut->mem_read_a = 1;
  dut->bw_a = BW_DBLWORD;
  
  dut->addr_b = 0x20000000ULL;
  dut->mem_read_b = 1;
  dut->bw_b = BW_DBLWORD;

  dut->eval();
  cycles = 0;
  while (dut->hard_stall && cycles < 10) {
    tick();
    dut->eval();
    cycles++;
  }

  run_test(cycles, 3, "Dual-Port Sv39 Walk exactly 3 stall cycles");
  run_test(dut->data_out_a, 0xCAFEBABE11223344ULL, "Port A Translated Output");
  run_test(dut->data_out_b, 0xCAFEBABE11223344ULL, "Port B Translated Output (Alias Map)");

  // Finish cleanly
  tick();
  tfp->dump(time++);
  tfp->close();

  delete dut;
  delete tfp;

  std::cout << "========================================\n";
  if (fails == 0)
  {
    std::cout << "SUCCESS: All MMU/Sv39 tests passed!\n";
    return 0;
  }
  else
  {
    std::cerr << "FAILURE: " << fails << " tests failed.\n";
    return -1;
  }
}