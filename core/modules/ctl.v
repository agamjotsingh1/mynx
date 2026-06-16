`include "defs.vh"

/* verilator lint_off UNUSEDSIGNAL */
module ctl (
  input wire `W(`ILEN)       instr,
  output reg `W(`CTL_BUSLEN) ctl_bus
);
  wire `W(`OLEN)   opcode  = instr`OSLICE;
  wire `W(`F3LEN)  funct3  = instr`F3SLICE;
  wire `W(`F12LEN) funct12 = instr`F12SLICE;
  wire `W(`RLEN)   rs1     = instr`RS1SLICE;
  wire `W(`RLEN)   rd      = instr`RDSLICE;

  always @(*) begin
    // all defaults
    ctl_bus = 0;

    case(opcode)
      `OP_SYS: begin
        case(funct3)
          `F3CSRRW : begin
            `REG_WRITE(ctl_bus) = 1;
            `CSR_WRITE(ctl_bus) = 1;
            `ZICSR_OP(ctl_bus)  = `ZICSR_OP_CSRRW;
          end
          `F3CSRRS : begin 
            `REG_WRITE(ctl_bus) = 1;
            `CSR_WRITE(ctl_bus) = (rs1 != 0);
            `ZICSR_OP(ctl_bus)  = `ZICSR_OP_CSRRS;
          end
          `F3CSRRC : begin
            `REG_WRITE(ctl_bus) = 1;
            `CSR_WRITE(ctl_bus) = (rs1 != 0);
            `ZICSR_OP(ctl_bus)  = `ZICSR_OP_CSRRC;
          end
          `F3CSRRWI: begin
            `REG_WRITE(ctl_bus) = 1;
            `CSR_WRITE(ctl_bus) = 1;
            `ZICSR_OP(ctl_bus)  = `ZICSR_OP_CSRRWI;
          end
          `F3CSRRSI: begin
            `REG_WRITE(ctl_bus) = 1;
            `CSR_WRITE(ctl_bus) = 1;
            `ZICSR_OP(ctl_bus)  = `ZICSR_OP_CSRRSI;
          end
          `F3CSRRCI: begin
            `REG_WRITE(ctl_bus) = 1;
            `CSR_WRITE(ctl_bus) = 1;
            `ZICSR_OP(ctl_bus)  = `ZICSR_OP_CSRRCI;
          end

          // ecall/mret/sret
          `F3NULL: begin
            if(rs1 == 0 && rd == 0) begin
              case(funct12)
                `F12MRET : `MRET(ctl_bus) = 1;
                `F12SRET : `SRET(ctl_bus) = 1;
                `F12ECALL: `ECALL(ctl_bus) = 1;
                default  : `ILLEGAL(ctl_bus) = 1;
              endcase
            end
            else `ILLEGAL(ctl_bus) = 1;
          end

          default: `ILLEGAL(ctl_bus) = 1;
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
          default:  `ILLEGAL(ctl_bus) = 1;
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
          default: `ILLEGAL(ctl_bus) = 1;
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
          default: `ILLEGAL(ctl_bus) = 1;
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
        // do nothing (nop)
        if(instr != 0) `ILLEGAL(ctl_bus) = 1;
      end

      default: begin
        `ILLEGAL(ctl_bus)     = 1;
      end
    endcase
  end
endmodule
/* verilator lint_on UNUSEDSIGNAL */
