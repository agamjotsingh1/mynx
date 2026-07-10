// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VSUBMEM_TB__SYMS_H_
#define VERILATED_VSUBMEM_TB__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vsubmem_tb.h"

// INCLUDE MODULE CLASSES
#include "Vsubmem_tb___024root.h"

// DPI TYPES for DPI Export callbacks (Internal use)

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vsubmem_tb__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vsubmem_tb* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vsubmem_tb___024root           TOP;

    // SCOPE NAMES
    VerilatedScope* __Vscopep_submem_tb__dut;
    VerilatedScope* __Vscopep_submem_tb__dut__cache_instance;
    VerilatedScope* __Vscopep_submem_tb__dut__cache_instance__cache_bram_instance;
    VerilatedScope* __Vscopep_submem_tb__slave;

    // CONSTRUCTORS
    Vsubmem_tb__Syms(VerilatedContext* contextp, const char* namep, Vsubmem_tb* modelp);
    ~Vsubmem_tb__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
