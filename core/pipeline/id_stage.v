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
  input wor               xcep,
  input wire `W(`DLEN)    xcep_cause,
  input wire `W(PRIVLEN)  priv,
  input wor  `W(NORILEN)  nori,

  input wire `W(`DLEN)    pc,
  input wire `W(`ILEN)    instr,
  input wor  `W(`STLEN)   stall, // for csr

  // parsing results
  output wire `W(`RLEN)   rs1,
  output wire `W(`RLEN)   rs2,
  output wire `W(`RLEN)   rd,
  output reg  `W(`DLEN)   csr_data,  // data to pass to EX-stage to update rd
  output wire `W(`DLEN)   satp,
  output wire `W(`DLEN)   regdata1,
  output wire `W(`DLEN)   regdata2,
  output wire `W(`DLEN)   imm,

  // alu control outputs
  output wire `W(`ALU_OPLEN) alu_op,

  // control outputs
  output wire `W(`CTL_BUSLEN) ctl_bus,

  // branch taken or not (for both branch and jal instr)
  output reg branch_taken,

  // next pc (for branching/jal)
  output reg `W(`DLEN) next_pc,

  // regwrites from wb stage
  input wire `W(`RLEN) __wb_rd,
  input wire           __wb_reg_write,

  // fwd controls
  input wire `W(`FWDLEN)  fwd1,
  input wire `W(`FWDLEN)  fwd2,

  // fwd inputs
  input wire `W(`DLEN)    __mem_ex_res,
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

    .write_en(__wb_reg_write),
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

  // TODO! think about how you would go about negedge/posedge for csrfile
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

  wire `W(DLEN) mstatus, mip, mie, mideleg, medeleg;

  /* --- determining trap mode --- */
  reg `W(TRAPMODELEN) trap_mode;
  wire m_intr_en = (priv < `PRIVM) || (priv == `PRIVM && `MSTATUS_MIE(mstatus));
  wire s_intr_en = (priv < `PRIVS) || (priv == `PRIVS && `MSTATUS_SIE(mstatus));

  wire `W(`DLEN) pending_intr    = mip & mie;
  wire `W(`DLEN) pending_s_instr = pending_intr & mideleg;
  wire `W(`DLEN) pending_m_instr = pending_intr & (~mideleg);

  always @(*) begin
    // intrs
    if((pending_m_intr != 0) && m_intr_en)      trap_mode = `TRAPMODE_MINTR;
    else if((pending_s_intr != 0) && s_intr_en) trap_mode = `TRAPMODE_SINTR;
    // xceps
    else if(xcep) begin
      // If in M-mode -> Always M-mode
      // If in U/S-mode AND delegated -> S-mode
      // If in U/S-mode AND NOT delegated -> M-mode
      if ((priv < `PRIVM) && medeleg[xcep_cause]) trap_mode = `TRAPMODE_SXCEP;
      else trap_mode = `TRAPMODE_MXCEP;
    end
  end
  /* ----------------------------- */

  // finish the csr reading/writing task in ID stage only
  wire `W(`CSRLEN) csr;
  wire `W(`DLEN) csr_read_data;
  // TODO! optimize this so ALU is used for | and &
  /* verilator lint_off WIDTHTRUNC */
  wire csr_write_en =
    (`ZICSR_OP(ctl_bus) != `ZICSR_OP_NONE) &&
    (!(stall & `STALL_CSRFILE)) &&
    (!hard_stall) &&
    (!trap);
  /* verilator lint_on WIDTHTRUNC */
  reg `W(`DLEN) csr_write_data;

  always @(*) begin
    if(trap) begin
      csr_write_data = 
    end
    else begin
      case(`ZICSR_OP(ctl_bus)) 
      `ZICSR_OP_NONE  : csr_write_data = 0;
      `ZICSR_OP_CSRRW : csr_write_data = regdata1_fwded;
      `ZICSR_OP_CSRRS : csr_write_data = csr_read_data | regdata1_fwded;
      `ZICSR_OP_CSRRC : csr_write_data = csr_read_data & (~regdata1_fwded);
      `ZICSR_OP_CSRRWI: csr_write_data = imm;
      `ZICSR_OP_CSRRSI: csr_write_data = csr_read_data | imm;
      `ZICSR_OP_CSRRCI: csr_write_data = csr_read_data & (~imm);
      default:          csr_write_data = 0;
      endcase
    end
  end

  // csrfile is negedge so this same stage writing works out
  csrfile csrfile_instance (
    .clk(clk),
    .rst(rst),
    .read_csr(csr),
    .read_data(csr_read_data),
    .satp(satp),
    .write_en(csr_write_en),
    .write_csr(csr),
    .write_data(csr_write_data)
  );

  always @(negedge clk) csr_data <= csr_read_data;

  // shift is implicitly added in the immgen block
  // TODO! optimize this to take the alu output instead of an extra adder here
  reg  `W(`DLEN)   trap_pc;

  reg  `W(`CSRLEN) trap_csr;
  wire `W(`CSRLEN) trap_csr_data = trap_cause;

  always @(*) begin
    trap_saved_cause = trap_cause;

    case(priv)
      `PRIVM: begin
        trap_pc  = mtvec;
        trap_csr = `CSR_MCAUSE;
      end
      `PRIVS: begin
        trap_pc
      end
    endcase
  end

  assign next_pc = trap
    ? trap_pc
    :(`JALR(ctl_bus) ? regdata1_fwded: pc) + imm;

  // flush the IF_ID and ID_EX stages if trap occurs
  assign nopi = trap ? `NOPI_IF_ID | `NOPI_ID_EX: `NOPI_NONE;
endmodule
