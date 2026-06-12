`include "defs.vh"

module ex_mem_reg (
  input wor `W(`STLEN)   stall,
  input wor `W(`NOPILEN) nopi,

  input wire clk,
  input wire rst,

  input wire `W(`RLEN)       in_rd,
  input wire `W(`DLEN)       in_ex_res,
  input wire `W(`DLEN)       in_mem_data,
  input wire `W(`CTL_BUSLEN) in_ctl_bus,

  output reg `W(`RLEN)       out_rd,
  output reg `W(`DLEN)       out_ex_res,
  output reg `W(`DLEN)       out_mem_data,
  output reg `W(`CTL_BUSLEN) out_ctl_bus
);
  /* verilator lint_off WIDTHTRUNC */
  always @(posedge clk) begin
    if(rst || (nopi & `NOPI_EX_MEM)) begin
      out_rd <= 0;
      out_ex_res <= 0;
      out_mem_data <= 0;
      out_ctl_bus <= 0;
    end
    else if (!(stall & `STALL_EX_MEM)) begin
      out_rd <= in_rd;
      out_ex_res <= in_ex_res;
      out_mem_data <= in_mem_data;
      out_ctl_bus <= in_ctl_bus;
   end
  end
  /* verilator lint_on WIDTHTRUNC */
endmodule
