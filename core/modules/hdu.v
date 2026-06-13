// hazard detection unit
module hdu (
  output wor `W(`STLEN)   stall,
  output wor `W(`NOPILEN) nopi,

  input wire `W(`RLEN)       __id_rs1,
  input wire `W(`RLEN)       __id_rs2,
  input wire                 __id_branch_taken,
  input wire `W(`RLEN)       __ex_rd,
  input wire `W(`RLEN)       __mem_rd,
  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`CTL_BUSLEN) __id_ctl_bus,
  input wire `W(`CTL_BUSLEN) __ex_ctl_bus,
  input wire `W(`CTL_BUSLEN) __mem_ctl_bus
  /* verilator lint_on UNUSEDSIGNAL */
);
  // TODO!
  // this is conservative when it need not be
  // this stalls on instructions like lui, auipc etc.
  // add more checks

  // simple load hazard
  wire load_hazard =
    `MEM_READ(__ex_ctl_bus) &&
    (__ex_rd != 0) &&
    ((__ex_rd == __id_rs1) || (__ex_rd == __id_rs2));
  
  /* verilator lint_off WIDTHTRUNC */

  // control/csr hazard
  // branch/jalr or csr just after non-load instr with same reg
  // TODO! make this more granular, jalr hazard only if rs1 is same as rd
  wire control_csr_hazard =
    `REG_WRITE(__ex_ctl_bus) &&
    (__ex_rd != 0) &&
    (`BR(__id_ctl_bus) || `JALR(__id_ctl_bus) || `ZICSR_OP(__id_ctl_bus)) &&
    ((__ex_rd == __id_rs1) || (__ex_rd == __id_rs2));

  // branch/jalr (control) or csr load hazard
  wire control_csr_load_hazard = 
    `MEM_READ(__mem_ctl_bus) && 
    (__mem_rd != 0) &&
    (`BR(__id_ctl_bus) || `JALR(__id_ctl_bus) || `ZICSR_OP(__id_ctl_bus)) &&
    ((__mem_rd == __id_rs1) || (__mem_rd == __id_rs2));
  /* verilator lint_on WIDTHTRUNC */

  wire is_hazard =
    load_hazard || control_csr_hazard  || control_csr_load_hazard;

  assign nopi =
    is_hazard ? `NOPI_ID_EX: `NOPI_NONE;

  assign stall =
    is_hazard ? (`STALL_PC | `STALL_IF_ID | `STALL_CSRFILE): `STALL_NONE;

  // control nop insert
  // only insert if there is no load hazard
  // or control load hazard or control hazard
  assign nopi = 
    __id_branch_taken && !is_hazard
    ? `NOPI_IF_ID: `NOPI_NONE;
endmodule
