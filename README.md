# mynx
Modular riscv core with xv6
riscv64-unknown-elf-gcc -march=rv64i -mabi=lp64 -nostdlib -nostartfiles -I./tests/riscv/env -I./tests/riscv/macros/ -T./tests/riscv/env/link.ld ./tests/riscv/rv64ui/add.S -o add.elf