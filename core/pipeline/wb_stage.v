`include "defs.vh"

module wb_stage (
  input wire `W(`DLEN)       regw_data,
  input wire `W(`DLEN)       mem_res,
  // TODO! remove lint violations
  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`CTL_BUSLEN) ctl_bus,
  /* verilator lint_on UNUSEDSIGNAL */

  output wire `W(`DLEN)      wb_write_data
);
  assign wb_write_data =
    `MEM_TO_REG(ctl_bus) ? mem_res: regw_data;
endmodule

