`include "defs.vh"

/* verilator lint_off UNUSEDSIGNAL */
module alu_ctl (
  input wire `W(`ILEN)      instr,
  output reg `W(`ALU_OPLEN) alu_op
);
  wire `W(`OLEN)  opcode = instr`OSLICE;
  wire `W(`F3LEN) funct3 = instr`F3SLICE;
  wire `W(`F7LEN) funct7 = instr`F7SLICE;

  always @(*) begin
    casez ({opcode, funct3, funct7})
      `BOP_ADD,
      `BOP_ADDW,
      `BOP_ADDI,
      `BOP_ADDIW,
      `BOP_LB,
      `BOP_LH, 
      `BOP_LW, 
      `BOP_LD, 
      `BOP_LBU,
      `BOP_LHU,
      `BOP_LWU,
      `BOP_SB, 
      `BOP_SH, 
      `BOP_SW, 
      `BOP_SD 
      : alu_op = `ALU_OP_ADD;

      `BOP_SUB,
      `BOP_SUBW
      : alu_op = `ALU_OP_SUB;

      `BOP_SLT, 
      `BOP_SLTI
      : alu_op = `ALU_OP_SLT;

      `BOP_SLTU, 
      `BOP_SLTIU
      : alu_op = `ALU_OP_SLTU;

      `BOP_XOR, 
      `BOP_XORI
      : alu_op = `ALU_OP_XOR;

      `BOP_OR, 
      `BOP_ORI
      : alu_op = `ALU_OP_OR;

      `BOP_AND, 
      `BOP_ANDI
      : alu_op = `ALU_OP_AND;

      `BOP_SLL, 
      `BOP_SLLW, 
      `BOP_SLLI,
      `BOP_SLLIW
      : alu_op = `ALU_OP_SLL;

      `BOP_SRL,
      `BOP_SRLW
      : alu_op = `ALU_OP_SRL;

      `BOP_SRA,
      `BOP_SRAW
      : alu_op = `ALU_OP_SRA;

      `BOP_SRLI,
      `BOP_SRLIW // SRAI(W) only differ by upper immediate bits, BOP is same
      : begin
        // upper immediate extraction
        if(instr[30]) alu_op = `ALU_OP_SRA;
        else alu_op = `ALU_OP_SRL;
      end

      default
      : alu_op = `ALU_OP_ADD;

      endcase
  end
endmodule
/* verilator lint_on UNUSEDSIGNAL */
