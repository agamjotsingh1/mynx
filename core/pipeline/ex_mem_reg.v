`include "defs.vh"

module ex_mem_reg (
  input wor `W(`STLEN)   stall,
  input wor `W(`NOPILEN) nopi,

  input wire clk,
  input wire rst,

  input wire `W(`DLEN)       in_pc,
  input wire `W(`RLEN)       in_rs1,
  input wire `W(`RLEN)       in_rs2,
  input wire `W(`RLEN)       in_rd,
  input wire `W(`DLEN)       in_imm,
  input wire `W(`DLEN)       in_ex_res,
  input wire `W(`DLEN)       in_mem_data,
  input wire `W(`CTL_BUSLEN) in_ctl_bus,

  output reg `W(`DLEN)       out_pc,
  output reg `W(`RLEN)       out_rs1,
  output reg `W(`RLEN)       out_rs2,
  output reg `W(`RLEN)       out_rd,
  output reg `W(`DLEN)       out_imm,
  output reg `W(`DLEN)       out_ex_res,
  output reg `W(`DLEN)       out_mem_data,
  output reg `W(`CTL_BUSLEN) out_ctl_bus
);
  /* verilator lint_off WIDTHTRUNC */
  always @(posedge clk) begin
    if(rst || (nopi & `NOPI_EX_MEM)) begin
      out_pc <= `RSTPC;
      out_rs1 <= 0;
      out_rs2 <= 0;
      out_rd <= 0;
      out_imm <= 0;
      out_ex_res <= 0;
      out_mem_data <= 0;
      out_ctl_bus <= 0;
    end
    else if (!(stall & `STALL_EX_MEM)) begin
      out_pc <= in_pc;
      out_rs1 <= in_rs1;
      out_rs2 <= in_rs2;
      out_rd <= in_rd;
      out_imm <= in_imm;
      out_ex_res <= in_ex_res;
      out_mem_data <= in_mem_data;
      out_ctl_bus <= in_ctl_bus;
   end
  end
  /* verilator lint_on WIDTHTRUNC */
endmodule
