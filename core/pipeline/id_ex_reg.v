`include "defs.vh"

module id_ex_reg (
  input wor `W(`STLEN)   stall,
  input wor `W(`NOPILEN) nopi,

  input wire clk,
  input wire rst,

  input wire `W(`DLEN)       in_pc,
  input wire `W(`RLEN)       in_rs1,
  input wire `W(`RLEN)       in_rs2,
  input wire `W(`RLEN)       in_rd,
  input wire `W(`DLEN)       in_regdata1,
  input wire `W(`DLEN)       in_regdata2,
  input wire `W(`DLEN)       in_csr_data,
  input wire `W(`DLEN)       in_imm,
  input wire `W(`ALU_OPLEN)  in_alu_op,
  input wire `W(`CTL_BUSLEN) in_ctl_bus,

  output reg `W(`DLEN)       out_pc,
  output reg `W(`RLEN)       out_rs1,
  output reg `W(`RLEN)       out_rs2,
  output reg `W(`RLEN)       out_rd,
  output reg `W(`DLEN)       out_regdata1,
  output reg `W(`DLEN)       out_csr_data,
  output reg `W(`DLEN)       out_regdata2,
  output reg `W(`DLEN)       out_imm,
  output reg `W(`ALU_OPLEN)  out_alu_op,
  output reg `W(`CTL_BUSLEN) out_ctl_bus
);
  /* verilator lint_off WIDTHTRUNC */
  always @(posedge clk) begin
    if(rst || (nopi & `NOPI_ID_EX)) begin
      out_pc <= `RSTPC;
      out_rs1 <= 0;
      out_rs2 <= 0;
      out_rd <= 0;
      out_regdata1 <= 0;
      out_regdata2 <= 0;
      out_imm <= 0;
      out_alu_op <= 0;
      out_ctl_bus <= 0;
      out_csr_data <= 0;
    end
    else if (!(stall & `STALL_ID_EX)) begin
      out_pc <= in_pc;
      out_rs1 <= in_rs1;
      out_rs2 <= in_rs2;
      out_rd <= in_rd;
      out_regdata1 <= in_regdata1;
      out_regdata2 <= in_regdata2;
      out_imm <= in_imm;
      out_alu_op <= in_alu_op;
      out_ctl_bus <= in_ctl_bus;
      out_csr_data <= in_csr_data ;
    end
  end
  /* verilator lint_on WIDTHTRUNC */
endmodule
