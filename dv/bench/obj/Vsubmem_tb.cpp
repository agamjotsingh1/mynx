// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vsubmem_tb__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vsubmem_tb::Vsubmem_tb(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vsubmem_tb__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , mem_read{vlSymsp->TOP.mem_read}
    , mem_write{vlSymsp->TOP.mem_write}
    , bw{vlSymsp->TOP.bw}
    , busy{vlSymsp->TOP.busy}
    , flush{vlSymsp->TOP.flush}
    , flush_done{vlSymsp->TOP.flush_done}
    , addr{vlSymsp->TOP.addr}
    , rng_seed{vlSymsp->TOP.rng_seed}
    , bd_addr{vlSymsp->TOP.bd_addr}
    , data_in{vlSymsp->TOP.data_in}
    , data_out{vlSymsp->TOP.data_out}
    , bd_data{vlSymsp->TOP.bd_data}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vsubmem_tb::Vsubmem_tb(const char* _vcname__)
    : Vsubmem_tb(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vsubmem_tb::~Vsubmem_tb() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vsubmem_tb___024root___eval_debug_assertions(Vsubmem_tb___024root* vlSelf);
#endif  // VL_DEBUG
void Vsubmem_tb___024root___eval_static(Vsubmem_tb___024root* vlSelf);
void Vsubmem_tb___024root___eval_initial(Vsubmem_tb___024root* vlSelf);
void Vsubmem_tb___024root___eval_settle(Vsubmem_tb___024root* vlSelf);
void Vsubmem_tb___024root___eval(Vsubmem_tb___024root* vlSelf);

void Vsubmem_tb::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vsubmem_tb::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vsubmem_tb___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vsubmem_tb___024root___eval_static(&(vlSymsp->TOP));
        Vsubmem_tb___024root___eval_initial(&(vlSymsp->TOP));
        Vsubmem_tb___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vsubmem_tb___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vsubmem_tb::eventsPending() { return false; }

uint64_t Vsubmem_tb::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vsubmem_tb::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vsubmem_tb___024root___eval_final(Vsubmem_tb___024root* vlSelf);

VL_ATTR_COLD void Vsubmem_tb::final() {
    contextp()->executingFinal(true);
    Vsubmem_tb___024root___eval_final(&(vlSymsp->TOP));
    contextp()->executingFinal(false);
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vsubmem_tb::hierName() const { return vlSymsp->name(); }
const char* Vsubmem_tb::modelName() const { return "Vsubmem_tb"; }
unsigned Vsubmem_tb::threads() const { return 1; }
void Vsubmem_tb::prepareClone() const { contextp()->prepareClone(); }
void Vsubmem_tb::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vsubmem_tb::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false}};
};

//============================================================
// Trace configuration

void Vsubmem_tb___024root__trace_decl_types(VerilatedVcd* tracep);

void Vsubmem_tb___024root__trace_init_top(Vsubmem_tb___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vsubmem_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsubmem_tb___024root*>(voidSelf);
    Vsubmem_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(vlSymsp->name(), VerilatedTracePrefixType::SCOPE_MODULE);
    Vsubmem_tb___024root__trace_decl_types(tracep);
    Vsubmem_tb___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vsubmem_tb___024root__trace_register(Vsubmem_tb___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vsubmem_tb::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vsubmem_tb::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP), name(), false, 194);
    Vsubmem_tb___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
