`include "../defs.vh"

module wb_stage (
  // global stall wire
  output wor stall,

  input wire `W(`DLEN)       alu_out,
  input wire `W(`DLEN)       mem_out,
  input wire `W(`CTL_BUSLEN) ctl_bus,

  output wire `W(`DLEN)      wb_write_data
);
  // no stalls in wb stage
  assign stall = 0;

  assign wb_write_data =
    MEM_TO_REG(ctl_bus) ? mem_out: alu_out;
endmodule

