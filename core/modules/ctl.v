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
