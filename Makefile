TARGET  = riscv64-elf-
CC      = $(TARGET)gcc
AS      = $(TARGET)as
LD      = $(TARGET)ld
OBJCOPY = $(TARGET)objcopy
HEXDUMP = hexdump
VERILATOR = verilator
PY      = python3

CORE    = core
MODULES = modules
PIPELINE = pipeline
DV      = dv
OBJ     = obj_dir
VCD     = vcd
TEST    ?= deadbeef
LOGGING ?= 1
FILE    ?= deadbeef.hex

# core verilator build
CORE_TOP  = $(CORE)/core.v
CORE_TB   = $(DV)/core_tb.cpp
CORE_BIN  = $(OBJ)/core/Vcore
CORE_SRCS = $(shell find $(CORE) -name '*.v')

# directories
TEST_DIR = tests
ASMTEST_DIR = $(TEST_DIR)/asm
ASMTEST_HEX_DIR = $(ASMTEST_DIR)/hex
CTEST_DIR = $(TEST_DIR)/c
CTEST_HEX_DIR = $(CTEST_DIR)/hex
CENV_DIR = $(CTEST_DIR)/env
RISCVTEST_DIR = $(TEST_DIR)/riscv
RISCVTEST_HEX_DIR = $(RISCVTEST_DIR)/hex
RISCVTEST_ASM_DIR = $(RISCVTEST_DIR)/asm
RISCVTEST_ENV_DIR = $(RISCVTEST_DIR)/env
RISCVTEST_MACROS_DIR = $(RISCVTEST_DIR)/macros

# asm tests
ASMLINKER = $(TEST_DIR)/link.ld
ASMTEST_SRCS = $(wildcard $(ASMTEST_DIR)/*.s)
ASMTEST_HEX  = $(patsubst $(ASMTEST_DIR)/%.s, $(ASMTEST_HEX_DIR)/%.hex, $(ASMTEST_SRCS))

# c tests
CLINKER = $(TEST_DIR)/linkc.ld
CRUNTIME = $(CENV_DIR)/crt0.S
CSOFTMATH = $(CENV_DIR)/softmath.c
CTRAPVEC = $(CENV_DIR)/trapvec.S
CTEST_SRCS = $(wildcard $(CTEST_DIR)/*.c)
CTEST_HEX  = $(patsubst $(CTEST_DIR)/%.c, $(CTEST_HEX_DIR)/%.hex, $(CTEST_SRCS))

# riscv tests
RISCVLINKER = $(RISCVTEST_ENV_DIR)/link.ld
RISCVTEST_SRCS = $(wildcard $(RISCVTEST_ASM_DIR)/*.S)
RISCVTEST_HEX  = $(patsubst $(RISCVTEST_ASM_DIR)/%.S, $(RISCVTEST_HEX_DIR)/%.hex, $(RISCVTEST_SRCS))

# flags
ARCHFLAGS = -march=rv64i_zicsr_zifencei -mabi=lp64
ASFLAGS  = $(ARCHFLAGS)

# ASM_CFLAGS are for macro and .S file compilation
ASM_CFLAGS = $(ARCHFLAGS) -nostdlib -nostartfiles -Wl,--no-warn-rwx-segments
# CFLAGS are for proper C compilation
CFLAGS = $(ARCHFLAGS) -mcmodel=medany -ffreestanding -nostdlib -nostartfiles -Wl,--no-warn-rwx-segments

LDFLAGS = -N -T
OBJCOPYFLAGS = -O binary --change-addresses=-0x80000000
OBJCOPYFLAGS_NOCHANGEADDR = -O binary
HEXDUMPFLAGS = -v -e '/4 "%08x\n"'

# verilator conf file
VCONF = $(CORE)/core.vc

# verilator flags
VFLAGS = -f $(VCONF) --top-module core --prefix Vcore \
	 -Wall --cc --exe --build -I$(CORE) -O3 \
         --x-assign fast --x-initial fast --noassert \
         -CFLAGS "-O3 -march=native -flto -DNDEBUG" \
         -LDFLAGS "-flto"

# old code w/ vcd dump
# VFLAGS = -Wall --trace --cc --exe --build -I$(CORE) -O3 -CFLAGS "-O3"

# verification scripts
PY_VERIFY_SCRIPT = $(DV)/verify.py

# Disk image
FSIMG = fs.img

# XV6 build targets
XV6_ROOT = xv6
XV6_FSIMG = $(XV6_ROOT)/fs.img
XV6_FSIMG_TARGET = fs.img
XV6_KERNEL = $(XV6_ROOT)/kernel
XV6_KERNEL_TARGET = kernel/kernel
XV6_KERNEL_BIN = $(XV6_KERNEL)/kernel.bin
XV6_KERNEL_HEX = $(XV6_KERNEL)/kernel.hex

# remote files on pynq
REMOTE_DIR = mynx
HWH_LOCAL = vivado/mynx/mynx.gen/sources_1/bd/design_1/hw_handoff/design_1.hwh
HWH_REMOTE = $(REMOTE_DIR)/design_1.hwh
BITSTREAM_LOCAL = vivado/mynx/mynx.runs/impl_1/design_1_wrapper.bit
BITSTREAM_REMOTE = $(REMOTE_DIR)/design_1.bit
PROG ?= $(ASMTEST_HEX_DIR)/deadbeef.hex
PROG_REMOTE = $(REMOTE_DIR)/prog.hex
RUN_SCRIPT ?= pynq/run.py
RUN_SCRIPT_REMOTE = $(REMOTE_DIR)/run.py

# vivado
VIV = vivado
VIV_INIT_PROJ_SCRIPT = init.tcl
VIV_INIT_PROJ_FLAGS = -mode batch -source $(VIV_INIT_PROJ_SCRIPT)
VIV_PROJ_FILE = mynx/mynx.xpr
VIV_BD_SCRIPT = pynq/bd/bd.tcl
VIV_BUILD_PROJ_SCRIPT = build.tcl
VIV_BUILD_PROJ_FLAGS = -mode batch -source $(VIV_BUILD_PROJ_SCRIPT)

# colors for display
GREEN   = \033[1;32m
RED     = \033[1;31m
YELLOW  = \033[1;33m
NC      = \033[0m

# --- builds ---

# core verilator binary
$(CORE_BIN): $(CORE_SRCS) $(CORE_TB)
	@mkdir -p $(OBJ) $(VCD)
	$(VERILATOR) $(VFLAGS) $(CORE_TOP) $(CORE_TB) --Mdir $(dir $@)

build-core: $(CORE_BIN)
.PHONY: build-core

# asm tests
$(ASMTEST_HEX_DIR)/%.hex: $(ASMTEST_DIR)/%.s
	@mkdir -p $(ASMTEST_HEX_DIR)
	$(AS) $(ASFLAGS) $< -o $(ASMTEST_HEX_DIR)/$*.o
	$(LD) $(LDFLAGS) $(ASMLINKER) $(ASMTEST_HEX_DIR)/$*.o -o $(ASMTEST_HEX_DIR)/$*.elf
	$(OBJCOPY) $(OBJCOPYFLAGS) $(ASMTEST_HEX_DIR)/$*.elf $(ASMTEST_HEX_DIR)/$*.bin
	$(HEXDUMP) $(HEXDUMPFLAGS) $(ASMTEST_HEX_DIR)/$*.bin > $@

build-asm-test: $(ASMTEST_HEX_DIR)/$(TEST).hex
	@echo -e "$(GREEN)Compiled ASM test $(TEST) successfully!$(NC)"

build-asm-test-all: $(ASMTEST_HEX)
	@echo -e "$(GREEN)All ASM tests compiled successfully!$(NC)"

.PHONY: build-asm-test build-asm-test-all

# c tests
$(CTEST_HEX_DIR)/%.hex: $(CTEST_DIR)/%.c $(CRUNTIME) $(CTRAPVEC) $(CSOFTMATH)
	@mkdir -p $(CTEST_HEX_DIR)
	$(CC) $(CFLAGS) -T $(CLINKER) $(CRUNTIME) $(CTRAPVEC) $(CSOFTMATH) $< -o $(CTEST_HEX_DIR)/$*.elf
	$(OBJCOPY) $(OBJCOPYFLAGS) $(CTEST_HEX_DIR)/$*.elf $(CTEST_HEX_DIR)/$*.bin
	$(HEXDUMP) $(HEXDUMPFLAGS) $(CTEST_HEX_DIR)/$*.bin > $@

build-c-test: $(CTEST_HEX_DIR)/$(TEST).hex
	@echo -e "$(GREEN)Compiled C test $(TEST) successfully!$(NC)"

build-c-test-all: $(CTEST_HEX)
	@echo -e "$(GREEN)All C tests compiled successfully!$(NC)"

.PHONY: build-c-test build-c-test-all

# riscv tests
$(RISCVTEST_HEX_DIR)/%.hex: $(RISCVTEST_ASM_DIR)/%.S
	@mkdir -p $(RISCVTEST_HEX_DIR)
	$(CC) $(ASM_CFLAGS) -I$(RISCVTEST_ENV_DIR) -I$(RISCVTEST_MACROS_DIR) -T$(RISCVLINKER) $< -o $(RISCVTEST_HEX_DIR)/$*.elf
	$(OBJCOPY) $(OBJCOPYFLAGS_NOCHANGEADDR) $(RISCVTEST_HEX_DIR)/$*.elf $(RISCVTEST_HEX_DIR)/$*.bin
	$(HEXDUMP) $(HEXDUMPFLAGS) $(RISCVTEST_HEX_DIR)/$*.bin > $@

build-riscv-test: $(RISCVTEST_HEX_DIR)/$(TEST).hex
	@echo -e "$(GREEN)Compiled RISC-V test $(TEST) successfully!$(NC)"

build-riscv-test-all: $(RISCVTEST_HEX)
	@echo -e "$(GREEN)All RISC-V tests compiled successfully!$(NC)"

.PHONY: build-riscv-test build-riscv-test-all

# --- running ---
run-asm: $(CORE_BIN) $(ASMTEST_HEX_DIR)/$(TEST).hex
	@echo -e "$(YELLOW)Running ASM test: $(TEST)...$(NC)"
	./$(CORE_BIN) $(ASMTEST_HEX_DIR)/$(TEST).hex $(LOGGING) 1

run-c: $(CORE_BIN) $(CTEST_HEX_DIR)/$(TEST).hex
	@echo -e "$(YELLOW)Running C test: $(TEST)...$(NC)"
	./$(CORE_BIN) $(CTEST_HEX_DIR)/$(TEST).hex $(LOGGING) 1

run-riscv: $(CORE_BIN) $(RISCVTEST_HEX_DIR)/$(TEST).hex
	@echo -e "$(YELLOW)Running RISC-V test: $(TEST)...$(NC)"
	./$(CORE_BIN) $(RISCVTEST_HEX_DIR)/$(TEST).hex $(LOGGING) 1

run: $(CORE_BIN)
	@echo -e "$(YELLOW)Booting core with $(FILE)...$(NC)"
	@if [ ! -f $(FILE) ]; then \
		echo -e "$(RED)Hex file '$(FILE)' does not exist! Compile it first.$(NC)"; \
		exit 1; \
	fi
	./$(CORE_BIN) $(FILE) $(LOGGING) 1

.PHONY: run run-asm run-c run-riscv

# --- verification ---
verify-asm: $(CORE_BIN) $(ASMTEST_HEX_DIR)/$(TEST).hex
	@echo -e "$(YELLOW)Verifying core with ASM test $(TEST)...$(NC)"
	$(PY) $(PY_VERIFY_SCRIPT) $(ASMTEST_HEX_DIR)/$(TEST).elf $(ASMTEST_HEX_DIR)/$(TEST).hex $(CORE_BIN) || { echo -e "$(RED)ASM Test verification failed on $(TEST)!$(NC)"; exit 1; };
	@echo -e "$(GREEN)ASM test $(TEST) verified against Spike!$(NC)"

verify-c: $(CORE_BIN) $(CTEST_HEX_DIR)/$(TEST).hex
	@echo -e "$(YELLOW)Verifying core with C test $(TEST)...$(NC)"
	@echo -e "$(YELLOW)NOTE: C test verification may fail as a result of Spike not having I/O$(NC)"
	$(PY) $(PY_VERIFY_SCRIPT) $(CTEST_HEX_DIR)/$(TEST).elf $(CTEST_HEX_DIR)/$(TEST).hex $(CORE_BIN) || { echo -e "$(RED)C Test verification failed on $(TEST)!$(NC)"; exit 1; };
	@echo -e "$(GREEN)C test $(TEST) verified successfully against Spike!$(NC)"

verify-riscv: $(CORE_BIN) $(RISCVTEST_HEX_DIR)/$(TEST).hex
	@echo -e "$(YELLOW)Verifying core with RISC-V test $(TEST)...$(NC)"
	$(PY) $(PY_VERIFY_SCRIPT) $(RISCVTEST_HEX_DIR)/$(TEST).elf $(RISCVTEST_HEX_DIR)/$(TEST).hex $(CORE_BIN) || { echo -e "$(RED)RISC-V Test verification failed on $(TEST)!$(NC)"; exit 1; };
	@echo -e "$(GREEN)RISC-V test $(TEST) verified successfully against Spike!$(NC)"

verify-asm-all: $(CORE_BIN) $(ASMTEST_HEX)
	@echo -e "$(YELLOW)Verifying core with ASM tests...$(NC)"
	@for file in $(ASMTEST_HEX); do \
		prog=$$(basename $$file .hex); \
		$(PY) $(PY_VERIFY_SCRIPT) $(ASMTEST_HEX_DIR)/$$prog.elf $$file $(CORE_BIN) || { echo -e "$(RED)ASM Verification failed on $$prog!$(NC)"; exit 1; }; \
	done
	@echo -e "$(GREEN)All ASM tests verified successfully against Spike!$(NC)"

verify-c-all: $(CORE_BIN) $(CTEST_HEX)
	@echo -e "$(YELLOW)Verifying core with C tests...$(NC)"
	@echo -e "$(YELLOW)NOTE: C test verifications may fail as a result of Spike not having I/O$(NC)"
	@for file in $(CTEST_HEX); do \
		prog=$$(basename $$file .hex); \
		$(PY) $(PY_VERIFY_SCRIPT) $(CTEST_HEX_DIR)/$$prog.elf $$file $(CORE_BIN) || { echo -e "$(RED)C Verification failed on $$prog!$(NC)"; exit 1; }; \
	done
	@echo -e "$(GREEN)All C tests verified successfully against Spike!$(NC)"

verify-riscv-all: $(CORE_BIN) $(RISCVTEST_HEX)
	@echo -e "$(YELLOW)Verifying core with RISC-V tests...$(NC)"
	@for file in $(RISCVTEST_HEX); do \
		prog=$$(basename $$file .hex); \
		$(PY) $(PY_VERIFY_SCRIPT) $(RISCVTEST_HEX_DIR)/$$prog.elf $$file $(CORE_BIN) || { echo -e "$(RED)RISC-V Verification failed on $$prog!$(NC)"; exit 1; }; \
	done
	@echo -e "$(GREEN)All RISC-V tests verified successfully against Spike!$(NC)"

.PHONY: verify-asm verify-c verify-riscv verify-asm-all verify-c-all verify-riscv-all

# --- xv6 build ---
build-kernel:
	@echo -e "$(YELLOW)Building xv6...$(NC)"
	$(MAKE) -C $(XV6_ROOT) $(XV6_KERNEL_TARGET) $(XV6_FSIMG_TARGET)
	$(OBJCOPY) $(OBJCOPYFLAGS) $(XV6_ROOT)/$(XV6_KERNEL_TARGET) $(XV6_KERNEL_BIN)
	$(HEXDUMP) $(HEXDUMPFLAGS) $(XV6_KERNEL_BIN) > $(XV6_KERNEL_HEX)
	@cp $(XV6_FSIMG) ./$(FSIMG)
	@echo -e "$(GREEN)xv6 successfully built!$(NC)"

.PHONY: build-kernel

# -- xv6 boot ---
boot: $(CORE_BIN) build-kernel
	@echo -e "$(YELLOW)Booting xv6 on core...$(NC)"
	./$(CORE_BIN) $(XV6_KERNEL_HEX) $(LOGGING) 0

.PHONY: boot

# --- vivado file upload ---
upload: $(HWH_LOCAL) $(BITSTREAM_LOCAL)
	@sudo chmod +x ./pynq/samba.sh
	@./pynq/samba.sh 

# --- pynq file upload ---
pynq-upload: $(HWH_LOCAL) $(BITSTREAM_LOCAL) $(PROG) $(RUN_SCRIPT)
	@echo -e "$(YELLOW)Uploading Bitstream and HWH to PYNQ...$(NC)"
	@chmod +x ./pynq/samba.sh
	@echo -e "$(YELLOW)Uploading HWH...$(NC)"
	@./pynq/samba.sh upload $(HWH_LOCAL) $(REMOTE_DIR) $(HWH_REMOTE)
	@echo -e "$(YELLOW)Uploading Bitstream...$(NC)"
	@./pynq/samba.sh upload $(BITSTREAM_LOCAL) $(REMOTE_DIR) $(BITSTREAM_REMOTE)
	@echo -e "$(YELLOW)Uploading program hex...$(NC)"
	@./pynq/samba.sh upload $(PROG) $(REMOTE_DIR) $(PROG_REMOTE)
	@echo -e "$(YELLOW)Uploading Run script...$(NC)"
	@./pynq/samba.sh upload $(RUN_SCRIPT) $(REMOTE_DIR) $(RUN_SCRIPT_REMOTE)
	@echo -e "$(GREEN)Vivado files successfully uploaded to PYNQ!$(NC)"

.PHONY: pynq-upload

# --- vivado init project ---
viv-init:
	$(VIV) $(VIV_INIT_PROJ_FLAGS)

.PHONY: viv-init

# --- vivado make block design ---
viv-bd:
	@echo -e "$(YELLOW)Exporting block design...$(NC)"
	@echo "open_project $(VIV_PROJ_FILE); open_bd_design [get_files design_1.bd]; write_bd_tcl -force $(BD_SCRIPT); close_project; exit" | vivado -mode tcl
	@echo -e "$(YELLOW)Sanitizing block design script...$(NC)"
	@sed -i -E 's/-net [^ ]+ +//g' $(BD_SCRIPT)
	@echo -e "$(GREEN)Vivado block design script generated!$(NC)"

.PHONY: viv-bd

# --- vivado synthesize project ---
viv-build:
	$(VIV) $(VIV_BUILD_PROJ_FLAGS)

.PHONY: viv-build

# --- clean ---
clean:
	@echo -e "$(YELLOW)Cleaning...$(NC)"
	@rm -rf $(OBJ) $(VCD)
	@rm -rf $(ASMTEST_HEX_DIR)
	@rm -rf $(CTEST_HEX_DIR)
	@rm -rf $(RISCVTEST_HEX_DIR)
	@rm -f $(FSIMG) spike.cmd
	@if [ -d "$(XV6_ROOT)" ]; then \
		rm -f $(XV6_KERNEL_BIN) $(XV6_KERNEL_HEX); \
		$(MAKE) -C $(XV6_ROOT) clean; \
	fi
	@echo -e "$(GREEN)Clean complete!$(NC)"
 
# --- diff ---
diff:
	@git status
	@git --no-pager diff --stat

.PHONY: diff
