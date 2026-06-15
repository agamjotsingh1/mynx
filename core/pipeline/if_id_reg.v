`include "defs.vh"

module if_id_reg (
  input wor hard_stall,

  input wor `W(`STLEN)   stall,
  input wor `W(`NOPILEN) nopi,

  input wire clk,
  input wire rst,

  input wire `W(`DLEN) in_pc,
  input wire `W(`ILEN) in_instr,

  output reg `W(`DLEN) out_pc,
  output reg `W(`ILEN) out_instr
);
  /* verilator lint_off WIDTHTRUNC */
  always @(posedge clk) begin
    if(!hard_stall) begin
      if(rst || (nopi & `NOPI_IF_ID)) begin
        out_pc <= `RSTPC;
        out_instr <= `RSTINSTR;
      end
      else if (!(stall & `STALL_IF_ID)) begin
        out_pc <= in_pc;
        out_instr <= in_instr;
      end
    end
  end
  /* verilator lint_on WIDTHTRUNC */
endmodule
