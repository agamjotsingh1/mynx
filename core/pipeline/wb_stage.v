module wb_stage (
  output wire `W(`STLEN) stall,

  input wire clk,
  input wire rst,

  input wire `W(`DLEN)       regw_data,
  input wire `W(`DLEN)       mem_res,
  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`CTL_BUSLEN) ctl_bus,
  /* verilator lint_on UNUSEDSIGNAL */

  output wire `W(`DLEN)      write_data,

  // trap handling
  input wire                 valid,
  input wire  `W(`DLEN)      pc,
  input wire  `W(`DLEN)      anchor_pc,
  input wire  `W(`PRIVLEN)   priv,
  input wire  `W(`DLEN)      xcep,
  output wire `W(`NOPILEN)   nopi,
  output wire                trap_taken,
  output wire `W(`DLEN)      next_pc,
  output reg  `W(`PRIVLEN)   next_priv,

  // trap handling (csrfile)
  output reg `W(`TRAPMODELEN) trap_mode,
  input wire `W(`DLEN)        mip,
  input wire `W(`DLEN)        epc,
  input wire `W(`DLEN)        mstatus,
  input wire `W(`DLEN)        mie,
  input wire `W(`DLEN)        vec,
  input wire `W(`DLEN)        mideleg,
  input wire `W(`DLEN)        medeleg,
  output reg `W(`DLEN)        write_mstatus,
  output reg `W(`DLEN)        write_cause,
  output reg `W(`DLEN)        write_epc
);
  // anchors even when interrupt on bubble
  reg `W(`DLEN) safe_anchor_pc;

  assign write_data =
    `MEM_TO_REG(ctl_bus) ? mem_res: regw_data;

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

  /* --- determining trap mode --- */
  wire m_intr_en = (priv < `PRIVM) || (priv == `PRIVM && `MSTATUS_MIE(mstatus));
  wire s_intr_en = (priv < `PRIVS) || (priv == `PRIVS && `MSTATUS_SIE(mstatus));

  wire `W(`DLEN) pending_intr   = mip & mie;
  wire `W(`DLEN) pending_s_intr = pending_intr & mideleg;
  wire `W(`DLEN) pending_m_intr = pending_intr & (~mideleg);

  always @(*) begin
    trap_mode = `TRAPMODE_NONE;

    // xceps (higher priority than intrs)
    if(valid && `XCEP(xcep)) begin
      // if in M-mode -> Always M-mode
      // if in U/S-mode AND delegated -> S-mode
      // if in U/S-mode AND NOT delegated -> M-mode
      /* verilator lint_off WIDTHTRUNC */
      if ((priv < `PRIVM) && medeleg[`XCEP_CAUSE(xcep)])
      /* verilator lint_on WIDTHTRUNC */
        trap_mode = `TRAPMODE_SXCEP;
      else
        trap_mode = `TRAPMODE_MXCEP;
    end

    // rets
    else if(`MRET(ctl_bus))
      trap_mode = `TRAPMODE_MRET;
    else if(`SRET(ctl_bus))
      trap_mode = `TRAPMODE_SRET;

    // intrs
    else if((pending_m_intr != 0) && m_intr_en && valid)
      trap_mode = `TRAPMODE_MINTR;
    else if((pending_s_intr != 0) && s_intr_en && valid)
      trap_mode = `TRAPMODE_SINTR;
  end
  /* ----------------------------- */


  /* --- setting values for trap csr writes --- */
  assign trap_taken = `TRAP_TAKEN(trap_mode);

  always @(*) begin
    write_mstatus = mstatus;
    write_cause   = 0;
    // if exception -> store current pc as this instr is NOT executed
    // if intr -> store mem pc as this instr is executed
    // if ret -> ignored in csrfile
    write_epc     = `TRAP_XCEP(trap_mode) ? pc: (valid ? anchor_pc: safe_anchor_pc);

    if(trap_mode == `TRAPMODE_MRET) begin
      `MSTATUS_MIE(write_mstatus) = `MSTATUS_MPIE(mstatus);
      `MSTATUS_MPP(write_mstatus) = `PRIVU;
      `MSTATUS_MPIE(write_mstatus) = 1;
    end
    else if(trap_mode == `TRAPMODE_SRET) begin
      `MSTATUS_SIE(write_mstatus) = `MSTATUS_SPIE(mstatus);
      /* verilator lint_off WIDTHTRUNC */
      `MSTATUS_SPP(write_mstatus) = `PRIVU;
      /* verilator lint_on WIDTHTRUNC */
      `MSTATUS_SPIE(write_mstatus) = 1;
    end

    // intr/xcep
    else if(`TRAP_M(trap_mode)) begin
      `MSTATUS_MPP(write_mstatus) = priv;
      `MSTATUS_MPIE(write_mstatus) = `MSTATUS_MIE(mstatus);
      `MSTATUS_MIE(write_mstatus) = 0;
      write_cause = {~`TRAP_XCEP(trap_mode),
        `TRAP_XCEP(trap_mode) ? `XCEP_CAUSE(xcep): `MIP_GET_MICAUSE(pending_m_intr)};
    end
    else if(`TRAP_S(trap_mode)) begin
      // LSB of priv specifies user/supervisor if we know we trapped into supervisor
      `MSTATUS_SPP(write_mstatus) = priv[0];
      `MSTATUS_SPIE(write_mstatus) = `MSTATUS_SIE(mstatus);
      `MSTATUS_SIE(write_mstatus) = 0;
      write_cause = {~`TRAP_XCEP(trap_mode),
        `TRAP_XCEP(trap_mode) ? `XCEP_CAUSE(xcep): `MIP_GET_SICAUSE(pending_s_intr)};
    end
  end
  /* ------------------------------------------ */

  always @(posedge clk) begin
    if(rst) safe_anchor_pc <= `RSTPC;
    else if(valid && (!`TRAP_XCEP(trap_mode))) safe_anchor_pc <= anchor_pc;
  end

  // flush everything except the PC
  assign nopi = trap_taken ? (`NOPI_ALL & (~(`NOPI_PC))): `NOPI_NONE;

  // TODO! add support for vector interrutps
  // assign next pc to whatever vec
  // will be taken up if trap_taken is high
  assign next_pc = `TRAP_RET(trap_mode)
    ? epc
    : vec & `VEC_MASK;

  always @(*) begin
    next_priv = priv;

    if(trap_mode == `TRAPMODE_MRET)
      next_priv = `MSTATUS_MPP(mstatus);
    else if(trap_mode == `TRAPMODE_SRET)
      next_priv = {1'b0, `MSTATUS_SPP(mstatus)};
    else if(`TRAP_M(trap_mode))
      next_priv = `PRIVM;
    else if(`TRAP_S(trap_mode))
      next_priv = `PRIVS;
  end

  // stall the regfile and csrfile
  // so that no updates happen when exceptions
  // in interrupt the instruction should still execute
  assign stall = `TRAP_XCEP(trap_mode)
    ? `STALL_REGFILE | `STALL_CSRFILE
    : `STALL_NONE;
endmodule
