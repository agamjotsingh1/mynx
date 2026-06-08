`include "defs.vh"

module alu_ctl (
  input wire `W(`ILEN) instr,
  output reg `W(`ALU_OP_W) alu_op
);
  wire `W(`OLEN) opcode = instr[`OSTART +: `OLEN];
  wire `W(`F3LEN) funct3 = instr[`F3START +: `F3LEN];
  wire `W(`F7LEN) funct7 = instr[`F7START +: `F7LEN];

  always @(*) begin
    casez ({opcode, funct3, funct7})
      `BOP_ADD,
      `BOP_ADDI,
      `BOP_LB,
      `BOP_LH, 
      `BOP_LW, 
      `BOP_LD, 
      `BOP_LBU,
      `BOP_LHU,
      `BOP_SB, 
      `BOP_SH, 
      `BOP_SW, 
      `BOP_SD 
      : alu_op = `ALU_OP_ADD

      `BOP_SUB
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
      `BOP_SLLI
      : alu_op = `ALU_OP_SLL;

      `BOP_SRL, 
      `BOP_SRLI
      : alu_op = `ALU_OP_SRL;

      `BOP_SRA, 
      `BOP_SRAI
      : alu_op = `ALU_OP_SRA;

      default
      : alu_op = `ALU_OP_ADD;

      endcase
  end
endmodule