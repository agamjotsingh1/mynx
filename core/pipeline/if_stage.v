`include "defs.vh"

// memory lies outside this stage
module if_stage (
  input wor hard_stall,

  input wor `W(`STLEN)   stall,
  input wor `W(`NOPILEN) nopi,

  input wire clk,
  input wire rst,
  input wire __id_branch_taken,
  input wire `W(`DLEN) __id_next_pc,

  output reg `W(`DLEN)  pc
);
  /* verilator lint_off WIDTHTRUNC */
  always @(posedge clk) begin
    if(!hard_stall) begin
      if(rst || (nopi & `NOPI_PC)) begin
        pc <= `RSTPC;
      end
      else if(!(stall & `STALL_PC)) begin
        if(__id_branch_taken) begin
          pc <= __id_next_pc;
        end
        else begin
          pc <= pc + 4;
        end
      end
    end
  end
  /* verilator lint_on WIDTHTRUNC */
endmodule
