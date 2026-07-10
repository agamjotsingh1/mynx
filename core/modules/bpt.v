`include "defs.vh"

// branch predictor table
// correlating branch prediction
module bpt (
  input wire clk,
  input wire rst,
  input wire hard_stall,
  input wire `W(`STLEN) stall,
  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`ILEN)  instr,
  /* verilator lint_on UNUSEDSIGNAL */
  input wire `W(`DLEN)  pc,
  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`DLEN)  __id_pc,
  /* verilator lint_on UNUSEDSIGNAL */
  input wire `W(`BRLEN) __id_branch,
  input wire            __id_branch_taken,

  /* verilator lint_off UNUSEDSIGNAL */
  output wire `W(`DLEN) predicted_pc
  /* verilator lint_on UNUSEDSIGNAL */
);
  reg `W(`LHT_ELEN) lht [0:`LHT_DEPTH-1];
  reg `W(`LPT_ELEN) lpt [0:`LPT_DEPTH-1];

  // predict the pc if instruction is branch
  wire is_branch = (instr`OSLICE == `OP_B);
  wire is_jal    = (instr`OSLICE == `OP_J);
  /* verilator lint_off WIDTHEXPAND */
  wire `W(`DLEN) imm = is_branch
  ? $signed({instr[31], instr[7], instr[30:25], instr[11:8], 1'b0})
  : (is_jal ? $signed({instr[31], instr[19:12], instr[20], instr[30:21], 1'b0}) : 0);
  /* verilator lint_on WIDTHEXPAND */

  /* verilator lint_off UNUSEDSIGNAL */
  wire `W(`LPT_ELEN) predicted_state = lpt[lht[`LHT_INDEX(pc)]];
  /* verilator lint_on UNUSEDSIGNAL */

  assign predicted_pc = pc + ((`TAKEN(predicted_state) && is_branch) || is_jal ? imm: 4);

  integer i;
  always @(posedge clk) begin
    if(rst) begin
      for(i = 0; i < `LHT_DEPTH; i = i + 1) lht[i] <= 0;
      for(i = 0; i < `LPT_DEPTH; i = i + 1) lpt[i] <= 0;
    end
    /* verilator lint_off WIDTHTRUNC */
    else if(__id_branch != `BR_NONE && !(stall & `STALL_IF_ID) && (!hard_stall)) begin
    /* verilator lint_on WIDTHTRUNC */
      // shift the actual branch taken into the lht
      lht[`LHT_INDEX(__id_pc)] <= {__id_branch_taken, lht[`LHT_INDEX(__id_pc)][`LHT_ELEN-1:1]};

      // update the lpt with the result of branch prediction
      if(!__id_branch_taken) begin
        if(lpt[lht[`LHT_INDEX(__id_pc)]] != `STATE_BOTTOM)
          lpt[lht[`LHT_INDEX(__id_pc)]] <= lpt[lht[`LHT_INDEX(__id_pc)]] - 1;
      end
      else begin
        if(lpt[lht[`LHT_INDEX(__id_pc)]] != `STATE_TOP)
          lpt[lht[`LHT_INDEX(__id_pc)]] <= lpt[lht[`LHT_INDEX(__id_pc)]] + 1;
      end
    end
  end
endmodule
