// hazard detection unit
module hdu (
  output wor `W(`STLEN)   stall,
  output wor `W(`NOPILEN) nopi,

  input wire `W(`RLEN)       __id_rs1,
  input wire `W(`RLEN)       __id_rs2,
  input wire                 __id_branch_taken,
  input wire `W(`RLEN)       __ex_rd,
  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`CTL_BUSLEN) __ex_ctl_bus
  /* verilator lint_on UNUSEDSIGNAL */
);
  // simple load hazard
  wire load_hazard =
    `MEM_READ(__ex_ctl_bus) &&
    (__ex_rd != 0) &&
    ((__ex_rd == __id_rs1) || (__ex_rd == __id_rs2));

  assign nopi =
    load_hazard ? `NOPI_ID_EX: `NOPI_NONE;

  assign stall =
    load_hazard ? (`STALL_PC | `STALL_IF_ID): `STALL_NONE;

  // control nop insert

  // TODO!
  // this might be slightly wrong
  // taking into account load hazards
  assign nopi = 
    __id_branch_taken ? `NOPI_IF_ID: `NOPI_NONE;
endmodule
