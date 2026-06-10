`include "defs.vh"

// forwarding unit
module fwd_unit (
  input wire `W(`RLEN)       __ex_rs1,
  input wire `W(`RLEN)       __ex_rs2,
  input wire `W(`RLEN)       __mem_rd,
  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`CTL_BUSLEN) __mem_ctl_bus,
  /* verilator lint_on UNUSEDSIGNAL */
  input wire `W(`RLEN)       __wb_rd,

  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`CTL_BUSLEN) __wb_ctl_bus,
  /* verilator lint_on UNUSEDSIGNAL */

  output reg `W(`FWDLEN)     __ex_fwd1,
  output reg `W(`FWDLEN)     __ex_fwd2
);
  always @(*) begin
    __ex_fwd1 = `FWD_NONE;
    __ex_fwd2 = `FWD_NONE;

    // EX hazard
    if(`REG_WRITE(__mem_ctl_bus) && (__mem_rd != 0)) begin
      if(__mem_rd == __ex_rs1) __ex_fwd1 = `FWD_EX_MEM;
      if(__mem_rd == __ex_rs2) __ex_fwd2 = `FWD_EX_MEM;
    end

    // MEM hazard
    if((`REG_WRITE(__wb_ctl_bus)) && (__wb_rd != 0)) begin
      // prevent double data hazards by prioritizing EX hazard
      if(!(`REG_WRITE(__mem_ctl_bus) && (__mem_rd != 0) && (__mem_rd == __ex_rs1)) &&
          (__wb_rd == __ex_rs1)) __ex_fwd1 = `FWD_MEM_WB;

      if(!(`REG_WRITE(__mem_ctl_bus) && (__mem_rd != 0) && (__mem_rd == __ex_rs2)) &&
          (__wb_rd == __ex_rs2)) __ex_fwd2 = `FWD_MEM_WB;
    end
 
  end
endmodule
