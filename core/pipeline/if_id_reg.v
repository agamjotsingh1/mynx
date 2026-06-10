`include "defs.vh"

module if_id_reg (
  input wor `W(`STLEN) stall,

  input wire clk,
  input wire rst,

  input wire `W(`DLEN) in_pc,
  input wire `W(`ILEN) in_instr,

  output reg `W(`DLEN) out_pc,
  output reg `W(`ILEN) out_instr
);
  always @(posedge clk) begin
    if(rst) begin
      out_pc <= `RSTPC;
      out_instr <= `RSTINSTR;
    end
    /* verilator lint_off WIDTHTRUNC */
    else if (!(stall & `STALL_IF_ID)) begin
    /* verilator lint_on WIDTHTRUNC */
      out_pc <= in_pc;
      out_instr <= in_instr;
    end
  end
endmodule
