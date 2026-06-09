#include "Vmem.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>
#include <cstdint>

// Re-defining the bandwidth macros for the testbench
#define BW_BYTE     0x0
#define BW_HALFWORD 0x1
#define BW_WORD     0x2
#define BW_DBLWORD  0x3

int main(int argc, char **argv)
{
  Verilated::commandArgs(argc, argv);
  Vmem *dut = new Vmem;

  Verilated::traceEverOn(true);
  VerilatedVcdC *tfp = new VerilatedVcdC;

  dut->trace(tfp, 99); 
  tfp->open("vcd/mem_trace.vcd");

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

  std::cout << "====== Starting Main Memory Controller Tests ======\n";

  dut->clk = 0;
  dut->addr_a = 0; dut->mem_read_a = 0; dut->mem_write_a = 0; dut->bw_a = 0; dut->data_in_a = 0; dut->sign_extend_a = 0;
  dut->addr_b = 0; dut->mem_read_b = 0; dut->mem_write_b = 0; dut->bw_b = 0; dut->data_in_b = 0; dut->sign_extend_b = 0;
  tick();

  // aligned doubleword write & read
  dut->mem_write_a = 1;
  dut->bw_a = BW_DBLWORD;
  dut->addr_a = 0x00;
  dut->data_in_a = 0x1122334455667788ULL;
  tick();
  dut->mem_write_a = 0;

  dut->mem_read_a = 1;
  dut->eval();
  run_test(dut->data_out_a, 0x1122334455667788ULL, "Aligned Doubleword Write/Read");
  dut->mem_read_a = 0;

  // write halfword from middle of doubleword
  // double word at 0x00 is 11 22 33 44 55 66 77 88
  dut->mem_write_a = 1;
  dut->bw_a = BW_HALFWORD;
  dut->addr_a = 0x02; // write to 3rd and 4th byte
  dut->data_in_a = 0xAAAAULL;
  tick();
  dut->mem_write_a = 0;

  dut->mem_read_a = 1;
  dut->addr_a = 0x02;
  dut->bw_a = BW_HALFWORD;
  dut->sign_extend_a = 0;
  dut->eval();
  run_test(dut->data_out_a, 0x000000000000AAAAULL, "Aligned Halfword Write/Read (Zero Extended)");
  dut->mem_read_a = 0;

  // --- TEST 3: Unaligned Spillover Test (The Hard One) ---
  // A word is 4 bytes. Writing to 0x06 (Bank 6) means it must write to:
  // Bank 6, Bank 7, Bank 0 (next addr), Bank 1 (next addr).
  dut->mem_write_a = 1;
  dut->bw_a = BW_WORD;
  dut->addr_a = 0x06; 
  dut->data_in_a = 0xDEADBEEFULL;
  tick();
  dut->mem_write_a = 0;

  dut->mem_read_a = 1;
  dut->addr_a = 0x06;
  dut->eval();
  run_test(dut->data_out_a, 0x00000000DEADBEEFULL, "Unaligned Word Cross-Boundary Spillover Write/Read");
  dut->mem_read_a = 0;

  // --- TEST 4: Sign Extension Logic ---
  dut->mem_write_a = 1;
  dut->bw_a = BW_BYTE;
  dut->addr_a = 0x10;
  dut->data_in_a = 0xF0ULL; // MSB is 1 (Negative in 2's complement)
  tick();
  dut->mem_write_a = 0;

  // Read Zero Extended
  dut->mem_read_a = 1;
  dut->sign_extend_a = 0;
  dut->eval();
  run_test(dut->data_out_a, 0x00000000000000F0ULL, "Byte Read (Zero Extended)");

  // Read Sign Extended
  dut->sign_extend_a = 1;
  dut->eval();
  run_test(dut->data_out_a, 0xFFFFFFFFFFFFFFF0ULL, "Byte Read (Sign Extended)");
  dut->mem_read_a = 0;

  // port b independence 
  dut->mem_write_b = 1;
  dut->bw_b = BW_BYTE;
  dut->addr_b = 0x10;
  dut->data_in_b = 0x42ULL; 
  tick();
  dut->mem_write_b = 0;

  // verify port a sees port b's write
  dut->mem_read_a = 1;
  dut->addr_a = 0x10;
  dut->sign_extend_a = 0;
  dut->eval();
  run_test(dut->data_out_a, 0x0000000000000042ULL, "Port A reads Port B's Byte Write");
  dut->mem_read_a = 0;

  // writing a 64-bit value to an address ending in 0x07 means 1 byte lands in bank 7,
  // and the remaining 7 bytes spill over into banks 0-6 of the next doubleword address.
  dut->mem_write_a = 1;
  dut->bw_a = BW_DBLWORD;
  dut->addr_a = 0x07;
  dut->data_in_a = 0x1122334455667788ULL;
  tick();
  dut->mem_write_a = 0;

  dut->mem_read_a = 1;
  dut->addr_a = 0x07;
  dut->bw_a = BW_DBLWORD;
  dut->eval();
  run_test(dut->data_out_a, 0x1122334455667788ULL, "Extreme Unaligned Doubleword Read (Offset 7)");
  dut->mem_read_a = 0;

  // write a full block of 1s, then overwrite a single byte in the middle to 0s.
  dut->mem_write_a = 1; dut->bw_a = BW_DBLWORD; dut->addr_a = 0x20; dut->data_in_a = 0xFFFFFFFFFFFFFFFFULL;
  tick();
  dut->bw_a = BW_BYTE; dut->addr_a = 0x23; dut->data_in_a = 0x00ULL; // Overwrite 4th byte
  tick();
  dut->mem_write_a = 0;

  dut->mem_read_a = 1; dut->bw_a = BW_DBLWORD; dut->addr_a = 0x20; dut->eval();
  run_test(dut->data_out_a, 0xFFFFFFFF00FFFFFFULL, "Byte Overwrite Inside Doubleword");
  dut->mem_read_a = 0;

  // port a writes the lower word, port b writes the upper word of the same doubleword block.
  dut->mem_write_a = 1; dut->bw_a = BW_WORD; dut->addr_a = 0x30; dut->data_in_a = 0xAAAAAAAAULL;
  dut->mem_write_b = 1; dut->bw_b = BW_WORD; dut->addr_b = 0x34; dut->data_in_b = 0xBBBBBBBBULL;
  tick();
  dut->mem_write_a = 0; dut->mem_write_b = 0;

  dut->mem_read_a = 1; dut->bw_a = BW_DBLWORD; dut->addr_a = 0x30; dut->eval();
  run_test(dut->data_out_a, 0xBBBBBBBBAAAAAAAAULL, "Simultaneous Adjacent Word Writes (Merged to DBLWORD)");
  dut->mem_read_a = 0;

  // sign extension - max negative byte
  dut->mem_write_a = 1; dut->bw_a = BW_BYTE; dut->addr_a = 0x40; dut->data_in_a = 0x80ULL; // 10000000
  tick();
  dut->mem_write_a = 0;
  
  dut->mem_read_a = 1; dut->bw_a = BW_BYTE; dut->addr_a = 0x40; dut->sign_extend_a = 1; dut->eval();
  run_test(dut->data_out_a, 0xFFFFFFFFFFFFFF80ULL, "Sign Extend Max Negative Byte (0x80)");

  // sign extension - max positive byte
  dut->mem_write_a = 1; dut->bw_a = BW_BYTE; dut->addr_a = 0x41; dut->data_in_a = 0x7FULL; // 01111111
  tick();
  dut->mem_write_a = 0;

  dut->mem_read_a = 1; dut->bw_a = BW_BYTE; dut->addr_a = 0x41; dut->sign_extend_a = 1; dut->eval();
  run_test(dut->data_out_a, 0x000000000000007FULL, "Sign Extend Max Positive Byte (0x7F - Stays Positive)");
  dut->mem_read_a = 0;

  // starts at bank 7, spills over to bank 0 of the next word.
  dut->mem_write_a = 1; dut->bw_a = BW_HALFWORD; dut->addr_a = 0x0F; dut->data_in_a = 0xBEEFULL;
  tick();
  dut->mem_write_a = 0;

  dut->mem_read_a = 1; dut->bw_a = BW_HALFWORD; dut->addr_a = 0x0F; dut->sign_extend_a = 0; dut->eval();
  run_test(dut->data_out_a, 0x000000000000BEEFULL, "Unaligned Halfword Spillover");
  dut->mem_read_a = 0;

  // ensure the output is strictly 0 when mem_read is low, even if valid data exists.
  dut->mem_read_a = 0; dut->bw_a = BW_DBLWORD; dut->addr_a = 0x30; dut->eval();
  run_test(dut->data_out_a, 0x0000000000000000ULL, "Read Enable Low forces output to 0");

  // write a patterned dblword, then extract an unaligned word from the middle to verify right-shift logic.
  dut->mem_write_a = 1; dut->bw_a = BW_DBLWORD; dut->addr_a = 0x50; dut->data_in_a = 0x1122334455667788ULL;
  tick();
  dut->mem_write_a = 0;

  dut->mem_read_a = 1; dut->bw_a = BW_WORD; dut->addr_a = 0x53; dut->sign_extend_a = 0; dut->eval();
  run_test(dut->data_out_a, 0x0000000022334455ULL, "Checkerboard Shift Extraction (Read unaligned Word)");
  dut->mem_read_a = 0;

  // depth is 1024 doublewords. max address is (1024 * 8) - 8 = 8184 = 0x1ff8.
  dut->mem_write_a = 1; dut->bw_a = BW_DBLWORD; dut->addr_a = 0x1FF8; dut->data_in_a = 0x9999888877776666ULL;
  tick();
  dut->mem_write_a = 0;

  dut->mem_read_a = 1; dut->bw_a = BW_DBLWORD; dut->addr_a = 0x1FF8; dut->eval();
  run_test(dut->data_out_a, 0x9999888877776666ULL, "Highest Memory Address Boundary Write/Read");
  dut->mem_read_a = 0;

  // ensure that asking to sign-extend a dblword (which already takes up the whole 64-bit wire) doesn't corrupt it.
  dut->mem_write_a = 1; dut->bw_a = BW_DBLWORD; dut->addr_a = 0x60; dut->data_in_a = 0x8000000000000000ULL;
  tick();
  dut->mem_write_a = 0;

  dut->mem_read_a = 1; dut->bw_a = BW_DBLWORD; dut->addr_a = 0x60; dut->sign_extend_a = 1; dut->eval();
  run_test(dut->data_out_a, 0x8000000000000000ULL, "Sign-Extend a full Doubleword");
  dut->mem_read_a = 0;

  tick();
  tfp->dump(time++);
  tfp->close();

  delete dut;
  delete tfp;

  std::cout << "========================================\n";
  if (fails == 0)
  {
    std::cout << "SUCCESS: All main memory tests passed!\n";
    return 0;
  }
  else
  {
    std::cerr << "FAILURE: " << fails << " tests failed.\n";
    return -1;
  }
}