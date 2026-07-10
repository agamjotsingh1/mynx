// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vsubmem_tb__pch.h"

Vsubmem_tb__Syms::Vsubmem_tb__Syms(VerilatedContext* contextp, const char* namep, Vsubmem_tb* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup top module instance
    , TOP{this, namep}
{
    // Check resources
    Verilated::stackCheck(1330);
    // Setup sub module instances
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-12);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
    __Vscopep_submem_tb__dut = new VerilatedScope{this, "submem_tb.dut", "dut", "<null>", 0, VerilatedScope::SCOPE_OTHER};
    __Vscopep_submem_tb__dut__cache_instance = new VerilatedScope{this, "submem_tb.dut.cache_instance", "cache_instance", "<null>", 0, VerilatedScope::SCOPE_OTHER};
    __Vscopep_submem_tb__dut__cache_instance__cache_bram_instance = new VerilatedScope{this, "submem_tb.dut.cache_instance.cache_bram_instance", "cache_bram_instance", "<null>", 0, VerilatedScope::SCOPE_OTHER};
    __Vscopep_submem_tb__slave = new VerilatedScope{this, "submem_tb.slave", "slave", "<null>", -12, VerilatedScope::SCOPE_OTHER};
    // Setup export functions - final: 0
    // Setup export functions - final: 1
    // Setup public variables
    __Vscopep_submem_tb__dut->varInsert("flush_line", &(TOP.submem_tb__DOT__dut__DOT__flush_line), false, VLVT_UINT16, VLVD_NODIR|VLVF_PUB_RD|VLVF_CONTINUOUSLY, 0, 1 ,10,0);
    __Vscopep_submem_tb__dut->varInsert("state", &(TOP.submem_tb__DOT__dut__DOT__state), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RD|VLVF_CONTINUOUSLY, 0, 1 ,4,0);
    __Vscopep_submem_tb__dut__cache_instance->varInsert("meta_even", &(TOP.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even), false, VLVT_UINT16, VLVD_NODIR|VLVF_PUB_RD, 1, 1 ,0,1023 ,11,0);
    __Vscopep_submem_tb__dut__cache_instance->varInsert("meta_odd", &(TOP.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd), false, VLVT_UINT16, VLVD_NODIR|VLVF_PUB_RD, 1, 1 ,0,1023 ,11,0);
    __Vscopep_submem_tb__dut__cache_instance__cache_bram_instance->varInsert("mem", &(TOP.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem), false, VLVT_UINT64, VLVD_NODIR|VLVF_PUB_RD, 1, 1 ,0,16383 ,63,0);
}

Vsubmem_tb__Syms::~Vsubmem_tb__Syms() {
    // Tear down scopes
    VL_DO_CLEAR(delete __Vscopep_submem_tb__dut, __Vscopep_submem_tb__dut = nullptr);
    VL_DO_CLEAR(delete __Vscopep_submem_tb__dut__cache_instance, __Vscopep_submem_tb__dut__cache_instance = nullptr);
    VL_DO_CLEAR(delete __Vscopep_submem_tb__dut__cache_instance__cache_bram_instance, __Vscopep_submem_tb__dut__cache_instance__cache_bram_instance = nullptr);
    VL_DO_CLEAR(delete __Vscopep_submem_tb__slave, __Vscopep_submem_tb__slave = nullptr);
    // Tear down sub module instances
}
