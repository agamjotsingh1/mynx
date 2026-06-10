`include "defs.vh"

/* verilator lint_off UNUSEDSIGNAL */
module alu_ctl (
  // global stall wire
  output wor `W(`STLEN) stall,

  input wire `W(`ILEN)      instr,
  output reg `W(`ALU_OPLEN) alu_op
);
  assign stall = `STALL_NONE;

  wire `W(`OLEN)  opcode = instr`OSLICE;
  wire `W(`F3LEN) funct3 = instr`F3SLICE;
  wire `W(`F7LEN) funct7 = instr`F7SLICE;

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
      : alu_op = `ALU_OP_ADD;

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

      `BOP_SRL
      : alu_op = `ALU_OP_SRL;

      `BOP_SRA
      : alu_op = `ALU_OP_SRA;

      `BOP_SRLI // SRAI only differ by upper immediate bits, BOP is same
      : begin
        // upper immediate extraction
        if(instr[31:25] == 7'h20) alu_op = `ALU_OP_SRA;
        else alu_op = `ALU_OP_SRL;
      end

      default
      : alu_op = `ALU_OP_ADD;

      endcase
  end
endmodule
/* verilator lint_on UNUSEDSIGNAL */
