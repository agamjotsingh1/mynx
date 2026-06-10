`include "defs.vh"

// memory lies outside this stage
module if_stage (
  input wor `W(`STLEN) stall,

  input wire clk,
  input wire rst,
  input wire __id_branch_taken,
  input wire `W(`DLEN) __id_next_pc,

  output reg `W(`DLEN)  pc
);
  always @(posedge clk) begin
    if(rst) begin
      pc <= `RSTPC;
    end
    /* verilator lint_off WIDTHTRUNC */
    else if(!(stall & `STALL_PC)) begin
    /* verilator lint_on WIDTHTRUNC */
      if(__id_branch_taken) begin
        pc <= __id_next_pc;
      end
      else begin
        pc <= pc + 4;
      end
    end
  end
endmodule
