`include "defs.vh"

module core (
  input wire clk,
  input wire rst,

  // AMC exposed ports
  output wire  `W(`ADDRLEN)  __amc_addr_a,
  output wire                __amc_mem_read_a,
  output wire                __amc_mem_write_a,
  output wire  `W(`DLEN)     __amc_data_in_a,
  input  wire `W($clog2(`AXI_AWLEN)) __amc_data_in_index_a,
  input  wire               __amc_data_in_last_a,
  input  wire               __amc_data_in_valid_a,
  input  wire `W(`DLEN)     __amc_data_out_a,
  input  wire `W($clog2(`AXI_AWLEN)) __amc_data_out_index_a,
  input  wire               __amc_data_out_valid_a,
  input  wire               __amc_data_out_last_a,
  input  wire               __amc_busy_a,
  input  wire               __amc_err_a,

  output wire  `W(`ADDRLEN)  __amc_addr_b,
  output wire                __amc_mem_read_b,
  output wire                __amc_mem_write_b,
  output wire  `W(`DLEN)     __amc_data_in_b,
  input  wire `W($clog2(`AXI_AWLEN)) __amc_data_in_index_b,
  input  wire               __amc_data_in_last_b,
  input  wire               __amc_data_in_valid_b,
  input  wire `W(`DLEN)     __amc_data_out_b,
  input  wire `W($clog2(`AXI_AWLEN)) __amc_data_out_index_b,
  input  wire               __amc_data_out_valid_b,
  input  wire               __amc_data_out_last_b,
  input  wire               __amc_busy_b,
  input  wire               __amc_err_b,

  // ASDC exposed ports
  output wire __asdc_read_en,
  output wire __asdc_write_en,
  output wire  `W(`ASDC_ADDRLEN)  __asdc_addr,
  output wire  `W(`ASDC_DATALEN)  __asdc_data_in,
  input  wire  `W(`ASDC_DATALEN)  __asdc_data_out,
  input  wire  __asdc_data_out_valid,
  input  wire  __asdc_busy,
  input  wire  __asdc_err,

  // tx, goes to disp driver
  output wire           tx_valid,
  input  wire           tx_ready,
  output wire `W(`BYTE) tx_data,

  `ifdef __SYNTH___
  output wire ext_spi_clk,
  `endif

  input wire           rx_valid,
  input wire `W(`BYTE) rx_data
);
  reg  `W(`PRIVLEN) priv;
  wire `W(`PRIVLEN) next_priv;

  wire hard_stall; // stall the entire pipeline

  `ifdef __SYNTH__
  wire slow_sel;
  `endif

  wire `W(`STLEN)        trap_stall;
  wire `W(`STLEN)        hazard_stall;
  wire `W(`STLEN)        stall = trap_stall | hazard_stall;

  wire `W(`NOPILEN)      trap_nopi;
  wire `W(`NOPILEN)      hazard_nopi;
  wire `W(`NOPILEN)      nopi = trap_nopi | hazard_nopi;

  wire `W(`DLEN)        satp;

  wire                  __if_valid = 1;
  wire `W(`DLEN)        __if_pc /* verilator public*/;
  wire `W(`ILEN)        __if_instr;
  wire `W(`DLEN)        __if_xcep = 0;
  wire `W(`DLEN)        __if_uxcep;
  wire `W(`DLEN)        __if_predicted_pc;
  wire                  __if_bpt_mispredict;

  wire                  __id_valid;
  wire `W(`DLEN)        __id_pc;
  wire `W(`DLEN)        __id_anchor_pc;
  wire `W(`DLEN)        __id_xcep;
  wire `W(`DLEN)        __id_uxcep;
  wire `W(`ILEN)        __id_instr;
  wire `W(`RLEN)        __id_rs1;
  wire `W(`RLEN)        __id_rs2;
  wire `W(`RLEN)        __id_rd;
  wire `W(`DLEN)        __id_regdata1;
  wire `W(`DLEN)        __id_regdata2;
  wire `W(`CSRLEN)      __id_csr;
  wire `W(`DLEN)        __id_csrdata;
  wire `W(`DLEN)        __id_imm;
  wire `W(`ALU_OPLEN)   __id_alu_op;
  wire `W(`CTL_BUSLEN)  __id_ctl_bus;
  wire                  __id_branch_taken;
  wire `W(`DLEN)        __id_next_pc;
  wire `W(`FWDLEN)      __id_fwd1;
  wire `W(`FWDLEN)      __id_fwd2;
  wire `W(`DLEN)        __id_mip;
  wire `W(`DLEN)        __id_mstatus;
  wire `W(`DLEN)        __id_mie;
  wire `W(`DLEN)        __id_vec;
  wire `W(`DLEN)        __id_epc;
  wire `W(`DLEN)        __id_mideleg;
  wire `W(`DLEN)        __id_medeleg;
  wire `W(`DLEN)        __id_predicted_pc;
  wire `W(`FWDLEN)      __id_fwdcsr;

  wire                  __ex_valid;
  wire `W(`DLEN)        __ex_pc;
  wire `W(`DLEN)        __ex_anchor_pc;
  wire `W(`DLEN)        __ex_xcep;
  wire `W(`DLEN)        __ex_uxcep;
  wire `W(`RLEN)        __ex_rs1;
  wire `W(`RLEN)        __ex_rs2;
  wire `W(`RLEN)        __ex_rd;
  wire `W(`DLEN)        __ex_regdata1;
  wire `W(`DLEN)        __ex_regdata2;
  wire `W(`CSRLEN)      __ex_csr;
  wire `W(`DLEN)        __ex_csrdata;
  wire `W(`DLEN)        __ex_imm;
  wire `W(`ALU_OPLEN)   __ex_alu_op;
  wire `W(`CTL_BUSLEN)  __ex_ctl_bus;
  wire `W(`DLEN)        __ex_ex_res;
  wire `W(`DLEN)        __ex_mem_data;
  wire `W(`DLEN)        __ex_csr_write_data;
  wire `W(`FWDLEN)      __ex_fwd1;
  wire `W(`FWDLEN)      __ex_fwd2;
  wire `W(`FWDLEN)      __ex_fwdcsr;

  wire                  __mem_valid;
  wire `W(`DLEN)        __mem_pc;
  wire `W(`DLEN)        __mem_anchor_pc;
  wire `W(`DLEN)        __mem_xcep;
  wire `W(`DLEN)        __mem_uxcep;
  wire `W(`RLEN)        __mem_rd;
  wire `W(`CSRLEN)      __mem_csr;
  wire `W(`DLEN)        __mem_ex_res;
  wire `W(`DLEN)        __mem_csr_write_data;
  wire `W(`DLEN)        __mem_mem_data;
  wire `W(`CTL_BUSLEN)  __mem_ctl_bus;
  wire `W(`DLEN)        __mem_mem_res;
  wire `W(`DLEN)        __mem_regw_data;
  wire                  __mem_ext_irq;
  wire                  __mem_timer_irq;

  wire                  __wb_valid;
  wire `W(`DLEN)        __wb_pc;
  wire `W(`DLEN)        __wb_anchor_pc;
  wire `W(`DLEN)        __wb_next_pc;
  wire `W(`DLEN)        __wb_xcep;
  wire `W(`RLEN)        __wb_rd;
  wire `W(`CSRLEN)      __wb_csr;
  wire `W(`DLEN)        __wb_regw_data;
  wire `W(`DLEN)        __wb_mem_res;
  wire `W(`DLEN)        __wb_csr_write_data;
  wire `W(`CTL_BUSLEN)  __wb_ctl_bus;
  wire `W(`DLEN)        __wb_write_data;
  wire `W(`TRAPMODELEN) __wb_trap_mode;
  wire                  __wb_trap_taken;
  wire `W(`DLEN)        __wb_write_mstatus;
  wire `W(`DLEN)        __wb_write_cause;
  wire `W(`DLEN)        __wb_write_epc;

  wire tlb_flush = `SFENCEVMA(__id_ctl_bus);
  wire cache_flush = `FENCE(__id_ctl_bus) &&
    !(__ex_valid || __mem_valid || __wb_valid);

  always @(posedge clk) begin
    if(rst) priv <= `PRIVM;
    else if(__wb_trap_taken && (!hard_stall)) priv <= next_priv;
  end

  /* verilator lint_off UNUSEDSIGNAL */
  wire `W(`DLEN) __mem_instr_addr = __if_pc;
  wire `W(`DLEN) __mem_data_addr = __mem_ex_res;
  /* verilator lint_on UNUSEDSIGNAL */

  mmu mmu_instance (
    .clk(clk),
    .rst(rst),
    .hard_stall(hard_stall),
    `ifdef __SYNTH__
    .slow_sel(slow_sel),
    `endif
    .tlb_flush(tlb_flush),
    .cache_flush(cache_flush),
    .priv(priv),
    .satp(satp),
    .xcep_a(__if_xcep),
    .uxcep_a(__if_uxcep),
    .xcep_b(__mem_xcep),
    .uxcep_b(__mem_uxcep),
    .__wb_trap_mode(__wb_trap_mode),

    .ext_irq(__mem_ext_irq),
    .timer_irq(__mem_timer_irq),

    .rx_valid(rx_valid),
    .rx_data(rx_data),

    // AMC port A
    .__amc_addr_a(__amc_addr_a),
    .__amc_mem_read_a(__amc_mem_read_a),
    .__amc_mem_write_a(__amc_mem_write_a),
    .__amc_data_in_a(__amc_data_in_a),
    .__amc_data_in_index_a(__amc_data_in_index_a),
    .__amc_data_in_last_a(__amc_data_in_last_a),
    .__amc_data_in_valid_a(__amc_data_in_valid_a),
    .__amc_data_out_a(__amc_data_out_a),
    .__amc_data_out_index_a(__amc_data_out_index_a),
    .__amc_data_out_valid_a(__amc_data_out_valid_a),
    .__amc_data_out_last_a(__amc_data_out_last_a),
    .__amc_busy_a(__amc_busy_a),
    .__amc_err_a(__amc_err_a),

    // AMC port B
    .__amc_addr_b(__amc_addr_b),
    .__amc_mem_read_b(__amc_mem_read_b),
    .__amc_mem_write_b(__amc_mem_write_b),
    .__amc_data_in_b(__amc_data_in_b),
    .__amc_data_in_index_b(__amc_data_in_index_b),
    .__amc_data_in_last_b(__amc_data_in_last_b),
    .__amc_data_in_valid_b(__amc_data_in_valid_b),
    .__amc_data_out_b(__amc_data_out_b),
    .__amc_data_out_index_b(__amc_data_out_index_b),
    .__amc_data_out_valid_b(__amc_data_out_valid_b),
    .__amc_data_out_last_b(__amc_data_out_last_b),
    .__amc_busy_b(__amc_busy_b),
    .__amc_err_b(__amc_err_b),

    // ASDC port
    .__asdc_read_en(__asdc_read_en),
    .__asdc_write_en(__asdc_write_en),
    .__asdc_addr(__asdc_addr),
    .__asdc_data_in(__asdc_data_in),
    .__asdc_data_out(__asdc_data_out),
    .__asdc_data_out_valid(__asdc_data_out_valid),
    .__asdc_busy(__asdc_busy),
    .__asdc_err(__asdc_err),

    .tx_valid(tx_valid),
    .tx_ready(tx_ready),
    .tx_data(tx_data),

    // port a for instr fetch
    .addr_a(__mem_instr_addr),
    .mem_read_a(1),
    .mem_write_a(0),
    .sign_extend_a(0),
    .bw_a(`BW_WORD),
    .data_in_a(0),

    /* verilator lint_off WIDTHEXPAND */
    .data_out_a(__if_instr),
    /* verilator lint_on WIDTHEXPAND */

    // port b for mem stage access
    .addr_b(__mem_data_addr),
    .mem_read_b(`MEM_READ(__mem_ctl_bus)),
    .mem_write_b(`MEM_WRITE(__mem_ctl_bus)),
    .sign_extend_b(`SIGN_EXTEND(__mem_ctl_bus)),
    .bw_b(`BW(__mem_ctl_bus)),
    .data_in_b(__mem_mem_data),
    .data_out_b(__mem_mem_res)
  );

  /* ----- IF STAGE ------ */
  if_stage if_stage_instance (
    .hard_stall(hard_stall),
    .stall(stall),
    .nopi(nopi),
    .clk(clk),
    .rst(rst),
    .pc(__if_pc),
    .instr(__if_instr),
    .__id_valid(__id_valid),
    .__id_predicted_pc(__id_predicted_pc),
    .__id_branch_taken(__id_branch_taken),
    .__wb_trap_taken(__wb_trap_taken),
    .__id_next_pc(__id_next_pc),
    .__wb_next_pc(__wb_next_pc),
    .__id_ctl_bus(__id_ctl_bus),
    .__id_pc(__id_pc),
    .predicted_pc(__if_predicted_pc),
    .bpt_mispredict(__if_bpt_mispredict)
  );
  /* -------------------- */

  if_id_reg if_id_reg_instance (
    .hard_stall(hard_stall),
    .stall(stall),
    .nopi(nopi),
    .clk(clk),
    .rst(rst),
    .in_valid(__if_valid),
    .in_pc(__if_pc),
    .in_instr(__if_instr),
    .in_xcep(__if_uxcep),
    .in_predicted_pc(__if_predicted_pc),

    .out_valid(__id_valid),
    .out_pc(__id_pc),
    .out_instr(__id_instr),
    .out_xcep(__id_xcep),
    .out_predicted_pc(__id_predicted_pc)
  );

  /* ----- ID STAGE ------ */
  id_stage id_stage_instance (
    .clk(clk),
    .rst(rst),
    .stall(stall),
    .priv(priv),
    .hard_stall(hard_stall),
    .pc(__id_pc),
    .anchor_pc(__id_anchor_pc),
    .instr(__id_instr),
    .rs1(__id_rs1),
    .rs2(__id_rs2),
    .rd(__id_rd),
    .regdata1(__id_regdata1),
    .regdata2(__id_regdata2),
    .csr(__id_csr),
    .csrdata(__id_csrdata),
    .satp(satp),
    .imm(__id_imm),
    .alu_op(__id_alu_op),
    .ctl_bus(__id_ctl_bus),
    .branch_taken(__id_branch_taken),
    .next_pc(__id_next_pc),
    .__wb_rd(__wb_rd),
    .__wb_csr(__wb_csr),
    .__wb_ctl_bus(__wb_ctl_bus),
    .__wb_csr_write_data(__wb_csr_write_data),
    .fwd1(__id_fwd1),
    .fwd2(__id_fwd2),
    .fwdcsr(__id_fwdcsr),
    .__mem_ex_res(__mem_ex_res),
    .__wb_write_data(__wb_write_data),
    .xcep(__id_xcep),
    .uxcep(__id_uxcep),

    // irq handling
    .__mem_ext_irq(__mem_ext_irq),
    .__mem_timer_irq(__mem_timer_irq),

    // instruction retire (minstret)
    .__wb_valid(__wb_valid),

    // trap handling
    .__wb_trap_mode(__wb_trap_mode),
    .mip(__id_mip),
    .mstatus(__id_mstatus),
    .mie(__id_mie),
    .vec(__id_vec),
    .epc(__id_epc),
    .mideleg(__id_mideleg),
    .medeleg(__id_medeleg),
    .__wb_write_mstatus(__wb_write_mstatus),
    .__wb_write_cause(__wb_write_cause),
    .__wb_write_epc(__wb_write_epc)
  );
  /* -------------------- */

  id_ex_reg id_ex_reg_instance (
    .hard_stall(hard_stall),
    .stall(stall),
    .nopi(nopi),
    .clk(clk),
    .rst(rst),
    .in_valid(__id_valid),
    .in_pc(__id_pc),
    .in_anchor_pc(__id_anchor_pc),
    .in_rs1(__id_rs1),
    .in_rs2(__id_rs2),
    .in_rd(__id_rd),
    .in_regdata1(__id_regdata1),
    .in_regdata2(__id_regdata2),
    .in_csr(__id_csr),
    .in_csrdata(__id_csrdata),
    .in_imm(__id_imm),
    .in_alu_op(__id_alu_op),
    .in_ctl_bus(__id_ctl_bus),
    .in_xcep(__id_uxcep),

    .out_valid(__ex_valid),
    .out_pc(__ex_pc),
    .out_anchor_pc(__ex_anchor_pc),
    .out_rs1(__ex_rs1),
    .out_rs2(__ex_rs2),
    .out_rd(__ex_rd),
    .out_regdata1(__ex_regdata1),
    .out_regdata2(__ex_regdata2),
    .out_csr(__ex_csr),
    .out_csrdata(__ex_csrdata),
    .out_imm(__ex_imm),
    .out_alu_op(__ex_alu_op),
    .out_ctl_bus(__ex_ctl_bus),
    .out_xcep(__ex_xcep)
  );

  /* ----- EX STAGE ------ */
  ex_stage ex_stage_instance (
    .pc(__ex_pc),
    .csr(__ex_csr),
    .regdata1(__ex_regdata1),
    .regdata2(__ex_regdata2),
    .csrdata(__ex_csrdata),
    .imm(__ex_imm),
    .mem_data(__ex_mem_data),
    .alu_op(__ex_alu_op),
    .ctl_bus(__ex_ctl_bus),
    .ex_res(__ex_ex_res),
    .csr_write_data(__ex_csr_write_data),
    .xcep(__ex_xcep),
    .uxcep(__ex_uxcep),

    .fwd1(__ex_fwd1),
    .fwd2(__ex_fwd2),
    .fwdcsr(__ex_fwdcsr),
    .__mem_ex_res(__mem_ex_res),
    .__wb_write_data(__wb_write_data),
    .__mem_csr_write_data(__mem_csr_write_data),
    .__wb_csr_write_data(__wb_csr_write_data)
  );
  /* -------------------- */

  ex_mem_reg ex_mem_reg_instance (
    .hard_stall(hard_stall),
    .stall(stall),
    .nopi(nopi),
    .clk(clk),
    .rst(rst),
    .in_valid(__ex_valid),
    .in_pc(__ex_pc),
    .in_anchor_pc(__ex_anchor_pc),
    .in_rd(__ex_rd),
    .in_csr(__ex_csr),
    .in_ex_res(__ex_ex_res),
    .in_csr_write_data(__ex_csr_write_data),
    .in_mem_data(__ex_mem_data),
    .in_ctl_bus(__ex_ctl_bus),
    .in_xcep(__ex_uxcep),

    .out_valid(__mem_valid),
    .out_pc(__mem_pc),
    .out_anchor_pc(__mem_anchor_pc),
    .out_rd(__mem_rd),
    .out_csr(__mem_csr),
    .out_ex_res(__mem_ex_res),
    .out_mem_data(__mem_mem_data),
    .out_csr_write_data(__mem_csr_write_data),
    .out_ctl_bus(__mem_ctl_bus),
    .out_xcep(__mem_xcep)
  );

  /* ----- MEM STAGE ------ */
  assign __mem_regw_data = __mem_ex_res;
  // goes through mmu
  // assign __mem_uxcep = __mem_xcep; 
  /* -------------------- */

  mem_wb_reg mem_wb_reg_instance (
    .hard_stall(hard_stall),
    .stall(stall),
    .nopi(nopi),
    .clk(clk),
    .rst(rst),
    .in_valid(__mem_valid),
    .in_pc(__mem_pc),
    .in_anchor_pc(__mem_anchor_pc),
    .in_rd(__mem_rd),
    .in_csr(__mem_csr),
    .in_mem_res(__mem_mem_res),
    .in_regw_data(__mem_regw_data),
    .in_csr_write_data(__mem_csr_write_data),
    .in_ctl_bus(__mem_ctl_bus),
    .in_xcep(__mem_uxcep),

    .out_valid(__wb_valid),
    .out_pc(__wb_pc),
    .out_anchor_pc(__wb_anchor_pc),
    .out_rd(__wb_rd),
    .out_csr(__wb_csr),
    .out_mem_res(__wb_mem_res),
    .out_regw_data(__wb_regw_data),
    .out_csr_write_data(__wb_csr_write_data),
    .out_ctl_bus(__wb_ctl_bus),
    .out_xcep(__wb_xcep)
  );

  /* ----- WB STAGE ------ */
  wb_stage wb_stage_instance (
    .clk(clk),
    .rst(rst),
    .stall(trap_stall),
    .hard_stall(hard_stall),
    .regw_data(__wb_regw_data),
    .mem_res(__wb_mem_res),
    .ctl_bus(__wb_ctl_bus),
    .write_data(__wb_write_data),
    .__mem_ctl_bus(__mem_ctl_bus),
    .__mem_valid(__mem_valid),

    // trap handling
    .valid(__wb_valid),
    .pc(__wb_pc),
    .anchor_pc(__wb_anchor_pc),
    .priv(priv),
    .xcep(__wb_xcep),
    .nopi(trap_nopi),
    .trap_taken(__wb_trap_taken),
    .next_pc(__wb_next_pc),
    .next_priv(next_priv),
    .trap_mode(__wb_trap_mode),
    .mip(__id_mip),
    .mstatus(__id_mstatus),
    .mie(__id_mie),
    .vec(__id_vec),
    .epc(__id_epc),
    .mideleg(__id_mideleg),
    .medeleg(__id_medeleg),
    .write_mstatus(__wb_write_mstatus),
    .write_cause(__wb_write_cause),
    .write_epc(__wb_write_epc)
  );
  /* -------------------- */

  /* ----- FWD UNIT ------ */
  fwd_unit fwd_unit_instance (
    .__id_rs1(__id_rs1),
    .__id_rs2(__id_rs2),
    .__ex_rs1(__ex_rs1),
    .__ex_rs2(__ex_rs2),
    .__id_csr(__id_csr),
    .__ex_csr(__ex_csr),
    .__mem_rd(__mem_rd),
    .__mem_csr(__mem_csr),
    .__mem_ctl_bus(__mem_ctl_bus),
    .__wb_rd(__wb_rd),
    .__wb_csr(__wb_csr),
    .__wb_ctl_bus(__wb_ctl_bus),
    .__id_fwd1(__id_fwd1),
    .__id_fwd2(__id_fwd2),
    .__ex_fwd1(__ex_fwd1),
    .__ex_fwd2(__ex_fwd2),
    .__id_fwdcsr(__id_fwdcsr),
    .__ex_fwdcsr(__ex_fwdcsr)
  );
  /* -------------------- */

  /* ----- HAZARD DETECTION UNIT ------ */
  hdu hdu_instance (
    .stall(hazard_stall),
    .nopi(hazard_nopi),
    .__ex_valid(__ex_valid),
    .__mem_valid(__mem_valid),
    .__wb_valid(__wb_valid),
    .__id_rs1(__id_rs1),
    .__id_rs2(__id_rs2),
    .__if_bpt_mispredict(__if_bpt_mispredict),
    .__id_ctl_bus(__id_ctl_bus),
    .__ex_rd(__ex_rd),
    .__ex_ctl_bus(__ex_ctl_bus),
    .__mem_rd(__mem_rd),
    .__mem_ctl_bus(__mem_ctl_bus),
    .__wb_ctl_bus(__wb_ctl_bus)
  );
  /* ---------------------------------- */

  `ifdef __SYNTH___
  spi_clkmux spi_clkmux_instance (
    .clk(clk),
    .rst(rst),
    .slow_sel(slow_sel),
    .ext_spi_clk(ext_spi_clk)
  );
  `endif
endmodule
