`include "defs.vh"

/* verilator lint_off UNUSEDSIGNAL */
module ctl (
  input wire `W(`ILEN)       instr,
  output reg `W(`CTL_BUSLEN) ctl_bus
);
  wire `W(`OLEN)  opcode = instr`OSLICE;
  wire `W(`F3LEN) funct3 = instr`F3SLICE;

  always @(*) begin
    // defaults
    ctl_bus = 0;

    case(opcode)
      `OP_SYS: begin
        `REG_WRITE(ctl_bus)   = 1;
        case(funct3)
          `F3CSRRW : `ZICSR_OP(ctl_bus) = `ZICSR_OP_CSRRW;
          `F3CSRRS : `ZICSR_OP(ctl_bus) = `ZICSR_OP_CSRRS;
          `F3CSRRC : `ZICSR_OP(ctl_bus) = `ZICSR_OP_CSRRC;
          `F3CSRRWI: `ZICSR_OP(ctl_bus) = `ZICSR_OP_CSRRWI;
          `F3CSRRSI: `ZICSR_OP(ctl_bus) = `ZICSR_OP_CSRRSI;
          `F3CSRRCI: `ZICSR_OP(ctl_bus) = `ZICSR_OP_CSRRCI;
          default:   `ZICSR_OP(ctl_bus) = `ZICSR_OP_NONE;
        endcase
      end

      `OP_R: begin
        `REG_WRITE(ctl_bus)   = 1;
      end

      `OP_RW: begin
        `REG_WRITE(ctl_bus)   = 1;
        `WORDTRUNC(ctl_bus)   = 1;
      end

      `OP_I: begin
        `ALU_SRC(ctl_bus)     = 1;
        `REG_WRITE(ctl_bus)   = 1;
      end

      `OP_IW: begin
        `ALU_SRC(ctl_bus)     = 1;
        `REG_WRITE(ctl_bus)   = 1;
        `WORDTRUNC(ctl_bus)   = 1;
      end

      `OP_I_LOAD: begin
        `ALU_SRC(ctl_bus)     = 1;
        `REG_WRITE(ctl_bus)   = 1;
        `MEM_READ(ctl_bus)    = 1;
        `MEM_TO_REG(ctl_bus)  = 1;

        case(funct3) 
          `F3LB, `F3LBU: `BW(ctl_bus) = `BW_BYTE;
          `F3LH, `F3LHU: `BW(ctl_bus) = `BW_HALFWORD;
          `F3LW, `F3LWU: `BW(ctl_bus) = `BW_WORD;
          `F3LD:         `BW(ctl_bus) = `BW_DBLWORD;
          default:       `BW(ctl_bus) = `BW_BYTE;
        endcase

        case(funct3)
          `F3LBU,
          `F3LHU,
          `F3LWU:  `SIGN_EXTEND(ctl_bus) = 0;
          default: `SIGN_EXTEND(ctl_bus) = 1;
        endcase
      end

      `OP_I_JALR: begin
        `ALU_SRC(ctl_bus)     = 1;
        `REG_WRITE(ctl_bus)   = 1;
        `JALR(ctl_bus)        = 1;
      end

      // TODO!
      // `OP_I_ECALL: begin
      //   ALU_SRC(ctl_bus)     = 1;
      //   REG_WRITE(ctl_bus)   = 1;
      // end

      `OP_S: begin
        `ALU_SRC(ctl_bus)     = 1;
        `MEM_WRITE(ctl_bus)   = 1;

        case(funct3) 
          `F3SB:   `BW(ctl_bus) = `BW_BYTE;
          `F3SH:   `BW(ctl_bus) = `BW_HALFWORD;
          `F3SW:   `BW(ctl_bus) = `BW_WORD;
          `F3SD:   `BW(ctl_bus) = `BW_DBLWORD;
          default: `BW(ctl_bus) = `BW_BYTE;
        endcase
      end

      `OP_B: begin
        case(funct3)
          `F3BEQ:  `BR(ctl_bus) = `BR_BEQ;
          `F3BNE:  `BR(ctl_bus) = `BR_BNE;
          `F3BLT:  `BR(ctl_bus) = `BR_BLT;
          `F3BGE:  `BR(ctl_bus) = `BR_BGE;
          `F3BLTU: `BR(ctl_bus) = `BR_BLTU;
          `F3BGEU: `BR(ctl_bus) = `BR_BGEU;
          default: `BR(ctl_bus) = `BR_NONE;
        endcase
      end

      `OP_U_LUI: begin
        `REG_WRITE(ctl_bus)   = 1;
        `LUI(ctl_bus)         = 1;
      end

      `OP_U_AUIPC: begin
        `REG_WRITE(ctl_bus)   = 1;
        `AUIPC(ctl_bus)       = 1;
      end

      `OP_J: begin
        `REG_WRITE(ctl_bus)   = 1;
        `JAL(ctl_bus)         = 1;
      end

      `OP_NULL: begin
      end

      default: begin
        `ILLEGAL(ctl_bus)     = 1;
      end
    endcase
  end
endmodule
/* verilator lint_on UNUSEDSIGNAL */
