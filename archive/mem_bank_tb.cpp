#include "Vmem_bank.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>
#include <cstdint>

int main(int argc, char **argv)
{
  Verilated::commandArgs(argc, argv);
  Vmem_bank *dut = new Vmem_bank;

  Verilated::traceEverOn(true);
  VerilatedVcdC *tfp = new VerilatedVcdC;

  dut->trace(tfp, 99); // trace 99 levels deep
  tfp->open("vcd/mem_bank_trace.vcd");

  int time = 0;
  int fails = 0;

  // simulates one full clock cycle
  auto tick = [&]() {
    dut->clk = 0;
    dut->eval();
    tfp->dump(time++);
    
    dut->clk = 1;
    dut->eval();
    tfp->dump(time++);
  };

  auto run_test = [&](uint32_t got, uint32_t expected, const char *name)
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

  std::cout << "====== Starting 8-bit Memory Bank Tests ======\n";

  dut->clk = 0;
  dut->addr_a = 0; dut->mem_read_a = 0; dut->mem_write_a = 0; dut->data_in_a = 0;
  dut->addr_b = 0; dut->mem_read_b = 0; dut->mem_write_b = 0; dut->data_in_b = 0;
  tick();

  // standard write to Port A
  dut->mem_write_a = 1;
  dut->addr_a = 0x10;
  dut->data_in_a = 0xAB;
  tick(); 
  dut->mem_write_a = 0; 

  // combinational read from Port A
  dut->addr_a = 0x10;
  dut->mem_read_a = 1;
  dut->eval(); 
  run_test(dut->data_out_a, 0xAB, "Port A Write & Combinational Read");
  dut->mem_read_a = 0;

  // standard write to Port B
  dut->mem_write_b = 1;
  dut->addr_b = 0x20;
  dut->data_in_b = 0xCD;
  tick();
  dut->mem_write_b = 0;

  // read B's write from Port A
  dut->addr_a = 0x20;
  dut->mem_read_a = 1;
  dut->eval();
  run_test(dut->data_out_a, 0xCD, "Cross-Port Read (A reads B's write)");
  dut->mem_read_a = 0;

  // simultaneous Dual Write (different addresses)
  dut->mem_write_a = 1; dut->addr_a = 0x01; dut->data_in_a = 0x11;
  dut->mem_write_b = 1; dut->addr_b = 0x02; dut->data_in_b = 0x22; 
  tick();
  dut->mem_write_a = 0; 
  dut->mem_write_b = 0;

  // verify both writes simultaneously
  dut->addr_a = 0x01; dut->mem_read_a = 1;
  dut->addr_b = 0x02; dut->mem_read_b = 1;
  dut->eval();
  run_test(dut->data_out_a, 0x11, "Simultaneous Dual Read (Port A)");
  run_test(dut->data_out_b, 0x22, "Simultaneous Dual Read (Port B)");
  dut->mem_read_a = 0; 
  dut->mem_read_b = 0;

  // read enable check
  dut->addr_a = 0x01;
  dut->mem_read_a = 0; 
  dut->eval();
  run_test(dut->data_out_a, 0x00, "Output is 0 when mem_read is low");

  tick();
  tfp->dump(time++);
  tfp->close();

  delete dut;
  delete tfp;

  std::cout << "========================================\n";
  if (fails == 0)
  {
    std::cout << "SUCCESS: All memory bank tests passed!\n";
    return 0;
  }
  else
  {
    std::cerr << "FAILURE: " << fails << " tests failed.\n";
    return -1;
  }
}