TARGET  = riscv64-elf-
CC      = $(TARGET)gcc
AS      = $(TARGET)as
LD      = $(TARGET)ld
OBJCOPY = $(TARGET)objcopy
HEXDUMP = hexdump

CORE    = core
MODULES = modules
DV      = dv
OBJ     = obj_dir
VCD     = vcd
TEST    ?= deadbeef

CORE_TOP  = $(CORE)/core.v
CORE_TB   = $(DV)/core_tb.cpp
CORE_BIN  = $(OBJ)/core/Vcore
CORE_SRCS = $(shell find $(CORE) -name '*.v')

TEST_DIR = tests
ASMTEST_DIR = $(TEST_DIR)/asm
CTEST_DIR = $(TEST_DIR)/c
RISCVTEST_DIR = $(TEST_DIR)/riscv
ASMTEST_HEX_DIR = $(ASMTEST_DIR)/hex
CTEST_HEX_DIR = $(CTEST_DIR)/hex
RISCVTEST_HEX_DIR = $(RISCVTEST_DIR)/hex
CENV_DIR = $(CTEST_DIR)/env

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

ARCHFLAGS = -march=rv64i_zicsr -mabi=lp64
ASFLAGS  = $(ARCHFLAGS)

# ASM_CFLAGS are for macro and .S file compilation
ASM_CFLAGS = $(ARCHFLAGS) -nostdlib -nostartfiles -Wl,--no-warn-rwx-segments
# CFLAGS are for proper C compilation
CFLAGS = $(ARCHFLAGS) -mcmodel=medany -ffreestanding -nostdlib -nostartfiles -Wl,--no-warn-rwx-segments

LDFLAGS = -N -T
OBJCOPYFLAGS = -O binary --change-addresses=-0x80000000 
HEXDUMPFLAGS = -v -e '/4 "%08x\n"'

# verilator flags
VERILATOR = verilator
VFLAGS    = -Wall --trace --cc --exe --build -I$(CORE)

# colors for display
GREEN   = \033[1;32m
RED     = \033[1;31m
NC      = \033[0m

# --- targets ---

# core verilator binary
$(CORE_BIN): $(CORE_SRCS) $(CORE_TB)
	@mkdir -p $(OBJ) $(VCD)
	$(VERILATOR) $(VFLAGS) $(CORE_TOP) $(CORE_TB) --Mdir $(dir $@)

build-core: $(CORE_BIN)

# asm tests
$(ASMTEST_HEX_DIR)/%.hex: $(ASMTEST_DIR)/%.s
	@mkdir -p $(ASMTEST_HEX_DIR)
	$(AS) $(ASFLAGS) $< -o $(ASMTEST_HEX_DIR)/$*.o
	$(LD) $(LDFLAGS) $(ASMLINKER) $(ASMTEST_HEX_DIR)/$*.o -o $(ASMTEST_HEX_DIR)/$*.elf
	$(OBJCOPY) $(OBJCOPYFLAGS) $(ASMTEST_HEX_DIR)/$*.elf $(ASMTEST_HEX_DIR)/$*.bin
	$(HEXDUMP) $(HEXDUMPFLAGS) $(ASMTEST_HEX_DIR)/$*.bin > $@

build-asm-test: $(ASMTEST_HEX_DIR)/$(TEST).hex
	@echo -e "$(GREEN)Compiled asm test $(TEST) successfully!$(NC)"

build-asm-tests: $(ASMTEST_HEX)
	@echo -e "$(GREEN)All asm tests compiled successfully!$(NC)"

# c tests
$(CTEST_HEX_DIR)/%.hex: $(CTEST_DIR)/%.c $(CRUNTIME) $(CTRAPVEC) $(CSOFTMATH)
	@mkdir -p $(CTEST_HEX_DIR)
	$(CC) $(CFLAGS) -T $(CLINKER) $(CRUNTIME) $(CTRAPVEC) $(CSOFTMATH) $< -o $(CTEST_HEX_DIR)/$*.elf
	$(OBJCOPY) $(OBJCOPYFLAGS) $(CTEST_HEX_DIR)/$*.elf $(CTEST_HEX_DIR)/$*.bin
	$(HEXDUMP) $(HEXDUMPFLAGS) $(CTEST_HEX_DIR)/$*.bin > $@

build-c-test: $(CTEST_HEX_DIR)/$(TEST).hex
	@echo -e "$(GREEN)Compiled C test $(TEST) successfully!$(NC)"

build-c-tests: $(CTEST_HEX)
	@echo -e "$(GREEN)All C tests compiled successfully!$(NC)"

# generate a git diff
diff:
	@git status
	@git diff --stat

.PHONY: build-core build-asm-test build-asm-tests build-c-test build-c-tests diff