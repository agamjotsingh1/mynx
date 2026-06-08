#include "Valu_ctl.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>
#include <cstdint>

#define ALU_OP_ADD  0x0
#define ALU_OP_SUB  0x1
#define ALU_OP_XOR  0x2
#define ALU_OP_OR   0x3
#define ALU_OP_AND  0x4
#define ALU_OP_SLL  0x5
#define ALU_OP_SRL  0x6
#define ALU_OP_SRA  0x7
#define ALU_OP_SLT  0x8
#define ALU_OP_SLTU 0x9

#define OP_R_TYPE 0x33
#define OP_I_TYPE 0x13
#define OP_LOAD   0x03
#define OP_STORE  0x23

uint32_t make_instr(uint32_t opcode, uint32_t funct3, uint32_t funct7) {
    return (funct7 << 25) | (funct3 << 12) | opcode;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Valu_ctl* dut = new Valu_ctl;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("vcd/alu_ctl_trace.vcd");

    int time = 0;
    int fails = 0;

    auto run_test = [&](uint32_t instr, uint8_t expected, const char* name) {
        dut->instr = instr;
        dut->eval();
        
        tfp->dump(time++);

        if (dut->alu_op != expected) {
            std::cerr << "[FAILED] " << name 
                      << "\n         Expected: 0x" << std::hex << (int)expected 
                      << "\n         Got:      0x" << (int)dut->alu_op << std::dec << "\n";
            fails++;
        } else {
            std::cout << "[PASSED] " << name << "\n";
        }
    };

    std::cout << "====== Starting ALU Control Tests ======\n";

    // R-Type Instructions
    run_test(make_instr(OP_R_TYPE, 0x0, 0x00), ALU_OP_ADD,  "ADD");
    run_test(make_instr(OP_R_TYPE, 0x0, 0x20), ALU_OP_SUB,  "SUB");
    run_test(make_instr(OP_R_TYPE, 0x1, 0x00), ALU_OP_SLL,  "SLL");
    run_test(make_instr(OP_R_TYPE, 0x2, 0x00), ALU_OP_SLT,  "SLT");
    run_test(make_instr(OP_R_TYPE, 0x3, 0x00), ALU_OP_SLTU, "SLTU");
    run_test(make_instr(OP_R_TYPE, 0x4, 0x00), ALU_OP_XOR,  "XOR");
    run_test(make_instr(OP_R_TYPE, 0x5, 0x00), ALU_OP_SRL,  "SRL");
    run_test(make_instr(OP_R_TYPE, 0x5, 0x20), ALU_OP_SRA,  "SRA");
    run_test(make_instr(OP_R_TYPE, 0x6, 0x00), ALU_OP_OR,   "OR");
    run_test(make_instr(OP_R_TYPE, 0x7, 0x00), ALU_OP_AND,  "AND");

    // I-Type Arithmetic Instructions
    run_test(make_instr(OP_I_TYPE, 0x0, 0x00), ALU_OP_ADD,  "ADDI (Positive Imm)");
    run_test(make_instr(OP_I_TYPE, 0x0, 0x7F), ALU_OP_ADD,  "ADDI (Negative Imm)");
    run_test(make_instr(OP_I_TYPE, 0x2, 0x00), ALU_OP_SLT,  "SLTI");
    run_test(make_instr(OP_I_TYPE, 0x3, 0x00), ALU_OP_SLTU, "SLTIU");
    run_test(make_instr(OP_I_TYPE, 0x4, 0x00), ALU_OP_XOR,  "XORI");
    run_test(make_instr(OP_I_TYPE, 0x6, 0x00), ALU_OP_OR,   "ORI");
    run_test(make_instr(OP_I_TYPE, 0x7, 0x00), ALU_OP_AND,  "ANDI");
    
    // Wonky Shift Immediates
    run_test(make_instr(OP_I_TYPE, 0x1, 0x00), ALU_OP_SLL,  "SLLI");
    run_test(make_instr(OP_I_TYPE, 0x5, 0x00), ALU_OP_SRL,  "SRLI");
    run_test(make_instr(OP_I_TYPE, 0x5, 0x20), ALU_OP_SRA,  "SRAI");

    // Memory Instructions (Address calculation)
    run_test(make_instr(OP_LOAD,  0x0, 0x00), ALU_OP_ADD, "LB  (Load Byte)");
    run_test(make_instr(OP_LOAD,  0x2, 0x00), ALU_OP_ADD, "LW  (Load Word)");
    run_test(make_instr(OP_LOAD,  0x4, 0x00), ALU_OP_ADD, "LBU (Load Byte Unsigned)");
    run_test(make_instr(OP_STORE, 0x0, 0x00), ALU_OP_ADD, "SB  (Store Byte)");
    run_test(make_instr(OP_STORE, 0x2, 0x00), ALU_OP_ADD, "SW  (Store Word)");

    // Unknown Instruction
    run_test(make_instr(0x7F, 0x7, 0x7F), ALU_OP_ADD, "Default Case (Garbage Instruction)");

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