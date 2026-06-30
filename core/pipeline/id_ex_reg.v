`include "defs.vh"

module id_ex_reg (
  input wire hard_stall,

  input wire `W(`STLEN)   stall,
  input wire `W(`NOPILEN) nopi,

  input wire clk,
  input wire rst,

  input wire                 in_valid,
  input wire `W(`DLEN)       in_pc,
  input wire `W(`DLEN)       in_anchor_pc,
  input wire `W(`RLEN)       in_rs1,
  input wire `W(`RLEN)       in_rs2,
  input wire `W(`RLEN)       in_rd,
  input wire `W(`DLEN)       in_regdata1,
  input wire `W(`DLEN)       in_regdata2,
  input wire `W(`CSRLEN)     in_csr,
  input wire `W(`DLEN)       in_csrdata,
  input wire `W(`DLEN)       in_imm,
  input wire `W(`ALU_OPLEN)  in_alu_op,
  input wire `W(`CTL_BUSLEN) in_ctl_bus,
  input wire `W(`DLEN)       in_xcep,

  output reg                 out_valid,
  output reg `W(`DLEN)       out_pc,
  output reg `W(`DLEN)       out_anchor_pc,
  output reg `W(`RLEN)       out_rs1,
  output reg `W(`RLEN)       out_rs2,
  output reg `W(`RLEN)       out_rd,
  output reg `W(`DLEN)       out_regdata1,
  output reg `W(`DLEN)       out_regdata2,
  output reg `W(`CSRLEN)     out_csr,
  output reg `W(`DLEN)       out_csrdata,
  output reg `W(`DLEN)       out_imm,
  output reg `W(`ALU_OPLEN)  out_alu_op,
  output reg `W(`CTL_BUSLEN) out_ctl_bus,
  output reg `W(`DLEN)       out_xcep
);
  /* verilator lint_off WIDTHTRUNC */
  always @(posedge clk) begin
    if(rst || ((nopi & `NOPI_ID_EX) && !hard_stall)) begin
      out_valid <= 0;
      out_pc <= `RSTPC;
      out_anchor_pc <= `RSTPC;
      out_rs1 <= 0;
      out_rs2 <= 0;
      out_rd <= 0;
      out_regdata1 <= 0;
      out_regdata2 <= 0;
      out_imm <= 0;
      out_alu_op <= 0;
      out_ctl_bus <= 0;
      out_csr <= 0;
      out_csrdata <= 0;
      out_xcep <= 0;
    end
    else if (!hard_stall && (!(stall & `STALL_ID_EX))) begin
      out_valid <= in_valid;
      out_pc <= in_pc;
      out_anchor_pc <= in_anchor_pc;
      out_rs1 <= in_rs1;
      out_rs2 <= in_rs2;
      out_rd <= in_rd;
      out_regdata1 <= in_regdata1;
      out_regdata2 <= in_regdata2;
      out_imm <= in_imm;
      out_alu_op <= in_alu_op;
      out_ctl_bus <= in_ctl_bus;
      out_csr <= in_csr;
      out_csrdata <= in_csrdata;
      out_xcep <= in_xcep;
    end
  end
  /* verilator lint_on WIDTHTRUNC */
endmodule
