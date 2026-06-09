`include "../defs.vh"

// just a placeholder mostly
// memory lies outside this stage
module if_stage (
  // global stall wire
  input wor stall,

  input wire clk,
  input wire rst,

  output reg `W(`DLEN)  pc
);
  always @(posedge clk) begin
    if(rst) begin
      pc <= `RSTPC;
    end
    else if(!stall) begin
      pc <= pc + 4;
    end
  end
endmodule
