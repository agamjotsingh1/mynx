`include "defs.vh"

module wb_stage (
  output wor `W(`STLEN) stall,

  input wire `W(`DLEN)       regw_data,
  input wire `W(`DLEN)       mem_res,
  // TODO! remove lint violations
  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`CTL_BUSLEN) ctl_bus,
  /* verilator lint_on UNUSEDSIGNAL */

  output wire `W(`DLEN)      wb_write_data
);
  assign stall = `STALL_NONE;

  assign wb_write_data =
    `MEM_TO_REG(ctl_bus) ? mem_res: regw_data;
endmodule

