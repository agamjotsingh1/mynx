`include "defs.vh"
`include "modules/alu.v"

module ex_stage (
  // global stall wire
  output wor stall,

  // TODO! remove lint violations
  /* verilator lint_off UNUSEDSIGNAL */
  input wire           clk,
  input wire           rst,
  /* verilator lint_on UNUSEDSIGNAL */

  input wire `W(`DLEN)       regdata1,
  input wire `W(`DLEN)       regdata2,
  input wire `W(`DLEN)       imm,
  input wire `W(`ALU_OPLEN)  alu_op,


  // TODO! remove lint violations
  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`CTL_BUSLEN) ctl_bus,
  /* verilator lint_on UNUSEDSIGNAL */

  output wire `W(`DLEN) mem_data,
  output wire `W(`DLEN) alu_res
);
  assign mem_data = regdata2;

  alu alu_instance (
    .stall(stall),

    .alu_op(alu_op),
    .in1(regdata1),
    .in2(`ALU_SRC(ctl_bus) ? imm: regdata2),
    .out(alu_res)
  );
endmodule
