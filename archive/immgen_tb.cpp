#include "Vimmgen.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>
#include <cstdint>
#include <iomanip>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vimmgen* dut = new Vimmgen;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("vcd/immgen_trace.vcd");

    int time = 0;
    int fails = 0;

    auto run_test = [&](uint32_t instr, uint64_t expected, const char* name) {
        dut->instr = instr;
        dut->eval();
        
        tfp->dump(time++);

        if (dut->imm != expected) {
            std::cerr << "[FAILED] " << name 
                      << "\n         Instr:     0x" << std::hex << std::setw(8) << std::setfill('0') << instr
                      << "\n         Expected: 0x" << std::setw(16) << expected 
                      << "\n         Got:      0x" << std::setw(16) << dut->imm << std::dec << "\n";
            fails++;
        } else {
            std::cout << "[PASSED] " << name << "\n";
        }
    };

    std::cout << "====== Starting ImmGen Tests ======\n";

    // R-Type (Should output 0)
    // add x1, x2, x3
    run_test(0x003100B3, 0x0000000000000000ULL, "R-Type (ADD)");

    // I-Type 
    // addi x1, x0, 2047 (Max Positive)
    run_test(0x7FF00093, 0x00000000000007FFULL, "I-Type (Max Positive)");
    // addi x1, x0, -2048 (Max Negative)
    run_test(0x80000093, 0xFFFFFFFFFFFFF800ULL, "I-Type (Max Negative)");

    // S-Type
    // sw x2, 2047(x1) (Max Positive)
    run_test(0x7E20AFA3, 0x00000000000007FFULL, "S-Type (Max Positive)");
    // sw x2, -2048(x1) (Max Negative)
    run_test(0x8020A023, 0xFFFFFFFFFFFFF800ULL, "S-Type (Max Negative)");

    // B-Type
    // beq x1, x2, 4094 (Max Positive Forward Branch)
    run_test(0x7E208FE3, 0x0000000000000FFEULL, "B-Type (Max Positive)");
    // beq x1, x2, -4096 (Max Negative Backward Branch)
    run_test(0x80208063, 0xFFFFFFFFFFFFF000ULL, "B-Type (Max Negative)");

    // U-Type
    // lui x1, 0x12345 (Positive Upper)
    run_test(0x123450B7, 0x0000000012345000ULL, "U-Type (Positive)");
    // lui x1, 0x87654 (Negative Upper - MSB is 1)
    run_test(0x876540B7, 0xFFFFFFFF87654000ULL, "U-Type (Negative/Sign Extended)");

    // J-Type
    // jal x1, 1048574 (Max Positive Forward Jump)
    run_test(0x7FFFF0EF, 0x00000000000FFFFEULL, "J-Type (Max Positive)");
    // jal x1, -1048576 (Max Negative Backward Jump)
    run_test(0x800000EF, 0xFFFFFFFFFFF00000ULL, "J-Type (Max Negative)");

    // J-Type Mixed Bits (Specifically tests for correct J-Type bit ordering)
    // jal x1, 703696 -> imm = 0x0ABCD0
    run_test(0x4d1ab0ef, 0x00000000000ABCD0ULL, "J-Type (Mixed Bit Ordering)");

    // Flush and close
    dut->eval();
    tfp->dump(time++);
    tfp->close();
    
    delete dut;
    delete tfp;

    std::cout << "========================================\n";
    if (fails == 0) {
        std::cout << "SUCCESS: All tests passed!\n";
        return 0;
    } else {
        std::cerr << "FAILURE: " << fails << " tests failed.\n";
        return -1;
    }
}