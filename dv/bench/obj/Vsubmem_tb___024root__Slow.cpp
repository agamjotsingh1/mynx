// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsubmem_tb.h for the primary calling header

#include "Vsubmem_tb__pch.h"

void Vsubmem_tb___024root___ctor_var_reset(Vsubmem_tb___024root* vlSelf);

Vsubmem_tb___024root::Vsubmem_tb___024root(Vsubmem_tb__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vsubmem_tb___024root___ctor_var_reset(this);
}

void Vsubmem_tb___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vsubmem_tb___024root::~Vsubmem_tb___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
