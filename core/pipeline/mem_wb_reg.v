`include "defs.vh"

module mem_wb_reg (
  input wor hard_stall,
  input wor `W(`STLEN)   stall,
  input wor `W(`NOPILEN) nopi,
  input wire clk,
  input wire rst,

  input wire `W(`RLEN)       in_rd,
  input wire `W(`DLEN)       in_mem_res,
  input wire `W(`DLEN)       in_regw_data,
  input wire `W(`CTL_BUSLEN) in_ctl_bus,

  output reg `W(`RLEN)       out_rd,
  output reg `W(`DLEN)       out_mem_res,
  output reg `W(`DLEN)       out_regw_data,
  output reg `W(`CTL_BUSLEN) out_ctl_bus
);
  /* verilator lint_off WIDTHTRUNC */
  always @(posedge clk) begin
    if(!hard_stall) begin
      if(rst || (nopi & `NOPI_MEM_WB)) begin
        out_rd        <= 0;
        out_mem_res   <= 0;
        out_regw_data <= 0;
        out_ctl_bus   <= 0;
      end
      else if (!(stall & `STALL_MEM_WB)) begin
        out_rd        <= in_rd;
        out_mem_res   <= in_mem_res;
        out_regw_data <= in_regw_data;
        out_ctl_bus   <= in_ctl_bus;
      end
    end
  end
  /* verilator lint_on WIDTHTRUNC */
endmodule
