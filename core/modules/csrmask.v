`include "defs.vh"

module csrmask (
  input wire `W(`CSRLEN) csr,
  input wire `W(`DLEN)   csr_read_data,
  input wire `W(`DLEN)   csr_write_data,
  output reg `W(`DLEN)   masked_csr_write_data
);
  always @(*) begin
    case(csr)
      `CSR_MSTATUS : masked_csr_write_data = (csr_write_data & `MSTATUS_MASK)  | (csr_read_data & (~`MSTATUS_MASK));
      `CSR_SSTATUS : masked_csr_write_data = (csr_write_data & `SSTATUS_MASK)  | (csr_read_data & (~`SSTATUS_MASK));
      `CSR_MEPC    : masked_csr_write_data = (csr_write_data & `MEPC_MASK)     | (csr_read_data & (~`MEPC_MASK));
      `CSR_SEPC    : masked_csr_write_data = (csr_write_data & `SEPC_MASK)     | (csr_read_data & (~`SEPC_MASK));
      `CSR_MEDELEG : masked_csr_write_data = (csr_write_data & `MEDELEG_MASK)  | (csr_read_data & (~`MEDELEG_MASK));
      `CSR_MIDELEG : masked_csr_write_data = (csr_write_data & `MIDELEG_MASK)  | (csr_read_data & (~`MIDELEG_MASK));
      `CSR_MIE     : masked_csr_write_data = (csr_write_data & `MIE_MASK)      | (csr_read_data & (~`MIE_MASK));
      `CSR_SIE     : masked_csr_write_data = (csr_write_data & `SIE_MASK)      | (csr_read_data & (~`SIE_MASK));
      `CSR_MIP     : masked_csr_write_data = (csr_write_data & `MIP_MASK)      | (csr_read_data & (~`MIP_MASK));
      `CSR_SIP     : masked_csr_write_data = (csr_write_data & `SIP_MASK)      | (csr_read_data & (~`SIP_MASK));
      `CSR_MTVEC   : masked_csr_write_data = (csr_write_data & `MTVEC_MASK)    | (csr_read_data & (~`MTVEC_MASK));
      `CSR_STVEC   : masked_csr_write_data = (csr_write_data & `STVEC_MASK)    | (csr_read_data & (~`STVEC_MASK));
      `CSR_MSCRATCH: masked_csr_write_data = csr_write_data;
      `CSR_SSCRATCH: masked_csr_write_data = csr_write_data;
      `CSR_MCAUSE  : masked_csr_write_data = csr_write_data;
      `CSR_SCAUSE  : masked_csr_write_data = csr_write_data;
      `CSR_SATP    : masked_csr_write_data = (csr_write_data & `SATP_MASK)     | (csr_read_data & (~`SATP_MASK));
      default      : masked_csr_write_data = 0;
    endcase
  end
endmodule
