#include "Vfwd_unit.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>
#include <cstdint>

// Emulate definitions from defs.vh
#define FWD_NONE   0x0
#define FWD_EX_MEM 0x1
#define FWD_MEM_WB 0x2

// Mock control bus values (Assuming LSB is RegWrite)
#define CTL_REGWRITE_ON  0x1
#define CTL_REGWRITE_OFF 0x0

int main(int argc, char **argv)
{
  Verilated::commandArgs(argc, argv);
  Vfwd_unit *dut = new Vfwd_unit;

  Verilated::traceEverOn(true);
  VerilatedVcdC *tfp = new VerilatedVcdC;

  dut->trace(tfp, 99); 
  tfp->open("vcd/fwd_unit_trace.vcd");

  int time = 0;
  int fails = 0;

  auto run_test = [&](uint32_t got1, uint32_t got2, uint32_t exp1, uint32_t exp2, const char *name)
  {
    dut->eval();
    tfp->dump(time++);

    if (got1 != exp1 || got2 != exp2)
    {
      std::cerr << "[FAILED] " << name
                << "\n         Expected: fwd1=0x" << exp1 << ", fwd2=0x" << exp2
                << "\n         Got:      fwd1=0x" << got1 << ", fwd2=0x" << got2 << "\n";
      fails++;
    }
    else
    {
      std::cout << "[PASSED] " << name << "\n";
    }
  };

  // Helper to reset inputs
  auto reset_inputs = [&]() {
    dut->___05Fex_rs1 = 0; dut->___05Fex_rs2 = 0;
    dut->___05Fmem_rd = 0; dut->___05Fmem_ctl_bus = CTL_REGWRITE_OFF;
    dut->___05Fwb_rd = 0;  dut->___05Fwb_ctl_bus = CTL_REGWRITE_OFF;
    dut->eval();
  };

  std::cout << "====== Starting Forwarding Unit Tests ======\n";

  // --- TEST 1: No Hazards ---
  reset_inputs();
  dut->___05Fex_rs1 = 5; dut->___05Fex_rs2 = 6;
  dut->___05Fmem_rd = 7; dut->___05Fwb_rd = 8;
  run_test(dut->fwd1, dut->fwd2, FWD_NONE, FWD_NONE, "No Hazards");

  // --- TEST 2: EX Hazard on RS1 ---
  reset_inputs();
  dut->___05Fex_rs1 = 10; dut->___05Fex_rs2 = 11;
  dut->___05Fmem_rd = 10; dut->___05Fmem_ctl_bus = CTL_REGWRITE_ON;
  run_test(dut->fwd1, dut->fwd2, FWD_EX_MEM, FWD_NONE, "EX Hazard on rs1");

  // --- TEST 3: EX Hazard on RS2 ---
  reset_inputs();
  dut->___05Fex_rs1 = 10; dut->___05Fex_rs2 = 11;
  dut->___05Fmem_rd = 11; dut->___05Fmem_ctl_bus = CTL_REGWRITE_ON;
  run_test(dut->fwd1, dut->fwd2, FWD_NONE, FWD_EX_MEM, "EX Hazard on rs2");

  // --- TEST 4: MEM Hazard on RS1 ---
  reset_inputs();
  dut->___05Fex_rs1 = 20; dut->___05Fex_rs2 = 21;
  dut->___05Fwb_rd = 20; dut->___05Fwb_ctl_bus = CTL_REGWRITE_ON;
  run_test(dut->fwd1, dut->fwd2, FWD_MEM_WB, FWD_NONE, "MEM Hazard on rs1");

  // --- TEST 5: Simultaneous Hazards (EX on rs1, MEM on rs2) ---
  reset_inputs();
  dut->___05Fex_rs1 = 5; dut->___05Fex_rs2 = 6;
  dut->___05Fmem_rd = 5; dut->___05Fmem_ctl_bus = CTL_REGWRITE_ON;
  dut->___05Fwb_rd = 6;  dut->___05Fwb_ctl_bus = CTL_REGWRITE_ON;
  run_test(dut->fwd1, dut->fwd2, FWD_EX_MEM, FWD_MEM_WB, "Simultaneous EX(rs1) and MEM(rs2) Hazards");

  // --- TEST 6: Double Data Hazard (rs1) -> Prioritize EX ---
  // The classic case: 
  // add x1, x2, x3
  // add x1, x1, x4
  // add x5, x1, x1  <- EX stage wants x1 from the immediately previous instruction!
  reset_inputs();
  dut->___05Fex_rs1 = 15; dut->___05Fex_rs2 = 2;
  dut->___05Fmem_rd = 15; dut->___05Fmem_ctl_bus = CTL_REGWRITE_ON;
  dut->___05Fwb_rd = 15;  dut->___05Fwb_ctl_bus = CTL_REGWRITE_ON;
  run_test(dut->fwd1, dut->fwd2, FWD_EX_MEM, FWD_NONE, "Double Data Hazard (rs1) - EX wins");

  // --- TEST 7: Double Data Hazard (rs2) -> Prioritize EX ---
  reset_inputs();
  dut->___05Fex_rs1 = 2; dut->___05Fex_rs2 = 15;
  dut->___05Fmem_rd = 15; dut->___05Fmem_ctl_bus = CTL_REGWRITE_ON;
  dut->___05Fwb_rd = 15;  dut->___05Fwb_ctl_bus = CTL_REGWRITE_ON;
  run_test(dut->fwd1, dut->fwd2, FWD_NONE, FWD_EX_MEM, "Double Data Hazard (rs2) - EX wins");

  // --- TEST 8: The x0 Zero-Register Constraint ---
  // If instructions try to write to x0, we should NEVER forward that garbage data.
  reset_inputs();
  dut->___05Fex_rs1 = 0; dut->___05Fex_rs2 = 0;
  dut->___05Fmem_rd = 0; dut->___05Fmem_ctl_bus = CTL_REGWRITE_ON;
  dut->___05Fwb_rd = 0;  dut->___05Fwb_ctl_bus = CTL_REGWRITE_ON;
  run_test(dut->fwd1, dut->fwd2, FWD_NONE, FWD_NONE, "Zero Register (x0) Bypass Check");

  // --- TEST 9: RegWrite Safety Check ---
  // Even if rd == rs1, if the previous instruction doesn't write to a register (like a Branch), don't forward.
  reset_inputs();
  dut->___05Fex_rs1 = 9; dut->___05Fex_rs2 = 10;
  dut->___05Fmem_rd = 9; dut->___05Fmem_ctl_bus = CTL_REGWRITE_OFF; // Note: RegWrite is OFF
  dut->___05Fwb_rd = 10; dut->___05Fwb_ctl_bus = CTL_REGWRITE_OFF;  // Note: RegWrite is OFF
  run_test(dut->fwd1, dut->fwd2, FWD_NONE, FWD_NONE, "RegWrite Disable Check");

  // Flush and close
  tfp->dump(time++);
  tfp->close();

  delete dut;
  delete tfp;

  std::cout << "========================================\n";
  if (fails == 0)
  {
    std::cout << "SUCCESS: All forwarding unit tests passed!\n";
    return 0;
  }
  else
  {
    std::cerr << "FAILURE: " << fails << " tests failed.\n";
    return -1;
  }
}