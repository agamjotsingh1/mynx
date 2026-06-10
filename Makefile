CORE = core
MODULES = modules
DV = dv
OBJ = obj_dir
VCD = vcd
AS = riscv64-elf-as
OBJCOPY = riscv64-elf-objcopy
ASFLAGS = -march=rv64i -mabi=lp64

VERILATOR = verilator
VFLAGS = -Wall --trace --cc --exe --build -I$(CORE)

PROG ?= program

HEX_FILE = tests/hex/$(PROG).hex

.PHONY: clean

tests/hex/%.hex: tests/asm/%.s
	@echo "Assembling $< into $@..."
	mkdir -p tests/hex
	$(AS) $(ASFLAGS) $< -o tests/hex/$*.o
	$(OBJCOPY) -O binary tests/hex/$*.o tests/hex/$*.bin
	hexdump -v -e '/4 "%08x\n"' tests/hex/$*.bin > $@
	rm -f tests/hex/$*.o tests/hex/$*.bin

core: $(HEX_FILE) $(CORE)/core.v $(DV)/core_tb.cpp
	@echo "Building and Running $@ with $(HEX_FILE)..."
	mkdir -p $(OBJ) $(VCD)
	$(VERILATOR) $(VFLAGS) $(CORE)/core.v $(DV)/$@_tb.cpp --Mdir $(OBJ)/$@
	./$(OBJ)/$@/V$@ $(HEX_FILE)

verify: core
	@echo "Generating trace with spike..."
	# -m0x0:0x2000 maps 8192 bytes of memory starting at 0x0 (1024 doublewords)
	# timeout is used because your ASM files contain infinite loops
	-timeout 1s spike --isa=rv64i -m0x0:0x2000 --log-commits $(ELF_FILE) 2> spike_trace.log
	@echo "Trace saved to spike_trace.log"

# typing "make alu" automatically pairs "core/alu.v" with "dv/alu_tb.cpp"
%: $(CORE)/$(MODULES)/%.v $(DV)/%_tb.cpp
	@echo "Building and Running $@..."
	mkdir -p $(OBJ) $(VCD)
	$(VERILATOR) $(VFLAGS) $(CORE)/$(MODULES)/$@.v $(DV)/$@_tb.cpp --Mdir $(OBJ)/$@
	./$(OBJ)/$@/V$@

clean:
	@echo "Cleaning up..."
	rm -rf $(OBJ)
	rm -rf $(VCD)
	rm -rf tests/hex/