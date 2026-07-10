// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsubmem_tb.h for the primary calling header

#include "Vsubmem_tb__pch.h"

VL_ATTR_COLD void Vsubmem_tb___024root___eval_static(Vsubmem_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___eval_static\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst__0 = vlSelfRef.rst;
    vlSelfRef.__Vtrigprevexpr___TOP__addr__0 = vlSelfRef.addr;
    vlSelfRef.__Vtrigprevexpr___TOP__mem_read__0 = vlSelfRef.mem_read;
    vlSelfRef.__Vtrigprevexpr___TOP__mem_write__0 = vlSelfRef.mem_write;
    vlSelfRef.__Vtrigprevexpr___TOP__bw__0 = vlSelfRef.bw;
    vlSelfRef.__Vtrigprevexpr___TOP__data_in__0 = vlSelfRef.data_in;
    vlSelfRef.__Vtrigprevexpr___TOP__flush__0 = vlSelfRef.flush;
    vlSelfRef.__Vtrigprevexpr___TOP__rng_seed__0 = vlSelfRef.rng_seed;
    vlSelfRef.__Vtrigprevexpr___TOP__bd_addr__0 = vlSelfRef.bd_addr;
    vlSelfRef.__Vtrigprevexpr___TOP__clk__1 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vsubmem_tb___024root___eval_initial(Vsubmem_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___eval_initial\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    {
        // Inlined CFunc: _eval_initial__TOP
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__i = 0U;
        while (VL_GTS_III(32, 0x00000400U, vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__i)) {
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd[(0x000003ffU 
                                                                               & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__i)] = 0U;
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even[(0x000003ffU 
                                                                                & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__i)] = 0U;
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__i 
                = ((IData)(1U) + vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__i);
        }
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__i = 0U;
        while (VL_GTS_III(32, 0x00004000U, vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__i)) {
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[(0x00003fffU 
                                                                                & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__i)] = 0xccccccccccccccccULL;
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__i 
                = ((IData)(1U) + vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__i);
        }
        vlSelfRef.submem_tb__DOT__slave__DOT__i = 0U;
        while (VL_GTS_III(32, 0x00020000U, vlSelfRef.submem_tb__DOT__slave__DOT__i)) {
            vlSelfRef.submem_tb__DOT__slave__DOT__i64 
                = VL_EXTENDS_QI(64,32, vlSelfRef.submem_tb__DOT__slave__DOT__i);
            vlSelfRef.submem_tb__DOT__slave__DOT__ram[(0x0001ffffU 
                                                       & vlSelfRef.submem_tb__DOT__slave__DOT__i)] 
                = (0xa5a5deadbeef5a5aULL ^ (0x9e3779b97f4a7c15ULL 
                                            * vlSelfRef.submem_tb__DOT__slave__DOT__i64));
            vlSelfRef.submem_tb__DOT__slave__DOT__i 
                = ((IData)(1U) + vlSelfRef.submem_tb__DOT__slave__DOT__i);
        }
    }
    {
        // Inlined CFunc: __Vm_traceActivitySetAll
        vlSelfRef.__Vm_traceActivity[0U] = 1U;
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        vlSelfRef.__Vm_traceActivity[3U] = 1U;
        vlSelfRef.__Vm_traceActivity[4U] = 1U;
    }
}

VL_ATTR_COLD void Vsubmem_tb___024root___eval_final(Vsubmem_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___eval_final\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsubmem_tb___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vsubmem_tb___024root___eval_phase__stl(Vsubmem_tb___024root* vlSelf);

VL_ATTR_COLD void Vsubmem_tb___024root___eval_settle(Vsubmem_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___eval_settle\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vsubmem_tb___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("submem_tb.v", 8, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 10000 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vsubmem_tb___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD bool Vsubmem_tb___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsubmem_tb___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vsubmem_tb___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vsubmem_tb___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___trigger_anySet__stl\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

VL_ATTR_COLD void Vsubmem_tb___024root___stl_sequent__TOP__0(Vsubmem_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___stl_sequent__TOP__0\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_13;
    __VdfgRegularize_h6e95ff9d_0_13 = 0;
    IData/*26:0*/ __VdfgRegularize_h6e95ff9d_0_15;
    __VdfgRegularize_h6e95ff9d_0_15 = 0;
    // Body
    vlSelfRef.bd_data = vlSelfRef.submem_tb__DOT__slave__DOT__ram
        [(0x0001ffffU & (vlSelfRef.bd_addr >> 3U))];
    vlSelfRef.submem_tb__DOT__slave__DOT__rng_next1 
        = (vlSelfRef.submem_tb__DOT__slave__DOT__rng 
           ^ (vlSelfRef.submem_tb__DOT__slave__DOT__rng 
              << 0x0000000dU));
    __VdfgRegularize_h6e95ff9d_0_15 = ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))
                                        ? (0x07ffffc0U 
                                           & vlSelfRef.submem_tb__DOT__dut__DOT__evict_addr)
                                        : (0x07ffffc0U 
                                           & vlSelfRef.addr));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
        = vlSelfRef.data_in;
    vlSelfRef.submem_tb__DOT__s_amc_data_in_last = 
        ((7U == (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr)) 
         & ((IData)(vlSelfRef.submem_tb__DOT__wvalid) 
            & (IData)(vlSelfRef.submem_tb__DOT__wready)));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__flush 
        = ((7U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)) 
           | (6U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)));
    vlSelfRef.submem_tb__DOT__s_amc_data_out_valid 
        = ((IData)(vlSelfRef.submem_tb__DOT__rready) 
           & ((IData)(vlSelfRef.submem_tb__DOT__rvalid) 
              & (2U == (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__state))));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw = 3U;
    vlSelfRef.submem_tb__DOT__s_amc_data_in_valid = 
        ((IData)(vlSelfRef.submem_tb__DOT__wready) 
         & ((IData)(vlSelfRef.submem_tb__DOT__wvalid) 
            & ((6U == (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__state)) 
               | (3U == (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__state)))));
    vlSelfRef.submem_tb__DOT__slave__DOT__rng_next2 
        = ((vlSelfRef.submem_tb__DOT__slave__DOT__rng_next1 
            >> 0x00000011U) ^ vlSelfRef.submem_tb__DOT__slave__DOT__rng_next1);
    vlSelfRef.submem_tb__DOT__dut__DOT__last_flush 
        = ((7U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)) 
           & (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_in_last));
    vlSelfRef.submem_tb__DOT__s_amc_data_out_last = 
        ((IData)(vlSelfRef.submem_tb__DOT__rlast) & (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_out_valid));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry = 0U;
    if ((0x00000010U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
            = vlSelfRef.data_in;
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw = 3U;
        vlSelfRef.submem_tb__DOT__s_amc_addr = (0x07ffffc0U 
                                                & vlSelfRef.addr);
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry = 0U;
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
            = (0x07ffffffU & vlSelfRef.addr);
    } else if ((8U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
            = vlSelfRef.data_in;
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw = 3U;
        vlSelfRef.submem_tb__DOT__s_amc_addr = (0x07ffffc0U 
                                                & vlSelfRef.addr);
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry = 0U;
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
            = (0x07ffffffU & vlSelfRef.addr);
    } else if ((4U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
        if ((1U & (~ ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state) 
                      >> 1U)))) {
            if ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
                    = vlSelfRef.data_in;
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw = 3U;
            } else {
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
                    = vlSelfRef.submem_tb__DOT__rdata;
            }
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry 
                = ((1U & (~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) 
                   && (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_out_valid));
        }
        if ((2U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
            vlSelfRef.submem_tb__DOT__s_amc_addr = __VdfgRegularize_h6e95ff9d_0_15;
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                = (0x07ffffffU & ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))
                                   ? (((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__flush_line) 
                                       << 6U) + (0x00000038U 
                                                 & (((IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr) 
                                                     + (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_in_valid)) 
                                                    << 3U)))
                                   : ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__flush_line) 
                                      << 6U)));
        } else if ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
            vlSelfRef.submem_tb__DOT__s_amc_addr = 
                (0x07ffffc0U & vlSelfRef.addr);
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                = (0x07ffffffU & vlSelfRef.addr);
        } else {
            vlSelfRef.submem_tb__DOT__s_amc_addr = 
                (0x07ffffc0U & ((IData)(0x00000040U) 
                                + vlSelfRef.submem_tb__DOT__dut__DOT__miss_addr));
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                = (0x07ffffffU & ((0x07ffffc0U & ((IData)(0x00000040U) 
                                                  + vlSelfRef.submem_tb__DOT__dut__DOT__miss_addr)) 
                                  + ((IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr) 
                                     << 3U)));
        }
    } else {
        if ((2U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
            if ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
                    = vlSelfRef.submem_tb__DOT__rdata;
                vlSelfRef.submem_tb__DOT__s_amc_addr 
                    = (0x07ffffc0U & vlSelfRef.submem_tb__DOT__dut__DOT__miss_addr);
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry 
                    = vlSelfRef.submem_tb__DOT__s_amc_data_out_valid;
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                    = (0x07ffffffU & ((0x07ffffc0U 
                                       & vlSelfRef.submem_tb__DOT__dut__DOT__miss_addr) 
                                      + ((IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr) 
                                         << 3U)));
            } else {
                vlSelfRef.submem_tb__DOT__s_amc_addr 
                    = (0x07ffffc0U & vlSelfRef.submem_tb__DOT__dut__DOT__spill_evict_addr);
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                    = (0x07ffffffU & ((0x07ffffc0U 
                                       & vlSelfRef.submem_tb__DOT__dut__DOT__spill_evict_addr) 
                                      + (0x00000038U 
                                         & (((IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr) 
                                             + (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_in_valid)) 
                                            << 3U))));
            }
        } else {
            if ((1U & (~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)))) {
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
                    = vlSelfRef.data_in;
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry = 0U;
            }
            vlSelfRef.submem_tb__DOT__s_amc_addr = __VdfgRegularize_h6e95ff9d_0_15;
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                = (0x07ffffffU & ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))
                                   ? ((0x07ffffc0U 
                                       & vlSelfRef.submem_tb__DOT__dut__DOT__evict_addr) 
                                      + (0x00000038U 
                                         & (((IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr) 
                                             + (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_in_valid)) 
                                            << 3U)))
                                   : vlSelfRef.addr));
        }
        if ((1U & (~ ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)))) {
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw 
                    = vlSelfRef.bw;
            }
        }
    }
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb 
        = VL_SHIFTR_QQI(64,64,7, vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in, 
                        (0x00000078U & (((IData)(8U) 
                                         - (7U & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)) 
                                        << 3U)));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__data_out_rotated 
        = (((- (QData)((IData)((0x40U > (0x00000078U 
                                         & (((IData)(8U) 
                                             - (7U 
                                                & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)) 
                                            << 3U)))))) 
            & VL_SHIFTL_QQI(64,64,7, vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb, 
                            (0x00000078U & (((IData)(8U) 
                                             - (7U 
                                                & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)) 
                                            << 3U)))) 
           | (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta 
              >> (0x00000038U & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                 << 3U))));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_primary 
        = ((0x00000040U & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)
            ? vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd
           [(0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                            >> 7U))] : vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even
           [(0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                            >> 7U))]);
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_8 = ((0x000000ffU 
                                                 & (0xff0f0301U 
                                                    >> 
                                                    ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw) 
                                                     << 3U))) 
                                                >> 
                                                (0x0000000fU 
                                                 & ((IData)(8U) 
                                                    - 
                                                    (7U 
                                                     & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr))));
    vlSelfRef.data_out = ((((2U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw))
                             ? (((QData)((IData)(((IData)(
                                                          (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__data_out_rotated 
                                                           >> 0x00000020U)) 
                                                  & (- (IData)(
                                                               (1U 
                                                                & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw))))))) 
                                 << 0x00000018U) | (QData)((IData)(
                                                                   (0x00ffffffU 
                                                                    & (IData)(
                                                                              (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__data_out_rotated 
                                                                               >> 8U))))))
                             : (QData)((IData)((0x000000ffU 
                                                & ((- (IData)(
                                                              (1U 
                                                               & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw)))) 
                                                   & (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__data_out_rotated 
                                                              >> 8U))))))) 
                           << 8U) | (QData)((IData)(
                                                    (0x000000ffU 
                                                     & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__data_out_rotated)))));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_evict_addr 
        = ((0x07fe0000U & ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_primary) 
                           << 0x00000011U)) | (0x0001ffc0U 
                                               & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_hit = 
        ((~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry)) 
         & (((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_primary) 
             >> 0x0000000bU) & ((0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                >> 0x00000011U)) 
                                == (0x000003ffU & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_primary)))));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__actual_flush 
        = ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__flush) 
           & (0x0c00U == (0x0c00U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_primary))));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_line_spill 
        = (IData)(((0x00000038U == (0x00000038U & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)) 
                   & (0U != (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_8))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_9 = ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry) 
                                                | (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__actual_flush));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_tag 
        = (0x000003ffU & ((vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                           >> 0x00000011U) + ((0x000007ffU 
                                               == (0x000007ffU 
                                                   & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                      >> 6U))) 
                                              & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_line_spill))));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_index 
        = (0x000007ffU & ((vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                           >> 6U) + (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_line_spill)));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_9)
            ? vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in
            : (vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
               << (0x00000038U & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  << 3U))));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_spill 
        = ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_index))
            ? vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd
           [(0x000003ffU & ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_index) 
                            >> 1U))] : vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even
           [(0x000003ffU & ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_index) 
                            >> 1U))]);
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_spill_dirty 
        = (((~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry)) 
            & (~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__actual_flush))) 
           & (0x0c00U == (0x0c00U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_spill))));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_spill_hit 
        = ((~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry)) 
           & ((~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__actual_flush)) 
              & (((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_spill) 
                  >> 0x0000000bU) & ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_tag) 
                                     == (0x000003ffU 
                                         & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_spill))))));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_miss 
        = (1U & ((~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_hit)) 
                 | ((~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_spill_hit)) 
                    & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_line_spill))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_7 = (1U 
                                                & ((4U 
                                                    & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))
                                                    ? 
                                                   (((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state) 
                                                     >> 1U) 
                                                    & ((~ (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_in_last)) 
                                                       & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)))
                                                    : 
                                                   ((2U 
                                                     & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))
                                                     ? 
                                                    (~ 
                                                     ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state) 
                                                      | (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_in_last)))
                                                     : 
                                                    ((1U 
                                                      & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))
                                                      ? 
                                                     (~ (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_in_last))
                                                      : 
                                                     ((~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_miss)) 
                                                      & (IData)(vlSelfRef.mem_read))))));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_mem_write 
        = (IData)(((0U == (0x18U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) 
                   & ((4U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))
                       ? (IData)(((0U == (3U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) 
                                  & (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_out_valid)))
                       : ((2U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))
                           ? ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state) 
                              & (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_out_valid))
                           : ((~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)) 
                              & ((~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_miss)) 
                                 & (IData)(vlSelfRef.mem_write)))))));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_waddr = 0U;
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_we = 0U;
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_waddr = 0U;
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_we = 0U;
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_wdata = 0U;
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_wdata = 0U;
    if (((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__actual_flush) 
         & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__last_flush))) {
        if ((0x00000040U & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)) {
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_waddr 
                = (0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  >> 7U));
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_we = 1U;
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_wdata 
                = (0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  >> 0x00000011U));
        }
        if ((1U & (~ (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                      >> 6U)))) {
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_waddr 
                = (0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  >> 7U));
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_we = 1U;
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_wdata 
                = (0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  >> 0x00000011U));
        }
    } else if (((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__flush) 
                & (~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__actual_flush)))) {
        if ((0x00000040U & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)) {
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_waddr 
                = (0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  >> 7U));
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_we = 1U;
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_wdata 
                = (0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  >> 0x00000011U));
        }
        if ((1U & (~ (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                      >> 6U)))) {
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_waddr 
                = (0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  >> 7U));
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_we = 1U;
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_wdata 
                = (0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  >> 0x00000011U));
        }
    } else if (((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry) 
                & (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_out_last))) {
        if ((0x00000040U & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)) {
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_waddr 
                = (0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  >> 7U));
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_we = 1U;
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_wdata 
                = (0x00000800U | (0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                 >> 0x00000011U)));
        }
        if ((1U & (~ (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                      >> 6U)))) {
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_waddr 
                = (0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  >> 7U));
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_we = 1U;
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_wdata 
                = (0x00000800U | (0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                 >> 0x00000011U)));
        }
    } else if (vlSelfRef.submem_tb__DOT__dut__DOT__cache_mem_write) {
        if (vlSelfRef.submem_tb__DOT__dut__DOT__cache_hit) {
            if ((0x00000040U & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)) {
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_waddr 
                    = (0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                      >> 7U));
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_we = 1U;
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_wdata 
                    = (0x00000c00U | (0x000003ffU & 
                                      (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                       >> 0x00000011U)));
            }
            if ((1U & (~ (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                          >> 6U)))) {
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_waddr 
                    = (0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                      >> 7U));
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_we = 1U;
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_wdata 
                    = (0x00000c00U | (0x000003ffU & 
                                      (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                       >> 0x00000011U)));
            }
        }
        if (((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_spill_hit) 
             & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_line_spill))) {
            if ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_index))) {
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_waddr 
                    = (0x000003ffU & ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_index) 
                                      >> 1U));
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_we = 1U;
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_wdata 
                    = (0x00000c00U | (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_tag));
            }
            if ((1U & (~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_index)))) {
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_waddr 
                    = (0x000003ffU & ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_index) 
                                      >> 1U));
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_we = 1U;
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_wdata 
                    = (0x00000c00U | (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_tag));
            }
        }
    }
    __VdfgRegularize_h6e95ff9d_0_13 = ((IData)(((0U 
                                                 == 
                                                 (0x18U 
                                                  & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) 
                                                & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_7))) 
                                       | (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_mem_write));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_10 = ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_mem_write) 
                                                 & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_hit));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__ena 
        = (((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_hit) 
            | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_9)) 
           & (IData)(__VdfgRegularize_h6e95ff9d_0_13));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__enb 
        = ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_spill_hit) 
           & ((0U != (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_8)) 
              & (IData)(__VdfgRegularize_h6e95ff9d_0_13)));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_8) 
           & (- (IData)(((~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry)) 
                         & ((~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__actual_flush)) 
                            & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_10))))));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea 
        = (0x000000ffU & (((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry)
                            ? (- (IData)((1U & ((0U 
                                                 != 
                                                 (0x18U 
                                                  & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) 
                                                | (~ (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_7))))))
                            : (((0xff0f0301U >> ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw) 
                                                 << 3U)) 
                                << (7U & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)) 
                               & (- (IData)((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_10))))) 
                          & (- (IData)((1U & (~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__actual_flush)))))));
}

VL_ATTR_COLD bool Vsubmem_tb___024root___eval_phase__stl(Vsubmem_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___eval_phase__stl\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__stl
        vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                          & vlSelfRef.__VstlTriggered[0U]) 
                                         | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vsubmem_tb___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vsubmem_tb___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        {
            // Inlined CFunc: _eval_stl
            if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
                Vsubmem_tb___024root___stl_sequent__TOP__0(vlSelf);
                {
                    // Inlined CFunc: __Vm_traceActivitySetAll
                    vlSelfRef.__Vm_traceActivity[0U] = 1U;
                    vlSelfRef.__Vm_traceActivity[1U] = 1U;
                    vlSelfRef.__Vm_traceActivity[2U] = 1U;
                    vlSelfRef.__Vm_traceActivity[3U] = 1U;
                    vlSelfRef.__Vm_traceActivity[4U] = 1U;
                }
            }
        }
    }
    return (__VstlExecute);
}

bool Vsubmem_tb___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 2> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsubmem_tb___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vsubmem_tb___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @( clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @( rst)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @( addr)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @( mem_read)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 4U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 4 is active: @( mem_write)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 5U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 5 is active: @( bw)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 6U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 6 is active: @( data_in)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 7U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 7 is active: @( flush)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 8U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 8 is active: @( rng_seed)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 9U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 9 is active: @( bd_addr)\n");
    }
    if ((1U & (IData)(triggers[1U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 64 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vsubmem_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsubmem_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vsubmem_tb___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vsubmem_tb___024root___ctor_var_reset(Vsubmem_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___ctor_var_reset\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->addr = VL_SCOPED_RAND_RESET_I(27, __VscopeHash, 14934084843038794831ull);
    vlSelf->mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13326595402784547387ull);
    vlSelf->mem_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11468839172742666876ull);
    vlSelf->bw = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 7951444373538714003ull);
    vlSelf->data_in = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 10574596302020702150ull);
    vlSelf->data_out = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 11675680895196038875ull);
    vlSelf->busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6386567572483775230ull);
    vlSelf->flush = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8361382489806169962ull);
    vlSelf->flush_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1514054278905831748ull);
    vlSelf->rng_seed = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8433346597645965783ull);
    vlSelf->bd_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2981555744781489759ull);
    vlSelf->bd_data = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 7269964216898786980ull);
    vlSelf->submem_tb__DOT__s_amc_addr = VL_SCOPED_RAND_RESET_I(27, __VscopeHash, 16906537732841695177ull);
    vlSelf->submem_tb__DOT__s_amc_data_in_last = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13496952352032523132ull);
    vlSelf->submem_tb__DOT__s_amc_data_in_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12999567827317103439ull);
    vlSelf->submem_tb__DOT__s_amc_data_out_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7955929089576410260ull);
    vlSelf->submem_tb__DOT__s_amc_data_out_last = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7858724233061142045ull);
    vlSelf->submem_tb__DOT__s_amc_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12870617746364586443ull);
    vlSelf->submem_tb__DOT__s_amc_err = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18347627312994621914ull);
    vlSelf->submem_tb__DOT__arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5286832126733039992ull);
    vlSelf->submem_tb__DOT__arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 725221077495027241ull);
    vlSelf->submem_tb__DOT__rlast = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13970900770857123373ull);
    vlSelf->submem_tb__DOT__rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5030408046346751652ull);
    vlSelf->submem_tb__DOT__rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13414479409526909717ull);
    vlSelf->submem_tb__DOT__awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 463964491382486355ull);
    vlSelf->submem_tb__DOT__awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16407892854087001175ull);
    vlSelf->submem_tb__DOT__wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12228720523846883592ull);
    vlSelf->submem_tb__DOT__wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5702226101444259047ull);
    vlSelf->submem_tb__DOT__bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4102875076064777859ull);
    vlSelf->submem_tb__DOT__bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17092539195850616135ull);
    vlSelf->submem_tb__DOT__araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5810305483440135111ull);
    vlSelf->submem_tb__DOT__awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8789414847932828969ull);
    vlSelf->submem_tb__DOT__rdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 11704209212904694118ull);
    vlSelf->submem_tb__DOT__dut__DOT__state = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 2711746110694998080ull);
    vlSelf->submem_tb__DOT__dut__DOT__flush_line = VL_SCOPED_RAND_RESET_I(11, __VscopeHash, 6409712535281960178ull);
    vlSelf->submem_tb__DOT__dut__DOT__dirty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9742731907466517977ull);
    vlSelf->submem_tb__DOT__dut__DOT__hit = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8363876379411652143ull);
    vlSelf->submem_tb__DOT__dut__DOT__spill_hit = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 877590463201326268ull);
    vlSelf->submem_tb__DOT__dut__DOT__spill_dirty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4853406917656558863ull);
    vlSelf->submem_tb__DOT__dut__DOT__line_spill = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12170828675503789457ull);
    vlSelf->submem_tb__DOT__dut__DOT__evict_addr = VL_SCOPED_RAND_RESET_I(27, __VscopeHash, 6469160380517182540ull);
    vlSelf->submem_tb__DOT__dut__DOT__spill_evict_addr = VL_SCOPED_RAND_RESET_I(27, __VscopeHash, 639515509480906996ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_hit = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17745831830835582123ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_spill_dirty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1893222119735253556ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_spill_hit = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7756938430376686235ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_mem_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16725111948860671121ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_entry = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 940386269881391324ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_addr = VL_SCOPED_RAND_RESET_I(27, __VscopeHash, 7346228702175296352ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_evict_addr = VL_SCOPED_RAND_RESET_I(27, __VscopeHash, 12151087298331217175ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_data_in = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13034837632549121217ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_bw = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 4862648234889449022ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_line_spill = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13518813791330266278ull);
    vlSelf->submem_tb__DOT__dut__DOT__last_flush = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6173070564328566880ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_miss = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9649597048978487344ull);
    vlSelf->submem_tb__DOT__dut__DOT__miss_addr = VL_SCOPED_RAND_RESET_I(27, __VscopeHash, 2463316045254126050ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__flush = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11931266406326768565ull);
    for (int __Vi0 = 0; __Vi0 < 1024; ++__Vi0) {
        vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even[__Vi0] = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 15969442300473685183ull);
    }
    for (int __Vi0 = 0; __Vi0 < 1024; ++__Vi0) {
        vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd[__Vi0] = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 12594782633092156808ull);
    }
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18379856240608796802ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__actual_flush = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6325628335259235749ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_primary = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 11935655371660992355ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_index = VL_SCOPED_RAND_RESET_I(11, __VscopeHash, 14572282649395151872ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_tag = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 10062462262847223057ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_spill = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 843882557743937728ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 17015648190753178344ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 8261724432625276454ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__data_out_rotated = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 16975620540073056407ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_we = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17600998015199260043ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_waddr = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 320108876883299532ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_wdata = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 7741116663323033174ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_we = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8445421073430093660ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_waddr = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 11421666533913649949ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_wdata = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 7500946581042263046ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 9640567347017004878ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__ena = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 868395269397646666ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11485566037893742249ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 15183387450019103058ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__enb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12797521728288040539ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15346004662562580492ull);
    for (int __Vi0 = 0; __Vi0 < 16384; ++__Vi0) {
        vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 9181347177536836631ull);
    }
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16992480487528907781ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__j = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7530626621028701126ull);
    vlSelf->submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__k = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1627959075043118558ull);
    for (int __Vi0 = 0; __Vi0 < 131072; ++__Vi0) {
        vlSelf->submem_tb__DOT__slave__DOT__ram[__Vi0] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 6766860153658852423ull);
    }
    vlSelf->submem_tb__DOT__slave__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13598350924945640178ull);
    vlSelf->submem_tb__DOT__slave__DOT__i64 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 2662461644110187428ull);
    vlSelf->submem_tb__DOT__slave__DOT__rng = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1057690519099043963ull);
    vlSelf->submem_tb__DOT__slave__DOT__rng_next1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8275140730598681697ull);
    vlSelf->submem_tb__DOT__slave__DOT__rng_next2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2960067511795319640ull);
    vlSelf->submem_tb__DOT__slave__DOT__rstate = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2572157156299810189ull);
    vlSelf->submem_tb__DOT__slave__DOT__raddr_q = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4239348905405179095ull);
    vlSelf->submem_tb__DOT__slave__DOT__rbeat = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 4174348086462561429ull);
    vlSelf->submem_tb__DOT__slave__DOT__rdelay = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 9200186458774701415ull);
    vlSelf->submem_tb__DOT__slave__DOT__aw_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6360194343567855599ull);
    vlSelf->submem_tb__DOT__slave__DOT__waddr_q = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4664931593495165023ull);
    vlSelf->submem_tb__DOT__slave__DOT__wbeat = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 17765746417886675448ull);
    vlSelf->submem_tb__DOT__slave__DOT__w_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3929384344733673871ull);
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->submem_tb__DOT__slave__DOT__wbuf[__Vi0] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 15383297182530088826ull);
    }
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->submem_tb__DOT__slave__DOT__wstrb_q[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 12060159068806254211ull);
    }
    vlSelf->submem_tb__DOT__slave__DOT__bdelay = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 14869567813686080011ull);
    vlSelf->submem_tb__DOT__slave__DOT__b_pending = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8380330585422258255ull);
    vlSelf->submem_tb__DOT__slave__DOT__awdelay = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 5315764262832042024ull);
    vlSelf->submem_tb__DOT__slave__DOT__aw_late = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17350152565645291809ull);
    vlSelf->submem_tb__DOT__slave__DOT__wi = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9714934145931661794ull);
    vlSelf->submem_tb__DOT__slave__DOT__wb = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13483687948972773223ull);
    vlSelf->submem_tb__DOT__amc_instance__DOT__state = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 205815049351739570ull);
    vlSelf->submem_tb__DOT__amc_instance__DOT__cntr = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 14805894181818541496ull);
    vlSelf->__VdfgRegularize_h6e95ff9d_0_7 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_8 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_9 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_10 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rst__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__addr__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__mem_read__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__mem_write__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__bw__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__data_in__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__flush__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rng_seed__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__bd_addr__0 = 0;
    vlSelf->__VicoDidInit = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__1 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 5; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
