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

// enable waveform tracing
// #define TRACE

#define MEM(dut)    ((dut)->soc->__PVT__u_amc_slave__DOT__mem)
#define PC(dut)     ((dut)->soc->u_core->___05Fif_pc)
#define REG(dut, i) ((dut)->soc->u_core->__PVT__id_stage_instance__DOT__regfile_instance__DOT__reg_array[i])

#define DISK_IMAGE          "fs.img"
#define TRACE_FILE          "vcd/soc_trace.vcd"
#define TRACE_DEPTH         99

#define MEM_WORDS           16777216ULL
#define MEM_WORD_BYTES      8
#define MEM_BYTES           (MEM_WORDS * MEM_WORD_BYTES)
#define INSTR_BYTES         4
#define INSTR_MASK          0xFFFFFFFFULL

#define SECTOR_BYTES        1024
#define DISK_WORD_BYTES     8

#define NUM_REGS            32
#define LOOP_THRESHOLD      20
#define INPUT_POLL_CYCLES   100000
#define KEY_CTRL_C          3

#define HEXDUMP_COLS        16
#define HEXDUMP_MIN_BYTES   128
#define ASCII_PRINT_LO      32
#define ASCII_PRINT_HI      126

static uint8_t* disk_data = nullptr;
static size_t   disk_size = 0;

static bool disk_ready() {
    return disk_data && disk_data != MAP_FAILED;
}

static void init_disk() {
    int fd = open(DISK_IMAGE, O_RDWR);
    if (fd < 0) {
        std::cerr << "Could not open " DISK_IMAGE "! Disk operations will fail.\n";
        return;
    }

    struct stat st;
    fstat(fd, &st);
    disk_size = st.st_size;

    disk_data = (uint8_t*)mmap(NULL, disk_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
}

static void close_disk() {
    if (disk_ready()) munmap(disk_data, disk_size);
}

static long disk_offset(int sector, int word_offset) {
    return (long)sector * SECTOR_BYTES + (long)word_offset * DISK_WORD_BYTES;
}

extern "C" {
    long long host_disk_read_word(int sector, int word_offset) {
        if (!disk_ready()) return 0;

        long offset = disk_offset(sector, word_offset);
        if (offset < 0 || offset + DISK_WORD_BYTES > (long)disk_size) return 0;

        return *(uint64_t*)(disk_data + offset);
    }

    void host_disk_write_word(int sector, int word_offset, long long data) {
        if (!disk_ready()) return;

        long offset = disk_offset(sector, word_offset);
        if (offset < 0 || offset + DISK_WORD_BYTES > (long)disk_size) return;

        *(uint64_t*)(disk_data + offset) = data;
    }
}

static bool load_hex_file(const std::string& path, std::vector<uint32_t>& instructions) {
    std::ifstream infile(path);
    if (!infile.is_open()) {
        std::cerr << "Could not open program file: " << path << "\n";
        std::cerr << "Usage: --PROGFILE [path to program file]\n";
        return false;
    }

    std::string line;
    while (std::getline(infile, line)) {
        line.erase(line.find_last_not_of(" \n\r\t") + 1);
        if (line.empty() || line[0] == '/' || line[0] == '#') continue;

        try {
            instructions.push_back((uint32_t)std::stoul(line, nullptr, 16));
        } catch (...) {
            std::cerr << "Skipping invalid hex line: " << line << "\n";
        }
    }

    return true;
}

static void load_memory(Vsoc* dut, const std::vector<uint32_t>& instructions) {
    for (size_t i = 0; i < instructions.size(); i++) {
        uint64_t byte_addr = (uint64_t)i * INSTR_BYTES;
        uint64_t word_idx  = byte_addr / MEM_WORD_BYTES;
        int      shift     = (byte_addr % MEM_WORD_BYTES) * 8;

        if (word_idx >= MEM_WORDS) {
            std::cerr << "Hex file exceeds memory depth of " << MEM_WORDS << " words!\n";
            return;
        }

        MEM(dut)[word_idx] = (MEM(dut)[word_idx] & ~(INSTR_MASK << shift)) |
                             ((uint64_t)instructions[i] << shift);
    }
}

static uint8_t mem_byte(Vsoc* dut, uint64_t addr) {
    uint64_t word_idx = addr / MEM_WORD_BYTES;
    int      shift    = (addr % MEM_WORD_BYTES) * 8;
    return (MEM(dut)[word_idx] >> shift) & 0xFF;
}

static void set_raw_mode(struct termios* saved) {
    struct termios raw;
    tcgetattr(STDIN_FILENO, saved);
    raw = *saved;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

static void restore_mode(const struct termios* saved) {
    tcsetattr(STDIN_FILENO, TCSANOW, saved);
}

static void dump_regs(Vsoc* dut) {
    std::cout << "PC : 0x" << std::hex << std::setw(16) << std::setfill('0') << (uint64_t)PC(dut) << "\n";

    for (int i = 0; i < NUM_REGS; i++) {
        std::cout << "x" << std::dec << i << (i < 10 ? " " : "") << ": 0x"
                  << std::hex << std::setw(16) << std::setfill('0') << (uint64_t)REG(dut, i) << "\n";
    }
}

static void dump_memory(Vsoc* dut) {
    std::cout << "\n----------------------------- Memory Hexdump -----------------------------\n";
    std::cout << " Address | 00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F | ASCII\n";
    std::cout << "----------------------------------------------------------------------------\n";

    bool last_was_zero = false;

    for (uint64_t base = 0; base < MEM_BYTES; base += HEXDUMP_COLS) {
        uint8_t bytes[HEXDUMP_COLS];
        bool    has_data = false;

        for (int j = 0; j < HEXDUMP_COLS; j++) {
            bytes[j] = mem_byte(dut, base + j);
            if (bytes[j] != 0) has_data = true;
        }

        if (!has_data && base >= HEXDUMP_MIN_BYTES) {
            if (!last_was_zero) {
                std::cout << "       * |" << std::string(3 * HEXDUMP_COLS, ' ') << "  | ................\n";
                last_was_zero = true;
            }
            continue;
        }

        std::cout << "  0x" << std::hex << std::setw(4) << std::setfill('0') << base << " | ";

        for (int j = 0; j < HEXDUMP_COLS; j++) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)bytes[j] << " ";
            if (j == HEXDUMP_COLS / 2 - 1) std::cout << " ";
        }

        std::cout << "| ";

        for (int j = 0; j < HEXDUMP_COLS; j++) {
            bool printable = bytes[j] >= ASCII_PRINT_LO && bytes[j] <= ASCII_PRINT_HI;
            std::cout << (printable ? (char)bytes[j] : '.');
        }

        std::cout << "\n";
        last_was_zero = false;
    }

    std::cout << "----------------------------------------------------------------------------\n";
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    CLI::App app{"mynx"};

    int         log     = 0;
    int         loopbrk = 0;
    std::string progfile;

    app.add_option("--LOG",      log,      "Enable logging with register and memory hexdump display");
    app.add_option("--LOOPBRK",  loopbrk,  "Enable breaking on infinite loop");
    app.add_option("--PROGFILE", progfile, "Path to program hex file");

    CLI11_PARSE(app, argc, argv);

    Vsoc*          dut  = new Vsoc;
    uint64_t       time = 0;

#ifdef TRACE
    VerilatedVcdC* tfp  = nullptr;
    Verilated::traceEverOn(true);
    tfp = new VerilatedVcdC;
    dut->trace(tfp, TRACE_DEPTH);
    tfp->open(TRACE_FILE);
#endif

    auto dump_wave = [&]() {
#ifdef TRACE
        tfp->dump(time++);
#endif
    };

    auto tick = [&]() {
        dut->clk = 0;
        dut->eval();
        dump_wave();

        dut->clk = 1;
        dut->eval();
        dump_wave();
    };

    auto teardown = [&](int status) {
        dut->eval();
#ifdef TRACE
        tfp->dump(time++);
        tfp->close();
        delete tfp;
#endif
        delete dut;
        close_disk();
        return status;
    };

    init_disk();

    std::cout << "Starting SoC Execution Tests...\n";

    std::vector<uint32_t> instructions;
    if (!load_hex_file(progfile, instructions)) return teardown(1);

    dut->rst = 1;
    tick();
    dut->clk = 0;
    dut->eval();
    dump_wave();

    std::cout << "Loading " << instructions.size() << " instructions from " << progfile << " into memory...\n";
    load_memory(dut, instructions);

    dut->tx_ready = 1;
    dut->rst      = 0;
    dut->clk      = 1;
    dut->eval();
    dump_wave();

    std::cout << "Running soc...\n";

    struct termios saved_tio;
    set_raw_mode(&saved_tio);

    uint64_t prev_pc1     = UINT64_MAX;
    uint64_t prev_pc2     = UINT64_MAX;
    int      loop_counter = 0;
    uint64_t sim_cycle    = 0;

    while (1) {
        if (sim_cycle % INPUT_POLL_CYCLES == 0) {
            char ch;
            if (read(STDIN_FILENO, &ch, 1) > 0) {
                if (ch == KEY_CTRL_C) break;
                dut->rx_valid = 1;
                dut->rx_data  = ch;
            } else {
                dut->rx_valid = 0;
                dut->rx_data  = 0;
            }
        } else {
            dut->rx_valid = 0;
        }

        sim_cycle++;
        tick();

        if (dut->tx_valid) std::cout << (char)dut->tx_data << std::flush;

        if (!loopbrk) continue;

        uint64_t current_pc = PC(dut);

        if (current_pc == prev_pc1 || current_pc == prev_pc2) {
            loop_counter++;
            if (loop_counter > LOOP_THRESHOLD) {
                std::cout << "\n[INFO] Infinite loop detected at PC 0x"
                          << std::hex << current_pc << std::dec << ".\n";
                break;
            }
        } else {
            loop_counter = 0;
        }

        prev_pc2 = prev_pc1;
        prev_pc1 = current_pc;
    }

    restore_mode(&saved_tio);

    if (log) {
        dump_regs(dut);
        dump_memory(dut);
    }

    std::cout << "SoC simulation finished.\n";
    return teardown(0);
}
