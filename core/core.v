`include "defs.vh"
`include "pipeline/if_stage.v"
`include "pipeline/if_id_reg.v"
`include "pipeline/id_stage.v"
`include "pipeline/id_ex_reg.v"
`include "pipeline/ex_stage.v"
`include "pipeline/ex_mem_reg.v"
`include "pipeline/mem_wb_reg.v"
`include "pipeline/wb_stage.v"

module core (
  input wire clk,
  input wire rst
);
  wor stall;

  wire `W(`DLEN)       __if_pc;
  wire `W(`ILEN)       __if_instr;

  wire `W(`DLEN)       __id_pc;
  wire `W(`ILEN)       __id_instr;
  wire `W(`RLEN)       __id_rs1;
  wire `W(`RLEN)       __id_rs2;
  wire `W(`RLEN)       __id_rd;
  wire `W(`DLEN)       __id_regdata1;
  wire `W(`DLEN)       __id_regdata2;
  wire `W(`DLEN)       __id_imm;
  wire `W(`ALU_OPLEN)  __id_alu_op;
  wire `W(`CTL_BUSLEN) __id_ctl_bus;

  wire `W(`DLEN)       __ex_pc;
  wire `W(`RLEN)       __ex_rs1;
  wire `W(`RLEN)       __ex_rs2;
  wire `W(`RLEN)       __ex_rd;
  wire `W(`DLEN)       __ex_regdata1;
  wire `W(`DLEN)       __ex_regdata2;
  wire `W(`DLEN)       __ex_imm;
  wire `W(`ALU_OPLEN)  __ex_alu_op;
  wire `W(`CTL_BUSLEN) __ex_ctl_bus;
  wire `W(`DLEN)       __ex_alu_res;
  wire `W(`DLEN)       __ex_mem_data;

  wire `W(`DLEN)       __mem_pc;
  wire `W(`RLEN)       __mem_rs1;
  wire `W(`RLEN)       __mem_rs2;
  wire `W(`RLEN)       __mem_rd;
  wire `W(`DLEN)       __mem_imm;
  wire `W(`DLEN)       __mem_alu_res;
  wire `W(`DLEN)       __mem_mem_data;
  wire `W(`CTL_BUSLEN) __mem_ctl_bus;
  wire `W(`DLEN)       __mem_mem_res;
  wire `W(`DLEN)       __mem_regw_data;

  wire `W(`RLEN)       __wb_rd;
  wire `W(`DLEN)       __wb_regw_data;
  wire `W(`DLEN)       __wb_mem_res;
  wire `W(`CTL_BUSLEN) __wb_ctl_bus;
  wire `W(`DLEN)       __wb_write_data;

  `ifdef SIM

  mem mem_instance (
    .clk(clk),

    // port a for instr fetch
    .addr_a(__if_pc[0 +: `ADDRLEN]),
    .mem_read_a(1),
    .mem_write_a(0),
    .sign_extend_a(0),
    .bw_a(`BW_WORD),
    .data_in_a(0),
    .data_out_a(__if_instr),

    // port b for mem stage access
    .addr_b(__mem_alu_res[0 +: `ADDRLEN]),
    .mem_read_b(MEM_READ(__mem_ctl_bus)),
    .mem_write_b(MEM_WRITE(__mem_ctl_bus)),
    .sign_extend_b(SIGN_EXTEND(__mem_ctl_bus)),
    .bw_b(BW(__mem_ctl_bus)),
    .data_in_b(__mem_mem_data),
    .data_out_b(__mem_mem_res),
  );

  `endif

  /* ----- IF STAGE ------ */
  if_stage if_stage_instance (
    .stall(stall),
    .clk(clk),
    .rst(rst),
    .pc(__if_pc)
  );
  /* -------------------- */

  if_id_reg if_id_reg_instance (
    .stall(stall),
    .clk(clk),
    .rst(rst),
    .in_pc(__if_pc),
    .in_instr(__if_instr),

    .out_pc(__id_pc),
    .out_instr(__id_instr)
  );

  /* ----- ID STAGE ------ */
  id_stage id_stage_instance (
    .stall(stall),
    .clk(clk),
    .rst(rst),
    .instr(__id_instr),
    .rs1(__id_rs1),
    .rs2(__id_rs2),
    .rd(__id_rd),
    .regdata1(__id_regdata1),
    .regdata2(__id_regdata2),
    .imm(__id_imm),
    .alu_op(__id_alu_op),
    .ctl_bus(__id_ctl_bus),
    .__wb_rd(__wb_rd),
    .__wb_write_data(__wb_write_data),
    .__wb_reg_write(REG_WRITE(__wb_ctl_bus))
  );
  /* -------------------- */

  id_ex_reg id_ex_reg_instance (
    .stall(stall),
    .clk(clk),
    .rst(rst),
    .in_pc(__id_pc),
    .in_rs1(__id_rs1),
    .in_rs2(__id_rs2),
    .in_rd(__id_rd),
    .in_regdata1(__id_regdata1),
    .in_regdata2(__id_regdata2),
    .in_imm(__id_imm),
    .in_alu_op(__id_alu_op),
    .in_ctl_bus(__id_ctl_bus),

    .out_pc(__ex_pc),
    .out_rs1(__ex_rs1),
    .out_rs2(__ex_rs2),
    .out_rd(__ex_rd),
    .out_regdata1(__ex_regdata1),
    .out_regdata2(__ex_regdata2),
    .out_imm(__ex_imm),
    .out_alu_op(__ex_alu_op),
    .out_ctl_bus(__ex_ctl_bus)
  );

  /* ----- EX STAGE ------ */
  ex_stage ex_stage_instance (
    .stall(stall),
    .clk(clk),
    .rst(rst),

    .regdata1(__ex_regdata1),
    .regdata2(__ex_regdata2),
    .imm(__ex_imm),
    .mem_data(__ex_mem_data),
    .alu_op(__ex_alu_op),
    .ctl_bus(__ex_ctl_bus),
    .alu_res(__ex_alu_res)
  );
  /* -------------------- */

  ex_mem_reg ex_mem_reg_instance (
    .stall(stall),
    .clk(clk),
    .rst(rst),
    .in_pc(__ex_pc),
    .in_rs1(__ex_rs1),
    .in_rs2(__ex_rs2),
    .in_rd(__ex_rd),
    .in_imm(__ex_imm),
    .in_alu_res(__ex_alu_res),
    .in_mem_data(__ex_mem_data),
    .in_ctl_bus(__ex_ctl_bus),

    .out_pc(__mem_pc),
    .out_rs1(__mem_rs1),
    .out_rs2(__mem_rs2),
    .out_rd(__mem_rd),
    .out_imm(__mem_imm),
    .out_alu_res(__mem_alu_res),
    .out_mem_data(__mem_mem_data),
    .out_ctl_bus(__mem_ctl_bus),
  );

  /* ----- MEM STAGE ------ */
  // TODO!
  /* -------------------- */

  mem_wb_reg mem_wb_reg_instance (
    .stall(stall),
    .clk(clk),
    .rst(rst),
    .in_rd(__mem_rd),
    .in_mem_res(__mem_mem_res),
    .in_regw_data(__mem_regw_data),
    .in_ctl_bus(__mem_ctl_bus),

    .out_rd(__wb_rd),
    .out_mem_res(__wb_mem_res),
    .out_regw_data(__wb_regw_data),
    .out_ctl_bus(__wb_ctl_bus)
  );

  /* ----- WB STAGE ------ */
  wb_stage wb_stage_instance (
    .stall(stall),
    .regw_data(__wb_regw_data),
    .ctl_bus(__wb_ctl_bus),
    .wb_write_data(__wb_write_data)
  );
  /* -------------------- */
endmodule
