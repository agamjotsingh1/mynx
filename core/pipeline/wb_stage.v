`include "defs.vh"

module wb_stage (
  output wor `W(`STLEN) stall,

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
  output wor  `W(`NOPILEN)   nopi,
  output wire                trap_taken,
  output wire `W(`DLEN)      next_pc,
  output wire `W(`PRIVLEN)   next_priv,

  // trap handling (csrfile)
  output reg `W(`TRAPMODELEN) trap_mode,
  input wire `W(`DLEN)        mip,
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
    if(`XCEP(xcep)) begin
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
    // intrs
    else if((pending_m_intr != 0) && m_intr_en)
      trap_mode = `TRAPMODE_MINTR;
    else if((pending_s_intr != 0) && s_intr_en)
      trap_mode = `TRAPMODE_SINTR;
  end
  /* ----------------------------- */


  /* --- setting values for trap csr writes --- */
  wire   is_trap_m  = (trap_mode == `TRAPMODE_MINTR || trap_mode == `TRAPMODE_MXCEP);
  wire   is_trap_s  = (trap_mode == `TRAPMODE_SINTR || trap_mode == `TRAPMODE_SXCEP);
  wire   is_xcep    = (trap_mode == `TRAPMODE_MXCEP || trap_mode == `TRAPMODE_SXCEP);
  assign trap_taken = (trap_mode != `TRAPMODE_NONE);

  always @(*) begin
    write_mstatus = mstatus;
    write_cause   = 0;

    // if exception -> store current pc as this instr is NOT executed
    // if intr -> store mem pc as this instr is executed
    write_epc     = is_xcep ? pc: (valid ? anchor_pc: safe_anchor_pc);

    if(is_trap_m) begin
      `MSTATUS_MPP(write_mstatus) = priv;
      `MSTATUS_MPIE(write_mstatus) = `MSTATUS_MIE(mstatus);
      `MSTATUS_MIE(write_mstatus) = 0;
      // MSB of trap mode specifies interrupt or exception
      write_cause = {trap_mode[`TRAPMODELEN-1], 
        trap_mode[`TRAPMODELEN-1] ? `MIP_GET_MICAUSE(pending_m_intr): `XCEP_CAUSE(xcep)};
    end
    else if(is_trap_s) begin
      // LSB of priv specifies user/supervisor if we know we trapped into supervisor
      `MSTATUS_SPP(write_mstatus) = priv[0];
      `MSTATUS_SPIE(write_mstatus) = `MSTATUS_SIE(mstatus);
      `MSTATUS_SIE(write_mstatus) = 0;
      // MSB of trap mode specifies interrupt or exception
      write_cause = {trap_mode[`TRAPMODELEN-1], 
        trap_mode[`TRAPMODELEN-1] ? `MIP_GET_SICAUSE(pending_s_intr): `XCEP_CAUSE(xcep)};
    end
  end
  /* ------------------------------------------ */

  always @(posedge clk) begin
    if(rst) safe_anchor_pc <= `RSTPC;
    else if(valid && (!is_xcep)) safe_anchor_pc <= anchor_pc;
  end

  // flush everything except the PC
  assign nopi = trap_taken ? (`NOPI_ALL & (~(`NOPI_PC))): `NOPI_NONE;

  // assign next pc to whatever vec
  // will be taken up if trap_taken is high
  assign next_pc = vec & `VEC_MASK;

  assign next_priv = is_trap_m
    ? `PRIVM
    : (is_trap_s ? `PRIVS: priv);

  // stall the regfile and csrfile
  // so that no updates happen when exceptions
  // in interrupt the instruction should still execute
  assign stall = is_xcep
    ? `STALL_REGFILE | `STALL_CSRFILE
    : `STALL_NONE;
endmodule
