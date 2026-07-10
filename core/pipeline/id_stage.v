`include "defs.vh"

module id_stage (
  input wire clk,
  input wire rst,
  input wire  hard_stall,
  input wire `W(`PRIVLEN) priv,

  input wire  `W(`DLEN)   pc,
  output wire `W(`DLEN)   anchor_pc,
  input wire  `W(`ILEN)   instr,
  input wire  `W(`STLEN)  stall,

  // parsing results
  output wire `W(`RLEN)   rs1,
  output wire `W(`RLEN)   rs2,
  output wire `W(`RLEN)   rd,
  output wire `W(`DLEN)   satp,
  output wire `W(`DLEN)   regdata1,
  output wire `W(`DLEN)   regdata2,
  output wire `W(`CSRLEN) csr,
  output wire `W(`DLEN)   csrdata,
  output wire `W(`DLEN)   imm,

  // alu control outputs
  output wire `W(`ALU_OPLEN) alu_op,

  // control outputs
  output wire `W(`CTL_BUSLEN) ctl_bus,

  // branch taken or not (for both branch and jal instr)
  output reg  branch_taken,

  // next pc (for branching/jal)
  output wire `W(`DLEN) next_pc,

  // (reg/csr)writes from wb stage
  input wire `W(`RLEN)       __wb_rd,
  input wire `W(`CSRLEN)     __wb_csr,
  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`CTL_BUSLEN) __wb_ctl_bus,
  /* verilator lint_on UNUSEDSIGNAL */
  input wire `W(`DLEN)       __wb_csr_write_data,
  input wire `W(`DLEN)       __wb_write_data,

  // fwd controls
  input wire `W(`FWDLEN)  fwd1,
  input wire `W(`FWDLEN)  fwd2,

  // fwd inputs
  input wire `W(`DLEN)    __mem_ex_res,

  input wire `W(`DLEN)   xcep,
  output reg `W(`DLEN)   uxcep,

  // irq
  input wire __mem_ext_irq,
  input wire __mem_timer_irq,

  // trap handling ports
  input wire  `W(`TRAPMODELEN) __wb_trap_mode,
  output wire `W(`DLEN)        mip,
  output wire `W(`DLEN)        mstatus,
  output wire `W(`DLEN)        mie,
  output wire `W(`DLEN)        vec,
  output wire `W(`DLEN)        epc,
  output wire `W(`DLEN)        mideleg,
  output wire `W(`DLEN)        medeleg,
  input wire  `W(`DLEN)        __wb_write_mstatus,
  input wire  `W(`DLEN)        __wb_write_cause,
  input wire  `W(`DLEN)        __wb_write_epc
);
  wire illegal_csr;

  // always@(posedge clk) begin
  //   $display("PC: %x, illegal csr: %d, csr: %x, priv: %d", pc, illegal_csr && (`ZICSR_OP(ctl_bus) != `ZICSR_OP_NONE), csr, priv);
  // end

  always @(*) begin
    uxcep = 0;

    if(`XCEP(xcep))
      uxcep = xcep;
    else if(
      `ILLEGAL(ctl_bus) |
      (illegal_csr && (`ZICSR_OP(ctl_bus) != `ZICSR_OP_NONE)) |
      (priv < `PRIVM && `MRET(ctl_bus)) |
      (priv < `PRIVS && `SRET(ctl_bus))
    ) uxcep = {1'b1, `XCEP_ILLEGAL_INSTRUCTION};
    else if(`ECALL(ctl_bus)) begin
      /* verilator lint_off CASEINCOMPLETE */
      case(priv)
        `PRIVU: uxcep = {1'b1, `XCEP_ECALL_FROM_U_MODE};
        `PRIVS: uxcep = {1'b1, `XCEP_ECALL_FROM_S_MODE};
        `PRIVM: uxcep = {1'b1, `XCEP_ECALL_FROM_M_MODE};
      endcase
      /* verilator lint_on CASEINCOMPLETE */
    end
    else if(`EBREAK(ctl_bus))
      uxcep = {1'b1, `XCEP_BREAKPOINT};
  end

  // instruction parsing
  assign rs1 = instr`RS1SLICE;
  assign rs2 = instr`RS2SLICE;
  assign rd  = instr`RDSLICE;
  assign csr = instr`CSRSLICE;

  regfile regfile_instance (
    .clk(clk),
    .rst(rst),
    .hard_stall(hard_stall),
    .stall(stall),

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

  wire `W(`DLEN) regdata1_fwded = (fwd1 == `FWD_EX_MEM) ? __mem_ex_res: regdata1;
  wire `W(`DLEN) regdata2_fwded = (fwd2 == `FWD_EX_MEM) ? __mem_ex_res: regdata2;

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

    branch_taken = branch_taken | (`JAL(ctl_bus) | `JALR(ctl_bus));
  end

  csrfile csrfile_instance (
    .clk(clk),
    .rst(rst),
    .hard_stall(hard_stall),
    .priv(priv),
    .read_csr_future_write(`CSR_WRITE(ctl_bus)),
    .illegal_csr(illegal_csr),
    .stall(stall),
    .read_csr(csr),
    .read_data(csrdata),
    .satp_mmu(satp),
    .write_en(`CSR_WRITE(__wb_ctl_bus)),
    .write_csr(__wb_csr),
    .write_data(__wb_csr_write_data),

    // ext irq
    .m_ext_irq(0),
    .s_ext_irq(__mem_ext_irq),

    // timer irq
    .m_timer_irq(__mem_timer_irq),
    .s_timer_irq(0),

    // trap handling ports
    .trap_mode(__wb_trap_mode),
    .read_mip(mip),
    .read_mstatus(mstatus),
    .read_mie(mie),
    .read_vec(vec),
    .read_epc(epc),
    .read_mideleg(mideleg),
    .read_medeleg(medeleg),
    .write_mstatus(__wb_write_mstatus),
    .write_cause(__wb_write_cause),
    .write_epc(__wb_write_epc)
  );

  // shift is implicitly added in the immgen block
  assign next_pc = (`JALR(ctl_bus) ? regdata1_fwded: pc) + imm;

  // anchor to this PC if you see a nop
  assign anchor_pc = branch_taken ? next_pc: pc + 4;
endmodule
