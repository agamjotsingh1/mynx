#include "Vcore.h"
#include "Vcore_core.h"      // The top-level module wrapper
#include "Vcore_mem.h"       // Generated for the mem module
#include "Vcore_mem_bank.h"  // Generated for the mem_bank module
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <iomanip>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vcore* dut = new Vcore;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("vcd/core_trace.vcd");

    int time = 0;
    auto tick = [&]() {
        dut->clk = 0;
        dut->eval();
        tfp->dump(time++);
        
        dut->clk = 1;
        dut->eval();
        tfp->dump(time++);
    };

    std::cout << "====== Starting Core Execution Tests ======\n";

    // 1. Determine Hex File
    std::string hex_file = "program.hex";
    if (argc > 1) {
        hex_file = argv[1];
    }

    // 2. Read the Hex File
    std::vector<uint32_t> instructions;
    std::ifstream infile(hex_file);
    if (!infile.is_open()) {
        std::cerr << "[ERROR] Could not open hex file: " << hex_file << "\n";
        std::cerr << "        Usage: ./Vcore [path_to_hex_file.hex]\n";
        return 1;
    }

    std::string line;
    while (std::getline(infile, line)) {
        line.erase(line.find_last_not_of(" \n\r\t") + 1);
        if (line.empty() || line[0] == '/' || line[0] == '#') continue;

        try {
            uint32_t instr = std::stoul(line, nullptr, 16);
            instructions.push_back(instr);
        } catch (...) {
            std::cerr << "[WARNING] Skipping invalid hex line: " << line << "\n";
        }
    }
    infile.close();

    // 3. System Reset
    dut->rst = 1;
    tick();
    dut->rst = 0;

    // 4. Backdoor Memory Loading using exact C++ Object Hierarchy
    std::cout << "Loading " << instructions.size() << " instructions from " << hex_file << " into memory...\n";
    const uint32_t MAX_DEPTH = 1024; 

    for (size_t i = 0; i < instructions.size(); i++) {
        uint32_t instr = instructions[i];
        
        for (int b = 0; b < 4; b++) {
            uint32_t addr = (i * 4) + b;
            uint8_t byte_val = (instr >> (b * 8)) & 0xFF;
            
            uint32_t bank_idx = addr % 8;
            uint32_t mem_idx = addr / 8;

            if (mem_idx >= MAX_DEPTH) {
                std::cerr << "[ERROR] Hex file exceeds memory depth of " << MAX_DEPTH << "\n";
                break;
            }

            /* * THE EXACT C++ PATH BASED ON YOUR HEADERS:
             * dut->core                 : Matches Vcore_core* in Vcore.h
             * ->mem_instance            : The instantiated mem module
             * ->mem_banks__BRA_...      : The mangled generate loop array found in Vcore_mem.h
             * ->bank[mem_idx]           : The public VlUnpacked array found in Vcore_mem_bank.h
             */
            switch(bank_idx) {
                case 0: dut->core->mem_instance->mem_banks__BRA__0__KET____DOT__mem_bank_instance->bank[mem_idx] = byte_val; break;
                case 1: dut->core->mem_instance->mem_banks__BRA__1__KET____DOT__mem_bank_instance->bank[mem_idx] = byte_val; break;
                case 2: dut->core->mem_instance->mem_banks__BRA__2__KET____DOT__mem_bank_instance->bank[mem_idx] = byte_val; break;
                case 3: dut->core->mem_instance->mem_banks__BRA__3__KET____DOT__mem_bank_instance->bank[mem_idx] = byte_val; break;
                case 4: dut->core->mem_instance->mem_banks__BRA__4__KET____DOT__mem_bank_instance->bank[mem_idx] = byte_val; break;
                case 5: dut->core->mem_instance->mem_banks__BRA__5__KET____DOT__mem_bank_instance->bank[mem_idx] = byte_val; break;
                case 6: dut->core->mem_instance->mem_banks__BRA__6__KET____DOT__mem_bank_instance->bank[mem_idx] = byte_val; break;
                case 7: dut->core->mem_instance->mem_banks__BRA__7__KET____DOT__mem_bank_instance->bank[mem_idx] = byte_val; break;
            }
        }
    }

    // 5. Execute Pipeline
    int max_cycles = (instructions.size() * 5) + 50; 
    std::cout << "Executing pipeline for " << max_cycles << " cycles...\n";
    
    for (int cycle = 0; cycle < max_cycles; cycle++) {
        tick();
    }

    // 6. Cleanup
    dut->eval();
    tfp->dump(time++);
    tfp->close();
    
    delete dut;
    delete tfp;

    std::cout << "SUCCESS: Execution simulation finished. Check vcd/core_trace.vcd.\n";
    return 0;
}