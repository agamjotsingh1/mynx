`include "defs.vh"

// memory lies outside this stage
module if_stage (
  input wor hard_stall,

  input wor `W(`STLEN)   stall,
  input wor `W(`NOPILEN) nopi,

  output wire `W(`DLEN)  uxcep,

  input wire clk,
  input wire rst,
  output reg `W(`DLEN)  pc,

  input wire __id_branch_taken,
  input wire __wb_trap_taken,
  input wire `W(`DLEN) __id_next_pc,
  input wire `W(`DLEN) __wb_next_pc
);
  assign uxcep = 0;

  /* verilator lint_off WIDTHTRUNC */
  always @(posedge clk) begin
    if(!hard_stall) begin
      if(rst || (nopi & `NOPI_PC)) pc <= `RSTPC;
      else if(__wb_trap_taken) pc <= __wb_next_pc;
      else if(!(stall & `STALL_PC)) begin
        if(__id_branch_taken) pc <= __id_next_pc;
        else pc <= pc + 4;
      end
    end
  end
  /* verilator lint_on WIDTHTRUNC */
endmodule
