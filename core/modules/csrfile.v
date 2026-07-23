`include "defs.vh"

// CSR Fields
// 1. WARL -> Write Any, Read Legal
// ..Ignore all illegal writes, preserve the values in these fields
// ..but dont generate exceptions when software tries to write to them
// 2. WPRI -> Write Preserves, Read Ignores
// ..Writes are ignored, preserved for later use
// 3. WLRL -> Write Legal, Read Legal
// ..Software can write whatever it wants
// ..but its the job of software to ensure legality,
// ..hardware has nothing to do with this
module csrfile (
	input wire  clk,
  input wire  rst,
  input wire  hard_stall,
  output wire illegal_csr,

  input wire `W(`PRIVLEN) priv,

  input wire `W(`STLEN) stall,

	// standard read port
	input wire `W(`CSRLEN) read_csr,
	input wire             read_csr_future_write, // will read_csr be written to in future 
	output reg `W(`DLEN)   read_data,

  // satp read port (mmu -> pagetable ppn fetching)
  // posedge triggered
  output wire `W(`DLEN)   read_satp,

	// standard write port
	input wire              write_en,
	input wire `W(`CSRLEN)  write_csr,
	input wire `W(`DLEN)    write_data,

  // external interrupt req
  input wire m_ext_irq,
  input wire s_ext_irq,

  // timer interrupt req
  input wire m_timer_irq,
  input wire s_timer_irq,

  // instruction retire (minstret)
  input wire  __wb_valid,

  // perf counters
  input wire `W(`DLEN)   perf_cache_hits_instr,
  input wire `W(`DLEN)   perf_mem_acc_instr,
  input wire `W(`DLEN)   perf_cache_hits_data,
  input wire `W(`DLEN)   perf_mem_acc_data,

  // trap handling ports
  input wire  `W(`TRAPMODELEN) trap_mode,
  output wire `W(`DLEN)        read_mip,
  output wire `W(`DLEN)        read_mstatus,
  output wire `W(`DLEN)        read_mie,
  output wire `W(`DLEN)        read_vec,
  output wire `W(`DLEN)        read_epc,
  output wire `W(`DLEN)        read_mideleg,
  output wire `W(`DLEN)        read_medeleg,
  input  wire `W(`DLEN)        write_mstatus,
  input  wire `W(`DLEN)        write_cause,
  input  wire `W(`DLEN)        write_epc
);
  reg invalid_address;

  wire ro_violation = read_csr_future_write &&
    (read_csr`CSRPERMSLICE == `CSR_PERM_RO); 

  wire priv_violation = (priv < read_csr`CSRPRIVSLICE);

  assign illegal_csr =
    invalid_address | ro_violation | priv_violation;

  // CSRs
  reg `W(`DLEN) mstatus;
  reg `W(`DLEN) mepc;
  reg `W(`DLEN) mhartid;
  reg `W(`DLEN) medeleg;
  reg `W(`DLEN) mideleg;
  reg `W(`DLEN) mie;
  reg `W(`DLEN) mip;
  reg `W(`DLEN) mtvec;
  reg `W(`DLEN) mscratch;
  reg `W(`DLEN) mcause;
  reg `W(`DLEN) sepc;
  reg `W(`DLEN) stvec;
  reg `W(`DLEN) sscratch;
  reg `W(`DLEN) scause;
  reg `W(`DLEN) satp;

  reg `W(`DLEN) mcycle;
  reg `W(`DLEN) minstret;
  reg `W(`DLEN) mcountinhibit;
  reg `W(`DLEN) mcounteren;
  reg `W(`DLEN) scounteren;
  reg `W(`DLEN) mhpmcounter [`HPM_COUNTER_START_IDX:`HPM_COUNTER_END_IDX];

  // buffers to handle negedge/posedge mismatch
  reg `W(`TRAPMODELEN) trap_mode_buf;
  reg `W(`DLEN)        mstatus_buf;
  reg `W(`DLEN)        cause_buf;
  reg `W(`DLEN)        epc_buf;
  
  always @(posedge clk) begin
    if(rst || (trap_mode == `TRAPMODE_NONE && (!hard_stall))) begin
      trap_mode_buf <= 0;
      mstatus_buf <= 0;
      cause_buf <= 0;
      epc_buf <= 0;
    end
    else if(!hard_stall) begin
      trap_mode_buf <= trap_mode;
      mstatus_buf <= write_mstatus;
      cause_buf <= write_cause;
      epc_buf <= write_epc;
    end
  end

  integer i;
	always @(posedge clk) begin
    if(rst) begin
      mstatus <= `MSTATUS_RST;
      mepc <= `MEPC_RST;
      sepc <= `SEPC_RST;
      mhartid <= `MHARTID_RST;
      medeleg <= `MEDELEG_RST;
      mideleg <= `MIDELEG_RST;
      mie <= `MIE_RST;
      mip <= `MIP_RST;
      mtvec <= `MTVEC_RST;
      stvec <= `MTVEC_RST;
      mscratch <= `MSCRATCH_RST;
      sscratch <= `SSCRATCH_RST;
      mcause <= `MCAUSE_RST;
      scause <= `SCAUSE_RST;
      satp <= `SATP_RST;
      mcountinhibit <= 0;
      mcounteren <= 0;
      scounteren <= 0;
    end
    else if(!hard_stall) begin
      if(trap_mode_buf != `TRAPMODE_NONE) begin
        // trust all buffers
        // as hardware will write it
        mstatus  <= mstatus_buf;

        if(`TRAP_M(trap_mode_buf)) begin
          mcause <= cause_buf;
          mepc   <= epc_buf;
        end
        else if(`TRAP_S(trap_mode_buf)) begin
          scause <= cause_buf;
          sepc   <= epc_buf;
        end
      end
      /* verilator lint_off WIDTHTRUNC */
      else if(write_en && (!(stall & `STALL_CSRFILE))) begin
      /* verilator lint_on WIDTHTRUNC */
      /* verilator lint_off CASEINCOMPLETE */
      // any changes made below have to be reproduced in csrmask.v
        case(write_csr)
          `CSR_MSTATUS : mstatus  <= (write_data & `MSTATUS_MASK)  | (mstatus  & (~`MSTATUS_MASK));
          `CSR_SSTATUS : mstatus  <= (write_data & `SSTATUS_MASK)  | (mstatus  & (~`SSTATUS_MASK));
          `CSR_MEPC    : mepc     <= (write_data & `MEPC_MASK)     | (mepc     & (~`MEPC_MASK));
          `CSR_SEPC    : sepc     <= (write_data & `SEPC_MASK)     | (sepc     & (~`SEPC_MASK));
          `CSR_MEDELEG : medeleg  <= (write_data & `MEDELEG_MASK)  | (medeleg  & (~`MEDELEG_MASK));
          `CSR_MIDELEG : mideleg  <= (write_data & `MIDELEG_MASK)  | (mideleg  & (~`MIDELEG_MASK));
          `CSR_MIE     : mie      <= (write_data & `MIE_MASK)      | (mie      & (~`MIE_MASK));
          `CSR_SIE     : mie      <= (write_data & `SIE_MASK)      | (mie      & (~`SIE_MASK));
          `CSR_MIP     : mip      <= (write_data & `MIP_MASK)      | (mip      & (~`MIP_MASK));
          `CSR_SIP     : mip      <= (write_data & `SIP_MASK)      | (mip      & (~`SIP_MASK));
          `CSR_MTVEC   : mtvec    <= (write_data & `MTVEC_MASK)    | (mtvec    & (~`MTVEC_MASK));
          `CSR_STVEC   : stvec    <= (write_data & `STVEC_MASK)    | (stvec    & (~`STVEC_MASK));
          `CSR_MSCRATCH: mscratch <= write_data;
          `CSR_SSCRATCH: sscratch <= write_data;
          `CSR_MCAUSE  : mcause   <= write_data;
          `CSR_SCAUSE  : scause   <= write_data;
          `CSR_SATP    : satp     <= (write_data & `SATP_MASK)     | (satp     & (~`SATP_MASK));

          `CSR_MCOUNTINHIBIT: mcountinhibit <= write_data;
          `CSR_MCOUNTEREN   : mcounteren    <= write_data;
          `CSR_SCOUNTEREN   : scounteren    <= write_data;
        endcase
      /* verilator lint_on CASEINCOMPLETE */
      end
    end
	end

  wire retire =
    __wb_valid && (!hard_stall) && !(`TRAP_XCEP(trap_mode));

  always @(posedge clk) begin
    if(rst) begin
      mcycle <= 0;
      minstret <= 0;

      for(i = `HPM_COUNTER_START_IDX; i <= `HPM_COUNTER_END_IDX; i = i+1)
        mhpmcounter[i] <= 0;
    end
    else begin
      mcycle <= mcycle + (!mcountinhibit[`HPM_CYCLE_IDX]);
      if(retire) minstret <= minstret + (!mcountinhibit[`HPM_INSTRET_IDX]);

      mhpmcounter[`HPM_CACHE_HITS_I_IDX] <= !mcountinhibit[`HPM_CACHE_HITS_I_IDX] ? perf_cache_hits_instr: 0;
      mhpmcounter[`HPM_MEM_ACC_I_IDX] <= !mcountinhibit[`HPM_MEM_ACC_I_IDX] ? perf_mem_acc_instr: 0;

      mhpmcounter[`HPM_CACHE_HITS_D_IDX] <= !mcountinhibit[`HPM_CACHE_HITS_D_IDX] ? perf_cache_hits_data: 0;
      mhpmcounter[`HPM_MEM_ACC_D_IDX] <= !mcountinhibit[`HPM_MEM_ACC_D_IDX] ? perf_mem_acc_data: 0;
    end
  end

  /* verilator lint_off WIDTHEXPAND */
  wire `W(`DLEN) mip_with_irq =
    mip | 
    ((m_ext_irq) << `MIP_MEIP_POS) |
    ((s_ext_irq) << `MIP_SEIP_POS) |
    ((m_timer_irq) << `MIP_MTIP_POS) |
    ((s_timer_irq) << `MIP_STIP_POS);
  /* verilator lint_on WIDTHEXPAND */

  /* verilator lint_off WIDTHEXPAND */
  wire `W(`DLEN) mhpm_idx = read_csr - `CSR_MHPM_COUNTER_BASE;
  wire `W(`DLEN) hpm_idx  = read_csr - `CSR_HPM_COUNTER_BASE;
  /* verilator lint_on WIDTHEXPAND */

  always @(*) begin
    read_data = 0;
    invalid_address = 0;

    case(read_csr)
      `CSR_SSTATUS : read_data = mstatus      & `SSTATUS_MASK;
      `CSR_SIE     : read_data = mie          & `SIE_MASK;
      `CSR_SIP     : read_data = mip_with_irq & `SIP_READ_MASK;
      `CSR_MSTATUS : read_data = mstatus;
      `CSR_MEPC    : read_data = mepc;
      `CSR_SEPC    : read_data = sepc;
      `CSR_MEDELEG : read_data = medeleg;
      `CSR_MIDELEG : read_data = mideleg;
      `CSR_MIE     : read_data = mie;
      `CSR_MIP     : read_data = mip_with_irq;
      `CSR_MTVEC   : read_data = mtvec;
      `CSR_STVEC   : read_data = stvec;
      `CSR_MSCRATCH: read_data = mscratch;
      `CSR_SSCRATCH: read_data = sscratch;
      `CSR_MCAUSE  : read_data = mcause;
      `CSR_SCAUSE  : read_data = scause;
      `CSR_MHARTID : read_data = mhartid;
      `CSR_SATP    : read_data = satp;
      `CSR_MCOUNTINHIBIT: read_data = mcountinhibit;
      `CSR_MCOUNTEREN   : read_data = mcounteren;
      `CSR_SCOUNTEREN   : read_data = scounteren;
      `CSR_MCYCLE  : read_data = `MHPM_COUNTER_EN(mcounteren, `HPM_CYCLE_IDX, priv) ? mcycle: 0;
      `CSR_CYCLE   : read_data = `HPM_COUNTER_EN(scounteren, `HPM_CYCLE_IDX, priv)  ? mcycle: 0;
      `CSR_MINSTRET: read_data = `MHPM_COUNTER_EN(mcounteren, `HPM_INSTRET_IDX, priv) ? minstret: 0;
      `CSR_INSTRET : read_data = `HPM_COUNTER_EN(scounteren, `HPM_INSTRET_IDX, priv)  ? minstret: 0;
      default      : begin
        /* verilator lint_off WIDTHTRUNC */
        if(mhpm_idx >= `HPM_COUNTER_START_IDX && mhpm_idx <= `HPM_COUNTER_END_IDX) begin
          read_data = `MHPM_COUNTER_EN(mcounteren, mhpm_idx, priv) ? mhpmcounter[mhpm_idx]: 0;
        end
        else if(hpm_idx >= `HPM_COUNTER_START_IDX && hpm_idx <= `HPM_COUNTER_END_IDX) begin
          read_data = `HPM_COUNTER_EN(scounteren, hpm_idx, priv) ? mhpmcounter[hpm_idx]: 0;
        end
        /* verilator lint_on WIDTHTRUNC */
        else invalid_address = 1;
      end
    endcase
  end

  assign read_mip     = mip_with_irq;
  assign read_mstatus = mstatus;
  assign read_mie     = mie;
  assign read_satp    = satp;
  assign read_vec     = `TRAP_M(trap_mode) ? mtvec: stvec;
  assign read_epc     = (trap_mode == `TRAPMODE_MRET) ? mepc: sepc;
  assign read_mideleg = mideleg;
  assign read_medeleg = medeleg;
endmodule
