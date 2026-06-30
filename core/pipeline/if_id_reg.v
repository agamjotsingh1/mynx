`include "defs.vh"

module if_id_reg (
  input wire hard_stall,

  input wire `W(`STLEN)   stall,
  input wire `W(`NOPILEN) nopi,

  input wire clk,
  input wire rst,

  input wire           in_valid,
  input wire `W(`DLEN) in_pc,
  input wire `W(`DLEN) in_xcep,
  input wire `W(`ILEN) in_instr,
  input wire `W(`DLEN) in_predicted_pc,

  output reg           out_valid,
  output reg `W(`DLEN) out_pc,
  output reg `W(`DLEN) out_xcep,
  output reg `W(`ILEN) out_instr,
  output reg `W(`DLEN) out_predicted_pc
);
  /* verilator lint_off WIDTHTRUNC */
  always @(posedge clk) begin
    if(rst || ((nopi & `NOPI_IF_ID) && (!hard_stall))) begin
      out_valid <= 0;
      out_pc <= `RSTPC;
      out_instr <= `RSTINSTR;
      out_xcep <= 0;
      out_predicted_pc <= `RSTPC;
    end
    else if (!(stall & `STALL_IF_ID) && !(hard_stall)) begin
      out_valid <= in_valid;
      out_pc <= in_pc;
      out_instr <= in_instr;
      out_xcep <= in_xcep;
      out_predicted_pc <= in_predicted_pc;
    end
  end
  /* verilator lint_on WIDTHTRUNC */
endmodule
