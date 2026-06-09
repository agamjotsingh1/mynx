`include "defs.vh"

/* verilator lint_off UNUSEDSIGNAL */
module ctl (
  // global stall wire
  output wor stall,

  input wire `W(`ILEN)      instr,
  output reg `W(`ALU_OPLEN) ctl_bus
);
  // ctl never stalls
  assign stall = 0;

  wire `W(`OLEN)  opcode = instr`OSLICE;
  wire `W(`F3LEN) funct3 = instr`F3SLICE;

  // TODO!
  // add jalr and branching controls

  always @(*) begin
    // defaults
    ctl_bus = 0;

    case(opcode)
      `OP_R: begin
        REG_WRITE(ctl_bus)   = 1;
      end

      `OP_I: begin
        ALU_SRC(ctl_bus)     = 1;
        REG_WRITE(ctl_bus)   = 1;
      end

      `OP_I_LOAD: begin
        ALU_SRC(ctl_bus)     = 1;
        REG_WRITE(ctl_bus)   = 1;
        MEM_READ(ctl_bus)    = 1;
        MEM_TO_REG(ctl_bus)  = 1;

        case(funct3) 
          `F3LB, `F3LBU: BW(ctl_bus) = `BW_BYTE;
          `F3LH, `F3LHU: BW(ctl_bus) = `BW_HALFWORD;
          `F3LW, `F3LWU: BW(ctl_bus) = `BW_WORD;
          `F3LD:         BW(ctl_bus) = `BW_DBLWORD;
          default:       BW(ctl_bus) = `BW_BYTE;
        endcase

        case(funct3)
          `F3LBU,
          `F3LHU,
          `F3LWU:  SIGN_EXTEND(ctl_bus) = 1;
          default: SIGN_EXTEND(ctl_bus) = 0;
        endcase
      end

      `OP_I_JALR: begin
        ALU_SRC(ctl_bus)     = 1;
        REG_WRITE(ctl_bus)   = 1;
      end

      // TODO!
      // `OP_I_ECALL: begin
      //   ALU_SRC(ctl_bus)     = 1;
      //   REG_WRITE(ctl_bus)   = 1;
      // end

      `OP_S: begin
        ALU_SRC(ctl_bus)     = 1;
        MEM_WRITE(ctl_bus)   = 1;

        case(funct3) 
          `F3SB:   BW(ctl_bus) = `BW_BYTE;
          `F3SH:   BW(ctl_bus) = `BW_HALFWORD;
          `F3SW:   BW(ctl_bus) = `BW_WORD;
          `F3SD:   BW(ctl_bus) = `BW_DBLWORD;
          default: BW(ctl_bus) = `BW_BYTE;
        endcase
      end

      // TODO!
      // `OP_B: begin
      //   ALU_SRC(ctl_bus)     = 1;
      //   MEM_WRITE(ctl_bus)   = 1;
      // end

      `OP_U_LUI: begin
        REG_WRITE(ctl_bus)   = 1;
      end

      `OP_U_AUIPC: begin
        reg_write(ctl_bus)   = 1;
      end

      `OP_J: begin
        reg_write(ctl_bus)   = 1;
      end
    endcase
  end
endmodule
/* verilator lint_on UNUSEDSIGNAL */
