// hazard detection unit
// only stalls for loads, for now
module hdu (
  output wor `W(`STLEN) stall,

  input wire `W(`RLEN)       __id_rs1,
  input wire `W(`RLEN)       __id_rs2,
  input wire `W(`RLEN)       __ex_rd,
  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`CTL_BUSLEN) __ex_ctl_bus,
  /* verilator lint_on UNUSEDSIGNAL */

  // stalls the id/ex reg
  output wire                __id_stall_nop
);
  assign __id_stall_nop =
    `MEM_READ(__ex_ctl_bus) &&
    (__ex_rd != 0) &&
    ((__ex_rd == __id_rs1) || (__ex_rd == __id_rs2));

  assign stall =
    __id_stall_nop ? (`STALL_PC | `STALL_IF_ID): `STALL_NONE;

  always @(*) begin
    if(__id_stall_nop) begin
      $display("i inserted a nop\n");
    end
  end
endmodule
