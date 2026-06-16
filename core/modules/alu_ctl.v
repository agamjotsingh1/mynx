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
      `BOP_SD,
      `BOP_CSRRW,
      `BOP_CSRRWI,

      // pass just for the sake of not creating illegal exceptions
      {`OP_NULL,    10'b?},
      {`OP_B,       10'b?},
      {`OP_J,       10'b?},
      {`OP_I_JALR,  10'b?},
      {`OP_U_LUI,   10'b?},
      {`OP_U_AUIPC, 10'b?}
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
      `BOP_ORI,
      `BOP_CSRRS,
      `BOP_CSRRSI
      : alu_op = `ALU_OP_OR;

      `BOP_AND, 
      `BOP_ANDI,
      `BOP_CSRRC,
      `BOP_CSRRCI
      : alu_op = `ALU_OP_AND;

      `BOP_SLL, 
      `BOP_SLLI
      : alu_op = `ALU_OP_SLL;

      `BOP_SLLW, 
      `BOP_SLLIW
      : alu_op = `ALU_OP_SLLW;

      `BOP_SRL
      : alu_op = `ALU_OP_SRL;

      `BOP_SRLW
      : alu_op = `ALU_OP_SRLW;

      `BOP_SRA
      : alu_op = `ALU_OP_SRA;

      `BOP_SRAW
      : alu_op = `ALU_OP_SRAW;

      `BOP_SRL,
      `BOP_SRLI
      : alu_op = `ALU_OP_SRL;

      `BOP_SRLW,
      `BOP_SRLIW
      : alu_op = `ALU_OP_SRLW;

      `BOP_SRA,
      `BOP_SRAI
      : alu_op = `ALU_OP_SRA;

      `BOP_SRAW,
      `BOP_SRAIW
      : alu_op = `ALU_OP_SRAW;

      default
      : alu_op = `ALU_OP_ILLEGAL;

      endcase
  end
endmodule
/* verilator lint_on UNUSEDSIGNAL */
