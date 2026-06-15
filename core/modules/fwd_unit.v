`include "defs.vh"

// TODO! optimize by eliminating some forwards to ID stage
// forwarding unit
module fwd_unit (
  input wire `W(`RLEN)       __id_rs1,
  input wire `W(`RLEN)       __id_rs2,
  input wire `W(`RLEN)       __ex_rs1,
  input wire `W(`RLEN)       __ex_rs2,
  input wire `W(`CSRLEN)     __ex_csr,

  input wire `W(`RLEN)       __mem_rd,
  input wire `W(`RLEN)       __wb_rd,

  input wire `W(`CSRLEN)     __mem_csr,
  input wire `W(`CSRLEN)     __wb_csr,

  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`CTL_BUSLEN) __mem_ctl_bus,
  input wire `W(`CTL_BUSLEN) __wb_ctl_bus,
  /* verilator lint_on UNUSEDSIGNAL */

  output reg `W(`FWDLEN)     __id_fwd1,
  output reg `W(`FWDLEN)     __id_fwd2,
  output reg `W(`FWDLEN)     __ex_fwd1,
  output reg `W(`FWDLEN)     __ex_fwd2,
  output reg `W(`FWDLEN)     __ex_fwdcsr
);
  wire is_write_ex_mem = `REG_WRITE(__mem_ctl_bus) && (__mem_rd != 0);
  wire is_write_mem_wb = `REG_WRITE(__wb_ctl_bus) && (__wb_rd != 0);

  /* Fwding to ID stage (for branching/jal) */

  // FIXME! mem/wb forward not needed
  // EX Hazard
  wire __id_fwd1_ex_mem = is_write_ex_mem && (__mem_rd == __id_rs1); 
  wire __id_fwd2_ex_mem = is_write_ex_mem && (__mem_rd == __id_rs2); 

  // MEM Hazard
  wire __id_fwd1_mem_wb = is_write_mem_wb && (__wb_rd == __id_rs1); 
  wire __id_fwd2_mem_wb = is_write_mem_wb && (__wb_rd == __id_rs2); 

  always @(*) begin
    if(__id_fwd1_ex_mem) __id_fwd1 = `FWD_EX_MEM;
    else if(__id_fwd1_mem_wb) __id_fwd1 = `FWD_MEM_WB;
    else __id_fwd1 = `FWD_NONE;

    if(__id_fwd2_ex_mem) __id_fwd2 = `FWD_EX_MEM;
    else if(__id_fwd2_mem_wb) __id_fwd2 = `FWD_MEM_WB;
    else __id_fwd2 = `FWD_NONE;
  end


  /* Fwding to EX stage */

  // EX Hazard
  wire __ex_fwd1_ex_mem = is_write_ex_mem && (__mem_rd == __ex_rs1); 
  wire __ex_fwd2_ex_mem = is_write_ex_mem && (__mem_rd == __ex_rs2); 

  // MEM Hazard
  wire __ex_fwd1_mem_wb = is_write_mem_wb && (__wb_rd == __ex_rs1); 
  wire __ex_fwd2_mem_wb = is_write_mem_wb && (__wb_rd == __ex_rs2); 

  always @(*) begin
    if(__ex_fwd1_ex_mem) __ex_fwd1 = `FWD_EX_MEM;
    else if(__ex_fwd1_mem_wb) __ex_fwd1 = `FWD_MEM_WB;
    else __ex_fwd1 = `FWD_NONE;

    if(__ex_fwd2_ex_mem) __ex_fwd2 = `FWD_EX_MEM;
    else if(__ex_fwd2_mem_wb) __ex_fwd2 = `FWD_MEM_WB;
    else __ex_fwd2 = `FWD_NONE;
  end

  // CSR forwards
  wire is_csrwrite_ex_mem = `ZICSR_OP(__mem_ctl_bus) != `ZICSR_OP_NONE;
  wire is_csrwrite_mem_wb = `ZICSR_OP(__wb_ctl_bus) != `ZICSR_OP_NONE;

  wire __ex_fwdcsr_ex_mem = is_csrwrite_ex_mem && (__mem_csr == __ex_csr);
  wire __ex_fwdcsr_mem_wb = is_csrwrite_mem_wb && (__wb_csr == __ex_csr);

  always @(*) begin
    if(__ex_fwdcsr_ex_mem) __ex_fwdcsr = `FWD_EX_MEM;
    else if(__ex_fwdcsr_mem_wb) __ex_fwdcsr = `FWD_MEM_WB;
    else __ex_fwdcsr = `FWD_NONE;
  end
endmodule
