CORE = core
MODULES = modules
DV = dv
OBJ = obj_dir
VCD = vcd

VERILATOR = verilator
VFLAGS = -Wall --trace --cc --exe --build -I$(CORE)

PROG ?= tests/program.hex

.PHONY: clean

core: $(CORE)/core.v $(DV)/core_tb.cpp
	@echo "Building and Running $@..."
	mkdir -p $(OBJ) $(VCD)
	$(VERILATOR) $(VFLAGS) $(CORE)/core.v $(DV)/$@_tb.cpp --Mdir $(OBJ)/$@
	./$(OBJ)/$@/V$@ $(PROG)

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