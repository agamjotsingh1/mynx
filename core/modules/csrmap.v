// map the CSRs to CSRMAPs for access in the file
module csrmap (
  input  wire `W(`CSRLEN)    csr,
  output reg  `W(`CSRMAPLEN) csrmap
);
  always @(*) begin
    case (csr)
      `CSR_MSTATUS:   csrmap = `CSRMAP_MSTATUS;
      `CSR_MEPC:      csrmap = `CSRMAP_MEPC;
      `CSR_MHARTID:   csrmap = `CSRMAP_MHARTID;
      `CSR_MEDELEG:   csrmap = `CSRMAP_MEDELEG;
      `CSR_MIDELEG:   csrmap = `CSRMAP_MIDELEG;
      `CSR_MIE:       csrmap = `CSRMAP_MIE;
      `CSR_MIP:       csrmap = `CSRMAP_MIP;
      `CSR_MTVEC:     csrmap = `CSRMAP_MTVEC;
      `CSR_MSCRATCH:  csrmap = `CSRMAP_MSCRATCH;
      `CSR_MCAUSE:    csrmap = `CSRMAP_MCAUSE;
      `CSR_MTVAL:     csrmap = `CSRMAP_MTVAL;
      `CSR_SSTATUS:   csrmap = `CSRMAP_SSTATUS;
      `CSR_SEPC:      csrmap = `CSRMAP_SEPC;
      `CSR_SATP:      csrmap = `CSRMAP_SATP;
      `CSR_STVEC:     csrmap = `CSRMAP_STVEC;
      `CSR_SSCRATCH:  csrmap = `CSRMAP_SSCRATCH;
      `CSR_SCAUSE:    csrmap = `CSRMAP_SCAUSE;
      `CSR_STVAL:     csrmap = `CSRMAP_STVAL;
      `CSR_SIE:       csrmap = `CSRMAP_SIE;
      `CSR_SIP:       csrmap = `CSRMAP_SIP;
      `CSR_PMPCFG0:   csrmap = `CSRMAP_PMPCFG0;
      `CSR_PMPADDR0:  csrmap = `CSRMAP_PMPADDR0;
      // TODO! make an invalid CSRMAP
      default:        csrmap = `CSRMAP_ILLEGAL;
    endcase
  end
endmodule
