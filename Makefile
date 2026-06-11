CORE = core
MODULES = modules
DV = dv
OBJ = obj_dir
VCD = vcd
AS = riscv64-elf-as
OBJCOPY = riscv64-elf-objcopy
LD = riscv64-elf-ld
ASFLAGS = -march=rv64i -mabi=lp64

VERILATOR = verilator
VFLAGS = -Wall --trace --cc --exe --build -I$(CORE)

PROG ?= program

HEX_FILE = tests/hex/$(PROG).hex

.PHONY: clean hex-all test-all verify verify-all

tests/hex/%.hex: tests/asm/%.s
	@echo "Assembling and Dual Linking $<..."
	@mkdir -p tests/hex
	$(AS) $(ASFLAGS) $< -o tests/hex/$*.o

	@# Generate the Hex file for Vcore
	$(LD) -N -T tests/link_vcore.ld tests/hex/$*.o -o tests/hex/$*_vcore.elf
	$(OBJCOPY) -O binary --change-addresses=-0x80000000 tests/hex/$*_vcore.elf tests/hex/$*.bin
	hexdump -v -e '/4 "%08x\n"' tests/hex/$*.bin > $@

	@# Generate the ELF file for Spike
	$(LD) -N -T tests/link_spike.ld tests/hex/$*.o -o tests/hex/$*_spike.elf
	@rm -f tests/hex/$*.o tests/hex/$*.bin tests/hex/$*_vcore.elf

core: $(HEX_FILE) $(CORE)/core.v $(DV)/core_tb.cpp
	@echo "Building and Running $@ with $(HEX_FILE)..."
	@mkdir -p $(OBJ) $(VCD)
	$(VERILATOR) $(VFLAGS) $(CORE)/core.v $(DV)/core_tb.cpp --Mdir $(OBJ)/core
	./$(OBJ)/core/Vcore $(HEX_FILE)

%: $(CORE)/$(MODULES)/%.v $(DV)/%_tb.cpp
	@echo "Building and Running $@..."
	@mkdir -p $(OBJ) $(VCD)
	$(VERILATOR) $(VFLAGS) $(CORE)/$(MODULES)/$@.v $(DV)/$@_tb.cpp --Mdir $(OBJ)/$@
	./$(OBJ)/$@/V$@

clean:
	@echo "Cleaning up..."
	rm -rf $(OBJ)
	rm -rf $(VCD)
	rm -rf tests/hex/

hex-all:
	@for file in tests/asm/*.s; do \
		prog=$$(basename $$file .s); \
		$(MAKE) tests/hex/$$prog.hex > /dev/null 2>&1; \
	done

run-all: hex-all $(CORE)/core.v $(DV)/core_tb.cpp
	@echo "Building hardware for basic run..."
	@mkdir -p $(OBJ) $(VCD)
	$(VERILATOR) $(VFLAGS) $(CORE)/core.v $(DV)/core_tb.cpp --Mdir $(OBJ)/core
	@echo "Running basic run..."
	@for file in tests/hex/*.hex; do \
		./$(OBJ)/core/Vcore $$file || exit 1; \
	done
	@echo "Basic run successfully done!"

verify: tests/hex/$(PROG).hex $(CORE)/core.v $(DV)/core_tb.cpp
	@echo "Building Hardware Simulator..."
	@mkdir -p $(OBJ) $(VCD)
	$(VERILATOR) $(VFLAGS) $(CORE)/core.v $(DV)/core_tb.cpp --Mdir $(OBJ)/core
	@python3 dv/verify.py tests/hex/$(PROG)_spike.elf tests/hex/$(PROG).hex ./$(OBJ)/core/Vcore

verify-all: hex-all $(CORE)/core.v $(DV)/core_tb.cpp
	@echo "Building Hardware..."
	@mkdir -p $(OBJ) $(VCD)
	$(VERILATOR) $(VFLAGS) $(CORE)/core.v $(DV)/core_tb.cpp --Mdir $(OBJ)/core
	@echo "Running verification suite..."
	@for file in tests/asm/*.s; do \
		prog=$$(basename $$file .s); \
		echo "------------------------------------------"; \
		python3 dv/verify.py tests/hex/$${prog}_spike.elf tests/hex/$${prog}.hex ./$(OBJ)/core/Vcore || exit 1; \
	done
	@echo "------------------------------------------";
	@echo "All tests fully verified against Spike!"