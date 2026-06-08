`include "defs.vh"

// ref: https://www.cs.sfu.ca/~ashriram/Courses/CS295/assets/notebooks/RISCV/RISCV_CARD.pdf

/* verilator lint_off WIDTHEXPAND */
module immgen (
  input wire `W(`ILEN) instr,
  output reg `W(`DLEN) imm
);
  wire `W(`OLEN)  opcode = instr`OSLICE;

  // WARNING! This code is standalone and isnt dependent on macros
  // defined in defs.vh, change this when defs.vh is edited
  always @(*) begin
    case(opcode)
      `OP_R:   imm = 0;
      `OP_I:   imm = $signed(instr[31:20]);
      `OP_S:   imm = $signed({instr[31:25], instr[11:7]});
      `OP_B:   imm = $signed({instr[31], instr[7], instr[30:25], instr[11:8], 1'b0});
      `OP_U:   imm = $signed({instr[31:12], 12'b0});
      `OP_J:   imm = $signed({instr[31], instr[19:12], instr[20], instr[30:21], 1'b0});
      default: imm = 0; 
    endcase
  end
endmodule
/* verilator lint_on WIDTHEXPAND */
