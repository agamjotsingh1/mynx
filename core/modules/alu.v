module alu (
  input wire `W(`ALU_OPLEN) alu_op,
  input wire `W(`DLEN)      in1,
  input wire `W(`DLEN)      in2,

  output reg `W(`DLEN)      out
);
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

      /* word truncs, so trunc input at max shift for a word (one less than dblword) */
      /* verilator lint_off WIDTHEXPAND */
      `ALU_OP_SLLW:  out = $signed(in1[`WORD-1:0] << in2[($clog2(`WORD))-1:0]);
      `ALU_OP_SRLW:  out = $signed(in1[`WORD-1:0] >> in2[($clog2(`WORD))-1:0]);
      `ALU_OP_SRAW:  out = $signed($signed(in1[`WORD-1:0]) >>> in2[($clog2(`WORD))-1:0]);
      /* verilator lint_on WIDTHEXPAND */

      `ALU_OP_SLT:  out = $signed(in1) < $signed(in2) ? 1: 0;
      `ALU_OP_SLTU: out = $unsigned(in1) < $unsigned(in2) ? 1: 0;
      default:      out = 0;
    endcase
  end
endmodule
