`include "defs.vh"

// forwarding unit
module fwd_unit (
  input wire `W(`RLEN)       __id_rs1,
  input wire `W(`RLEN)       __id_rs2,
  input wire `W(`RLEN)       __ex_rs1,
  input wire `W(`RLEN)       __ex_rs2,

  input wire `W(`RLEN)       __ex_rd,
  input wire `W(`RLEN)       __mem_rd,
  input wire `W(`RLEN)       __wb_rd,

  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`CTL_BUSLEN) __ex_ctl_bus,
  input wire `W(`CTL_BUSLEN) __mem_ctl_bus,
  input wire `W(`CTL_BUSLEN) __wb_ctl_bus,
  /* verilator lint_on UNUSEDSIGNAL */

  output reg `W(`FWDLEN)     __id_fwd1,
  output reg `W(`FWDLEN)     __id_fwd2,
  output reg `W(`FWDLEN)     __ex_fwd1,
  output reg `W(`FWDLEN)     __ex_fwd2
);
  wire is_write_id_ex  = `REG_WRITE(__ex_ctl_bus) & (__ex_rd != 0);
  wire is_write_ex_mem = `REG_WRITE(__mem_ctl_bus) && (__mem_rd != 0);
  wire is_write_mem_wb = `REG_WRITE(__wb_ctl_bus) && (__wb_rd != 0);

  /* Fwding to ID stage (for branching/jal) */

  // ID Hazard
  wire __id_fwd1_id_ex  = is_write_id_ex  && (__ex_rd == __id_rs1); 
  wire __id_fwd2_id_ex  = is_write_id_ex  && (__ex_rd == __id_rs2); 

  // EX Hazard
  wire __id_fwd1_ex_mem = is_write_ex_mem && (__mem_rd == __id_rs1); 
  wire __id_fwd2_ex_mem = is_write_ex_mem && (__mem_rd == __id_rs2); 

  // MEM Hazard
  wire __id_fwd1_mem_wb = is_write_mem_wb && (__wb_rd == __id_rs1); 
  wire __id_fwd2_mem_wb = is_write_mem_wb && (__wb_rd == __id_rs2); 

  always @(*) begin
    if(__id_fwd1_id_ex) __id_fwd1 = `FWD_ID_EX;
    else if(__id_fwd1_ex_mem) __id_fwd1 = `FWD_EX_MEM;
    else if(__id_fwd1_mem_wb) __id_fwd1 = `FWD_MEM_WB;
    else __id_fwd1 = `FWD_NONE;

    if(__id_fwd2_id_ex) __id_fwd2 = `FWD_ID_EX;
    else if(__id_fwd2_ex_mem) __id_fwd2 = `FWD_EX_MEM;
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

endmodule
