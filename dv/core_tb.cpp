#include "Vcore.h"
#include "Vcore_core.h"

// for access of internal mem_banks (display)
#include "Vcore_mmu.h"
#include "Vcore_mem.h"
#include "Vcore_mem_bank.h"

#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <cassert>

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "svdpi.h"

static FILE* disk_file = nullptr;

void init_disk() {
    disk_file = fopen("fs.img", "r+b");

    if(!disk_file) {
        std::cerr << "[WARNING] Could not open fs.img! Disk operations will fail." << std::endl;
    }
}

void close_disk() {
    if(disk_file) fclose(disk_file);
}

extern "C" {
    long long host_disk_read_word(int sector, int word_offset) {
        if (!disk_file) return 0;
        
        uint64_t data = 0;
        long offset = (sector * 512) + (word_offset * 8);
        
        fseek(disk_file, offset, SEEK_SET);
        fread(&data, sizeof(uint64_t), 1, disk_file);
        
        return data;
    }

    void host_disk_write_word(int sector, int word_offset, long long data) {
        if (!disk_file) return;
        
        uint64_t out_data = (uint64_t)data;
        long offset = (sector * 512) + (word_offset * 8);
        
        fseek(disk_file, offset, SEEK_SET);
        fwrite(&out_data, sizeof(uint64_t), 1, disk_file);
        
        // fflush(disk_file); 
    }

}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vcore* dut = new Vcore;

    init_disk();

    // Verilated::traceEverOn(true);
    // VerilatedVcdC* tfp = new VerilatedVcdC;
    // dut->trace(tfp, 99);
    // tfp->open("vcd/core_trace.vcd");

    int time = 0;
    auto tick = [&]() {
        dut->clk = 0;
        dut->eval();
        // tfp->dump(time++);
        
        dut->clk = 1;
        dut->eval();
        // tfp->dump(time++);
    };

    std::cout << "====== Starting Core Execution Tests ======\n";

    assert(argc > 2);
    std::string hex_file = argv[1];
    int logging = std::atoi(argv[2]);

    // read the hex file
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

    // system reset
    // dut->rst = 1;
    // tick();
    // dut->rst = 0;
    dut->rst = 1;
    tick();
    dut->clk = 0;
    dut->eval();
    // tfp->dump(time++);

    // backdoor memory loading with instructions
    // boot adress at 0x0
    std::cout << "Loading " << instructions.size() << " instructions from " << hex_file << " into memory...\n";
    const uint32_t MAX_DEPTH = 524288; 

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

            switch(bank_idx) {
                case 0: dut->core->mmu_instance->mem_instance->mem_banks__BRA__0__KET____DOT__mem_bank_instance->bank[mem_idx] = byte_val; break;
                case 1: dut->core->mmu_instance->mem_instance->mem_banks__BRA__1__KET____DOT__mem_bank_instance->bank[mem_idx] = byte_val; break;
                case 2: dut->core->mmu_instance->mem_instance->mem_banks__BRA__2__KET____DOT__mem_bank_instance->bank[mem_idx] = byte_val; break;
                case 3: dut->core->mmu_instance->mem_instance->mem_banks__BRA__3__KET____DOT__mem_bank_instance->bank[mem_idx] = byte_val; break;
                case 4: dut->core->mmu_instance->mem_instance->mem_banks__BRA__4__KET____DOT__mem_bank_instance->bank[mem_idx] = byte_val; break;
                case 5: dut->core->mmu_instance->mem_instance->mem_banks__BRA__5__KET____DOT__mem_bank_instance->bank[mem_idx] = byte_val; break;
                case 6: dut->core->mmu_instance->mem_instance->mem_banks__BRA__6__KET____DOT__mem_bank_instance->bank[mem_idx] = byte_val; break;
                case 7: dut->core->mmu_instance->mem_instance->mem_banks__BRA__7__KET____DOT__mem_bank_instance->bank[mem_idx] = byte_val; break;
            }
        }
    }

    dut->rst = 0;
    dut->clk = 1;
    dut->eval();
    // tfp->dump(time++);

    /* EXECUTION START */
    std::cout << "Executing pipeline till infinite loop is detected ...\n";
    
    uint64_t prev_pc1 = -1;
    uint64_t prev_pc2 = -1;
    int loop_counter = 0;
    #define LOOP_THRESHOLD 20

    struct termios old_tio, new_tio;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    uint32_t sim_cycle = 0;

    while(1){
        if (sim_cycle % 10000 == 0) {
            char ch;
            if (read(STDIN_FILENO, &ch, 1) > 0) {
                if (ch == 3) { 
                    std::cout << "\n[INFO] Exit requested (Ctrl+C).\n";
                    break;
                }
                dut->rx_valid = 1;
                dut->rx_data = ch;
            } else {
                dut->rx_valid = 0;
                dut->rx_data = 0;
            }
        } else {
            dut->rx_valid = 0; 
        }

        tick();

        uint64_t current_pc = dut->core->___05Fif_pc;

        // check if PC is stuck on the same instruction (e.g., j .) 
        // or alternating between two instructions
        if (current_pc == prev_pc1 || current_pc == prev_pc2) {
            loop_counter++;
            if (loop_counter > LOOP_THRESHOLD) {
                std::cout << "\n[INFO] Infinite loop detected at PC 0x" 
                          << std::hex << current_pc << std::dec 
                          << ".\n";
                break;
            }
        } else {
            loop_counter = 0;
        }

        prev_pc2 = prev_pc1;
        prev_pc1 = current_pc;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
    /* EXECUTION FINISH */

    if(logging == 0) {
        dut->eval();
        // tfp->dump(time++);
        // tfp->close();
        
        delete dut;
        // delete tfp;

        std::cout << "SUCCESS: Core simulation finished (without log). Check vcd/core_trace.vcd.\n";
        close_disk();
        return 0;
    }

    // riscv abi names mapping
    const char* abi[] = {
        "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
        "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
        "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
        "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
    };


    uint64_t pc = dut->core->___05Fif_pc;
    std::cout << "PC : 0x" << std::hex << std::setw(16) << std::setfill('0') << pc << "\n";

    // TODO! enable ABI mappings
    for (int i = 0; i < 32; i++) {
        uint64_t val = dut->core->__PVT__id_stage_instance__DOT__regfile_instance__DOT__reg_array[i];
        
        std::cout << "x" << std::dec << i << (i < 10 ? " ": "") << ": 0x" 
                    << std::hex << std::setw(16) << std::setfill('0') << val << "\n";
    }

    std::cout << "===========================================\n\n";

    // print final memory hexdump
    std::cout << "\n============================ Final Memory Hexdump ============================\n";
    std::cout << " Address | 00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F | ASCII\n";
    std::cout << "----------------------------------------------------------------------------\n";

    bool last_was_zero = false;
    for (int mem_base = 0; mem_base < MAX_DEPTH * 8; mem_base += 16) {
        uint8_t line_bytes[16];
        bool line_has_data = false;
        
        for (int j = 0; j < 16; j++) {
            int addr = mem_base + j;
            int bank_idx = addr % 8;
            int mem_idx = addr / 8;
            uint8_t byte_val = 0;
            
            switch(bank_idx) {
                case 0: byte_val = dut->core->mmu_instance->mem_instance->mem_banks__BRA__0__KET____DOT__mem_bank_instance->bank[mem_idx]; break;
                case 1: byte_val = dut->core->mmu_instance->mem_instance->mem_banks__BRA__1__KET____DOT__mem_bank_instance->bank[mem_idx]; break;
                case 2: byte_val = dut->core->mmu_instance->mem_instance->mem_banks__BRA__2__KET____DOT__mem_bank_instance->bank[mem_idx]; break;
                case 3: byte_val = dut->core->mmu_instance->mem_instance->mem_banks__BRA__3__KET____DOT__mem_bank_instance->bank[mem_idx]; break;
                case 4: byte_val = dut->core->mmu_instance->mem_instance->mem_banks__BRA__4__KET____DOT__mem_bank_instance->bank[mem_idx]; break;
                case 5: byte_val = dut->core->mmu_instance->mem_instance->mem_banks__BRA__5__KET____DOT__mem_bank_instance->bank[mem_idx]; break;
                case 6: byte_val = dut->core->mmu_instance->mem_instance->mem_banks__BRA__6__KET____DOT__mem_bank_instance->bank[mem_idx]; break;
                case 7: byte_val = dut->core->mmu_instance->mem_instance->mem_banks__BRA__7__KET____DOT__mem_bank_instance->bank[mem_idx]; break;
            }
            line_bytes[j] = byte_val;
            if (byte_val != 0) line_has_data = true;
        }

        if (line_has_data || mem_base < 128) {
            std::cout << "  0x" << std::hex << std::setw(4) << std::setfill('0') << mem_base << " | ";
            
            for (int j = 0; j < 16; j++) {
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)line_bytes[j] << " ";
                if (j == 7) std::cout << " ";
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
                std::cout << "       * |";
                for(int i = 0; i < 3*16; i++) {
                    std::cout << " ";
                }
                std::cout << "  | ................\n";
                last_was_zero = true;
            }
        }
    }
    std::cout << "==============================================================================\n\n";

    dut->eval();
    // tfp->dump(time++);
    // tfp->close();
    
    delete dut;
    // delete tfp;

    std::cout << "SUCCESS: Core simulation finished. Check vcd/core_trace.vcd.\n";
    close_disk();
    return 0;
}