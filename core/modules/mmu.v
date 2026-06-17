`include "defs.vh"
`include "modules/mem.v"

// SIMULATION ONLY
// true 2 port memory with pagetable
// a port -> instr fetch
// b port -> mem fetch

// TODO! add exception if sv39 not setup properly
// TODO! remove requirement for ports being assigned to isntr/memory
// TODO! conservatively we finish the walk for one port even though second port has aborted
module mmu (
  input wire clk,
  input wire rst,
  output wor hard_stall,
  input wire __wb_trap_taken,

  input wire  `W(`PRIVLEN)  priv,

  /* verilator lint_off UNUSEDSIGNAL */
  input wire  `W(`DLEN)     satp,
  input wire  `W(`DLEN)     xcep_a,
  output reg  `W(`DLEN)     uxcep_a,
  input wire  `W(`DLEN)     xcep_b,
  output reg  `W(`DLEN)     uxcep_b,
  /* verilator lint_on UNUSEDSIGNAL */

  // pmp handling
  input wire `W(`DLEN)      pmpaddr0,
  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`DLEN)      pmpcfg0,
  /* verilator lint_on UNUSEDSIGNAL */

  // Port A
  input wire  `W(`DLEN)     addr_a,
  input wire                mem_read_a,
  input wire                mem_write_a,
  input wire                sign_extend_a,
  input wire  `W(`BWLEN)    bw_a,
  input wire  `W(`DLEN)     data_in_a,
  output wire  `W(`DLEN)    data_out_a,

  // Port B
  input wire  `W(`DLEN)     addr_b,
  input wire                mem_read_b,
  input wire                mem_write_b,
  input wire                sign_extend_b,
  input wire  `W(`BWLEN)    bw_b,
  input wire  `W(`DLEN)     data_in_b,
  output wire  `W(`DLEN)    data_out_b
);
  wire ext_abort_a = `XCEP(xcep_a)  | __wb_trap_taken;
  wire ext_abort_b = `XCEP(xcep_b)  | __wb_trap_taken;
  wire mmu_abort_a = `XCEP(uxcep_a) | ext_abort_a;
  wire mmu_abort_b = `XCEP(uxcep_b) | ext_abort_b;

  /* verilator lint_off WIDTHTRUNC */
  // TODO! have seperate pbtl_en for a and b
  wire pgtbl_en_glbl = 
    (priv != `PRIVM) &&
    (`SATP_MODE(satp) == `SATP_MODE_SV39);
  /* verilator lint_on WIDTHTRUNC */

  wire pgtbl_en_a = (mem_read_a | mem_write_a) && pgtbl_en_glbl && (!ext_abort_a);
  wire pgtbl_en_b = (mem_read_b | mem_write_b) && pgtbl_en_glbl && (!ext_abort_b);
  wire walk_en    = (pgtbl_en_a | pgtbl_en_b); 

  // counter for lvl counting
  reg `W($clog2(`PGTBL_LVLS)) lvl;

  wire stall_req_a = pgtbl_en_a & (~mmu_abort_a) & (~pmp_fault_a);
  wire stall_req_b = pgtbl_en_b & (~mmu_abort_b) & (~pmp_fault_b);

  always @(posedge clk) begin
    if(rst || !(stall_req_a | stall_req_b)) begin
      lvl <= `PGTBL_LVLS;
    end
    else if(walk_en) begin
      lvl <= (lvl == 0) ? `PGTBL_LVLS: (lvl - 1);
    end
  end

  assign hard_stall = (stall_req_a | stall_req_b) && (lvl != 0);

  /* verilator lint_off UNUSEDSIGNAL */
  reg `W(`PTELEN) pte_a, pte_b;
  /* verilator lint_on UNUSEDSIGNAL */
  wire `W(`DLEN) phymem_data_out_a, phymem_data_out_b;

  wire `W(`PALEN) pte_addr_a = (lvl == `PGTBL_LVLS)
    ? {`SATP_PPN(satp), `VA2VPN(addr_a, lvl)}
    : `PTE2PA(pte_a, `VA2VPN(addr_a, lvl));

  wire `W(`PALEN) pte_addr_b = (lvl == `PGTBL_LVLS)
    ? {`SATP_PPN(satp), `VA2VPN(addr_b, lvl)}
    : `PTE2PA(pte_b, `VA2VPN(addr_b, lvl));

  always @(posedge clk) begin
    if(rst || mmu_abort_a || pmp_fault_a) 
      pte_a <= 0;
    else if(pgtbl_en_a) 
      pte_a <= phymem_data_out_a;
      
    if(rst || mmu_abort_b || pmp_fault_b) 
      pte_b <= 0;
    else if(pgtbl_en_b) 
      pte_b <= phymem_data_out_b;
  end

  always @(*) begin
    uxcep_a = 0;
    uxcep_b = 0;

    /* verilator lint_off WIDTHTRUNC */
    // a port -> instr fetch
    if(`XCEP(xcep_a)) 
      uxcep_a = xcep_a;
    else if (pgtbl_en_a && lvl < `PGTBL_LVLS) begin
      // invalid pte and write only pte are faults
      if(!(`PTEF(pte_a) & `PTEF_V) || (!(`PTEF(pte_a) & `PTEF_R) && (`PTEF(pte_a) & `PTEF_W)))
        uxcep_a = {1'b1, `XCEP_INST_PAGE_FAULT}; 
      else if(lvl == 0) begin
        if(!(`PTEF(pte_a) & `PTEF_X) || (!(`PTEF(pte_a) & `PTEF_U) && priv == `PRIVU))
          uxcep_a = {1'b1, `XCEP_INST_PAGE_FAULT};
      end
    end
    else if(pmp_fault_a)
      uxcep_a = {1'b1, pmp_xcep_cause_a};

    // b port -> mem fetch
    if(`XCEP(xcep_b)) 
      uxcep_b = xcep_b;
    else if (pgtbl_en_b && lvl < `PGTBL_LVLS) begin
      // invalid pte and write only pte are faults
      if(!(`PTEF(pte_b) & `PTEF_V) || (!(`PTEF(pte_b) & `PTEF_R) && (`PTEF(pte_b) & `PTEF_W)))
        uxcep_b = {1'b1, mem_write_b ? `XCEP_STORE_AMO_PAGE_FAULT : `XCEP_LOAD_PAGE_FAULT};

      else if(lvl == 0) begin
        if(
          (mem_read_b && !(`PTEF(pte_b) & `PTEF_R))    ||
          (mem_write_b && !(`PTEF(pte_b) & `PTEF_W))   ||
          (!(`PTEF(pte_b) & `PTEF_U) && priv == `PRIVU)
        ) uxcep_b = {1'b1, mem_write_b ? `XCEP_STORE_AMO_PAGE_FAULT : `XCEP_LOAD_PAGE_FAULT};
      end
    end
    else if(pmp_fault_b)
      uxcep_b = {1'b1, pmp_xcep_cause_b};
    /* verilator lint_on WIDTHTRUNC */
  end

  // Port A
  /* verilator lint_off WIDTHEXPAND */
  wire `W(`DLEN) phymem_addr_a = (!pgtbl_en_a) ? addr_a 
    :((lvl == 0) ? `PTE2PA(pte_a, `VA2OFF(addr_a)): pte_addr_a);
  /* verilator lint_on WIDTHEXPAND */

  wire phymem_raw_read_a = (!pgtbl_en_a) ? mem_read_a
    :((lvl == 0) ? mem_read_a: 1);

  wire phymem_raw_write_a = (!pgtbl_en_a) ? mem_write_a
    :((lvl == 0) ? mem_write_a: 0);

  wire phymem_read_a = phymem_raw_read_a & (~pmp_fault_a);
  wire phymem_write_a = phymem_raw_write_a & (~pmp_fault_a);

  wire `W(`BWLEN) phymem_bw_a = (!pgtbl_en_a) ? bw_a
    :((lvl == 0) ? bw_a: `BW_DBLWORD);

  // for pgtbl walk, sign extend, data in doesnt matter 
  wire phymem_sign_extend_a = sign_extend_a;
  wire `W(`DLEN) phymem_data_in_a = data_in_a;
  assign data_out_a = phymem_data_out_a;

  // Port B
  /* verilator lint_off WIDTHEXPAND */
  wire `W(`DLEN) phymem_addr_b = (!pgtbl_en_b) ? addr_b
    :((lvl == 0) ? `PTE2PA(pte_b, `VA2OFF(addr_b)): pte_addr_b);
  /* verilator lint_on WIDTHEXPAND */

  wire phymem_raw_read_b = (!pgtbl_en_b) ? mem_read_b
    :((lvl == 0) ? mem_read_b: 1);

  wire phymem_raw_write_b = (!pgtbl_en_b) ? mem_write_b
    :((lvl == 0) ? mem_write_b: 0);

  wire phymem_read_b = phymem_raw_read_b & (~pmp_fault_b);
  wire phymem_write_b = phymem_raw_write_b & (~pmp_fault_b);

  wire `W(`BWLEN) phymem_bw_b = (!pgtbl_en_b) ? bw_b
    :((lvl == 0) ? bw_b: `BW_DBLWORD);

  // for pgtbl walk, sign extend, data in doesnt matter 
  wire phymem_sign_extend_b = sign_extend_b;
  wire `W(`DLEN) phymem_data_in_b = data_in_b;
  assign data_out_b = phymem_data_out_b;

  /* --- PMP logic --- */
  wire `W(`DLEN) pmp_bound = pmpaddr0 << `PMPADDRSHIFT;
  wire pmp_enforce = (priv != `PRIVM) || `PMPCFG_L(pmpcfg0);
  reg pmp_fault_a, pmp_fault_b;
  reg `W(`XCEP_CAUSELEN) pmp_xcep_cause_a, pmp_xcep_cause_b;

  always @(*) begin
    pmp_fault_a = 0;
    pmp_fault_b = 0;
    pmp_xcep_cause_a = 0;
    pmp_xcep_cause_b = 0;

    if(pmp_enforce) begin
      if(phymem_addr_a < pmp_bound) begin
        // Address matches Entry 0, check specific permissions
        if (phymem_raw_read_a && !`PMPCFG_R(pmpcfg0)) begin
          pmp_xcep_cause_a = `XCEP_LOAD_ACCESS_FAULT;
          pmp_fault_a = 1;
        end
        if (phymem_raw_write_a && !`PMPCFG_W(pmpcfg0)) begin
          pmp_xcep_cause_a = `XCEP_STORE_AMO_ACCESS_FAULT;
          pmp_fault_a = 1'b1;
        end
        if (!`PMPCFG_X(pmpcfg0)) begin
          pmp_xcep_cause_a = `XCEP_INST_ACCESS_FAULT;
          pmp_fault_a = 1'b1;
        end
      end else begin
        pmp_fault_a = 1'b1; 
      end

      if(phymem_addr_b < pmp_bound) begin
        // Address matches Entry 0, check specific permissions
        if (phymem_raw_read_b && !`PMPCFG_R(pmpcfg0)) begin
          pmp_xcep_cause_b = `XCEP_LOAD_ACCESS_FAULT;
          pmp_fault_b = 1;
        end
        if (phymem_raw_write_b && !`PMPCFG_W(pmpcfg0)) begin
          pmp_xcep_cause_b = `XCEP_STORE_AMO_ACCESS_FAULT;
          pmp_fault_b = 1;
        end
      end else begin
        pmp_fault_b = 1;
      end
    end
  end
  /* ----------------- */

  mem mem_instance (
    .clk(clk),

    // port A
    /* verilator lint_off WIDTHTRUNC */
    .addr_a(phymem_addr_a - `MEMBASE),
    /* verilator lint_on WIDTHTRUNC */
    .mem_read_a(phymem_read_a),
    .mem_write_a(phymem_write_a),
    .sign_extend_a(phymem_sign_extend_a),
    .bw_a(phymem_bw_a),
    .data_in_a(phymem_data_in_a),
    .data_out_a(phymem_data_out_a),

    // port B
    /* verilator lint_off WIDTHTRUNC */
    .addr_b(phymem_addr_b - `MEMBASE),
    /* verilator lint_on WIDTHTRUNC */
    .mem_read_b(phymem_read_b),
    .mem_write_b(phymem_write_b),
    .sign_extend_b(phymem_sign_extend_b),
    .bw_b(phymem_bw_b),
    .data_in_b(phymem_data_in_b),
    .data_out_b(phymem_data_out_b)
  );
endmodule
