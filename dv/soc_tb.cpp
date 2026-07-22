#include "Vsoc.h"
#include "Vsoc_soc.h"
#include "Vsoc_core.h"

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
#include "svdpi.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <CLI/CLI.hpp>

#define MEM(dut)    ((dut)->soc->__PVT__u_amc_slave__DOT__mem)
#define PC(dut)     ((dut)->soc->u_core->___05Fif_pc)
#define REG(dut, i) ((dut)->soc->u_core->__PVT__id_stage_instance__DOT__regfile_instance__DOT__reg_array[i])

static const uint64_t MEM_WORDS = 16777216;
static uint8_t* disk_data = nullptr;
static size_t disk_size = 0;

void init_disk() {
    int fd = open("fs.img", O_RDWR);
    if (fd < 0) {
        std::cerr << "Could not open fs.img! Disk operations will fail.\n";
        return;
    }

    struct stat st;
    fstat(fd, &st);
    disk_size = st.st_size;

    disk_data = (uint8_t*)mmap(NULL, disk_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
}

void close_disk() {
    if (disk_data && disk_data != MAP_FAILED) {
        munmap(disk_data, disk_size);
    }
}

extern "C" {
    long long host_disk_read_word(int sector, int word_offset) {
        if (!disk_data || disk_data == MAP_FAILED) return 0;

        long offset = (sector * 1024) + (word_offset * 8);
        if (offset + 8 > (long)disk_size) return 0; // bounds check

        return *(uint64_t*)(disk_data + offset);
    }

    void host_disk_write_word(int sector, int word_offset, long long data) {
        if (!disk_data || disk_data == MAP_FAILED) return;

        long offset = (sector * 1024) + (word_offset * 8);
        if (offset + 8 <= (long)disk_size) {
            *(uint64_t*)(disk_data + offset) = data;
        }
    }
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vsoc* dut = new Vsoc;

    CLI::App app{"mynx"};

    int log = 0;
    int verify = 0;
    int loopbrk = 0;
    int trace = 0;
    std::string progfile;

    app.add_option("--LOG", log, "Enable logging with register and memory hexdump display");
    app.add_option("--VERIFY", verify, "Enable verification mode");
    app.add_option("--LOOPBRK", loopbrk, "Enable breaking on infinite loop");
    app.add_option("--TRACE", trace, "Enable waveform tracing");
    app.add_option("--PROGFILE", progfile, "Path to program hex file");

    CLI11_PARSE(app, argc, argv);

    init_disk();

    if(trace) {
      Verilated::traceEverOn(true);
      VerilatedVcdC* tfp = new VerilatedVcdC;
      dut->trace(tfp, 99);
      tfp->open("vcd/soc_trace.vcd");
    }

    int time = 0;

    auto tick = [&]() {
        dut->clk = 0;
        dut->eval();
        if(trace) tfp->dump(time++);

        dut->clk = 1;
        dut->eval();
        if(trace) tfp->dump(time++);
    };

    std::cout << "Starting SoC Execution Tests...\n";

    std::vector<uint32_t> instructions;
    std::ifstream infile(progfile);

    if (!infile.is_open()) {
        std::cerr << "Could not open program file: " << progfile << "\n";
        std::cerr << "Usage: --PROGFILE [path to program file]\n";
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
            std::cerr << "Skipping invalid hex line: " << line << "\n";
        }
    }

    infile.close();

    // system reset
    dut->rst = 1;
    tick();
    dut->clk = 0;
    dut->eval();
    if(trace) tfp->dump(time++);

    std::cout << "Loading " << instructions.size() << " instructions from " << hex_file << " into memory...\n";

    for (size_t i = 0; i < instructions.size(); i++) {
        uint32_t instr     = instructions[i];
        uint64_t byte_addr = (uint64_t)i * 4;
        uint64_t word_idx  = byte_addr >> 3;
        int      shift     = (byte_addr & 7) * 8; // 0 or 32 (4-byte aligned)

        if (word_idx >= MEM_WORDS) {
            std::cerr << "Hex file exceeds memory depth of " << MEM_WORDS << " words!\n";
            break;
        }

        MEM(dut)[word_idx] =
            (MEM(dut)[word_idx] & ~((uint64_t)0xFFFFFFFFULL << shift)) |
            ((uint64_t)instr << shift);
    }

    // always ready to accept uart output
    dut->tx_ready = 1;

    dut->rst = 0;
    dut->clk = 1;
    dut->eval();
    if(trace) tfp->dump(time++);

    std::cout << "Running soc...\n";

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
    #define INPUT_CYCLE 100000

    while(1){
        if (sim_cycle % INPUT_CYCLE == 0) {
            char ch;
            if (read(STDIN_FILENO, &ch, 1) > 0) {
                if (ch == 3) break; // Ctrl+C
                dut->rx_valid = 1;
                dut->rx_data = ch;
            } else {
                dut->rx_valid = 0;
                dut->rx_data = 0;
            }
        } else {
            dut->rx_valid = 0;
        }

        sim_cycle++;

        tick();

        if (dut->tx_valid) {
            std::cout << (char)dut->tx_data << std::flush;
        }

        uint64_t current_pc = PC(dut);

        if(loopbrk) {
          if (current_pc == prev_pc1 || current_pc == prev_pc2) {
              loop_counter++;
              if (loop_counter > LOOP_THRESHOLD && verify != 0) {
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
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

    if(log == 0) {
        dut->eval();
        if(trace) {
          tfp->dump(time++);
          tfp->close();
        }

        delete dut;
        if(trace) delete tfp;

        std::cout << "SoC simulation finished.\n";
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

    uint64_t pc = PC(dut);
    std::cout << "PC : 0x" << std::hex << std::setw(16) << std::setfill('0') << pc << "\n";

    // TODO! enable ABI mappings
    for (int i = 0; i < 32; i++) {
        uint64_t val = REG(dut, i);

        std::cout << "x" << std::dec << i << (i < 10 ? " ": "") << ": 0x"
                    << std::hex << std::setw(16) << std::setfill('0') << val << "\n";
    }

    std::cout << "===========================================\n\n";

    // print final memory hexdump
    std::cout << "\n============================ Final Memory Hexdump ============================\n";
    std::cout << " Address | 00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F | ASCII\n";
    std::cout << "----------------------------------------------------------------------------\n";

    bool last_was_zero = false;
    for (uint64_t mem_base = 0; mem_base < MEM_WORDS * 8; mem_base += 16) {
        uint8_t line_bytes[16];
        bool line_has_data = false;

        for (int j = 0; j < 16; j++) {
            uint64_t addr     = mem_base + j;
            uint64_t word_idx = addr >> 3;
            int      shift    = (addr & 7) * 8;
            uint8_t  byte_val = (MEM(dut)[word_idx] >> shift) & 0xFF;

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

    std::cout << "SUCCESS: SoC simulation finished.\n";
    close_disk();
    return 0;
}
