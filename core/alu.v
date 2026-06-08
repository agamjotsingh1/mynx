`include "defs.vh"

module alu (
  input wire  `W(`ALU_OP_W) alu_op,
  input wire  `W(`DLEN)     in1,
  input wire  `W(`DLEN)     in2,

  output wire `W(`DLEN)     out
);
  always @(*) begin
    case (alu_op)
      `ALU_OP_ADD: out = in1 + in2;
      `ALU_OP_SUB: out = in1 - in2;
      `ALU_OP_MUL: out = in1 * in2;
      `ALU_OP_DIV: out = in1 / in2;
      `ALU_OP_DIV: out = in1 / in2;
      default: out = {BUS_WIDTH{1'b0}};
    endcase
  end
endmodule