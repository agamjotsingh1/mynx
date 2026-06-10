`include "defs.vh"
`include "modules/alu.v"

module ex_stage (
  // TODO! remove lint violations
  /* verilator lint_off UNUSEDSIGNAL */
  input wire clk,
  input wire rst,
  /* verilator lint_on UNUSEDSIGNAL */

  input wire `W(`DLEN)       pc,
  input wire `W(`DLEN)       regdata1,
  input wire `W(`DLEN)       regdata2,
  input wire `W(`DLEN)       imm,
  input wire `W(`ALU_OPLEN)  alu_op,


  // TODO! remove lint violations
  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`CTL_BUSLEN) ctl_bus,
  /* verilator lint_on UNUSEDSIGNAL */

  output wire `W(`DLEN) mem_data,
  output wire `W(`DLEN) ex_res,

  // fwd controls
  input wire `W(`FWDLEN)     fwd1,
  input wire `W(`FWDLEN)     fwd2,

  // fwd inputs
  input wire `W(`DLEN)       __mem_ex_res,
  input wire `W(`DLEN)       __wb_write_data
);
  wire `W(`DLEN) alu_res;

  wire `W(`DLEN) alu_in1 = 
    (fwd1 == `FWD_EX_MEM) ? __mem_ex_res:
    ((fwd1 == `FWD_MEM_WB) ? __wb_write_data: regdata1);

  wire `W(`DLEN) alu_in2 = 
    (fwd2 == `FWD_EX_MEM) ? __mem_ex_res:
    ((fwd2 == `FWD_MEM_WB) ? __wb_write_data: regdata2);

  assign mem_data = alu_in2;

  alu alu_instance (
    .alu_op(alu_op),
    .in1(alu_in1),
    .in2(`ALU_SRC(ctl_bus) ? imm: alu_in2),
    .out(alu_res)
  );

  assign ex_res = (`JAL(ctl_bus) | `JALR(ctl_bus)) ? pc + 4: alu_res;
endmodule
