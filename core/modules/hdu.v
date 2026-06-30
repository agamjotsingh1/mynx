`include "defs.vh"

// hazard detection unit
module hdu (
  output wire `W(`STLEN)   stall,
  output wire `W(`NOPILEN) nopi,

  input wire `W(`RLEN)       __id_rs1,
  input wire `W(`RLEN)       __id_rs2,
  input wire                 __if_bpt_mispredict,
  input wire `W(`RLEN)       __ex_rd,
  input wire `W(`RLEN)       __mem_rd,
  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`CTL_BUSLEN) __id_ctl_bus,
  input wire `W(`CTL_BUSLEN) __ex_ctl_bus,
  input wire `W(`CTL_BUSLEN) __mem_ctl_bus,
  /* verilator lint_on UNUSEDSIGNAL */

  input wire __ex_valid,
  input wire __mem_valid,
  input wire __wb_valid
);
  // simple load hazard
  wire load_hazard =
    `MEM_READ(__ex_ctl_bus) &&
    (__ex_rd != 0) &&
    ((`USES_RS1(__id_ctl_bus) && __ex_rd == __id_rs1) ||
      (`USES_RS2(__id_ctl_bus) && __ex_rd == __id_rs2));
  
  // control/csr hazard
  // branch/jalr or csr just after non-load instr with same reg
  wire control_csr_hazard =
    `REG_WRITE(__ex_ctl_bus) &&
    (__ex_rd != 0) &&
    (
      ((`BR(__id_ctl_bus) != `BR_NONE) && ((__ex_rd == __id_rs1) || (__ex_rd == __id_rs2))) ||
      (`JALR(__id_ctl_bus) && (__ex_rd == __id_rs1)) ||
      ((`ZICSR_OP(__id_ctl_bus) != `ZICSR_OP_NONE) && (__ex_rd == __id_rs1))
    );

  // branch/jalr (control) or csr load hazard
  wire control_csr_load_hazard = 
    `MEM_READ(__mem_ctl_bus) && 
    (__mem_rd != 0) &&
    (
      ((`BR(__id_ctl_bus) != `BR_NONE) && ((__mem_rd == __id_rs1) || (__mem_rd == __id_rs2))) ||
      (`JALR(__id_ctl_bus) && (__mem_rd == __id_rs1)) ||
      ((`ZICSR_OP(__id_ctl_bus) != `ZICSR_OP_NONE) && (__mem_rd == __id_rs1))
    );

  wire sfence_barrier_hazard = `SFENCEVMA(__id_ctl_bus) &&
    (`CSR_WRITE(__ex_ctl_bus) || `CSR_WRITE(__mem_ctl_bus));

  wire fence_barrier_hazard = `FENCE(__id_ctl_bus) &&
    (__ex_valid || __mem_valid || __wb_valid);

  wire is_hazard =
    load_hazard ||
    control_csr_hazard  || 
    control_csr_load_hazard || 
    sfence_barrier_hazard ||
    fence_barrier_hazard;

  wire `W(`NOPILEN) hazard_nopi =
    is_hazard ? `NOPI_ID_EX: `NOPI_NONE;

  assign stall =
    is_hazard ? (`STALL_PC | `STALL_IF_ID): `STALL_NONE;

  // control nop insert
  // only insert if there is no load hazard
  // or control load hazard or control hazard
  wire `W(`NOPILEN) branch_nopi =
    __if_bpt_mispredict && !is_hazard
    ? `NOPI_IF_ID: `NOPI_NONE;

  assign nopi = branch_nopi | hazard_nopi;
endmodule
