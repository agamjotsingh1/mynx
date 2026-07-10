// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vsubmem_tb__Syms.h"


void Vsubmem_tb___024root__trace_chg_0_sub_0(Vsubmem_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vsubmem_tb___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root__trace_chg_0\n"); );
    // Body
    Vsubmem_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsubmem_tb___024root*>(voidSelf);
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vsubmem_tb___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vsubmem_tb___024root__trace_chg_dtype____0(Vsubmem_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp, uint32_t offset, const VlUnpacked<QData/*63:0*/, 8>& __VdtypeVar);
void Vsubmem_tb___024root__trace_chg_dtype____1(Vsubmem_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp, uint32_t offset, const VlUnpacked<CData/*7:0*/, 8>& __VdtypeVar);

void Vsubmem_tb___024root__trace_chg_0_sub_0(Vsubmem_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root__trace_chg_0_sub_0\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 0);
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[0U]))) {
        bufp->chgIData(oldp+0,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__i),32);
        bufp->chgIData(oldp+1,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__i),32);
        bufp->chgIData(oldp+2,(vlSelfRef.submem_tb__DOT__slave__DOT__i),32);
        bufp->chgQData(oldp+3,(vlSelfRef.submem_tb__DOT__slave__DOT__i64),64);
    }
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[1U] 
                      | vlSelfRef.__Vm_traceActivity[4U])))) {
        bufp->chgIData(oldp+5,(vlSelfRef.submem_tb__DOT__s_amc_addr),27);
        bufp->chgBit(oldp+6,((3U == (3U & ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_primary) 
                                           >> 0x0000000aU)))));
        bufp->chgBit(oldp+7,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_hit));
        bufp->chgIData(oldp+8,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr),27);
        bufp->chgIData(oldp+9,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_evict_addr),27);
        bufp->chgBit(oldp+10,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__actual_flush));
        bufp->chgCData(oldp+11,((7U & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)),3);
        bufp->chgCData(oldp+12,((0x0000000fU & ((IData)(8U) 
                                                - (7U 
                                                   & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)))),4);
        bufp->chgSData(oldp+13,((0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                >> 0x00000011U))),10);
        bufp->chgSData(oldp+14,((0x000007ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                >> 6U))),11);
        bufp->chgCData(oldp+15,((0x0000003fU & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)),6);
        bufp->chgSData(oldp+16,((0x000003ffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                >> 7U))),10);
        bufp->chgSData(oldp+17,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_primary),12);
        bufp->chgQData(oldp+18,((QData)((IData)((0x00000038U 
                                                 & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                    << 3U))))),64);
        bufp->chgQData(oldp+20,((QData)((IData)((0x00000078U 
                                                 & (((IData)(8U) 
                                                     - 
                                                     (7U 
                                                      & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)) 
                                                    << 3U))))),64);
        bufp->chgQData(oldp+22,(((- (QData)((IData)(
                                                    (0x40U 
                                                     > 
                                                     (0x00000078U 
                                                      & (((IData)(8U) 
                                                          - 
                                                          (7U 
                                                           & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)) 
                                                         << 3U)))))) 
                                 & VL_SHIFTL_QQI(64,64,7, vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb, 
                                                 (0x00000078U 
                                                  & (((IData)(8U) 
                                                      - 
                                                      (7U 
                                                       & vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr)) 
                                                     << 3U))))),64);
        bufp->chgQData(oldp+24,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__data_out_rotated),64);
        bufp->chgSData(oldp+26,((0x00003fffU & (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                >> 3U))),14);
        bufp->chgSData(oldp+27,((0x00003fffU & ((IData)(1U) 
                                                + (vlSelfRef.submem_tb__DOT__dut__DOT__cache_addr 
                                                   >> 3U)))),14);
    }
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[2U] 
                      | vlSelfRef.__Vm_traceActivity[4U])))) {
        bufp->chgBit(oldp+28,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_spill_dirty));
        bufp->chgBit(oldp+29,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_spill_hit));
        bufp->chgIData(oldp+30,(((0x07fe0000U & ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_spill) 
                                                 << 0x00000011U)) 
                                 | ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_index) 
                                    << 6U))),27);
        bufp->chgBit(oldp+31,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_line_spill));
        bufp->chgBit(oldp+32,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_miss));
        bufp->chgSData(oldp+33,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_index),11);
        bufp->chgSData(oldp+34,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_tag),10);
        bufp->chgSData(oldp+35,((0x000003ffU & ((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_index) 
                                                >> 1U))),10);
        bufp->chgSData(oldp+36,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_spill),12);
    }
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[3U] 
                      | vlSelfRef.__Vm_traceActivity[4U])))) {
        bufp->chgBit(oldp+37,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_mem_write));
        bufp->chgBit(oldp+38,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_we));
        bufp->chgSData(oldp+39,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_waddr),10);
        bufp->chgSData(oldp+40,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_wdata),12);
        bufp->chgBit(oldp+41,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_we));
        bufp->chgSData(oldp+42,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_waddr),10);
        bufp->chgSData(oldp+43,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_wdata),12);
        bufp->chgCData(oldp+44,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web),8);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[4U]))) {
        bufp->chgQData(oldp+45,(vlSelfRef.submem_tb__DOT__rdata),64);
        bufp->chgCData(oldp+47,(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr),3);
        bufp->chgBit(oldp+48,(vlSelfRef.submem_tb__DOT__s_amc_data_in_last));
        bufp->chgBit(oldp+49,(vlSelfRef.submem_tb__DOT__s_amc_data_in_valid));
        bufp->chgBit(oldp+50,(vlSelfRef.submem_tb__DOT__s_amc_data_out_valid));
        bufp->chgBit(oldp+51,(vlSelfRef.submem_tb__DOT__s_amc_data_out_last));
        bufp->chgBit(oldp+52,(vlSelfRef.submem_tb__DOT__s_amc_busy));
        bufp->chgBit(oldp+53,(vlSelfRef.submem_tb__DOT__s_amc_err));
        bufp->chgBit(oldp+54,(vlSelfRef.submem_tb__DOT__arvalid));
        bufp->chgBit(oldp+55,(vlSelfRef.submem_tb__DOT__arready));
        bufp->chgBit(oldp+56,(vlSelfRef.submem_tb__DOT__rlast));
        bufp->chgBit(oldp+57,(vlSelfRef.submem_tb__DOT__rvalid));
        bufp->chgBit(oldp+58,(vlSelfRef.submem_tb__DOT__rready));
        bufp->chgBit(oldp+59,(vlSelfRef.submem_tb__DOT__awvalid));
        bufp->chgBit(oldp+60,(vlSelfRef.submem_tb__DOT__awready));
        bufp->chgBit(oldp+61,((7U == (IData)(vlSelfRef.submem_tb__DOT__amc_instance__DOT__cntr))));
        bufp->chgBit(oldp+62,(vlSelfRef.submem_tb__DOT__wvalid));
        bufp->chgBit(oldp+63,(vlSelfRef.submem_tb__DOT__wready));
        bufp->chgBit(oldp+64,(vlSelfRef.submem_tb__DOT__bvalid));
        bufp->chgBit(oldp+65,(vlSelfRef.submem_tb__DOT__bready));
        bufp->chgIData(oldp+66,(vlSelfRef.submem_tb__DOT__araddr),32);
        bufp->chgIData(oldp+67,(vlSelfRef.submem_tb__DOT__awaddr),32);
        bufp->chgCData(oldp+68,(vlSelfRef.submem_tb__DOT__amc_instance__DOT__state),3);
        bufp->chgBit(oldp+69,(vlSelfRef.submem_tb__DOT__dut__DOT__dirty));
        bufp->chgBit(oldp+70,(vlSelfRef.submem_tb__DOT__dut__DOT__hit));
        bufp->chgBit(oldp+71,(vlSelfRef.submem_tb__DOT__dut__DOT__spill_hit));
        bufp->chgBit(oldp+72,(vlSelfRef.submem_tb__DOT__dut__DOT__spill_dirty));
        bufp->chgBit(oldp+73,(vlSelfRef.submem_tb__DOT__dut__DOT__line_spill));
        bufp->chgIData(oldp+74,(vlSelfRef.submem_tb__DOT__dut__DOT__evict_addr),27);
        bufp->chgIData(oldp+75,(vlSelfRef.submem_tb__DOT__dut__DOT__spill_evict_addr),27);
        bufp->chgBit(oldp+76,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_entry));
        bufp->chgBit(oldp+77,(vlSelfRef.submem_tb__DOT__dut__DOT__last_flush));
        bufp->chgIData(oldp+78,(vlSelfRef.submem_tb__DOT__dut__DOT__miss_addr),27);
        bufp->chgIData(oldp+79,((0x07ffffffU & ((IData)(0x00000040U) 
                                                + vlSelfRef.submem_tb__DOT__dut__DOT__miss_addr))),27);
        bufp->chgBit(oldp+80,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__flush));
        bufp->chgQData(oldp+81,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta),64);
        bufp->chgQData(oldp+83,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb),64);
        bufp->chgIData(oldp+85,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__j),32);
        bufp->chgIData(oldp+86,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__k),32);
        bufp->chgIData(oldp+87,(vlSelfRef.submem_tb__DOT__slave__DOT__rng),32);
        bufp->chgIData(oldp+88,(vlSelfRef.submem_tb__DOT__slave__DOT__rng_next1),32);
        bufp->chgIData(oldp+89,(vlSelfRef.submem_tb__DOT__slave__DOT__rng_next2),32);
        bufp->chgIData(oldp+90,(((vlSelfRef.submem_tb__DOT__slave__DOT__rng_next2 
                                  << 5U) ^ vlSelfRef.submem_tb__DOT__slave__DOT__rng_next2)),32);
        bufp->chgCData(oldp+91,(vlSelfRef.submem_tb__DOT__slave__DOT__rstate),2);
        bufp->chgIData(oldp+92,(vlSelfRef.submem_tb__DOT__slave__DOT__raddr_q),32);
        bufp->chgCData(oldp+93,(vlSelfRef.submem_tb__DOT__slave__DOT__rbeat),3);
        bufp->chgCData(oldp+94,(vlSelfRef.submem_tb__DOT__slave__DOT__rdelay),3);
        bufp->chgBit(oldp+95,(vlSelfRef.submem_tb__DOT__slave__DOT__aw_done));
        bufp->chgIData(oldp+96,(vlSelfRef.submem_tb__DOT__slave__DOT__waddr_q),32);
        bufp->chgCData(oldp+97,(vlSelfRef.submem_tb__DOT__slave__DOT__wbeat),3);
        bufp->chgBit(oldp+98,(vlSelfRef.submem_tb__DOT__slave__DOT__w_done));
        Vsubmem_tb___024root__trace_chg_dtype____0(vlSelf, bufp, 99, vlSelfRef.submem_tb__DOT__slave__DOT__wbuf);
        Vsubmem_tb___024root__trace_chg_dtype____1(vlSelf, bufp, 115, vlSelfRef.submem_tb__DOT__slave__DOT__wstrb_q);
        bufp->chgCData(oldp+123,(vlSelfRef.submem_tb__DOT__slave__DOT__bdelay),4);
        bufp->chgBit(oldp+124,(vlSelfRef.submem_tb__DOT__slave__DOT__b_pending));
        bufp->chgCData(oldp+125,(vlSelfRef.submem_tb__DOT__slave__DOT__awdelay),3);
        bufp->chgBit(oldp+126,(vlSelfRef.submem_tb__DOT__slave__DOT__aw_late));
        bufp->chgIData(oldp+127,(vlSelfRef.submem_tb__DOT__slave__DOT__wi),32);
        bufp->chgIData(oldp+128,(vlSelfRef.submem_tb__DOT__slave__DOT__wb),32);
    }
    bufp->chgBit(oldp+129,(vlSelfRef.clk));
    bufp->chgBit(oldp+130,(vlSelfRef.rst));
    bufp->chgIData(oldp+131,(vlSelfRef.addr),27);
    bufp->chgBit(oldp+132,(vlSelfRef.mem_read));
    bufp->chgBit(oldp+133,(vlSelfRef.mem_write));
    bufp->chgCData(oldp+134,(vlSelfRef.bw),2);
    bufp->chgQData(oldp+135,(vlSelfRef.data_in),64);
    bufp->chgQData(oldp+137,(vlSelfRef.data_out),64);
    bufp->chgBit(oldp+139,(vlSelfRef.busy));
    bufp->chgBit(oldp+140,(vlSelfRef.flush));
    bufp->chgBit(oldp+141,(vlSelfRef.flush_done));
    bufp->chgIData(oldp+142,(vlSelfRef.rng_seed),32);
    bufp->chgIData(oldp+143,(vlSelfRef.bd_addr),32);
    bufp->chgQData(oldp+144,(vlSelfRef.bd_data),64);
    bufp->chgBit(oldp+146,(((3U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)) 
                            | (4U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)))));
    bufp->chgBit(oldp+147,(((7U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)) 
                            | ((1U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state)) 
                               | (2U == (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))))));
    bufp->chgCData(oldp+148,(vlSelfRef.submem_tb__DOT__dut__DOT__state),5);
    bufp->chgSData(oldp+149,(vlSelfRef.submem_tb__DOT__dut__DOT__flush_line),11);
    bufp->chgIData(oldp+150,(((IData)(vlSelfRef.submem_tb__DOT__dut__DOT__flush_line) 
                              << 6U)),27);
    bufp->chgBit(oldp+151,(((IData)(vlSelfRef.mem_read) 
                            | (IData)(vlSelfRef.mem_write))));
    bufp->chgBit(oldp+152,((IData)(((0U == (0x18U & (IData)(vlSelfRef.submem_tb__DOT__dut__DOT__state))) 
                                    & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_7)))));
    bufp->chgQData(oldp+153,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_data_in),64);
    bufp->chgCData(oldp+155,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_bw),2);
    bufp->chgQData(oldp+156,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina),64);
    bufp->chgBit(oldp+158,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__ena));
    bufp->chgCData(oldp+159,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea),8);
    bufp->chgQData(oldp+160,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb),64);
    bufp->chgBit(oldp+162,(vlSelfRef.submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__enb));
}

void Vsubmem_tb___024root__trace_chg_dtype____0(Vsubmem_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp, uint32_t offset, const VlUnpacked<QData/*63:0*/, 8>& __VdtypeVar) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root__trace_chg_dtype____0\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode +  offset);
    bufp->chgQData(oldp+0,(__VdtypeVar[0]),64);
    bufp->chgQData(oldp+2,(__VdtypeVar[1]),64);
    bufp->chgQData(oldp+4,(__VdtypeVar[2]),64);
    bufp->chgQData(oldp+6,(__VdtypeVar[3]),64);
    bufp->chgQData(oldp+8,(__VdtypeVar[4]),64);
    bufp->chgQData(oldp+10,(__VdtypeVar[5]),64);
    bufp->chgQData(oldp+12,(__VdtypeVar[6]),64);
    bufp->chgQData(oldp+14,(__VdtypeVar[7]),64);
}

void Vsubmem_tb___024root__trace_chg_dtype____1(Vsubmem_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp, uint32_t offset, const VlUnpacked<CData/*7:0*/, 8>& __VdtypeVar) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root__trace_chg_dtype____1\n"); );
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode +  offset);
    bufp->chgCData(oldp+0,(__VdtypeVar[0]),8);
    bufp->chgCData(oldp+1,(__VdtypeVar[1]),8);
    bufp->chgCData(oldp+2,(__VdtypeVar[2]),8);
    bufp->chgCData(oldp+3,(__VdtypeVar[3]),8);
    bufp->chgCData(oldp+4,(__VdtypeVar[4]),8);
    bufp->chgCData(oldp+5,(__VdtypeVar[5]),8);
    bufp->chgCData(oldp+6,(__VdtypeVar[6]),8);
    bufp->chgCData(oldp+7,(__VdtypeVar[7]),8);
}

void Vsubmem_tb___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsubmem_tb___024root__trace_cleanup\n"); );
    // Body
    Vsubmem_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsubmem_tb___024root*>(voidSelf);
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[4U] = 0U;
}
