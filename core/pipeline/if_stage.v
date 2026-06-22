`include "defs.vh"
`include "modules/bpt.v"

// memory lies outside this stage
module if_stage (
  input wire hard_stall,

  input wire `W(`STLEN)   stall,
  input wire `W(`NOPILEN) nopi,

  input wire clk,
  input wire rst,
  input wire `W(`ILEN) instr,
  output reg `W(`DLEN) pc,

  input wire __id_branch_taken,
  input wire __wb_trap_taken,
  input wire `W(`DLEN) __id_next_pc,
  input wire `W(`DLEN) __wb_next_pc,

  // branch prediction
  input wire                 __id_valid,
  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`CTL_BUSLEN) __id_ctl_bus,
  /* verilator lint_on UNUSEDSIGNAL */
  input wire `W(`DLEN)       __id_pc,
  input wire `W(`DLEN)       __id_predicted_pc,
  output wire `W(`DLEN)      predicted_pc,
  output wire                bpt_mispredict
);
  wire `W(`BRLEN) __id_branch = `BR(__id_ctl_bus);

  bpt bpt_instance (
    .clk(clk),
    .rst(rst),
    .hard_stall(hard_stall),
    .stall(stall),
    .instr(instr),
    .pc(pc),
    .__id_pc(__id_pc),
    .__id_branch_taken(__id_branch_taken),
    .__id_branch(__id_branch),
    .predicted_pc(predicted_pc)
  );

  wire `W(`DLEN) __id_actual_next_pc = __id_branch_taken ? __id_next_pc: (__id_pc + 4);

  assign bpt_mispredict = __id_valid && (__id_actual_next_pc != __id_predicted_pc);

  /* verilator lint_off WIDTHTRUNC */
  always @(posedge clk) begin
    if(!hard_stall) begin
      if(rst || (nopi & `NOPI_PC)) pc <= `RSTPC;
      else if(__wb_trap_taken) pc <= __wb_next_pc;
      else if(!(stall & `STALL_PC)) begin
        if(bpt_mispredict) pc <= __id_actual_next_pc;
        else pc <= predicted_pc;
      end
    end
  end
  /* verilator lint_on WIDTHTRUNC */
endmodule
