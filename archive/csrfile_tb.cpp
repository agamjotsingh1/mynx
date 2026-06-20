// TODO! non AI-fy this code
#include "Vcsrfile.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>
#include <iomanip>
#include <cstdint>

// CSR Address definitions (from defs.vh)
#define CSR_MSTATUS   0x300
#define CSR_MEPC      0x341
#define CSR_MTVEC     0x305
#define CSR_SATP      0x180
#define CSR_MCAUSE    0x342
#define CSR_BOGUS     0xFFF // Invalid address to test default mapping

int main(int argc, char **argv)
{
  Verilated::commandArgs(argc, argv);
  Vcsrfile *dut = new Vcsrfile;

  Verilated::traceEverOn(true);
  VerilatedVcdC *tfp = new VerilatedVcdC;

  dut->trace(tfp, 99); 
  tfp->open("vcd/csrfile_trace.vcd");

  int time = 0;
  int fails = 0;

  // IMPORTANT: csrfile.v uses `always @(negedge clk)` for writes!
  // We tick starting high, then transition low to trigger the write.
  auto tick = [&]() {
    dut->clk = 1;
    dut->eval();
    tfp->dump(time++);
    
    dut->clk = 0;
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

  std::cout << "====== Starting CSR File Tests ======\n";

  // --- TEST 0: Reset Behavior ---
  dut->clk = 0;
  dut->rst = 1;
  dut->write_en = 0;
  dut->write_csr = 0;
  dut->write_data = 0;
  dut->read_csr = CSR_MSTATUS;
  tick(); // Negedge triggers the reset loop
  
  dut->rst = 0;
  dut->eval();
  run_test(dut->read_data, 0x0ULL, "Reset clears CSR (MSTATUS)");

  // --- TEST 1: Basic Write & Read (MEPC) ---
  dut->write_en = 1;
  dut->write_csr = CSR_MEPC;
  dut->write_data = 0x80000000DEADBEEFULL;
  tick(); // Data latched on negedge
  dut->write_en = 0;

  dut->read_csr = CSR_MEPC;
  dut->eval(); // Combinational read
  run_test(dut->read_data, 0x80000000DEADBEEFULL, "Basic Write/Read (MEPC)");

  // --- TEST 2: Write Enable Low (No-op check) ---
  dut->write_en = 0;
  dut->write_csr = CSR_MEPC;
  dut->write_data = 0x0ULL; // Attempt to overwrite with 0s
  tick();

  dut->read_csr = CSR_MEPC;
  dut->eval();
  run_test(dut->read_data, 0x80000000DEADBEEFULL, "Write Enable Low prevents overwrite");

  // --- TEST 3: Independent CSRs ---
  dut->write_en = 1;
  dut->write_csr = CSR_MTVEC;
  dut->write_data = 0x1122334455667788ULL;
  tick();
  dut->write_en = 0;

  // Verify MTVEC wrote successfully
  dut->read_csr = CSR_MTVEC;
  dut->eval();
  run_test(dut->read_data, 0x1122334455667788ULL, "Independent Write (MTVEC)");

  // Verify MEPC wasn't clobbered by the MTVEC write
  dut->read_csr = CSR_MEPC;
  dut->eval();
  run_test(dut->read_data, 0x80000000DEADBEEFULL, "Previous CSR (MEPC) remains unchanged");

  // --- TEST 4: Default Mapping Behavior (csrmap.v boundary check) ---
  // csrmap.v has a fallback: `default: csrmap = CSRMAP_MSTATUS`
  // We test if a completely unrecognized CSR address safely maps to MSTATUS.
  dut->write_en = 1;
  dut->write_csr = CSR_BOGUS; // 0xFFF
  dut->write_data = 0x9999999999999999ULL;
  tick();
  dut->write_en = 0;

  // Read from MSTATUS to see if the write landed there
  dut->read_csr = CSR_MSTATUS;
  dut->eval();
  run_test(dut->read_data, 0x9999999999999999ULL, "Invalid CSR Write falls back to MSTATUS map");

  // Read from the Bogus CSR address to verify read routing also falls back to MSTATUS
  dut->read_csr = CSR_BOGUS;
  dut->eval();
  run_test(dut->read_data, 0x9999999999999999ULL, "Invalid CSR Read falls back to MSTATUS map");

  // --- Cleanup ---
  tick();
  tfp->dump(time++);
  tfp->close();

  delete dut;
  delete tfp;

  std::cout << "========================================\n";
  if (fails == 0)
  {
    std::cout << "SUCCESS: All CSR tests passed!\n";
    return 0;
  }
  else
  {
    std::cerr << "FAILURE: " << fails << " tests failed.\n";
    return -1;
  }
}