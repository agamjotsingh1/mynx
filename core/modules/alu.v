`include "defs.vh"

module alu (
  // global stall wire
  output wor `W(`STLEN) stall,

  input wire `W(`ALU_OPLEN) alu_op,
  input wire `W(`DLEN)      in1,
  input wire `W(`DLEN)      in2,

  output reg `W(`DLEN)      out
);
  assign stall = `STALL_NONE;

  always @(*) begin
    case (alu_op)
      `ALU_OP_ADD:  out = in1 + in2;
      `ALU_OP_SUB:  out = in1 - in2;
      `ALU_OP_XOR:  out = in1 ^ in2;
      `ALU_OP_OR :  out = in1 | in2;
      `ALU_OP_AND:  out = in1 & in2;
      `ALU_OP_SLL:  out = in1 << in2[($clog2(`DLEN))-1:0];
      `ALU_OP_SRL:  out = in1 >> in2[($clog2(`DLEN))-1:0];
      `ALU_OP_SRA:  out = $signed(in1) >>> in2[($clog2(`DLEN))-1:0];
      `ALU_OP_SLT:  out = $signed(in1) < $signed(in2) ? 1: 0;
      `ALU_OP_SLTU: out = $unsigned(in1) < $unsigned(in2) ? 1: 0;
      default:      out = 0;
    endcase
  end
endmodule
