`include "defs.vh"
`include "modules/regfile.v"
`include "modules/immgen.v"
`include "modules/alu_ctl.v"
`include "modules/ctl.v"
`include "modules/csrfile.v"

module id_stage (
  input wire clk,
  input wire rst,
  input wor  hard_stall,

  // trap handling
  // input wor               xcep,
  // input wire `W(`DLEN)    xcep_cause,
  // input wire `W(PRIVLEN)  priv,
  // input wor  `W(NORILEN)  nopi,

  input wire `W(`DLEN)    pc,
  input wire `W(`ILEN)    instr,
  input wor  `W(`STLEN)   stall, // for csr

  // parsing results
  output wire `W(`RLEN)   rs1,
  output wire `W(`RLEN)   rs2,
  output wire `W(`RLEN)   rd,
  output wire `W(`DLEN)   satp,
  output wire `W(`DLEN)   regdata1,
  output wire `W(`DLEN)   regdata2,
  output wire `W(`CSRLEN) csr,
  output wire `W(`DLEN)   csrdata,  // data to pass to EX-stage to update rd
  output wire `W(`DLEN)   imm,

  // alu control outputs
  output wire `W(`ALU_OPLEN) alu_op,

  // control outputs
  output wire `W(`CTL_BUSLEN) ctl_bus,

  // branch taken or not (for both branch and jal instr)
  output reg  branch_taken,
  // output wire trap_taken,

  // next pc (for branching/jal)
  output reg `W(`DLEN) next_pc,

  // (reg/csr)writes from wb stage
  input wire `W(`RLEN)       __wb_rd,
  input wire `W(`CSRLEN)     __wb_csr,
  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`CTL_BUSLEN) __wb_ctl_bus,
  /* verilator lint_on UNUSEDSIGNAL */
  input wire `W(`DLEN)       __wb_csr_write_data,

  // fwd controls
  input wire `W(`FWDLEN)  fwd1,
  input wire `W(`FWDLEN)  fwd2,

  // fwd inputs
  input wire `W(`DLEN)    __mem_ex_res,
  // TODO! you dont really need this forward from WB stage hehe
  input wire `W(`DLEN)    __wb_write_data
);
  // instruction parsing
  assign rs1 = instr`RS1SLICE;
  assign rs2 = instr`RS2SLICE;
  assign rd  = instr`RDSLICE;
  assign csr = instr`CSRSLICE;

  regfile regfile_instance (
    .clk(clk),
    .rst(rst),

    .read_addr1(rs1),
    .read_data1(regdata1),

    .read_addr2(rs2),
    .read_data2(regdata2),

    .write_en(`REG_WRITE(__wb_ctl_bus)),
    .write_addr(__wb_rd),
    .write_data(__wb_write_data)
  );

  immgen immgen_instance (
    .instr(instr),
    .imm(imm)
  );

  alu_ctl alu_ctl_instance (
    .instr(instr),
    .alu_op(alu_op)
  );

  ctl ctl_instance (
    .instr(instr),
    .ctl_bus(ctl_bus)
  );

  wire `W(`DLEN) regdata1_fwded = 
    (fwd1 == `FWD_EX_MEM) ? __mem_ex_res:
    ((fwd1 == `FWD_MEM_WB) ? __wb_write_data: regdata1);

  wire `W(`DLEN) regdata2_fwded = 
    (fwd2 == `FWD_EX_MEM) ? __mem_ex_res:
    ((fwd2 == `FWD_MEM_WB) ? __wb_write_data: regdata2);

  // branching logic comparator
  wire zero = (regdata1_fwded == regdata2_fwded);
  wire lt   = ($signed(regdata1_fwded) < $signed(regdata2_fwded));
  wire ltu  = ($unsigned(regdata1_fwded) < $unsigned(regdata2_fwded));

  // branching logic
  always @(*) begin
    case (`BR(ctl_bus))
      `BR_NONE: branch_taken = 0;
      `BR_BEQ:  branch_taken = zero;
      `BR_BNE:  branch_taken = ~zero;
      `BR_BLT:  branch_taken = lt;
      `BR_BGE:  branch_taken = ~lt;
      `BR_BLTU: branch_taken = ltu;
      `BR_BGEU: branch_taken = ~ltu;
      default:  branch_taken = 0;
    endcase

    branch_taken |= (`JAL(ctl_bus) | `JALR(ctl_bus));
  end

  /* TRAP HANDLING
  wonderful video explaining exactly whats going on here
    - https://www.youtube.com/watch?v=YWSNj3Mn2gI

  read:
    - mip                     (for looking for an interrupt)
    - mstatus: (S/M)IE        (global interrupt enable)
    - mie                     (granular interrupt enable)
    - medeleg                 (intr delegation)
    - mideleg                 (xcep delegation)
    - (s/m)tvec               (for switching to trap handler)

  write:
    - mstatus: 
      (S/M)IE                 (global IE is disabled)
      (S/M)PP                 (previous mode is kept to current mode)
      (S/M)PIE                (previous IE is saved)
    - (s/m)cause              (writing the cause of trap)
    - (s/m)epc                (saved pc for (s/m)ret)
  */

  // wire `W(`DLEN) mstatus, mip, mie, mideleg, medeleg, vec;
  // reg  `W(`DLEN) write_mstatus, write_cause, write_epc;

  // /* --- determining trap mode --- */
  // reg `W(TRAPMODELEN) trap_mode;
  // wire m_intr_en = (priv < `PRIVM) || (priv == `PRIVM && `MSTATUS_MIE(mstatus));
  // wire s_intr_en = (priv < `PRIVS) || (priv == `PRIVS && `MSTATUS_SIE(mstatus));

  // wire `W(`DLEN) pending_intr   = mip & mie;
  // wire `W(`DLEN) pending_s_intr = pending_intr & mideleg;
  // wire `W(`DLEN) pending_m_intr = pending_intr & (~mideleg);

  // always @(*) begin
  //   trap_mode = `TRAPMODE_NONE;

  //   // intrs
  //   if((pending_m_intr != 0) && m_intr_en)
  //     trap_mode = `TRAPMODE_MINTR;
  //   else if((pending_s_intr != 0) && s_intr_en)
  //     trap_mode = `TRAPMODE_SINTR;

  //   // xceps
  //   else if(xcep) begin
  //     // if in M-mode -> Always M-mode
  //     // if in U/S-mode AND delegated -> S-mode
  //     // if in U/S-mode AND NOT delegated -> M-mode
  //     if ((priv < `PRIVM) && medeleg[xcep_cause])
  //       trap_mode = `TRAPMODE_SXCEP;
  //     else
  //       trap_mode = `TRAPMODE_MXCEP;
  //   end
  // end
  // /* ----------------------------- */

  // /* --- setting values for trap csr writes --- */
  // wire is_trap_m = (trap_mode == `TRAPMODE_MINTR || trap_mode == `TRAPMODE_MXCEP);
  // wire is_trap_s = (trap_mode == `TRAPMODE_SINTR || trap_mode == `TRAPMODE_SXCEP);
  // assign trap_taken = (trap_mode != `TRAPMODE_NONE);

  // always @(*) begin
  //   write_mstatus = mstatus;
  //   write_cause = 0;
  //   write_epc = pc;

  //   if(is_trap_m) begin
  //     `MSTATUS_MPP(write_mstatus) = priv;
  //     `MSTATUS_MPIE(write_mstatus) = `MSTATUS_MIE(mstatus);
  //     `MSTATUS_MIE(write_mstatus) = 0;
  //     // MSB of trap mode specifies interrupt or exception
  //     write_cause = {trap_mode[`TRAPMODELEN-1], 
  //       trap_mode[`TRAPMODELEN-1] ? `MIP_GET_MICAUSE(pending_m_intr): xcep_cause[`DLEN-2:0]};
  //   end
  //   else if(is_trap_s) begin
  //     // LSB of priv specifies user/supervisor if we know we trapped into supervisor
  //     `MSTATUS_SPP(write_mstatus) = priv[0];
  //     `MSTATUS_SPIE(write_mstatus) = `MSTATUS_SIE(mstatus);
  //     `MSTATUS_SIE(write_mstatus) = 0;
  //     // MSB of trap mode specifies interrupt or exception
  //     write_cause = {trap_mode[`TRAPMODELEN-1], 
  //       trap_mode[`TRAPMODELEN-1] ? `MIP_GET_SICAUSE(pending_s_intr): xcep_cause[`DLEN-2:0]};
  //   end
  // end
  // /* ------------------------------------------ */

  // always @(*) begin
  //   case(`ZICSR_OP(ctl_bus)) 
  //   `ZICSR_OP_NONE  : csr_write_data = 0;
  //   `ZICSR_OP_CSRRW : csr_write_data = regdata1_fwded;
  //   `ZICSR_OP_CSRRS : csr_write_data = csr_data | regdata1_fwded;
  //   `ZICSR_OP_CSRRC : csr_write_data = csr_data & (~regdata1_fwded);
  //   `ZICSR_OP_CSRRWI: csr_write_data = imm;
  //   `ZICSR_OP_CSRRSI: csr_write_data = csr_data | imm;
  //   `ZICSR_OP_CSRRCI: csr_write_data = csr_data & (~imm);
  //   default:          csr_write_data = 0;
  //   endcase
  // end
  /* ------------------------------ */

  csrfile csrfile_instance (
    .clk(clk),
    .rst(rst),
    .stall(stall),
    .hard_stall(hard_stall),
    .read_csr(csr),
    .read_data(csrdata),
    .satp(satp),
    .write_en(`ZICSR_OP(__wb_ctl_bus) != `ZICSR_OP_NONE),
    .write_csr(__wb_csr),
    .write_data(__wb_csr_write_data)

    // trap handling ports
    // .trap_mode(trap_mode),
    // .read_mip(mip),
    // .read_mstatus(mstatus),
    // .read_mie(mie),
    // .read_vec(vec),
    // .read_mideleg(mideleg),
    // .read_medeleg(medeleg),
    // .write_mstatus(write_mstatus),
    // .write_cause(write_cause),
    // .write_epc(write_epc)
  );

  // shift is implicitly added in the immgen block
  // TODO! optimize this to take the alu output instead of an extra adder here
  // assign next_pc = (trap_taken)
  //   ? vec
  //   :(`JALR(ctl_bus) ? regdata1_fwded: pc) + imm;
  assign next_pc = (`JALR(ctl_bus) ? regdata1_fwded: pc) + imm;

  // flush the IF_ID and ID_EX stages if trap occurs
  // assign nopi = (trap_taken)
  //   ? `NOPI_IF_ID | `NOPI_ID_EX
  //   :  `NOPI_NONE;
endmodule
