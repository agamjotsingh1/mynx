#include "Vregfile.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>
#include <cstdint>

// simulates one full clock cycle
// drops the clock, evaluates, raises the clock, evaluates, and dumps waveforms
void tick(Vregfile *dut, VerilatedVcdC *tfp, int &time)
{
  dut->clk = 0;
  dut->eval();
  tfp->dump(time++);

  dut->clk = 1;
  dut->eval();
  tfp->dump(time++);
}

int main(int argc, char **argv)
{
  Verilated::commandArgs(argc, argv);
  Vregfile *dut = new Vregfile;

  Verilated::traceEverOn(true);
  VerilatedVcdC *tfp = new VerilatedVcdC;

	dut->trace(tfp, 99); // trace 99 levels deep
  tfp->open("vcd/regfile_trace.vcd");

  int time = 0;
  int fails = 0;

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

  std::cout << "====== Starting Regfile Tests ======\n";

  // System Reset
  dut->rst = 1;
  dut->write_en = 0;
  tick(dut, tfp, time);

  dut->rst = 0;
  tick(dut, tfp, time);

  // read an arbitrary reg to ensure it cleared to 0
  dut->read_addr1 = 5;
  dut->eval(); // combinational read, no clock tick needed
  run_test(dut->read_data1, 0, "Reset clears registers to 0");

  // Standard Write and Read
  dut->write_en = 1;
  dut->write_addr = 10;
  dut->write_data = 0xDEADBEEF12345678ULL;
  tick(dut, tfp, time); // data is saved on this clock edge
  dut->write_en = 0;    // turn off write enable

  dut->read_addr1 = 10;
  dut->eval();
  run_test(dut->read_data1, 0xDEADBEEF12345678ULL, "Write and Read register x10");

  // The x0 Zero-Register Constraint
  dut->write_en = 1;
  dut->write_addr = 0;
  dut->write_data = 0xFFFFFFFFFFFFFFFFULL;
  tick(dut, tfp, time); // attempt to write to x0
  dut->write_en = 0;

  dut->read_addr1 = 0;
  dut->eval();
  run_test(dut->read_data1, 0, "Register x0 remains 0 after write attempt");

  // Write Enable Safety Check
  dut->write_en = 0; // try to write without setting write_en = 1
  dut->write_addr = 15;
  dut->write_data = 0xCAFEBABEULL;
  tick(dut, tfp, time);

  dut->read_addr1 = 15;
  dut->eval();
  run_test(dut->read_data1, 0, "Register ignores write when write_en = 0");

  // Simultaneous Dual-Port Reading
  dut->write_en = 1;
  dut->write_addr = 11;
  dut->write_data = 0x1111111111111111ULL;
  tick(dut, tfp, time);
  dut->write_en = 0;

  // read x10 and x11 at the exact same time
  dut->read_addr1 = 10;
  dut->read_addr2 = 11;
  dut->eval();

  run_test(dut->read_data1, 0xDEADBEEF12345678ULL, "Dual Read Port 1 (x10)");
  run_test(dut->read_data2, 0x1111111111111111ULL, "Dual Read Port 2 (x11)");

  // Flush and close waveforms
  tick(dut, tfp, time);
  tfp->dump(time++);
  tfp->close();

  delete dut;
  delete tfp;

  std::cout << "====================================\n";
  if (fails == 0)
  {
    std::cout << "SUCCESS: All tests passed!\n";
    return 0;
  }
  else
  {
    std::cerr << "FAILURE: " << fails << " tests failed.\n";
    return -1;
  }
}