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

    // RISC-V standard ABI names mapping
    const char* abi[] = {
        "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
        "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
        "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
        "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
    };

    for (int i = 0; i < 32; i++) {
        /*
         * C++ Backdoor into the mangled register file array.
         * Path: core -> id_stage_instance -> regfile_instance -> reg_array
         */
        uint64_t val = dut->core->__PVT__id_stage_instance__DOT__regfile_instance__DOT__reg_array[i];
        
        // Only print registers that changed (plus x0 for a baseline)
        if (val != 0 || i == 0) {
            std::cout << std::setw(4) << i << " (x" << std::setw(2) << std::dec << i << "): 0x" 
                      << std::hex << std::setw(16) << std::setfill('0') << val << "\n";
        }
    }
    std::cout << "==================================\n\n";

   // ==========================================
    // 2. PRINT FINAL MEMORY STATE (GRID DUMP)
    // ==========================================
    std::cout << "\n====== Final Memory State (Smart Hexdump) ======\n";
    std::cout << " Address | 00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F | ASCII\n";
    std::cout << "----------------------------------------------------------------------------\n";

    bool last_was_zero = false;
    for (int mem_base = 0; mem_base < MAX_DEPTH * 8; mem_base += 16) {
        uint8_t line_bytes[16];
        bool line_has_data = false;
        
        // Fetch 16 bytes for the current grid line
        for (int j = 0; j < 16; j++) {
            int addr = mem_base + j;
            int bank_idx = addr % 8;
            int mem_idx = addr / 8;
            uint8_t byte_val = 0;
            
            switch(bank_idx) {
                case 0: byte_val = dut->core->mem_instance->mem_banks__BRA__0__KET____DOT__mem_bank_instance->bank[mem_idx]; break;
                case 1: byte_val = dut->core->mem_instance->mem_banks__BRA__1__KET____DOT__mem_bank_instance->bank[mem_idx]; break;
                case 2: byte_val = dut->core->mem_instance->mem_banks__BRA__2__KET____DOT__mem_bank_instance->bank[mem_idx]; break;
                case 3: byte_val = dut->core->mem_instance->mem_banks__BRA__3__KET____DOT__mem_bank_instance->bank[mem_idx]; break;
                case 4: byte_val = dut->core->mem_instance->mem_banks__BRA__4__KET____DOT__mem_bank_instance->bank[mem_idx]; break;
                case 5: byte_val = dut->core->mem_instance->mem_banks__BRA__5__KET____DOT__mem_bank_instance->bank[mem_idx]; break;
                case 6: byte_val = dut->core->mem_instance->mem_banks__BRA__6__KET____DOT__mem_bank_instance->bank[mem_idx]; break;
                case 7: byte_val = dut->core->mem_instance->mem_banks__BRA__7__KET____DOT__mem_bank_instance->bank[mem_idx]; break;
            }
            line_bytes[j] = byte_val;
            if (byte_val != 0) line_has_data = true;
        }

        // FORCE PRINT the first 128 bytes (8 lines), or any line that contains data
        if (line_has_data || mem_base < 128) {
            std::cout << "  0x" << std::hex << std::setw(4) << std::setfill('0') << mem_base << " | ";
            
            for (int j = 0; j < 16; j++) {
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)line_bytes[j] << " ";
                if (j == 7) std::cout << " "; // Visual divider
            }
            std::cout << "| ";
            
            for (int j = 0; j < 16; j++) {
                char c = (line_bytes[j] >= 32 && line_bytes[j] <= 126) ? (char)line_bytes[j] : '.';
                std::cout << c;
            }
            std::cout << "\n";
            last_was_zero = false;
        } else {
            if (!last_was_zero) {
                std::cout << "    * |\n";
                last_was_zero = true;
            }
        }
    }
    std::cout << "============================================================================\n\n";
    // 6. Cleanup
    dut->eval();
    tfp->dump(time++);
    tfp->close();
    
    delete dut;
    delete tfp;

    std::cout << "SUCCESS: Execution simulation finished. Check vcd/core_trace.vcd.\n";
    return 0;
}