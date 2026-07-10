// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vsubmem_tb.h for the primary calling header

#ifndef VERILATED_VSUBMEM_TB___024ROOT_H_
#define VERILATED_VSUBMEM_TB___024ROOT_H_  // guard

#include "verilated.h"


class Vsubmem_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vsubmem_tb___024root final {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk,0,0);
        VL_IN8(rst,0,0);
        VL_IN8(mem_read,0,0);
        VL_IN8(mem_write,0,0);
        VL_IN8(bw,1,0);
        VL_OUT8(busy,0,0);
        VL_IN8(flush,0,0);
        VL_OUT8(flush_done,0,0);
        CData/*0:0*/ submem_tb__DOT__s_amc_data_in_last;
        CData/*0:0*/ submem_tb__DOT__s_amc_data_in_valid;
        CData/*0:0*/ submem_tb__DOT__s_amc_data_out_valid;
        CData/*0:0*/ submem_tb__DOT__s_amc_data_out_last;
        CData/*0:0*/ submem_tb__DOT__s_amc_busy;
        CData/*0:0*/ submem_tb__DOT__s_amc_err;
        CData/*0:0*/ submem_tb__DOT__arvalid;
        CData/*0:0*/ submem_tb__DOT__arready;
        CData/*0:0*/ submem_tb__DOT__rlast;
        CData/*0:0*/ submem_tb__DOT__rvalid;
        CData/*0:0*/ submem_tb__DOT__rready;
        CData/*0:0*/ submem_tb__DOT__awvalid;
        CData/*0:0*/ submem_tb__DOT__awready;
        CData/*0:0*/ submem_tb__DOT__wvalid;
        CData/*0:0*/ submem_tb__DOT__wready;
        CData/*0:0*/ submem_tb__DOT__bvalid;
        CData/*0:0*/ submem_tb__DOT__bready;
        CData/*4:0*/ submem_tb__DOT__dut__DOT__state;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__dirty;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__hit;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__spill_hit;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__spill_dirty;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__line_spill;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__cache_hit;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__cache_spill_dirty;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__cache_spill_hit;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__cache_mem_write;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__cache_entry;
        CData/*1:0*/ submem_tb__DOT__dut__DOT__cache_bw;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__cache_line_spill;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__last_flush;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__cache_miss;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__flush;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__actual_flush;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_we;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_we;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__ena;
        CData/*7:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__wea;
        CData/*0:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__enb;
        CData/*7:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__web;
        CData/*1:0*/ submem_tb__DOT__slave__DOT__rstate;
        CData/*2:0*/ submem_tb__DOT__slave__DOT__rbeat;
        CData/*2:0*/ submem_tb__DOT__slave__DOT__rdelay;
        CData/*0:0*/ submem_tb__DOT__slave__DOT__aw_done;
        CData/*2:0*/ submem_tb__DOT__slave__DOT__wbeat;
        CData/*0:0*/ submem_tb__DOT__slave__DOT__w_done;
        CData/*3:0*/ submem_tb__DOT__slave__DOT__bdelay;
        CData/*0:0*/ submem_tb__DOT__slave__DOT__b_pending;
        CData/*2:0*/ submem_tb__DOT__slave__DOT__awdelay;
        CData/*0:0*/ submem_tb__DOT__slave__DOT__aw_late;
        CData/*2:0*/ submem_tb__DOT__amc_instance__DOT__state;
        CData/*2:0*/ submem_tb__DOT__amc_instance__DOT__cntr;
        CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_7;
        CData/*7:0*/ __VdfgRegularize_h6e95ff9d_0_8;
        CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_9;
        CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_10;
    };
    struct {
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VstlPhaseResult;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__rst__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__mem_read__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__mem_write__0;
        CData/*1:0*/ __Vtrigprevexpr___TOP__bw__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__flush__0;
        CData/*0:0*/ __VicoDidInit;
        CData/*0:0*/ __VicoPhaseResult;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clk__1;
        CData/*0:0*/ __VactPhaseResult;
        CData/*0:0*/ __VnbaPhaseResult;
        SData/*10:0*/ submem_tb__DOT__dut__DOT__flush_line;
        SData/*11:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_primary;
        SData/*10:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_index;
        SData/*9:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__spill_tag;
        SData/*11:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_spill;
        SData/*9:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_waddr;
        SData/*11:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even_wdata;
        SData/*9:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_waddr;
        SData/*11:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd_wdata;
        VL_IN(addr,26,0);
        VL_IN(rng_seed,31,0);
        VL_IN(bd_addr,31,0);
        IData/*26:0*/ submem_tb__DOT__s_amc_addr;
        IData/*31:0*/ submem_tb__DOT__araddr;
        IData/*31:0*/ submem_tb__DOT__awaddr;
        IData/*26:0*/ submem_tb__DOT__dut__DOT__evict_addr;
        IData/*26:0*/ submem_tb__DOT__dut__DOT__spill_evict_addr;
        IData/*26:0*/ submem_tb__DOT__dut__DOT__cache_addr;
        IData/*26:0*/ submem_tb__DOT__dut__DOT__cache_evict_addr;
        IData/*26:0*/ submem_tb__DOT__dut__DOT__miss_addr;
        IData/*31:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__i;
        IData/*31:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__i;
        IData/*31:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__j;
        IData/*31:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__k;
        IData/*31:0*/ submem_tb__DOT__slave__DOT__i;
        IData/*31:0*/ submem_tb__DOT__slave__DOT__rng;
        IData/*31:0*/ submem_tb__DOT__slave__DOT__rng_next1;
        IData/*31:0*/ submem_tb__DOT__slave__DOT__rng_next2;
        IData/*31:0*/ submem_tb__DOT__slave__DOT__raddr_q;
        IData/*31:0*/ submem_tb__DOT__slave__DOT__waddr_q;
        IData/*31:0*/ submem_tb__DOT__slave__DOT__wi;
        IData/*31:0*/ submem_tb__DOT__slave__DOT__wb;
        IData/*26:0*/ __Vtrigprevexpr___TOP__addr__0;
        IData/*31:0*/ __Vtrigprevexpr___TOP__rng_seed__0;
        IData/*31:0*/ __Vtrigprevexpr___TOP__bd_addr__0;
        IData/*31:0*/ __VactIterCount;
        VL_IN64(data_in,63,0);
        VL_OUT64(data_out,63,0);
        VL_OUT64(bd_data,63,0);
        QData/*63:0*/ submem_tb__DOT__rdata;
        QData/*63:0*/ submem_tb__DOT__dut__DOT__cache_data_in;
        QData/*63:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_douta;
        QData/*63:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT_____05Fbram_doutb;
        QData/*63:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__data_out_rotated;
        QData/*63:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dina;
        QData/*63:0*/ submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__dinb;
        QData/*63:0*/ submem_tb__DOT__slave__DOT__i64;
        QData/*63:0*/ __Vtrigprevexpr___TOP__data_in__0;
        VlUnpacked<SData/*11:0*/, 1024> submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_even;
        VlUnpacked<SData/*11:0*/, 1024> submem_tb__DOT__dut__DOT__cache_instance__DOT__meta_odd;
        VlUnpacked<QData/*63:0*/, 16384> submem_tb__DOT__dut__DOT__cache_instance__DOT__cache_bram_instance__DOT__mem;
    };
    struct {
        VlUnpacked<QData/*63:0*/, 131072> submem_tb__DOT__slave__DOT__ram;
        VlUnpacked<QData/*63:0*/, 8> submem_tb__DOT__slave__DOT__wbuf;
        VlUnpacked<CData/*7:0*/, 8> submem_tb__DOT__slave__DOT__wstrb_q;
        VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 2> __VicoTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
        VlUnpacked<CData/*0:0*/, 5> __Vm_traceActivity;
    };

    // INTERNAL VARIABLES
    Vsubmem_tb__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vsubmem_tb___024root(Vsubmem_tb__Syms* symsp, const char* namep);
    ~Vsubmem_tb___024root();
    VL_UNCOPYABLE(Vsubmem_tb___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
