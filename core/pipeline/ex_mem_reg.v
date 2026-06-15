`include "defs.vh"

module ex_mem_reg (
  input wor hard_stall,
  input wor `W(`STLEN)   stall,
  input wor `W(`NOPILEN) nopi,

  input wire clk,
  input wire rst,

  input wire                 in_valid,
  input wire `W(`DLEN)       in_pc,
  input wire `W(`DLEN)       in_anchor_pc,
  input wire `W(`RLEN)       in_rd,
  input wire `W(`CSRLEN)     in_csr,
  input wire `W(`DLEN)       in_ex_res,
  input wire `W(`DLEN)       in_mem_data,
  input wire `W(`DLEN)       in_csr_write_data,
  input wire `W(`CTL_BUSLEN) in_ctl_bus,
  input wire `W(`DLEN)       in_xcep,

  output reg                 out_valid,
  output reg `W(`DLEN)       out_pc,
  output reg `W(`DLEN)       out_anchor_pc,
  output reg `W(`RLEN)       out_rd,
  output reg `W(`CSRLEN)     out_csr,
  output reg `W(`DLEN)       out_ex_res,
  output reg `W(`DLEN)       out_mem_data,
  output reg `W(`DLEN)       out_csr_write_data,
  output reg `W(`CTL_BUSLEN) out_ctl_bus,
  output reg `W(`DLEN)       out_xcep
);
  /* verilator lint_off WIDTHTRUNC */
  always @(posedge clk) begin
    if(!hard_stall) begin
      if(rst || (nopi & `NOPI_EX_MEM)) begin
        out_valid <= 0;
        out_pc <= `RSTPC;
        out_anchor_pc <= `RSTPC;
        out_rd <= 0;
        out_ex_res <= 0;
        out_mem_data <= 0;
        out_ctl_bus <= 0;
        out_csr <= 0;
        out_csr_write_data <= 0;
        out_xcep <= 0;
      end
      else if (!(stall & `STALL_EX_MEM)) begin
        out_valid <= in_valid;
        out_pc <= in_pc;
        out_anchor_pc <= in_anchor_pc;
        out_rd <= in_rd;
        out_ex_res <= in_ex_res;
        out_mem_data <= in_mem_data;
        out_ctl_bus <= in_ctl_bus;
        out_csr <= in_csr;
        out_csr_write_data <= in_csr_write_data;
        out_xcep <= in_xcep;
      end
    end
  end
  /* verilator lint_on WIDTHTRUNC */
endmodule
