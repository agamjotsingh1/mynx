// WARNING: legacy test, is not complete
#include "Valu.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>
#include <cstdint>

#define ALU_OP_ADD 0x0
#define ALU_OP_SUB 0x1
#define ALU_OP_XOR 0x2
#define ALU_OP_OR 0x3
#define ALU_OP_AND 0x4
#define ALU_OP_SLL 0x5
#define ALU_OP_SRL 0x6
#define ALU_OP_SRA 0x7
#define ALU_OP_SLT 0x8
#define ALU_OP_SLTU 0x9

uint64_t correct_alu(uint8_t op, uint64_t in1, uint64_t in2)
{
	switch (op)
	{
	case ALU_OP_ADD:
		return in1 + in2;
	case ALU_OP_SUB:
		return in1 - in2;
	case ALU_OP_XOR:
		return in1 ^ in2;
	case ALU_OP_OR:
		return in1 | in2;
	case ALU_OP_AND:
		return in1 & in2;
	case ALU_OP_SLL:
		return in1 << in2;
	case ALU_OP_SRL:
		return in1 >> in2;
	case ALU_OP_SRA:
		return (uint64_t)(((int64_t)in1) >> in2);
	case ALU_OP_SLT:
		return ((int64_t)in1 < (int64_t)in2) ? 1 : 0;
	case ALU_OP_SLTU:
		return (in1 < in2) ? 1 : 0;
	default:
		return 0;
	}
}

int main(int argc, char **argv)
{
	Verilated::commandArgs(argc, argv);
	Valu *dut = new Valu;

	// waveform tracing
	Verilated::traceEverOn(true);
	VerilatedVcdC *tfp = new VerilatedVcdC;

	dut->trace(tfp, 99); // trace 99 levels deep
	tfp->open("vcd/alu_trace.vcd");

	int time = 0;
	int fails = 0;

	auto run_test = [&](uint8_t alu_op, uint64_t in1, uint64_t in2, const char *name)
	{
		dut->alu_op = alu_op;
		dut->in1 = in1;
		dut->in2 = in2;
		dut->eval();

		tfp->dump(time++);

		uint64_t expected = correct_alu(alu_op, in1, in2);

		if (dut->out != expected)
		{
			std::cerr << "[FAILED] " << name
								<< "\n         Expected: 0x" << std::hex << expected
								<< "\n         Got:      0x" << dut->out << std::dec << "\n";
			fails++;
		}
		else
		{
			std::cout << "[PASSED] " << name << "\n";
		}
	};

	std::cout << "====== Starting ALU Tests ======\n";

	// Basic Arithmetic
	run_test(ALU_OP_ADD, 10, 15, "ADD: 10 + 15");
	run_test(ALU_OP_SUB, 20, 5, "SUB: 20 - 5");
	run_test(ALU_OP_ADD, 0xFFFFFFFFFFFFFFFFULL, 1, "ADD: Overflow (-1 + 1)");
	run_test(ALU_OP_SUB, 0, 1, "SUB: Underflow (0 - 1)");

	// Bitwise Logic
	run_test(ALU_OP_XOR, 0xFF, 0x0F, "XOR: 0xFF ^ 0x0F");
	run_test(ALU_OP_OR, 0xF0, 0x0F, "OR:  0xF0 | 0x0F");
	run_test(ALU_OP_AND, 0xFF, 0x0F, "AND: 0xFF & 0x0F");
	run_test(ALU_OP_XOR, 0xAAAAAAAAAAAAAAAAULL, 0x5555555555555555ULL, "XOR: Alternating Bits");
	run_test(ALU_OP_AND, 0xAAAAAAAAAAAAAAAAULL, 0x5555555555555555ULL, "AND: Mutually Exclusive Bits");

	// Shifts (Standard)
	run_test(ALU_OP_SLL, 0x1, 4, "SLL: 1 << 4");
	run_test(ALU_OP_SRL, 0x10, 4, "SRL: 0x10 >> 4");

	// Shifts (Edge Cases)
	run_test(ALU_OP_SLL, 0xFFFFFFFFFFFFFFFFULL, 63, "SLL: Max shift left");
	run_test(ALU_OP_SRL, 0xFFFFFFFFFFFFFFFFULL, 63, "SRL: Max shift right");
	run_test(ALU_OP_SLL, 0x1, 64, "SLL: Over-shift (masked to 0)");

	// SRA
	run_test(ALU_OP_SRA, 0x8000000000000000ULL, 4, "SRA: Sign Extension (Negative)");
	run_test(ALU_OP_SRA, 0x4000000000000000ULL, 4, "SRA: Zero Extension (Positive)");
	run_test(ALU_OP_SRA, 0xFFFFFFFFFFFFFFFFULL, 63, "SRA: All 1s (Negative 1)");

	// Comparisons
	run_test(ALU_OP_SLT, 0xFFFFFFFFFFFFFFFFULL, 5, "SLT:  -1 < 5 (Signed)");
	run_test(ALU_OP_SLTU, 0xFFFFFFFFFFFFFFFFULL, 5, "SLTU: MAX < 5 (Unsigned)");
	run_test(ALU_OP_SLT, 5, 0xFFFFFFFFFFFFFFFFULL, "SLT:  5 < -1 (Signed)");
	run_test(ALU_OP_SLTU, 5, 0xFFFFFFFFFFFFFFFFULL, "SLTU: 5 < MAX (Unsigned)");

	// Equal values
	run_test(ALU_OP_SLT, 42, 42, "SLT:  42 < 42");
	run_test(ALU_OP_SLTU, 42, 42, "SLTU: 42 < 42");

	// flush and close the waveform
	dut->eval();
	tfp->dump(time++);
	tfp->close();

	delete dut;
	delete tfp;

	std::cout << "================================\n";
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