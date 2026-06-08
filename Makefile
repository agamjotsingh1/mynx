CORE = core
DV = dv
OBJ = obj_dir
VCD = vcd

VERILATOR = verilator
VFLAGS = -Wall --trace --cc --exe --build -I$(CORE)

.PHONY: clean

# typing "make alu" automatically pairs "core/alu.v" with "dv/alu_tb.cpp"
%: $(CORE)/%.v $(DV)/%_tb.cpp
	@echo "Building and Running $@..."
	mkdir -p $(OBJ) $(VCD)
	$(VERILATOR) $(VFLAGS) $(CORE)/$@.v $(DV)/$@_tb.cpp --Mdir $(OBJ)/$@
	./$(OBJ)/$@/V$@

clean:
	@echo "Cleaning up..."
	rm -rf $(OBJ)
	rm -f $(VCD)