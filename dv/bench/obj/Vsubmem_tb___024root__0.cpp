// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsubmem_tb.h for the primary calling header

#include "Vsubmem_tb__pch.h"

bool Vsubmem_tb___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 2> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___trigger_anySet__ico\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((2U > n));
    return (0U);
}

void Vsubmem_tb___024root___ico_sequent__TOP__1(Vsubmem_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___ico_sequent__TOP__1\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*26:0*/ __VdfgRegularize_h6e95ff9d_0_15;
    __VdfgRegularize_h6e95ff9d_0_15 = 0;
    // Body
    __VdfgRegularize_h6e95ff9d_0_15 = ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))
                                        ? (0x07ffffc0U 
                                           & vlSelfRef.submem_tb__DOT__dut__DOT__evict_addr)
                                        : (0x07ffffc0U 
                                           & vlSelfRef.addr));
    if ((0x00000010U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
            = (0x07ffffffU & vlSelfRef.addr);
        vlSelfRef.submem_tb__DOT__s_amc_addr = (0x07ffffc0U 
                                                & vlSelfRef.addr);
    } else if ((8U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
            = (0x07ffffffU & vlSelfRef.addr);
        vlSelfRef.submem_tb__DOT__s_amc_addr = (0x07ffffc0U 
                                                & vlSelfRef.addr);
    } else if ((4U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
        if ((2U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                = (0x07ffffffU & ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))
                                   ? (((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__flush_line) 
                                       << 6U) + (0x00000038U 
                                                 & (((IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr) 
                                                     + (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_in_valid)) 
                                                    << 3U)))
                                   : ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__flush_line) 
                                      << 6U)));
            vlSelfRef.submem_tb__DOT__s_amc_addr = __VdfgRegularize_h6e95ff9d_0_15;
        } else if ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                = (0x07ffffffU & vlSelfRef.addr);
            vlSelfRef.submem_tb__DOT__s_amc_addr = 
                (0x07ffffc0U & vlSelfRef.addr);
        } else {
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                = (0x07ffffffU & ((0x07ffffc0U & ((IData)(0x00000040U) 
                                                  + vlSelfRef.submem_tb__DOT__dut__DOT__miss_addr)) 
                                  + ((IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr) 
                                     << 3U)));
            vlSelfRef.submem_tb__DOT__s_amc_addr = 
                (0x07ffffc0U & ((IData)(0x00000040U) 
                                + vlSelfRef.submem_tb__DOT__dut__DOT__miss_addr));
        }
    } else if ((2U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
        if ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                = (0x07ffffffU & ((0x07ffffc0U & vlSelfRef.submem_tb__DOT__dut__DOT__miss_addr) 
                                  + ((IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr) 
                                     << 3U)));
            vlSelfRef.submem_tb__DOT__s_amc_addr = 
                (0x07ffffc0U & vlSelfRef.submem_tb__DOT__dut__DOT__miss_addr);
        } else {
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                = (0x07ffffffU & ((0x07ffffc0U & vlSelfRef.submem_tb__DOT__dut__DOT__spill_evict_addr) 
                                  + (0x00000038U & 
                                     (((IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr) 
                                       + (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_in_valid)) 
                                      << 3U))));
            vlSelfRef.submem_tb__DOT__s_amc_addr = 
                (0x07ffffc0U & vlSelfRef.submem_tb__DOT__dut__DOT__spill_evict_addr);
        }
    } else {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
            = (0x07ffffffU & ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))
                               ? ((0x07ffffc0U & vlSelfRef.submem_tb__DOT__dut__DOT__evict_addr) 
                                  + (0x00000038U & 
                                     (((IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr) 
                                       + (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_in_valid)) 
                                      << 3U))) : vlSelfRef.addr));
        vlSelfRef.submem_tb__DOT__s_amc_addr = __VdfgRegularize_h6e95ff9d_0_15;
    }
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
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_9 = ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry) 
                                                | (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__actual_flush));
}

void Vsubmem_tb___024root___ico_comb__TOP__3(Vsubmem_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___ico_comb__TOP__3\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
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
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_10 = ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_mem_write) 
                                                 & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_hit));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_8) 
           & (- (IData)(((~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry)) 
                         & ((~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__actual_flush)) 
                            & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_10))))));
}

void Vsubmem_tb___024root___eval_ico(Vsubmem_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___eval_ico\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((0x0000000000000200ULL & vlSelfRef.__VicoTriggered[0U])) {
        {
            // Inlined CFunc: _ico_sequent__TOP__0
            vlSelfRef.bd_data = vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [(0x0001ffffU & (vlSelfRef.bd_addr 
                                 >> 3U))];
        }
    }
    if ((4ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vsubmem_tb___024root___ico_sequent__TOP__1(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
    }
    if ((0x0000000000000040ULL & vlSelfRef.__VicoTriggered[0U])) {
        {
            // Inlined CFunc: _ico_sequent__TOP__2
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
                = vlSelfRef.data_in;
            if ((0x00000010U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
                    = vlSelfRef.data_in;
            } else if ((8U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
                    = vlSelfRef.data_in;
            } else if ((4U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                if ((1U & (~ ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state) 
                              >> 1U)))) {
                    vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
                        = ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))
                            ? vlSelfRef.data_in : vlSelfRef.submem_tb__DOT__rdata);
                }
            } else if ((2U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                if ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                    vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
                        = vlSelfRef.submem_tb__DOT__rdata;
                }
            } else if ((1U & (~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)))) {
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
                    = vlSelfRef.data_in;
            }
        }
    }
    if ((0x0000000000000020ULL & vlSelfRef.__VicoTriggered[0U])) {
        {
            // Inlined CFunc: _ico_sequent__TOP__3
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw = 3U;
            if ((0x00000010U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw = 3U;
            } else if ((8U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw = 3U;
            } else if ((4U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                if ((1U & (~ ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state) 
                              >> 1U)))) {
                    if ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                        vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw = 3U;
                    }
                }
            } else if ((1U & (~ ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state) 
                                 >> 1U)))) {
                if ((1U & (~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)))) {
                    vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw 
                        = vlSelfRef.bw;
                }
            }
        }
    }
    if ((0x0000000000000044ULL & vlSelfRef.__VicoTriggered[0U])) {
        {
            // Inlined CFunc: _ico_comb__TOP__0
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb 
                = VL_SHIFTR_QQI(64,64,7, vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in, 
                                (0x00000078U & (((IData)(8U) 
                                                 - 
                                                 (7U 
                                                  & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)) 
                                                << 3U)));
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina 
                = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_9)
                    ? vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in
                    : (vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
                       << (0x00000038U & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                          << 3U))));
        }
    }
    if ((0x0000000000000024ULL & vlSelfRef.__VicoTriggered[0U])) {
        {
            // Inlined CFunc: _ico_comb__TOP__1
            vlSelfRef.__VdfgRegularize_h6e95ff9d_0_8 
                = ((0x000000ffU & (0xff0f0301U >> ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw) 
                                                   << 3U))) 
                   >> (0x0000000fU & ((IData)(8U) - 
                                      (7U & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr))));
            vlSelfRef.data_out = ((((2U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw))
                                     ? (((QData)((IData)(
                                                         ((IData)(
                                                                  (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__data_out_rotated 
                                                                   >> 0x00000020U)) 
                                                          & (- (IData)(
                                                                       (1U 
                                                                        & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw))))))) 
                                         << 0x00000018U) 
                                        | (QData)((IData)(
                                                          (0x00ffffffU 
                                                           & (IData)(
                                                                     (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__data_out_rotated 
                                                                      >> 8U))))))
                                     : (QData)((IData)(
                                                       (0x000000ffU 
                                                        & ((- (IData)(
                                                                      (1U 
                                                                       & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw)))) 
                                                           & (IData)(
                                                                     (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__data_out_rotated 
                                                                      >> 8U))))))) 
                                   << 8U) | (QData)((IData)(
                                                            (0x000000ffU 
                                                             & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__data_out_rotated)))));
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_line_spill 
                = (IData)(((0x00000038U == (0x00000038U 
                                            & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)) 
                           & (0U != (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_8))));
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_tag 
                = (0x000003ffU & ((vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                   >> 0x00000011U) 
                                  + ((0x000007ffU == 
                                      (0x000007ffU 
                                       & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                          >> 6U))) 
                                     & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_line_spill))));
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_index 
                = (0x000007ffU & ((vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                   >> 6U) + (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_line_spill)));
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
        }
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    if ((0x000000000000002cULL & vlSelfRef.__VicoTriggered[0U])) {
        {
            // Inlined CFunc: _ico_comb__TOP__2
            vlSelfRef.__VdfgRegularize_h6e95ff9d_0_7 
                = (1U & ((4U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))
                          ? (((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state) 
                              >> 1U) & ((~ (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_in_last)) 
                                        & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)))
                          : ((2U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))
                              ? (~ ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state) 
                                    | (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_in_last)))
                              : ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))
                                  ? (~ (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_in_last))
                                  : ((~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_miss)) 
                                     & (IData)(vlSelfRef.mem_read))))));
        }
    }
    if ((0x0000000000000034ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vsubmem_tb___024root___ico_comb__TOP__3(vlSelf);
        vlSelfRef.__Vm_traceActivity[3U] = 1U;
    }
    if ((0x000000000000003cULL & vlSelfRef.__VicoTriggered[0U])) {
        {
            // Inlined CFunc: _ico_comb__TOP__4
            CData/*0:0*/ __Vinline_0__ico_comb__TOP__4___VdfgRegularize_h6e95ff9d_0_13;
            __Vinline_0__ico_comb__TOP__4___VdfgRegularize_h6e95ff9d_0_13 = 0;
            __Vinline_0__ico_comb__TOP__4___VdfgRegularize_h6e95ff9d_0_13 
                = ((IData)(((0U == (0x18U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) 
                            & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_7))) 
                   | (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_mem_write));
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea 
                = (0x000000ffU & (((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry)
                                    ? (- (IData)((1U 
                                                  & ((0U 
                                                      != 
                                                      (0x18U 
                                                       & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) 
                                                     | (~ (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_7))))))
                                    : (((0xff0f0301U 
                                         >> ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw) 
                                             << 3U)) 
                                        << (7U & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)) 
                                       & (- (IData)((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_10))))) 
                                  & (- (IData)((1U 
                                                & (~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__actual_flush)))))));
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__ena 
                = (((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_hit) 
                    | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_9)) 
                   & __Vinline_0__ico_comb__TOP__4___VdfgRegularize_h6e95ff9d_0_13);
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__enb 
                = ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_spill_hit) 
                   & ((0U != (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_8)) 
                      & __Vinline_0__ico_comb__TOP__4___VdfgRegularize_h6e95ff9d_0_13));
        }
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsubmem_tb___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vsubmem_tb___024root___eval_phase__ico(Vsubmem_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___eval_phase__ico\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__ico
        vlSelfRef.__VicoTriggered[0U] = (QData)((IData)(
                                                        ((((vlSelfRef.bd_addr 
                                                            != vlSelfRef.__Vtrigprevexpr___TOP__bd_addr__0) 
                                                           << 9U) 
                                                          | ((vlSelfRef.rng_seed 
                                                              != vlSelfRef.__Vtrigprevexpr___TOP__rng_seed__0) 
                                                             << 8U)) 
                                                         | (((((((IData)(vlSelfRef.flush) 
                                                                 != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__flush__0)) 
                                                                << 3U) 
                                                               | ((vlSelfRef.data_in 
                                                                   != vlSelfRef.__Vtrigprevexpr___TOP__data_in__0) 
                                                                  << 2U)) 
                                                              | ((((IData)(vlSelfRef.bw) 
                                                                   != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__bw__0)) 
                                                                  << 1U) 
                                                                 | ((IData)(vlSelfRef.mem_write) 
                                                                    != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__mem_write__0)))) 
                                                             << 4U) 
                                                            | (((((IData)(vlSelfRef.mem_read) 
                                                                  != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__mem_read__0)) 
                                                                 << 3U) 
                                                                | ((vlSelfRef.addr 
                                                                    != vlSelfRef.__Vtrigprevexpr___TOP__addr__0) 
                                                                   << 2U)) 
                                                               | ((((IData)(vlSelfRef.rst) 
                                                                    != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__rst__0)) 
                                                                   << 1U) 
                                                                  | ((IData)(vlSelfRef.clk) 
                                                                     != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0))))))));
        vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
        vlSelfRef.__Vtrigprevexpr___TOP__rst__0 = vlSelfRef.rst;
        vlSelfRef.__Vtrigprevexpr___TOP__addr__0 = vlSelfRef.addr;
        vlSelfRef.__Vtrigprevexpr___TOP__mem_read__0 
            = vlSelfRef.mem_read;
        vlSelfRef.__Vtrigprevexpr___TOP__mem_write__0 
            = vlSelfRef.mem_write;
        vlSelfRef.__Vtrigprevexpr___TOP__bw__0 = vlSelfRef.bw;
        vlSelfRef.__Vtrigprevexpr___TOP__data_in__0 
            = vlSelfRef.data_in;
        vlSelfRef.__Vtrigprevexpr___TOP__flush__0 = vlSelfRef.flush;
        vlSelfRef.__Vtrigprevexpr___TOP__rng_seed__0 
            = vlSelfRef.rng_seed;
        vlSelfRef.__Vtrigprevexpr___TOP__bd_addr__0 
            = vlSelfRef.bd_addr;
        if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.__VicoDidInit)))))) {
            vlSelfRef.__VicoDidInit = 1U;
            vlSelfRef.__VicoTriggered[0U] = (1ULL | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (2ULL | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (4ULL | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (8ULL | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (0x0000000000000010ULL 
                                             | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (0x0000000000000020ULL 
                                             | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (0x0000000000000040ULL 
                                             | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (0x0000000000000080ULL 
                                             | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (0x0000000000000100ULL 
                                             | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (0x0000000000000200ULL 
                                             | vlSelfRef.__VicoTriggered[0U]);
        }
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vsubmem_tb___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = Vsubmem_tb___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vsubmem_tb___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

bool Vsubmem_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___trigger_anySet__act\n"); );
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

void Vsubmem_tb___024root___nba_sequent__TOP__0(Vsubmem_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___nba_sequent__TOP__0\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_13;
    __VdfgRegularize_h6e95ff9d_0_13 = 0;
    IData/*26:0*/ __VdfgRegularize_h6e95ff9d_0_15;
    __VdfgRegularize_h6e95ff9d_0_15 = 0;
    CData/*4:0*/ __Vdly__submem_tb__DOT__dut__DOT__state;
    __Vdly__submem_tb__DOT__dut__DOT__state = 0;
    CData/*0:0*/ __Vdly__busy;
    __Vdly__busy = 0;
    SData/*10:0*/ __Vdly__submem_tb__DOT__dut__DOT__flush_line;
    __Vdly__submem_tb__DOT__dut__DOT__flush_line = 0;
    CData/*0:0*/ __Vdly__flush_done;
    __Vdly__flush_done = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__dut__DOT__hit;
    __Vdly__submem_tb__DOT__dut__DOT__hit = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__dut__DOT__spill_hit;
    __Vdly__submem_tb__DOT__dut__DOT__spill_hit = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__dut__DOT__spill_dirty;
    __Vdly__submem_tb__DOT__dut__DOT__spill_dirty = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__dut__DOT__line_spill;
    __Vdly__submem_tb__DOT__dut__DOT__line_spill = 0;
    CData/*1:0*/ __Vdly__submem_tb__DOT__slave__DOT__rstate;
    __Vdly__submem_tb__DOT__slave__DOT__rstate = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__arready;
    __Vdly__submem_tb__DOT__arready = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__rvalid;
    __Vdly__submem_tb__DOT__rvalid = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__rlast;
    __Vdly__submem_tb__DOT__rlast = 0;
    CData/*2:0*/ __Vdly__submem_tb__DOT__slave__DOT__rbeat;
    __Vdly__submem_tb__DOT__slave__DOT__rbeat = 0;
    IData/*31:0*/ __Vdly__submem_tb__DOT__slave__DOT__raddr_q;
    __Vdly__submem_tb__DOT__slave__DOT__raddr_q = 0;
    CData/*2:0*/ __Vdly__submem_tb__DOT__slave__DOT__rdelay;
    __Vdly__submem_tb__DOT__slave__DOT__rdelay = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__slave__DOT__aw_done;
    __Vdly__submem_tb__DOT__slave__DOT__aw_done = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__awready;
    __Vdly__submem_tb__DOT__awready = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__wready;
    __Vdly__submem_tb__DOT__wready = 0;
    CData/*2:0*/ __Vdly__submem_tb__DOT__slave__DOT__wbeat;
    __Vdly__submem_tb__DOT__slave__DOT__wbeat = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__slave__DOT__w_done;
    __Vdly__submem_tb__DOT__slave__DOT__w_done = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__bvalid;
    __Vdly__submem_tb__DOT__bvalid = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__slave__DOT__b_pending;
    __Vdly__submem_tb__DOT__slave__DOT__b_pending = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__slave__DOT__aw_late;
    __Vdly__submem_tb__DOT__slave__DOT__aw_late = 0;
    CData/*2:0*/ __Vdly__submem_tb__DOT__slave__DOT__awdelay;
    __Vdly__submem_tb__DOT__slave__DOT__awdelay = 0;
    IData/*31:0*/ __Vdly__submem_tb__DOT__slave__DOT__waddr_q;
    __Vdly__submem_tb__DOT__slave__DOT__waddr_q = 0;
    CData/*3:0*/ __Vdly__submem_tb__DOT__slave__DOT__bdelay;
    __Vdly__submem_tb__DOT__slave__DOT__bdelay = 0;
    CData/*2:0*/ __Vdly__submem_tb__DOT__amc_instance__DOT__state;
    __Vdly__submem_tb__DOT__amc_instance__DOT__state = 0;
    CData/*2:0*/ __Vdly__submem_tb__DOT__amc_instance__DOT__cntr;
    __Vdly__submem_tb__DOT__amc_instance__DOT__cntr = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__arvalid;
    __Vdly__submem_tb__DOT__arvalid = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__awvalid;
    __Vdly__submem_tb__DOT__awvalid = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__wvalid;
    __Vdly__submem_tb__DOT__wvalid = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__rready;
    __Vdly__submem_tb__DOT__rready = 0;
    CData/*0:0*/ __Vdly__submem_tb__DOT__bready;
    __Vdly__submem_tb__DOT__bready = 0;
    SData/*11:0*/ __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd__v0;
    __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd__v0 = 0;
    SData/*9:0*/ __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd__v0;
    __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd__v0 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd__v0;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd__v0 = 0;
    SData/*11:0*/ __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even__v0;
    __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even__v0 = 0;
    SData/*9:0*/ __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even__v0;
    __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even__v0 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even__v0;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even__v0 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v0;
    __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v0 = 0;
    SData/*13:0*/ __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v0;
    __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v0;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v0 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v1;
    __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v1 = 0;
    SData/*13:0*/ __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v1;
    __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v1 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v1;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v1 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v2;
    __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v2 = 0;
    SData/*13:0*/ __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v2;
    __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v2 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v2;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v2 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v3;
    __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v3 = 0;
    SData/*13:0*/ __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v3;
    __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v3 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v3;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v3 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v4;
    __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v4 = 0;
    SData/*13:0*/ __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v4;
    __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v4 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v4;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v4 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v5;
    __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v5 = 0;
    SData/*13:0*/ __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v5;
    __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v5 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v5;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v5 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v6;
    __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v6 = 0;
    SData/*13:0*/ __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v6;
    __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v6 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v6;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v6 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v7;
    __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v7 = 0;
    SData/*13:0*/ __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v7;
    __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v7 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v7;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v7 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v8;
    __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v8 = 0;
    SData/*13:0*/ __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v8;
    __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v8 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v8;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v8 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v9;
    __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v9 = 0;
    SData/*13:0*/ __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v9;
    __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v9 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v9;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v9 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v10;
    __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v10 = 0;
    SData/*13:0*/ __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v10;
    __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v10 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v10;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v10 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v11;
    __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v11 = 0;
    SData/*13:0*/ __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v11;
    __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v11 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v11;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v11 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v12;
    __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v12 = 0;
    SData/*13:0*/ __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v12;
    __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v12 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v12;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v12 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v13;
    __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v13 = 0;
    SData/*13:0*/ __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v13;
    __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v13 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v13;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v13 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v14;
    __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v14 = 0;
    SData/*13:0*/ __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v14;
    __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v14 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v14;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v14 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v15;
    __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v15 = 0;
    SData/*13:0*/ __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v15;
    __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v15 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v15;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v15 = 0;
    QData/*63:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__wbuf__v0;
    __VdlyVal__submem_tb__DOT__slave__DOT__wbuf__v0 = 0;
    CData/*2:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__wbuf__v0;
    __VdlyDim0__submem_tb__DOT__slave__DOT__wbuf__v0 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__wbuf__v0;
    __VdlySet__submem_tb__DOT__slave__DOT__wbuf__v0 = 0;
    CData/*2:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__wstrb_q__v0;
    __VdlyDim0__submem_tb__DOT__slave__DOT__wstrb_q__v0 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v0;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v0 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v0;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v0 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v0;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v0 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v1;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v1 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v1;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v1 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v1;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v1 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v2;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v2 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v2;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v2 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v2;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v2 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v3;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v3 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v3;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v3 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v3;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v3 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v4;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v4 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v4;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v4 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v4;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v4 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v5;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v5 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v5;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v5 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v5;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v5 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v6;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v6 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v6;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v6 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v6;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v6 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v7;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v7 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v7;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v7 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v7;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v7 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v8;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v8 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v8;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v8 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v8;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v8 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v9;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v9 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v9;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v9 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v9;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v9 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v10;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v10 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v10;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v10 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v10;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v10 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v11;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v11 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v11;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v11 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v11;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v11 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v12;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v12 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v12;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v12 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v12;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v12 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v13;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v13 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v13;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v13 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v13;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v13 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v14;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v14 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v14;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v14 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v14;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v14 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v15;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v15 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v15;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v15 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v15;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v15 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v16;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v16 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v16;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v16 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v16;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v16 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v17;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v17 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v17;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v17 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v17;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v17 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v18;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v18 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v18;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v18 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v18;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v18 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v19;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v19 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v19;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v19 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v19;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v19 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v20;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v20 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v20;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v20 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v20;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v20 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v21;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v21 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v21;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v21 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v21;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v21 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v22;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v22 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v22;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v22 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v22;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v22 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v23;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v23 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v23;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v23 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v23;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v23 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v24;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v24 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v24;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v24 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v24;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v24 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v25;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v25 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v25;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v25 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v25;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v25 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v26;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v26 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v26;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v26 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v26;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v26 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v27;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v27 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v27;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v27 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v27;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v27 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v28;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v28 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v28;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v28 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v28;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v28 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v29;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v29 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v29;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v29 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v29;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v29 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v30;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v30 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v30;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v30 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v30;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v30 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v31;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v31 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v31;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v31 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v31;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v31 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v32;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v32 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v32;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v32 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v32;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v32 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v33;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v33 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v33;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v33 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v33;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v33 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v34;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v34 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v34;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v34 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v34;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v34 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v35;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v35 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v35;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v35 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v35;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v35 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v36;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v36 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v36;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v36 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v36;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v36 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v37;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v37 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v37;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v37 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v37;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v37 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v38;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v38 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v38;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v38 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v38;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v38 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v39;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v39 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v39;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v39 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v39;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v39 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v40;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v40 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v40;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v40 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v40;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v40 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v41;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v41 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v41;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v41 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v41;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v41 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v42;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v42 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v42;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v42 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v42;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v42 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v43;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v43 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v43;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v43 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v43;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v43 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v44;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v44 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v44;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v44 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v44;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v44 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v45;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v45 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v45;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v45 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v45;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v45 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v46;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v46 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v46;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v46 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v46;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v46 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v47;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v47 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v47;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v47 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v47;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v47 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v48;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v48 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v48;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v48 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v48;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v48 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v49;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v49 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v49;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v49 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v49;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v49 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v50;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v50 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v50;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v50 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v50;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v50 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v51;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v51 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v51;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v51 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v51;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v51 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v52;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v52 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v52;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v52 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v52;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v52 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v53;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v53 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v53;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v53 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v53;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v53 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v54;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v54 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v54;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v54 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v54;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v54 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v55;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v55 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v55;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v55 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v55;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v55 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v56;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v56 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v56;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v56 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v56;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v56 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v57;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v57 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v57;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v57 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v57;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v57 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v58;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v58 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v58;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v58 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v58;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v58 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v59;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v59 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v59;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v59 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v59;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v59 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v60;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v60 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v60;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v60 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v60;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v60 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v61;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v61 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v61;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v61 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v61;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v61 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v62;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v62 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v62;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v62 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v62;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v62 = 0;
    CData/*7:0*/ __VdlyVal__submem_tb__DOT__slave__DOT__ram__v63;
    __VdlyVal__submem_tb__DOT__slave__DOT__ram__v63 = 0;
    IData/*16:0*/ __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v63;
    __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v63 = 0;
    CData/*0:0*/ __VdlySet__submem_tb__DOT__slave__DOT__ram__v63;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v63 = 0;
    // Body
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd__v0 = 0U;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even__v0 = 0U;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v8 = 0U;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v9 = 0U;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v10 = 0U;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v11 = 0U;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v12 = 0U;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v13 = 0U;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v14 = 0U;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v15 = 0U;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v0 = 0U;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v1 = 0U;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v2 = 0U;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v3 = 0U;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v4 = 0U;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v5 = 0U;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v6 = 0U;
    __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v7 = 0U;
    __Vdly__submem_tb__DOT__arvalid = vlSelfRef.submem_tb__DOT__arvalid;
    __Vdly__submem_tb__DOT__awvalid = vlSelfRef.submem_tb__DOT__awvalid;
    __Vdly__submem_tb__DOT__bready = vlSelfRef.submem_tb__DOT__bready;
    __Vdly__submem_tb__DOT__rready = vlSelfRef.submem_tb__DOT__rready;
    __Vdly__submem_tb__DOT__slave__DOT__rstate = vlSelfRef.submem_tb__DOT__slave__DOT__rstate;
    __Vdly__submem_tb__DOT__arready = vlSelfRef.submem_tb__DOT__arready;
    __Vdly__submem_tb__DOT__slave__DOT__rbeat = vlSelfRef.submem_tb__DOT__slave__DOT__rbeat;
    __Vdly__submem_tb__DOT__slave__DOT__raddr_q = vlSelfRef.submem_tb__DOT__slave__DOT__raddr_q;
    __Vdly__submem_tb__DOT__slave__DOT__rdelay = vlSelfRef.submem_tb__DOT__slave__DOT__rdelay;
    __Vdly__submem_tb__DOT__rlast = vlSelfRef.submem_tb__DOT__rlast;
    __Vdly__submem_tb__DOT__amc_instance__DOT__cntr 
        = vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr;
    __Vdly__submem_tb__DOT__wvalid = vlSelfRef.submem_tb__DOT__wvalid;
    __Vdly__submem_tb__DOT__rvalid = vlSelfRef.submem_tb__DOT__rvalid;
    __Vdly__submem_tb__DOT__amc_instance__DOT__state 
        = vlSelfRef.submem_tb__DOT__amc_instance__DOT__state;
    __Vdly__busy = vlSelfRef.busy;
    __Vdly__flush_done = vlSelfRef.flush_done;
    __Vdly__submem_tb__DOT__dut__DOT__hit = vlSelfRef.submem_tb__DOT__dut__DOT__hit;
    __Vdly__submem_tb__DOT__dut__DOT__spill_hit = vlSelfRef.submem_tb__DOT__dut__DOT__spill_hit;
    __Vdly__submem_tb__DOT__dut__DOT__spill_dirty = vlSelfRef.submem_tb__DOT__dut__DOT__spill_dirty;
    __Vdly__submem_tb__DOT__dut__DOT__line_spill = vlSelfRef.submem_tb__DOT__dut__DOT__line_spill;
    __Vdly__submem_tb__DOT__dut__DOT__flush_line = vlSelfRef.submem_tb__DOT__dut__DOT__flush_line;
    __Vdly__submem_tb__DOT__dut__DOT__state = vlSelfRef.submem_tb__DOT__dut__DOT__state;
    __Vdly__submem_tb__DOT__slave__DOT__aw_done = vlSelfRef.submem_tb__DOT__slave__DOT__aw_done;
    __Vdly__submem_tb__DOT__awready = vlSelfRef.submem_tb__DOT__awready;
    __Vdly__submem_tb__DOT__slave__DOT__wbeat = vlSelfRef.submem_tb__DOT__slave__DOT__wbeat;
    __Vdly__submem_tb__DOT__slave__DOT__w_done = vlSelfRef.submem_tb__DOT__slave__DOT__w_done;
    __Vdly__submem_tb__DOT__bvalid = vlSelfRef.submem_tb__DOT__bvalid;
    __Vdly__submem_tb__DOT__slave__DOT__b_pending = vlSelfRef.submem_tb__DOT__slave__DOT__b_pending;
    __Vdly__submem_tb__DOT__slave__DOT__aw_late = vlSelfRef.submem_tb__DOT__slave__DOT__aw_late;
    __Vdly__submem_tb__DOT__slave__DOT__awdelay = vlSelfRef.submem_tb__DOT__slave__DOT__awdelay;
    __Vdly__submem_tb__DOT__slave__DOT__waddr_q = vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q;
    __Vdly__submem_tb__DOT__slave__DOT__bdelay = vlSelfRef.submem_tb__DOT__slave__DOT__bdelay;
    __VdlySet__submem_tb__DOT__slave__DOT__wbuf__v0 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v0 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v1 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v2 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v3 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v4 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v5 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v6 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v7 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v8 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v9 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v10 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v11 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v12 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v13 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v14 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v15 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v16 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v17 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v18 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v19 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v20 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v21 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v22 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v23 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v24 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v25 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v26 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v27 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v28 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v29 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v30 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v31 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v32 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v33 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v34 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v35 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v36 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v37 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v38 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v39 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v40 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v41 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v42 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v43 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v44 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v45 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v46 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v47 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v48 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v49 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v50 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v51 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v52 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v53 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v54 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v55 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v56 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v57 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v58 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v59 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v60 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v61 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v62 = 0U;
    __VdlySet__submem_tb__DOT__slave__DOT__ram__v63 = 0U;
    __Vdly__submem_tb__DOT__wready = vlSelfRef.submem_tb__DOT__wready;
    if (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__ena) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__j = 8U;
        if ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea))) {
            __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v0 
                = (0x000000ffU & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina));
            __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v0 
                = (0x00003fffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  >> 3U));
            __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v0 = 1U;
        }
        if ((2U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea))) {
            __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v1 
                = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina 
                                          >> 8U)));
            __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v1 
                = (0x00003fffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  >> 3U));
            __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v1 = 1U;
        }
        if ((4U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea))) {
            __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v2 
                = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina 
                                          >> 0x10U)));
            __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v2 
                = (0x00003fffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  >> 3U));
            __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v2 = 1U;
        }
        if ((8U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea))) {
            __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v3 
                = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina 
                                          >> 0x18U)));
            __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v3 
                = (0x00003fffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  >> 3U));
            __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v3 = 1U;
        }
        if ((0x00000010U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea))) {
            __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v4 
                = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina 
                                          >> 0x20U)));
            __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v4 
                = (0x00003fffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  >> 3U));
            __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v4 = 1U;
        }
        if ((0x00000020U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea))) {
            __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v5 
                = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina 
                                          >> 0x28U)));
            __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v5 
                = (0x00003fffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  >> 3U));
            __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v5 = 1U;
        }
        if ((0x00000040U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea))) {
            __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v6 
                = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina 
                                          >> 0x30U)));
            __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v6 
                = (0x00003fffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  >> 3U));
            __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v6 = 1U;
        }
        if ((0x00000080U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea))) {
            __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v7 
                = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina 
                                          >> 0x38U)));
            __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v7 
                = (0x00003fffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                  >> 3U));
            __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v7 = 1U;
        }
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta 
            = ((0xffffffffffffff00ULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta) 
               | (IData)((IData)((0x000000ffU & ((1U 
                                                  & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea))
                                                  ? (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina)
                                                  : (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                                                            [
                                                            (0x00003fffU 
                                                             & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                                >> 3U))]))))));
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta 
            = ((0xffffffffffff00ffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta) 
               | ((QData)((IData)((0x000000ffU & ((2U 
                                                   & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea))
                                                   ? (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina 
                                                              >> 8U))
                                                   : (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                                                              [
                                                              (0x00003fffU 
                                                               & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                                  >> 3U))] 
                                                              >> 8U)))))) 
                  << 8U));
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta 
            = ((0xffffffffff00ffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta) 
               | ((QData)((IData)((0x000000ffU & ((4U 
                                                   & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea))
                                                   ? (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina 
                                                              >> 0x10U))
                                                   : (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                                                              [
                                                              (0x00003fffU 
                                                               & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                                  >> 3U))] 
                                                              >> 0x10U)))))) 
                  << 0x00000010U));
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta 
            = ((0xffffffff00ffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta) 
               | ((QData)((IData)((0x000000ffU & ((8U 
                                                   & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea))
                                                   ? (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina 
                                                              >> 0x18U))
                                                   : (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                                                              [
                                                              (0x00003fffU 
                                                               & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                                  >> 3U))] 
                                                              >> 0x18U)))))) 
                  << 0x00000018U));
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta 
            = ((0xffffff00ffffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta) 
               | ((QData)((IData)((0x000000ffU & ((0x00000010U 
                                                   & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea))
                                                   ? (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina 
                                                              >> 0x20U))
                                                   : (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                                                              [
                                                              (0x00003fffU 
                                                               & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                                  >> 3U))] 
                                                              >> 0x20U)))))) 
                  << 0x00000020U));
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta 
            = ((0xffff00ffffffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta) 
               | ((QData)((IData)((0x000000ffU & ((0x00000020U 
                                                   & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea))
                                                   ? (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina 
                                                              >> 0x28U))
                                                   : (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                                                              [
                                                              (0x00003fffU 
                                                               & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                                  >> 3U))] 
                                                              >> 0x28U)))))) 
                  << 0x00000028U));
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta 
            = ((0xff00ffffffffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta) 
               | ((QData)((IData)((0x000000ffU & ((0x00000040U 
                                                   & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea))
                                                   ? (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina 
                                                              >> 0x30U))
                                                   : (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                                                              [
                                                              (0x00003fffU 
                                                               & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                                  >> 3U))] 
                                                              >> 0x30U)))))) 
                  << 0x00000030U));
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta 
            = ((0x00ffffffffffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta) 
               | ((QData)((IData)((0x000000ffU & ((0x00000080U 
                                                   & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea))
                                                   ? (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina 
                                                              >> 0x38U))
                                                   : (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                                                              [
                                                              (0x00003fffU 
                                                               & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                                  >> 3U))] 
                                                              >> 0x38U)))))) 
                  << 0x00000038U));
    }
    if (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__enb) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__k = 8U;
        if ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web))) {
            __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v8 
                = (0x000000ffU & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb));
            __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v8 
                = (0x00003fffU & ((IData)(1U) + (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                 >> 3U)));
            __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v8 = 1U;
        }
        if ((2U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web))) {
            __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v9 
                = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb 
                                          >> 8U)));
            __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v9 
                = (0x00003fffU & ((IData)(1U) + (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                 >> 3U)));
            __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v9 = 1U;
        }
        if ((4U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web))) {
            __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v10 
                = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb 
                                          >> 0x10U)));
            __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v10 
                = (0x00003fffU & ((IData)(1U) + (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                 >> 3U)));
            __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v10 = 1U;
        }
        if ((8U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web))) {
            __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v11 
                = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb 
                                          >> 0x18U)));
            __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v11 
                = (0x00003fffU & ((IData)(1U) + (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                 >> 3U)));
            __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v11 = 1U;
        }
        if ((0x00000010U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web))) {
            __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v12 
                = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb 
                                          >> 0x20U)));
            __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v12 
                = (0x00003fffU & ((IData)(1U) + (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                 >> 3U)));
            __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v12 = 1U;
        }
        if ((0x00000020U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web))) {
            __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v13 
                = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb 
                                          >> 0x28U)));
            __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v13 
                = (0x00003fffU & ((IData)(1U) + (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                 >> 3U)));
            __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v13 = 1U;
        }
        if ((0x00000040U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web))) {
            __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v14 
                = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb 
                                          >> 0x30U)));
            __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v14 
                = (0x00003fffU & ((IData)(1U) + (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                 >> 3U)));
            __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v14 = 1U;
        }
        if ((0x00000080U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web))) {
            __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v15 
                = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb 
                                          >> 0x38U)));
            __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v15 
                = (0x00003fffU & ((IData)(1U) + (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                 >> 3U)));
            __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v15 = 1U;
        }
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb 
            = ((0xffffffffffffff00ULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb) 
               | (IData)((IData)((0x000000ffU & ((1U 
                                                  & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web))
                                                  ? (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb)
                                                  : (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                                                            [
                                                            (0x00003fffU 
                                                             & ((IData)(1U) 
                                                                + 
                                                                (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                                 >> 3U)))]))))));
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb 
            = ((0xffffffffffff00ffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb) 
               | ((QData)((IData)((0x000000ffU & ((2U 
                                                   & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web))
                                                   ? (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb 
                                                              >> 8U))
                                                   : (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                                                              [
                                                              (0x00003fffU 
                                                               & ((IData)(1U) 
                                                                  + 
                                                                  (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                                   >> 3U)))] 
                                                              >> 8U)))))) 
                  << 8U));
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb 
            = ((0xffffffffff00ffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb) 
               | ((QData)((IData)((0x000000ffU & ((4U 
                                                   & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web))
                                                   ? (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb 
                                                              >> 0x10U))
                                                   : (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                                                              [
                                                              (0x00003fffU 
                                                               & ((IData)(1U) 
                                                                  + 
                                                                  (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                                   >> 3U)))] 
                                                              >> 0x10U)))))) 
                  << 0x00000010U));
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb 
            = ((0xffffffff00ffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb) 
               | ((QData)((IData)((0x000000ffU & ((8U 
                                                   & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web))
                                                   ? (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb 
                                                              >> 0x18U))
                                                   : (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                                                              [
                                                              (0x00003fffU 
                                                               & ((IData)(1U) 
                                                                  + 
                                                                  (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                                   >> 3U)))] 
                                                              >> 0x18U)))))) 
                  << 0x00000018U));
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb 
            = ((0xffffff00ffffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb) 
               | ((QData)((IData)((0x000000ffU & ((0x00000010U 
                                                   & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web))
                                                   ? (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb 
                                                              >> 0x20U))
                                                   : (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                                                              [
                                                              (0x00003fffU 
                                                               & ((IData)(1U) 
                                                                  + 
                                                                  (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                                   >> 3U)))] 
                                                              >> 0x20U)))))) 
                  << 0x00000020U));
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb 
            = ((0xffff00ffffffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb) 
               | ((QData)((IData)((0x000000ffU & ((0x00000020U 
                                                   & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web))
                                                   ? (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb 
                                                              >> 0x28U))
                                                   : (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                                                              [
                                                              (0x00003fffU 
                                                               & ((IData)(1U) 
                                                                  + 
                                                                  (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                                   >> 3U)))] 
                                                              >> 0x28U)))))) 
                  << 0x00000028U));
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb 
            = ((0xff00ffffffffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb) 
               | ((QData)((IData)((0x000000ffU & ((0x00000040U 
                                                   & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web))
                                                   ? (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb 
                                                              >> 0x30U))
                                                   : (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                                                              [
                                                              (0x00003fffU 
                                                               & ((IData)(1U) 
                                                                  + 
                                                                  (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                                   >> 3U)))] 
                                                              >> 0x30U)))))) 
                  << 0x00000030U));
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb 
            = ((0x00ffffffffffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb) 
               | ((QData)((IData)((0x000000ffU & ((0x00000080U 
                                                   & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web))
                                                   ? (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb 
                                                              >> 0x38U))
                                                   : (IData)(
                                                             (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                                                              [
                                                              (0x00003fffU 
                                                               & ((IData)(1U) 
                                                                  + 
                                                                  (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                                   >> 3U)))] 
                                                              >> 0x38U)))))) 
                  << 0x00000038U));
    }
    if (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_we) {
        __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd__v0 
            = vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_wdata;
        __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd__v0 
            = vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_waddr;
        __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd__v0 = 1U;
    }
    if (vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_we) {
        __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even__v0 
            = vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_wdata;
        __VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even__v0 
            = vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_waddr;
        __VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even__v0 = 1U;
    }
    if (vlSelfRef.rst) {
        __Vdly__submem_tb__DOT__slave__DOT__aw_done = 0U;
        __Vdly__submem_tb__DOT__awready = 0U;
        __Vdly__submem_tb__DOT__wready = 0U;
        __Vdly__submem_tb__DOT__slave__DOT__wbeat = 0U;
        __Vdly__submem_tb__DOT__slave__DOT__w_done = 0U;
        __Vdly__submem_tb__DOT__bvalid = 0U;
        __Vdly__submem_tb__DOT__slave__DOT__b_pending = 0U;
        __Vdly__submem_tb__DOT__slave__DOT__aw_late = 0U;
        __Vdly__submem_tb__DOT__slave__DOT__awdelay = 0U;
        __Vdly__submem_tb__DOT__slave__DOT__rstate = 0U;
        __Vdly__submem_tb__DOT__arready = 0U;
        __Vdly__submem_tb__DOT__rvalid = 0U;
        __Vdly__submem_tb__DOT__rlast = 0U;
        __Vdly__submem_tb__DOT__slave__DOT__rbeat = 0U;
        __Vdly__submem_tb__DOT__dut__DOT__state = 0U;
        __Vdly__busy = 1U;
        __Vdly__submem_tb__DOT__dut__DOT__flush_line = 0U;
        __Vdly__flush_done = 0U;
        vlSelfRef.submem_tb__DOT__slave__DOT__rng = 
            ((0U == vlSelfRef.rng_seed) ? 1U : vlSelfRef.rng_seed);
        __Vdly__submem_tb__DOT__amc_instance__DOT__state = 0U;
        vlSelfRef.submem_tb__DOT__s_amc_busy = 0U;
        vlSelfRef.submem_tb__DOT__s_amc_err = 0U;
        __Vdly__submem_tb__DOT__amc_instance__DOT__cntr = 0U;
        __Vdly__submem_tb__DOT__arvalid = 0U;
        __Vdly__submem_tb__DOT__awvalid = 0U;
        __Vdly__submem_tb__DOT__wvalid = 0U;
        __Vdly__submem_tb__DOT__rready = 0U;
        __Vdly__submem_tb__DOT__bready = 0U;
    } else {
        if (((IData)(vlSelfRef.submem_tb__DOT__awvalid) 
             & (IData)(vlSelfRef.submem_tb__DOT__awready))) {
            if (VL_UNLIKELY((((0U != (0x0000003fU & vlSelfRef.submem_tb__DOT__awaddr)) 
                              | (0x00100000U <= vlSelfRef.submem_tb__DOT__awaddr))))) {
                VL_WRITEF_NX("[%0t] %%Fatal: axi_slave_beh.v:195: Assertion failed in %m: AXI: bad awaddr %h\n",4, 'M',vlSymsp->name(),"submem_tb.slave", 'T',-12
                             , '#',64,VL_TIME_UNITED_Q(1)
                             , '#',32,vlSelfRef.submem_tb__DOT__awaddr);
                VL_STOP_MT("axi_slave_beh.v", 195, "", false);
            }
            __Vdly__submem_tb__DOT__awready = 0U;
            __Vdly__submem_tb__DOT__slave__DOT__waddr_q 
                = vlSelfRef.submem_tb__DOT__awaddr;
            __Vdly__submem_tb__DOT__slave__DOT__aw_done = 1U;
        } else if (((((IData)(vlSelfRef.submem_tb__DOT__awvalid) 
                      & (~ (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__aw_done))) 
                     & (~ (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__b_pending))) 
                    & (~ (IData)(vlSelfRef.submem_tb__DOT__bvalid)))) {
            if (((~ (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__aw_late)) 
                 & (0U == (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__awdelay)))) {
                if ((0U == (7U & (vlSelfRef.submem_tb__DOT__slave__DOT__rng 
                                  >> 5U)))) {
                    __Vdly__submem_tb__DOT__slave__DOT__aw_late = 1U;
                } else {
                    __Vdly__submem_tb__DOT__slave__DOT__awdelay 
                        = (7U & ((IData)(1U) + (3U 
                                                & (vlSelfRef.submem_tb__DOT__slave__DOT__rng 
                                                   >> 8U))));
                }
            } else if (vlSelfRef.submem_tb__DOT__slave__DOT__aw_late) {
                if (vlSelfRef.submem_tb__DOT__slave__DOT__w_done) {
                    __Vdly__submem_tb__DOT__slave__DOT__aw_late = 0U;
                    __Vdly__submem_tb__DOT__awready = 1U;
                }
            } else {
                __Vdly__submem_tb__DOT__slave__DOT__awdelay 
                    = (7U & ((IData)(vlSelfRef.submem_tb__DOT__slave__DOT__awdelay) 
                             - (IData)(1U)));
                if ((1U == (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__awdelay))) {
                    __Vdly__submem_tb__DOT__awready = 1U;
                }
            }
        }
        __Vdly__submem_tb__DOT__wready = ((((~ (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__w_done)) 
                                            & (~ (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__b_pending))) 
                                           & (~ (IData)(vlSelfRef.submem_tb__DOT__bvalid))) 
                                          & (6U > (7U 
                                                   & (vlSelfRef.submem_tb__DOT__slave__DOT__rng 
                                                      >> 0x0aU))));
        if ((((IData)(vlSelfRef.submem_tb__DOT__wvalid) 
              & (IData)(vlSelfRef.submem_tb__DOT__wready)) 
             & (~ (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__w_done)))) {
            __VdlyVal__submem_tb__DOT__slave__DOT__wbuf__v0 
                = vlSelfRef.data_out;
            __VdlyDim0__submem_tb__DOT__slave__DOT__wbuf__v0 
                = vlSelfRef.submem_tb__DOT__slave__DOT__wbeat;
            __VdlySet__submem_tb__DOT__slave__DOT__wbuf__v0 = 1U;
            __VdlyDim0__submem_tb__DOT__slave__DOT__wstrb_q__v0 
                = vlSelfRef.submem_tb__DOT__slave__DOT__wbeat;
            if (VL_UNLIKELY((((7U == (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr)) 
                              != (7U == (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__wbeat)))))) {
                VL_WRITEF_NX("[%0t] %%Fatal: axi_slave_beh.v:224: Assertion failed in %m: AXI: wlast on beat %0d\n",4, 'M',vlSymsp->name(),"submem_tb.slave", 'T',-12
                             , '#',64,VL_TIME_UNITED_Q(1)
                             , '#',3,(IData)(vlSelfRef.submem_tb__DOT__slave__DOT__wbeat));
                VL_STOP_MT("axi_slave_beh.v", 224, "", false);
            }
            if ((7U == (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__wbeat))) {
                __Vdly__submem_tb__DOT__slave__DOT__w_done = 1U;
            } else {
                __Vdly__submem_tb__DOT__slave__DOT__wbeat 
                    = (7U & ((IData)(1U) + (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__wbeat)));
            }
        }
        if (((((IData)(vlSelfRef.submem_tb__DOT__slave__DOT__aw_done) 
               & (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__w_done)) 
              & (~ (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__b_pending))) 
             & (~ (IData)(vlSelfRef.submem_tb__DOT__bvalid)))) {
            vlSelfRef.submem_tb__DOT__slave__DOT__wb = 8U;
            vlSelfRef.submem_tb__DOT__slave__DOT__wi = 8U;
            if ((1U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[0U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v0 
                    = (0x000000ffU & (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[0U]));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v0 
                    = (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                      >> 3U));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v0 = 1U;
            }
            __Vdly__submem_tb__DOT__slave__DOT__b_pending = 1U;
            __Vdly__submem_tb__DOT__slave__DOT__bdelay 
                = (7U & (vlSelfRef.submem_tb__DOT__slave__DOT__rng 
                         >> 0x0dU));
            if ((2U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[0U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v1 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[0U] 
                                              >> 8U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v1 
                    = (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                      >> 3U));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v1 = 1U;
            }
            if ((4U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[0U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v2 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[0U] 
                                              >> 0x10U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v2 
                    = (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                      >> 3U));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v2 = 1U;
            }
            if ((8U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[0U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v3 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[0U] 
                                              >> 0x18U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v3 
                    = (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                      >> 3U));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v3 = 1U;
            }
            if ((0x00000010U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[0U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v4 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[0U] 
                                              >> 0x20U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v4 
                    = (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                      >> 3U));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v4 = 1U;
            }
            if ((0x00000020U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[0U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v5 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[0U] 
                                              >> 0x28U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v5 
                    = (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                      >> 3U));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v5 = 1U;
            }
            if ((0x00000040U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[0U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v6 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[0U] 
                                              >> 0x30U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v6 
                    = (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                      >> 3U));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v6 = 1U;
            }
            if ((0x00000080U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[0U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v7 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[0U] 
                                              >> 0x38U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v7 
                    = (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                      >> 3U));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v7 = 1U;
            }
            if ((1U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[1U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v8 
                    = (0x000000ffU & (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[1U]));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v8 
                    = (1U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v8 = 1U;
            }
            if ((2U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[1U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v9 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[1U] 
                                              >> 8U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v9 
                    = (1U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v9 = 1U;
            }
            if ((4U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[1U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v10 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[1U] 
                                              >> 0x10U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v10 
                    = (1U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v10 = 1U;
            }
            if ((8U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[1U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v11 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[1U] 
                                              >> 0x18U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v11 
                    = (1U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v11 = 1U;
            }
            if ((0x00000010U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[1U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v12 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[1U] 
                                              >> 0x20U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v12 
                    = (1U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v12 = 1U;
            }
            if ((0x00000020U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[1U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v13 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[1U] 
                                              >> 0x28U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v13 
                    = (1U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v13 = 1U;
            }
            if ((0x00000040U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[1U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v14 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[1U] 
                                              >> 0x30U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v14 
                    = (1U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v14 = 1U;
            }
            if ((0x00000080U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[1U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v15 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[1U] 
                                              >> 0x38U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v15 
                    = (1U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v15 = 1U;
            }
            if ((1U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[2U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v16 
                    = (0x000000ffU & (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[2U]));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v16 
                    = (2U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v16 = 1U;
            }
            if ((2U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[2U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v17 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[2U] 
                                              >> 8U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v17 
                    = (2U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v17 = 1U;
            }
            if ((4U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[2U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v18 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[2U] 
                                              >> 0x10U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v18 
                    = (2U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v18 = 1U;
            }
            if ((8U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[2U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v19 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[2U] 
                                              >> 0x18U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v19 
                    = (2U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v19 = 1U;
            }
            if ((0x00000010U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[2U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v20 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[2U] 
                                              >> 0x20U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v20 
                    = (2U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v20 = 1U;
            }
            if ((0x00000020U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[2U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v21 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[2U] 
                                              >> 0x28U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v21 
                    = (2U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v21 = 1U;
            }
            if ((0x00000040U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[2U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v22 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[2U] 
                                              >> 0x30U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v22 
                    = (2U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v22 = 1U;
            }
            if ((0x00000080U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[2U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v23 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[2U] 
                                              >> 0x38U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v23 
                    = (2U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v23 = 1U;
            }
            if ((1U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[3U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v24 
                    = (0x000000ffU & (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[3U]));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v24 
                    = (3U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v24 = 1U;
            }
            if ((2U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[3U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v25 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[3U] 
                                              >> 8U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v25 
                    = (3U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v25 = 1U;
            }
            if ((4U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[3U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v26 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[3U] 
                                              >> 0x10U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v26 
                    = (3U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v26 = 1U;
            }
            if ((8U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[3U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v27 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[3U] 
                                              >> 0x18U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v27 
                    = (3U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v27 = 1U;
            }
            if ((0x00000010U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[3U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v28 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[3U] 
                                              >> 0x20U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v28 
                    = (3U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v28 = 1U;
            }
            if ((0x00000020U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[3U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v29 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[3U] 
                                              >> 0x28U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v29 
                    = (3U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v29 = 1U;
            }
            if ((0x00000040U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[3U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v30 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[3U] 
                                              >> 0x30U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v30 
                    = (3U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v30 = 1U;
            }
            if ((0x00000080U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[3U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v31 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[3U] 
                                              >> 0x38U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v31 
                    = (3U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v31 = 1U;
            }
            if ((1U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[4U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v32 
                    = (0x000000ffU & (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[4U]));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v32 
                    = (4U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v32 = 1U;
            }
            if ((2U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[4U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v33 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[4U] 
                                              >> 8U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v33 
                    = (4U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v33 = 1U;
            }
            if ((4U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[4U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v34 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[4U] 
                                              >> 0x10U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v34 
                    = (4U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v34 = 1U;
            }
            if ((8U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[4U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v35 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[4U] 
                                              >> 0x18U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v35 
                    = (4U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v35 = 1U;
            }
            if ((0x00000010U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[4U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v36 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[4U] 
                                              >> 0x20U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v36 
                    = (4U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v36 = 1U;
            }
            if ((0x00000020U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[4U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v37 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[4U] 
                                              >> 0x28U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v37 
                    = (4U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v37 = 1U;
            }
            if ((0x00000040U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[4U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v38 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[4U] 
                                              >> 0x30U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v38 
                    = (4U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v38 = 1U;
            }
            if ((0x00000080U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[4U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v39 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[4U] 
                                              >> 0x38U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v39 
                    = (4U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v39 = 1U;
            }
            if ((1U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[5U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v40 
                    = (0x000000ffU & (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[5U]));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v40 
                    = (5U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v40 = 1U;
            }
            if ((2U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[5U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v41 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[5U] 
                                              >> 8U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v41 
                    = (5U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v41 = 1U;
            }
            if ((4U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[5U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v42 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[5U] 
                                              >> 0x10U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v42 
                    = (5U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v42 = 1U;
            }
            if ((8U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[5U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v43 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[5U] 
                                              >> 0x18U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v43 
                    = (5U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v43 = 1U;
            }
            if ((0x00000010U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[5U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v44 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[5U] 
                                              >> 0x20U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v44 
                    = (5U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v44 = 1U;
            }
            if ((0x00000020U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[5U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v45 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[5U] 
                                              >> 0x28U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v45 
                    = (5U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v45 = 1U;
            }
            if ((0x00000040U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[5U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v46 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[5U] 
                                              >> 0x30U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v46 
                    = (5U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v46 = 1U;
            }
            if ((0x00000080U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[5U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v47 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[5U] 
                                              >> 0x38U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v47 
                    = (5U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v47 = 1U;
            }
            if ((1U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[6U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v48 
                    = (0x000000ffU & (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[6U]));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v48 
                    = (6U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v48 = 1U;
            }
            if ((2U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[6U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v49 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[6U] 
                                              >> 8U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v49 
                    = (6U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v49 = 1U;
            }
            if ((4U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[6U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v50 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[6U] 
                                              >> 0x10U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v50 
                    = (6U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v50 = 1U;
            }
            if ((8U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[6U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v51 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[6U] 
                                              >> 0x18U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v51 
                    = (6U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v51 = 1U;
            }
            if ((0x00000010U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[6U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v52 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[6U] 
                                              >> 0x20U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v52 
                    = (6U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v52 = 1U;
            }
            if ((0x00000020U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[6U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v53 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[6U] 
                                              >> 0x28U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v53 
                    = (6U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v53 = 1U;
            }
            if ((0x00000040U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[6U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v54 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[6U] 
                                              >> 0x30U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v54 
                    = (6U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v54 = 1U;
            }
            if ((0x00000080U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[6U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v55 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[6U] 
                                              >> 0x38U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v55 
                    = (6U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v55 = 1U;
            }
            if ((1U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[7U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v56 
                    = (0x000000ffU & (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[7U]));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v56 
                    = (7U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v56 = 1U;
            }
            if ((2U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[7U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v57 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[7U] 
                                              >> 8U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v57 
                    = (7U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v57 = 1U;
            }
            if ((4U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[7U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v58 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[7U] 
                                              >> 0x10U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v58 
                    = (7U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v58 = 1U;
            }
            if ((8U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[7U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v59 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[7U] 
                                              >> 0x18U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v59 
                    = (7U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v59 = 1U;
            }
            if ((0x00000010U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[7U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v60 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[7U] 
                                              >> 0x20U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v60 
                    = (7U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v60 = 1U;
            }
            if ((0x00000020U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[7U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v61 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[7U] 
                                              >> 0x28U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v61 
                    = (7U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v61 = 1U;
            }
            if ((0x00000040U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[7U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v62 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[7U] 
                                              >> 0x30U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v62 
                    = (7U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v62 = 1U;
            }
            if ((0x00000080U & vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[7U])) {
                __VdlyVal__submem_tb__DOT__slave__DOT__ram__v63 
                    = (0x000000ffU & (IData)((vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[7U] 
                                              >> 0x38U)));
                __VdlyDim0__submem_tb__DOT__slave__DOT__ram__v63 
                    = (7U | (0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q 
                                            >> 3U)));
                __VdlySet__submem_tb__DOT__slave__DOT__ram__v63 = 1U;
            }
        }
        if (vlSelfRef.submem_tb__DOT__slave__DOT__b_pending) {
            if ((0U == (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__bdelay))) {
                __Vdly__submem_tb__DOT__bvalid = 1U;
                __Vdly__submem_tb__DOT__slave__DOT__b_pending = 0U;
            } else {
                __Vdly__submem_tb__DOT__slave__DOT__bdelay 
                    = (0x0000000fU & ((IData)(vlSelfRef.submem_tb__DOT__slave__DOT__bdelay) 
                                      - (IData)(1U)));
            }
        }
        if (((IData)(vlSelfRef.submem_tb__DOT__bvalid) 
             & (IData)(vlSelfRef.submem_tb__DOT__bready))) {
            __Vdly__submem_tb__DOT__bvalid = 0U;
            __Vdly__submem_tb__DOT__slave__DOT__aw_done = 0U;
            __Vdly__submem_tb__DOT__slave__DOT__w_done = 0U;
            __Vdly__submem_tb__DOT__slave__DOT__wbeat = 0U;
        }
        if ((0U == (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__rstate))) {
            __Vdly__submem_tb__DOT__rvalid = 0U;
            __Vdly__submem_tb__DOT__rlast = 0U;
            if (((IData)(vlSelfRef.submem_tb__DOT__arvalid) 
                 & (IData)(vlSelfRef.submem_tb__DOT__arready))) {
                if (VL_UNLIKELY((((0U != (0x0000003fU 
                                          & vlSelfRef.submem_tb__DOT__araddr)) 
                                  | (0x00100000U <= vlSelfRef.submem_tb__DOT__araddr))))) {
                    VL_WRITEF_NX("[%0t] %%Fatal: axi_slave_beh.v:114: Assertion failed in %m: AXI: bad araddr %h\n",4, 'M',vlSymsp->name(),"submem_tb.slave", 'T',-12
                                 , '#',64,VL_TIME_UNITED_Q(1)
                                 , '#',32,vlSelfRef.submem_tb__DOT__araddr);
                    VL_STOP_MT("axi_slave_beh.v", 114, "", false);
                }
                __Vdly__submem_tb__DOT__arready = 0U;
                __Vdly__submem_tb__DOT__slave__DOT__raddr_q 
                    = vlSelfRef.submem_tb__DOT__araddr;
                __Vdly__submem_tb__DOT__slave__DOT__rbeat = 0U;
                __Vdly__submem_tb__DOT__slave__DOT__rdelay 
                    = (3U & vlSelfRef.submem_tb__DOT__slave__DOT__rng);
                __Vdly__submem_tb__DOT__slave__DOT__rstate = 1U;
            } else if (vlSelfRef.submem_tb__DOT__arvalid) {
                if (((0U == (3U & vlSelfRef.submem_tb__DOT__slave__DOT__rng)) 
                     | (IData)(vlSelfRef.submem_tb__DOT__arready))) {
                    __Vdly__submem_tb__DOT__arready = 1U;
                }
            }
        } else if ((1U == (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__rstate))) {
            if ((0U == (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__rdelay))) {
                __Vdly__submem_tb__DOT__rvalid = 1U;
                vlSelfRef.submem_tb__DOT__rdata = vlSelfRef.submem_tb__DOT__slave__DOT__ram
                    [((0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__raddr_q 
                                      >> 3U)) | (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__rbeat))];
                __Vdly__submem_tb__DOT__slave__DOT__rstate = 2U;
                __Vdly__submem_tb__DOT__rlast = (7U 
                                                 == (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__rbeat));
            } else {
                __Vdly__submem_tb__DOT__slave__DOT__rdelay 
                    = (7U & ((IData)(vlSelfRef.submem_tb__DOT__slave__DOT__rdelay) 
                             - (IData)(1U)));
            }
        } else if ((2U == (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__rstate))) {
            if (((IData)(vlSelfRef.submem_tb__DOT__rvalid) 
                 & (IData)(vlSelfRef.submem_tb__DOT__rready))) {
                if ((7U == (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__rbeat))) {
                    __Vdly__submem_tb__DOT__rvalid = 0U;
                    __Vdly__submem_tb__DOT__rlast = 0U;
                    __Vdly__submem_tb__DOT__slave__DOT__rstate = 0U;
                } else {
                    __Vdly__submem_tb__DOT__slave__DOT__rbeat 
                        = (7U & ((IData)(1U) + (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__rbeat)));
                    if ((5U > (7U & vlSelfRef.submem_tb__DOT__slave__DOT__rng))) {
                        vlSelfRef.submem_tb__DOT__rdata 
                            = vlSelfRef.submem_tb__DOT__slave__DOT__ram
                            [((0x0001fff8U & (vlSelfRef.submem_tb__DOT__slave__DOT__raddr_q 
                                              >> 3U)) 
                              | (7U & ((IData)(1U) 
                                       + (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__rbeat))))];
                        __Vdly__submem_tb__DOT__rlast 
                            = (6U == (IData)(vlSelfRef.submem_tb__DOT__slave__DOT__rbeat));
                    } else {
                        __Vdly__submem_tb__DOT__rvalid = 0U;
                        __Vdly__submem_tb__DOT__rlast = 0U;
                        __Vdly__submem_tb__DOT__slave__DOT__rdelay 
                            = (3U & (vlSelfRef.submem_tb__DOT__slave__DOT__rng 
                                     >> 3U));
                        __Vdly__submem_tb__DOT__slave__DOT__rstate = 1U;
                    }
                }
            }
        } else {
            __Vdly__submem_tb__DOT__slave__DOT__rstate = 0U;
        }
        if (((((((((0U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)) 
                   | (1U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) 
                  | (2U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) 
                 | (3U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) 
                | (4U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) 
               | (6U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) 
              | (7U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) 
             | (8U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)))) {
            if ((0U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                if (vlSelfRef.flush) {
                    if (vlSelfRef.flush_done) {
                        __Vdly__flush_done = 0U;
                    } else {
                        __Vdly__submem_tb__DOT__dut__DOT__state = 6U;
                    }
                } else if ((((IData)(vlSelfRef.mem_read) 
                             | (IData)(vlSelfRef.mem_write)) 
                            & (IData)(vlSelfRef.busy))) {
                    if (vlSelfRef.submem_tb__DOT__dut__DOT__cache_miss) {
                        vlSelfRef.submem_tb__DOT__dut__DOT__miss_addr 
                            = vlSelfRef.addr;
                        __Vdly__submem_tb__DOT__dut__DOT__hit 
                            = vlSelfRef.submem_tb__DOT__dut__DOT__cache_hit;
                        vlSelfRef.submem_tb__DOT__dut__DOT__dirty 
                            = (3U == (3U & ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_primary) 
                                            >> 0x0000000aU)));
                        __Vdly__submem_tb__DOT__dut__DOT__spill_hit 
                            = vlSelfRef.submem_tb__DOT__dut__DOT__cache_spill_hit;
                        __Vdly__submem_tb__DOT__dut__DOT__spill_dirty 
                            = vlSelfRef.submem_tb__DOT__dut__DOT__cache_spill_dirty;
                        __Vdly__submem_tb__DOT__dut__DOT__line_spill 
                            = vlSelfRef.submem_tb__DOT__dut__DOT__cache_line_spill;
                        vlSelfRef.submem_tb__DOT__dut__DOT__evict_addr 
                            = vlSelfRef.submem_tb__DOT__dut__DOT__cache_evict_addr;
                        vlSelfRef.submem_tb__DOT__dut__DOT__spill_evict_addr 
                            = ((0x07fe0000U & ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_spill) 
                                               << 0x00000011U)) 
                               | ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_index) 
                                  << 6U));
                        if ((IData)(((0x0c00U == (0x0c00U 
                                                  & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_primary))) 
                                     & (~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_hit))))) {
                            __Vdly__submem_tb__DOT__dut__DOT__state = 1U;
                        } else if ((((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_line_spill) 
                                     & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_spill_dirty)) 
                                    & (~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_spill_hit)))) {
                            __Vdly__submem_tb__DOT__dut__DOT__state = 2U;
                        } else if (vlSelfRef.submem_tb__DOT__dut__DOT__cache_hit) {
                            if (((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_line_spill) 
                                 & (~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_spill_hit)))) {
                                __Vdly__submem_tb__DOT__dut__DOT__state = 4U;
                            }
                        } else {
                            __Vdly__submem_tb__DOT__dut__DOT__state = 3U;
                        }
                    } else {
                        __Vdly__busy = 0U;
                    }
                } else {
                    __Vdly__busy = 1U;
                }
            } else if ((1U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                if (vlSelfRef.submem_tb__DOT__s_amc_data_in_last) {
                    __Vdly__submem_tb__DOT__dut__DOT__state 
                        = ((((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__line_spill) 
                             & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__spill_dirty)) 
                            & (~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__spill_hit)))
                            ? 2U : 3U);
                }
            } else if ((2U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                if (vlSelfRef.submem_tb__DOT__s_amc_data_in_last) {
                    if (vlSelfRef.submem_tb__DOT__dut__DOT__hit) {
                        if (((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__line_spill) 
                             & (~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__spill_hit)))) {
                            __Vdly__submem_tb__DOT__dut__DOT__state = 4U;
                        }
                    } else {
                        __Vdly__submem_tb__DOT__dut__DOT__state = 3U;
                    }
                }
            } else if ((3U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                if (vlSelfRef.submem_tb__DOT__s_amc_data_out_last) {
                    __Vdly__submem_tb__DOT__dut__DOT__state 
                        = (((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__line_spill) 
                            & (~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__spill_hit)))
                            ? 4U : 5U);
                }
            } else if ((4U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                if (vlSelfRef.submem_tb__DOT__s_amc_data_out_last) {
                    __Vdly__submem_tb__DOT__dut__DOT__state = 5U;
                }
            } else if ((6U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                if ((3U == (3U & ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_primary) 
                                  >> 0x0000000aU)))) {
                    __Vdly__submem_tb__DOT__dut__DOT__state = 7U;
                    vlSelfRef.submem_tb__DOT__dut__DOT__evict_addr 
                        = vlSelfRef.submem_tb__DOT__dut__DOT__cache_evict_addr;
                } else if ((0x000007ffU == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__flush_line))) {
                    __Vdly__flush_done = 1U;
                    __Vdly__submem_tb__DOT__dut__DOT__flush_line = 0U;
                    __Vdly__submem_tb__DOT__dut__DOT__state = 0U;
                } else {
                    __Vdly__submem_tb__DOT__dut__DOT__flush_line 
                        = (0x000007ffU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__flush_line)));
                }
            } else if ((7U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                if (vlSelfRef.submem_tb__DOT__s_amc_data_in_last) {
                    __Vdly__submem_tb__DOT__dut__DOT__state = 8U;
                }
            } else if ((1U & (~ (IData)(vlSelfRef.submem_tb__DOT__s_amc_busy)))) {
                if ((0x000007ffU == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__flush_line))) {
                    __Vdly__flush_done = 1U;
                    __Vdly__submem_tb__DOT__dut__DOT__flush_line = 0U;
                    __Vdly__submem_tb__DOT__dut__DOT__state = 0U;
                } else {
                    __Vdly__submem_tb__DOT__dut__DOT__flush_line 
                        = (0x000007ffU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__flush_line)));
                    __Vdly__submem_tb__DOT__dut__DOT__state = 6U;
                }
            }
        } else if ((5U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
            if ((1U & (~ (IData)(vlSelfRef.submem_tb__DOT__s_amc_busy)))) {
                __Vdly__submem_tb__DOT__dut__DOT__state = 0U;
            }
        }
        vlSelfRef.submem_tb__DOT__slave__DOT__rng = 
            ((vlSelfRef.submem_tb__DOT__slave__DOT__rng_next2 
              << 5U) ^ vlSelfRef.submem_tb__DOT__slave__DOT__rng_next2);
        if ((4U & (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__state))) {
            if ((2U & (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__state))) {
                if ((1U & (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__state))) {
                    if (((IData)(vlSelfRef.submem_tb__DOT__bready) 
                         & (IData)(vlSelfRef.submem_tb__DOT__bvalid))) {
                        __Vdly__submem_tb__DOT__amc_instance__DOT__state = 0U;
                        vlSelfRef.submem_tb__DOT__s_amc_busy = 0U;
                        __Vdly__submem_tb__DOT__bready = 0U;
                    }
                } else if (((IData)(vlSelfRef.submem_tb__DOT__wready) 
                            & (IData)(vlSelfRef.submem_tb__DOT__wvalid))) {
                    if ((7U == (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr))) {
                        __Vdly__submem_tb__DOT__amc_instance__DOT__state = 7U;
                        __Vdly__submem_tb__DOT__amc_instance__DOT__cntr = 0U;
                        __Vdly__submem_tb__DOT__wvalid = 0U;
                        __Vdly__submem_tb__DOT__bready = 1U;
                    } else {
                        __Vdly__submem_tb__DOT__amc_instance__DOT__cntr 
                            = (7U & ((IData)(1U) + (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr)));
                    }
                }
            } else {
                __Vdly__submem_tb__DOT__amc_instance__DOT__state = 0U;
            }
        } else if ((2U & (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__state))) {
            if ((1U & (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__state))) {
                if (((IData)(vlSelfRef.submem_tb__DOT__wready) 
                     & (IData)(vlSelfRef.submem_tb__DOT__wvalid))) {
                    if ((7U == (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr))) {
                        __Vdly__submem_tb__DOT__wvalid = 0U;
                    } else {
                        __Vdly__submem_tb__DOT__amc_instance__DOT__cntr 
                            = (7U & ((IData)(1U) + (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr)));
                    }
                }
                if (((IData)(vlSelfRef.submem_tb__DOT__awready) 
                     & (IData)(vlSelfRef.submem_tb__DOT__awvalid))) {
                    __Vdly__submem_tb__DOT__awvalid = 0U;
                    if ((1U & ((~ (IData)(vlSelfRef.submem_tb__DOT__wvalid)) 
                               | (((IData)(vlSelfRef.submem_tb__DOT__wready) 
                                   & (IData)(vlSelfRef.submem_tb__DOT__wvalid)) 
                                  & (7U == (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr)))))) {
                        __Vdly__submem_tb__DOT__amc_instance__DOT__state = 7U;
                        __Vdly__submem_tb__DOT__amc_instance__DOT__cntr = 0U;
                        __Vdly__submem_tb__DOT__wvalid = 0U;
                        __Vdly__submem_tb__DOT__bready = 1U;
                    } else {
                        __Vdly__submem_tb__DOT__amc_instance__DOT__state = 6U;
                    }
                }
            } else if (((IData)(vlSelfRef.submem_tb__DOT__rready) 
                        & (IData)(vlSelfRef.submem_tb__DOT__rvalid))) {
                if (vlSelfRef.submem_tb__DOT__rlast) {
                    __Vdly__submem_tb__DOT__amc_instance__DOT__state = 0U;
                    __Vdly__submem_tb__DOT__rready = 0U;
                    vlSelfRef.submem_tb__DOT__s_amc_busy = 0U;
                    __Vdly__submem_tb__DOT__amc_instance__DOT__cntr = 0U;
                } else {
                    __Vdly__submem_tb__DOT__amc_instance__DOT__cntr 
                        = (7U & ((IData)(1U) + (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr)));
                }
            }
        } else if ((1U & (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__state))) {
            if (((IData)(vlSelfRef.submem_tb__DOT__arready) 
                 & (IData)(vlSelfRef.submem_tb__DOT__arvalid))) {
                __Vdly__submem_tb__DOT__amc_instance__DOT__state = 2U;
                __Vdly__submem_tb__DOT__arvalid = 0U;
                __Vdly__submem_tb__DOT__rready = 1U;
            }
        } else {
            if (((3U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)) 
                 | (4U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)))) {
                __Vdly__submem_tb__DOT__amc_instance__DOT__state = 1U;
                vlSelfRef.submem_tb__DOT__s_amc_busy = 1U;
                __Vdly__submem_tb__DOT__arvalid = 1U;
                vlSelfRef.submem_tb__DOT__araddr = vlSelfRef.submem_tb__DOT__s_amc_addr;
            } else if (((7U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)) 
                        | ((1U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)) 
                           | (2U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))))) {
                __Vdly__submem_tb__DOT__amc_instance__DOT__state = 3U;
                vlSelfRef.submem_tb__DOT__s_amc_busy = 1U;
                __Vdly__submem_tb__DOT__awvalid = 1U;
                __Vdly__submem_tb__DOT__wvalid = 1U;
                vlSelfRef.submem_tb__DOT__awaddr = vlSelfRef.submem_tb__DOT__s_amc_addr;
            }
            vlSelfRef.submem_tb__DOT__s_amc_err = 0U;
        }
    }
    if (__VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd__v0) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd[__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd__v0] 
            = __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd__v0;
    }
    if (__VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even__v0) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even[__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even__v0] 
            = __VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even__v0;
    }
    vlSelfRef.submem_tb__DOT__slave__DOT__aw_done = __Vdly__submem_tb__DOT__slave__DOT__aw_done;
    vlSelfRef.submem_tb__DOT__slave__DOT__wbeat = __Vdly__submem_tb__DOT__slave__DOT__wbeat;
    vlSelfRef.submem_tb__DOT__slave__DOT__w_done = __Vdly__submem_tb__DOT__slave__DOT__w_done;
    vlSelfRef.submem_tb__DOT__slave__DOT__b_pending 
        = __Vdly__submem_tb__DOT__slave__DOT__b_pending;
    vlSelfRef.submem_tb__DOT__slave__DOT__aw_late = __Vdly__submem_tb__DOT__slave__DOT__aw_late;
    vlSelfRef.submem_tb__DOT__slave__DOT__awdelay = __Vdly__submem_tb__DOT__slave__DOT__awdelay;
    vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q = __Vdly__submem_tb__DOT__slave__DOT__waddr_q;
    vlSelfRef.submem_tb__DOT__slave__DOT__bdelay = __Vdly__submem_tb__DOT__slave__DOT__bdelay;
    if (__VdlySet__submem_tb__DOT__slave__DOT__wbuf__v0) {
        vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q[__VdlyDim0__submem_tb__DOT__slave__DOT__wstrb_q__v0] = 0xffU;
        vlSelfRef.submem_tb__DOT__slave__DOT__wbuf[__VdlyDim0__submem_tb__DOT__slave__DOT__wbuf__v0] 
            = __VdlyVal__submem_tb__DOT__slave__DOT__wbuf__v0;
    }
    if (__VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v0) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v0] 
            = ((0xffffffffffffff00ULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                [__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v0]) 
               | (IData)((IData)(__VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v0)));
    }
    if (__VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v1) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v1] 
            = ((0xffffffffffff00ffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                [__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v1]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v1)) 
                  << 8U));
    }
    if (__VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v2) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v2] 
            = ((0xffffffffff00ffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                [__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v2]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v2)) 
                  << 0x00000010U));
    }
    if (__VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v3) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v3] 
            = ((0xffffffff00ffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                [__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v3]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v3)) 
                  << 0x00000018U));
    }
    if (__VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v4) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v4] 
            = ((0xffffff00ffffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                [__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v4]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v4)) 
                  << 0x00000020U));
    }
    if (__VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v5) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v5] 
            = ((0xffff00ffffffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                [__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v5]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v5)) 
                  << 0x00000028U));
    }
    if (__VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v6) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v6] 
            = ((0xff00ffffffffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                [__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v6]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v6)) 
                  << 0x00000030U));
    }
    if (__VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v7) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v7] 
            = ((0x00ffffffffffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                [__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v7]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v7)) 
                  << 0x00000038U));
    }
    if (__VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v8) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v8] 
            = ((0xffffffffffffff00ULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                [__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v8]) 
               | (IData)((IData)(__VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v8)));
    }
    if (__VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v9) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v9] 
            = ((0xffffffffffff00ffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                [__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v9]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v9)) 
                  << 8U));
    }
    if (__VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v10) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v10] 
            = ((0xffffffffff00ffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                [__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v10]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v10)) 
                  << 0x00000010U));
    }
    if (__VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v11) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v11] 
            = ((0xffffffff00ffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                [__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v11]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v11)) 
                  << 0x00000018U));
    }
    if (__VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v12) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v12] 
            = ((0xffffff00ffffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                [__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v12]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v12)) 
                  << 0x00000020U));
    }
    if (__VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v13) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v13] 
            = ((0xffff00ffffffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                [__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v13]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v13)) 
                  << 0x00000028U));
    }
    if (__VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v14) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v14] 
            = ((0xff00ffffffffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                [__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v14]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v14)) 
                  << 0x00000030U));
    }
    if (__VdlySet__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v15) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem[__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v15] 
            = ((0x00ffffffffffffffULL & vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem
                [__VdlyDim0__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v15]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem__v15)) 
                  << 0x00000038U));
    }
    vlSelfRef.submem_tb__DOT__slave__DOT__rstate = __Vdly__submem_tb__DOT__slave__DOT__rstate;
    vlSelfRef.submem_tb__DOT__slave__DOT__rbeat = __Vdly__submem_tb__DOT__slave__DOT__rbeat;
    vlSelfRef.submem_tb__DOT__slave__DOT__raddr_q = __Vdly__submem_tb__DOT__slave__DOT__raddr_q;
    vlSelfRef.submem_tb__DOT__slave__DOT__rdelay = __Vdly__submem_tb__DOT__slave__DOT__rdelay;
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v0) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v0] 
            = ((0xffffffffffffff00ULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v0]) 
               | (IData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v0)));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v1) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v1] 
            = ((0xffffffffffff00ffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v1]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v1)) 
                  << 8U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v2) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v2] 
            = ((0xffffffffff00ffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v2]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v2)) 
                  << 0x00000010U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v3) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v3] 
            = ((0xffffffff00ffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v3]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v3)) 
                  << 0x00000018U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v4) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v4] 
            = ((0xffffff00ffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v4]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v4)) 
                  << 0x00000020U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v5) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v5] 
            = ((0xffff00ffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v5]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v5)) 
                  << 0x00000028U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v6) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v6] 
            = ((0xff00ffffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v6]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v6)) 
                  << 0x00000030U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v7) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v7] 
            = ((0x00ffffffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v7]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v7)) 
                  << 0x00000038U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v8) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v8] 
            = ((0xffffffffffffff00ULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v8]) 
               | (IData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v8)));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v9) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v9] 
            = ((0xffffffffffff00ffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v9]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v9)) 
                  << 8U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v10) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v10] 
            = ((0xffffffffff00ffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v10]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v10)) 
                  << 0x00000010U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v11) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v11] 
            = ((0xffffffff00ffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v11]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v11)) 
                  << 0x00000018U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v12) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v12] 
            = ((0xffffff00ffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v12]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v12)) 
                  << 0x00000020U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v13) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v13] 
            = ((0xffff00ffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v13]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v13)) 
                  << 0x00000028U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v14) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v14] 
            = ((0xff00ffffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v14]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v14)) 
                  << 0x00000030U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v15) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v15] 
            = ((0x00ffffffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v15]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v15)) 
                  << 0x00000038U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v16) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v16] 
            = ((0xffffffffffffff00ULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v16]) 
               | (IData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v16)));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v17) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v17] 
            = ((0xffffffffffff00ffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v17]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v17)) 
                  << 8U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v18) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v18] 
            = ((0xffffffffff00ffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v18]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v18)) 
                  << 0x00000010U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v19) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v19] 
            = ((0xffffffff00ffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v19]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v19)) 
                  << 0x00000018U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v20) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v20] 
            = ((0xffffff00ffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v20]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v20)) 
                  << 0x00000020U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v21) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v21] 
            = ((0xffff00ffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v21]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v21)) 
                  << 0x00000028U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v22) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v22] 
            = ((0xff00ffffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v22]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v22)) 
                  << 0x00000030U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v23) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v23] 
            = ((0x00ffffffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v23]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v23)) 
                  << 0x00000038U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v24) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v24] 
            = ((0xffffffffffffff00ULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v24]) 
               | (IData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v24)));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v25) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v25] 
            = ((0xffffffffffff00ffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v25]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v25)) 
                  << 8U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v26) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v26] 
            = ((0xffffffffff00ffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v26]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v26)) 
                  << 0x00000010U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v27) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v27] 
            = ((0xffffffff00ffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v27]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v27)) 
                  << 0x00000018U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v28) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v28] 
            = ((0xffffff00ffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v28]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v28)) 
                  << 0x00000020U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v29) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v29] 
            = ((0xffff00ffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v29]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v29)) 
                  << 0x00000028U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v30) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v30] 
            = ((0xff00ffffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v30]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v30)) 
                  << 0x00000030U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v31) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v31] 
            = ((0x00ffffffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v31]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v31)) 
                  << 0x00000038U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v32) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v32] 
            = ((0xffffffffffffff00ULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v32]) 
               | (IData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v32)));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v33) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v33] 
            = ((0xffffffffffff00ffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v33]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v33)) 
                  << 8U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v34) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v34] 
            = ((0xffffffffff00ffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v34]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v34)) 
                  << 0x00000010U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v35) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v35] 
            = ((0xffffffff00ffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v35]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v35)) 
                  << 0x00000018U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v36) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v36] 
            = ((0xffffff00ffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v36]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v36)) 
                  << 0x00000020U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v37) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v37] 
            = ((0xffff00ffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v37]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v37)) 
                  << 0x00000028U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v38) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v38] 
            = ((0xff00ffffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v38]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v38)) 
                  << 0x00000030U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v39) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v39] 
            = ((0x00ffffffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v39]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v39)) 
                  << 0x00000038U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v40) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v40] 
            = ((0xffffffffffffff00ULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v40]) 
               | (IData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v40)));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v41) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v41] 
            = ((0xffffffffffff00ffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v41]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v41)) 
                  << 8U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v42) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v42] 
            = ((0xffffffffff00ffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v42]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v42)) 
                  << 0x00000010U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v43) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v43] 
            = ((0xffffffff00ffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v43]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v43)) 
                  << 0x00000018U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v44) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v44] 
            = ((0xffffff00ffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v44]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v44)) 
                  << 0x00000020U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v45) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v45] 
            = ((0xffff00ffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v45]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v45)) 
                  << 0x00000028U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v46) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v46] 
            = ((0xff00ffffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v46]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v46)) 
                  << 0x00000030U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v47) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v47] 
            = ((0x00ffffffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v47]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v47)) 
                  << 0x00000038U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v48) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v48] 
            = ((0xffffffffffffff00ULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v48]) 
               | (IData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v48)));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v49) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v49] 
            = ((0xffffffffffff00ffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v49]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v49)) 
                  << 8U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v50) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v50] 
            = ((0xffffffffff00ffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v50]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v50)) 
                  << 0x00000010U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v51) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v51] 
            = ((0xffffffff00ffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v51]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v51)) 
                  << 0x00000018U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v52) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v52] 
            = ((0xffffff00ffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v52]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v52)) 
                  << 0x00000020U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v53) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v53] 
            = ((0xffff00ffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v53]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v53)) 
                  << 0x00000028U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v54) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v54] 
            = ((0xff00ffffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v54]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v54)) 
                  << 0x00000030U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v55) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v55] 
            = ((0x00ffffffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v55]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v55)) 
                  << 0x00000038U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v56) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v56] 
            = ((0xffffffffffffff00ULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v56]) 
               | (IData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v56)));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v57) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v57] 
            = ((0xffffffffffff00ffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v57]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v57)) 
                  << 8U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v58) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v58] 
            = ((0xffffffffff00ffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v58]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v58)) 
                  << 0x00000010U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v59) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v59] 
            = ((0xffffffff00ffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v59]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v59)) 
                  << 0x00000018U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v60) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v60] 
            = ((0xffffff00ffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v60]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v60)) 
                  << 0x00000020U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v61) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v61] 
            = ((0xffff00ffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v61]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v61)) 
                  << 0x00000028U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v62) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v62] 
            = ((0xff00ffffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v62]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v62)) 
                  << 0x00000030U));
    }
    if (__VdlySet__submem_tb__DOT__slave__DOT__ram__v63) {
        vlSelfRef.submem_tb__DOT__slave__DOT__ram[__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v63] 
            = ((0x00ffffffffffffffULL & vlSelfRef.submem_tb__DOT__slave__DOT__ram
                [__VdlyDim0__submem_tb__DOT__slave__DOT__ram__v63]) 
               | ((QData)((IData)(__VdlyVal__submem_tb__DOT__slave__DOT__ram__v63)) 
                  << 0x00000038U));
    }
    vlSelfRef.busy = __Vdly__busy;
    vlSelfRef.flush_done = __Vdly__flush_done;
    vlSelfRef.submem_tb__DOT__dut__DOT__hit = __Vdly__submem_tb__DOT__dut__DOT__hit;
    vlSelfRef.submem_tb__DOT__dut__DOT__spill_hit = __Vdly__submem_tb__DOT__dut__DOT__spill_hit;
    vlSelfRef.submem_tb__DOT__dut__DOT__spill_dirty 
        = __Vdly__submem_tb__DOT__dut__DOT__spill_dirty;
    vlSelfRef.submem_tb__DOT__dut__DOT__line_spill 
        = __Vdly__submem_tb__DOT__dut__DOT__line_spill;
    vlSelfRef.submem_tb__DOT__dut__DOT__flush_line 
        = __Vdly__submem_tb__DOT__dut__DOT__flush_line;
    vlSelfRef.bd_data = vlSelfRef.submem_tb__DOT__slave__DOT__ram
        [(0x0001ffffU & (vlSelfRef.bd_addr >> 3U))];
    vlSelfRef.submem_tb__DOT__bready = __Vdly__submem_tb__DOT__bready;
    vlSelfRef.submem_tb__DOT__bvalid = __Vdly__submem_tb__DOT__bvalid;
    vlSelfRef.submem_tb__DOT__awready = __Vdly__submem_tb__DOT__awready;
    vlSelfRef.submem_tb__DOT__awvalid = __Vdly__submem_tb__DOT__awvalid;
    vlSelfRef.submem_tb__DOT__arready = __Vdly__submem_tb__DOT__arready;
    vlSelfRef.submem_tb__DOT__arvalid = __Vdly__submem_tb__DOT__arvalid;
    vlSelfRef.submem_tb__DOT__rlast = __Vdly__submem_tb__DOT__rlast;
    vlSelfRef.submem_tb__DOT__rready = __Vdly__submem_tb__DOT__rready;
    vlSelfRef.submem_tb__DOT__rvalid = __Vdly__submem_tb__DOT__rvalid;
    vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr 
        = __Vdly__submem_tb__DOT__amc_instance__DOT__cntr;
    vlSelfRef.submem_tb__DOT__wready = __Vdly__submem_tb__DOT__wready;
    vlSelfRef.submem_tb__DOT__wvalid = __Vdly__submem_tb__DOT__wvalid;
    vlSelfRef.submem_tb__DOT__amc_instance__DOT__state 
        = __Vdly__submem_tb__DOT__amc_instance__DOT__state;
    vlSelfRef.submem_tb__DOT__dut__DOT__state = __Vdly__submem_tb__DOT__dut__DOT__state;
    vlSelfRef.submem_tb__DOT__slave__DOT__rng_next1 
        = (vlSelfRef.submem_tb__DOT__slave__DOT__rng 
           ^ (vlSelfRef.submem_tb__DOT__slave__DOT__rng 
              << 0x0000000dU));
    vlSelfRef.submem_tb__DOT__s_amc_data_in_last = 
        ((7U == (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr)) 
         & ((IData)(vlSelfRef.submem_tb__DOT__wvalid) 
            & (IData)(vlSelfRef.submem_tb__DOT__wready)));
    vlSelfRef.submem_tb__DOT__s_amc_data_out_valid 
        = ((IData)(vlSelfRef.submem_tb__DOT__rready) 
           & ((IData)(vlSelfRef.submem_tb__DOT__rvalid) 
              & (2U == (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__state))));
    vlSelfRef.submem_tb__DOT__s_amc_data_in_valid = 
        ((IData)(vlSelfRef.submem_tb__DOT__wready) 
         & ((IData)(vlSelfRef.submem_tb__DOT__wvalid) 
            & ((6U == (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__state)) 
               | (3U == (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__state)))));
    __VdfgRegularize_h6e95ff9d_0_15 = ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))
                                        ? (0x07ffffc0U 
                                           & vlSelfRef.submem_tb__DOT__dut__DOT__evict_addr)
                                        : (0x07ffffc0U 
                                           & vlSelfRef.addr));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
        = vlSelfRef.data_in;
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__flush 
        = ((7U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)) 
           | (6U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)));
    vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw = 3U;
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
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry = 0U;
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
            = (0x07ffffffU & vlSelfRef.addr);
        vlSelfRef.submem_tb__DOT__s_amc_addr = (0x07ffffc0U 
                                                & vlSelfRef.addr);
    } else if ((8U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
            = vlSelfRef.data_in;
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw = 3U;
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry = 0U;
        vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
            = (0x07ffffffU & vlSelfRef.addr);
        vlSelfRef.submem_tb__DOT__s_amc_addr = (0x07ffffc0U 
                                                & vlSelfRef.addr);
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
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                = (0x07ffffffU & ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))
                                   ? (((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__flush_line) 
                                       << 6U) + (0x00000038U 
                                                 & (((IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr) 
                                                     + (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_in_valid)) 
                                                    << 3U)))
                                   : ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__flush_line) 
                                      << 6U)));
            vlSelfRef.submem_tb__DOT__s_amc_addr = __VdfgRegularize_h6e95ff9d_0_15;
        } else if ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                = (0x07ffffffU & vlSelfRef.addr);
            vlSelfRef.submem_tb__DOT__s_amc_addr = 
                (0x07ffffc0U & vlSelfRef.addr);
        } else {
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                = (0x07ffffffU & ((0x07ffffc0U & ((IData)(0x00000040U) 
                                                  + vlSelfRef.submem_tb__DOT__dut__DOT__miss_addr)) 
                                  + ((IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr) 
                                     << 3U)));
            vlSelfRef.submem_tb__DOT__s_amc_addr = 
                (0x07ffffc0U & ((IData)(0x00000040U) 
                                + vlSelfRef.submem_tb__DOT__dut__DOT__miss_addr));
        }
    } else {
        if ((2U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
            if ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) {
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
                    = vlSelfRef.submem_tb__DOT__rdata;
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry 
                    = vlSelfRef.submem_tb__DOT__s_amc_data_out_valid;
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                    = (0x07ffffffU & ((0x07ffffc0U 
                                       & vlSelfRef.submem_tb__DOT__dut__DOT__miss_addr) 
                                      + ((IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr) 
                                         << 3U)));
                vlSelfRef.submem_tb__DOT__s_amc_addr 
                    = (0x07ffffc0U & vlSelfRef.submem_tb__DOT__dut__DOT__miss_addr);
            } else {
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                    = (0x07ffffffU & ((0x07ffffc0U 
                                       & vlSelfRef.submem_tb__DOT__dut__DOT__spill_evict_addr) 
                                      + (0x00000038U 
                                         & (((IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr) 
                                             + (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_in_valid)) 
                                            << 3U))));
                vlSelfRef.submem_tb__DOT__s_amc_addr 
                    = (0x07ffffc0U & vlSelfRef.submem_tb__DOT__dut__DOT__spill_evict_addr);
            }
        } else {
            if ((1U & (~ (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)))) {
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in 
                    = vlSelfRef.data_in;
                vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry = 0U;
            }
            vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                = (0x07ffffffU & ((1U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))
                                   ? ((0x07ffffc0U 
                                       & vlSelfRef.submem_tb__DOT__dut__DOT__evict_addr) 
                                      + (0x00000038U 
                                         & (((IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr) 
                                             + (IData)(vlSelfRef.submem_tb__DOT__s_amc_data_in_valid)) 
                                            << 3U)))
                                   : vlSelfRef.addr));
            vlSelfRef.submem_tb__DOT__s_amc_addr = __VdfgRegularize_h6e95ff9d_0_15;
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

void Vsubmem_tb___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsubmem_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vsubmem_tb___024root___eval_phase__act(Vsubmem_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___eval_phase__act\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__act
        vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                        ((IData)(vlSelfRef.clk) 
                                                         & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__1)))));
        vlSelfRef.__Vtrigprevexpr___TOP__clk__1 = vlSelfRef.clk;
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vsubmem_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vsubmem_tb___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vsubmem_tb___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vsubmem_tb___024root___eval_phase__nba(Vsubmem_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___eval_phase__nba\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vsubmem_tb___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        {
            // Inlined CFunc: _eval_nba
            if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
                Vsubmem_tb___024root___nba_sequent__TOP__0(vlSelf);
                vlSelfRef.__Vm_traceActivity[4U] = 1U;
            }
        }
        Vsubmem_tb___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vsubmem_tb___024root___eval(Vsubmem_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___eval\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VicoIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vsubmem_tb___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("submem_tb.v", 8, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 10000 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        vlSelfRef.__VicoPhaseResult = Vsubmem_tb___024root___eval_phase__ico(vlSelf);
    } while (vlSelfRef.__VicoPhaseResult);
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vsubmem_tb___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("submem_tb.v", 8, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 10000 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vsubmem_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("submem_tb.v", 8, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 10000 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vsubmem_tb___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vsubmem_tb___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vsubmem_tb___024root___eval_debug_assertions(Vsubmem_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root___eval_debug_assertions\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");
    }
    if (VL_UNLIKELY(((vlSelfRef.addr & 0xf8000000U)))) {
        Verilated::overWidthError("addr");
    }
    if (VL_UNLIKELY(((vlSelfRef.mem_read & 0xfeU)))) {
        Verilated::overWidthError("mem_read");
    }
    if (VL_UNLIKELY(((vlSelfRef.mem_write & 0xfeU)))) {
        Verilated::overWidthError("mem_write");
    }
    if (VL_UNLIKELY(((vlSelfRef.bw & 0xfcU)))) {
        Verilated::overWidthError("bw");
    }
    if (VL_UNLIKELY(((vlSelfRef.flush & 0xfeU)))) {
        Verilated::overWidthError("flush");
    }
}
#endif  // VL_DEBUG
