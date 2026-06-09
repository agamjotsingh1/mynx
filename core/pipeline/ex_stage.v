`include "defs.vh"
`include "modules/alu.v"

module ex_stage (
  // global stall wire
  output wor stall,

  input wire           clk,
  input wire           rst,
  input wire `W(`ILEN) instr,

  input wire `W(`DLEN)       regdata1,
  input wire `W(`DLEN)       regdata2,
  input wire `W(`DLEN)       imm,
  input wire `W(`ALU_OPLEN)  alu_op,
  input wire `W(`CTL_BUSLEN) ctl_bus,

  output wire `W(`DLEN) alu_res
);
  alu alu_instance (
    .stall(stall),

    .alu_op(alu_op),
    .in1(regdata1),
    .in2(ALU_SRC(ctl_bus) ? imm: regdata2),
    .out(alu_res)
  );
endmodule
