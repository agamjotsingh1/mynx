TARGET  ?= riscv64-elf-
CC      = $(TARGET)gcc
AS      = $(TARGET)as
LD      = $(TARGET)ld
OBJCOPY = $(TARGET)objcopy

ARCH    = -march=rv64i_zicsr -mabi=lp64
ASFLAGS = $(ARCH)
CFLAGS  = $(ARCH) -nostdlib -nostartfiles -Wl,--no-warn-rwx-segments

# compiler flags
C_CFLAGS = $(ARCH) -mcmodel=medany -ffreestanding -nostdlib -nostartfiles -Wl,--no-warn-rwx-segments

VERILATOR = verilator
VFLAGS    = -Wall --trace --cc --exe --build -I$(CORE)

CORE    = core
MODULES = modules
DV      = dv
OBJ     = obj_dir
VCD     = vcd
PROG    ?= deadbeef

GREEN   = \033[1;32m
RED     = \033[1;31m
NC      = \033[0m

.PHONY: clean build-tests build-riscv-tests run-all test test-all test-riscv-all build-core build-ctests testc-all

tests/hex/%.hex: tests/asm/%.s
	@mkdir -p tests/hex
	$(AS) $(ASFLAGS) $< -o tests/hex/$*.o
	$(LD) -N -T tests/link.ld tests/hex/$*.o -o tests/hex/$*_vcore.elf
	$(OBJCOPY) -O binary --change-addresses=-0x80000000 tests/hex/$*_vcore.elf tests/hex/$*.bin
	hexdump -v -e '/4 "%08x\n"' tests/hex/$*.bin > $@
	$(LD) -N -T tests/link.ld tests/hex/$*.o -o tests/hex/$*_spike.elf
	@rm -f tests/hex/$*.o tests/hex/$*.bin tests/hex/$*_vcore.elf

build-tests:
	@for file in tests/asm/*.s; do \
		$(MAKE) --no-print-directory tests/hex/$$(basename $$file .s).hex > /dev/null 2>&1; \
	done

build-riscv-tests:
	@mkdir -p tests/riscv/hex
	@for file in tests/riscv/asm/*.S; do \
		prog=$$(basename $$file .S); \
		$(CC) $(CFLAGS) -I./tests/riscv/env -I./tests/riscv/macros/ -T./tests/riscv/env/link.ld $$file -o tests/riscv/hex/$$prog.elf; \
		$(OBJCOPY) -O binary tests/riscv/hex/$$prog.elf tests/riscv/hex/$$prog.bin; \
		hexdump -v -e '1/4 "%08x\n"' tests/riscv/hex/$$prog.bin > tests/riscv/hex/$$prog.hex; \
	done

build-core:
	@mkdir -p $(OBJ) $(VCD)
	$(VERILATOR) $(VFLAGS) $(CORE)/core.v $(DV)/core_tb.cpp --Mdir $(OBJ)/core

core: build-core tests/hex/$(PROG).hex
	./$(OBJ)/core/Vcore tests/hex/$(PROG).hex

%: $(CORE)/$(MODULES)/%.v $(DV)/%_tb.cpp
	@mkdir -p $(OBJ) $(VCD)
	$(VERILATOR) $(VFLAGS) $< $(word 2,$^) --Mdir $(OBJ)/$@
	./$(OBJ)/$@/V$@

run-all: build-core build-tests
	@for file in tests/hex/*.hex; do \
		./$(OBJ)/core/Vcore $$file || { echo -e "$(RED)Run failed on $$file!$(NC)"; exit 1; }; \
	done
	@echo -e "$(GREEN)All basic runs completed successfully!$(NC)"

test: build-core tests/hex/$(PROG).hex
	@python3 dv/verify.py tests/hex/$(PROG)_spike.elf tests/hex/$(PROG).hex ./$(OBJ)/core/Vcore || { echo -e "$(RED)Test $(PROG) failed!$(NC)"; exit 1; }
	@echo -e "$(GREEN)Test $(PROG) verified successfully!$(NC)"

test-all: build-core build-tests
	@for file in tests/asm/*.s; do \
		prog=$$(basename $$file .s); \
		python3 dv/verify.py tests/hex/$${prog}_spike.elf tests/hex/$${prog}.hex ./$(OBJ)/core/Vcore || { echo -e "$(RED)Verification failed on $${prog}!$(NC)"; exit 1; }; \
	done
	@echo -e "$(GREEN)All tests fully verified against Spike!$(NC)"

test-riscv-all: build-core build-riscv-tests
	@for file in tests/riscv/asm/*.S; do \
		prog=$$(basename $$file .S); \
		python3 dv/verify.py tests/riscv/hex/$${prog}.elf tests/riscv/hex/$${prog}.hex ./$(OBJ)/core/Vcore || { echo -e "$(RED)RISC-V verification failed on $${prog}!$(NC)"; exit 1; }; \
	done
	@echo -e "$(GREEN)All RISC-V tests fully verified against Spike!$(NC)"

tests/c/hex/%.hex: tests/c/%.c tests/c/crt0.S
	@mkdir -p tests/c/hex
	$(CC) $(C_CFLAGS) -T tests/linkc.ld tests/c/crt0.S $< -o tests/c/hex/$*_vcore.elf
	$(OBJCOPY) -O binary --change-addresses=-0x80000000 tests/c/hex/$*_vcore.elf tests/c/hex/$*.bin
	hexdump -v -e '/4 "%08x\n"' tests/c/hex/$*.bin > $@
	$(CC) $(C_CFLAGS) -T tests/linkc.ld tests/c/crt0.S $< -o tests/c/hex/$*_spike.elf
	@rm -f tests/c/hex/$*.bin tests/c/hex/$*_vcore.elf

build-ctests:
	@mkdir -p tests/c/hex
	@for file in tests/c/*.c; do \
		if [ -f "$$file" ]; then \
			prog=$$(basename $$file .c); \
			$(MAKE) --no-print-directory tests/c/hex/$$prog.hex > /dev/null 2>&1; \
		fi \
	done

testc-all: build-core build-ctests
	@for file in tests/c/*.c; do \
		if [ -f "$$file" ]; then \
			prog=$$(basename $$file .c); \
			python3 dv/verify.py tests/c/hex/$${prog}_spike.elf tests/c/hex/$${prog}.hex ./$(OBJ)/core/Vcore || { echo -e "$(RED)C Verification failed on $${prog}!$(NC)"; exit 1; }; \
		fi \
	done
	@echo -e "$(GREEN)All C tests fully verified against Spike!$(NC)"

clean:
	rm -rf $(OBJ) $(VCD) tests/hex/ tests/riscv/hex/ tests/c/hex/
	@echo -e "$(GREEN)Cleaned up successfully!$(NC)"