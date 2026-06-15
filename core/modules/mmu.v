`include "defs.vh"
`include "modules/mem.v"

// SIMULATION ONLY
// true 2 port memory with pagetable

// TODO! add exception if sv39 not setup properly
// BUG! abort if trap is taken
module mmu (
  input wire clk,
  input wire rst,
  output wor hard_stall,

  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`DLEN)      satp,
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
  /* verilator lint_off WIDTHTRUNC */
  // TODO! have seperate pbtl_en for a and b
  wire pgtbl_en =
    (mem_read_a | mem_read_b | mem_write_a | mem_write_b) &&
    (`SATP_MODE(satp) == `SATP_MODE_SV39);
  /* verilator lint_on WIDTHTRUNC */

  // counter for lvl counting
  reg `W($clog2(`PGTBL_LVLS)) lvl;

  always @(posedge clk) begin
    if(rst) begin
      lvl <= `PGTBL_LVLS;
    end
    else if(pgtbl_en) begin
      lvl <= (lvl == 0) ? `PGTBL_LVLS: (lvl - 1);
    end
  end

  assign hard_stall = pgtbl_en && (lvl != 0);

  // TODO! add exception when PTE is invalid
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
    if(rst) begin
      pte_a <= 0;
      pte_b <= 0;
    end
    else if(pgtbl_en) begin
      pte_a <= phymem_data_out_a;
      pte_b <= phymem_data_out_b;
    end
  end

  // Port A
  /* verilator lint_off WIDTHEXPAND */
  wire `W(`DLEN) phymem_addr_a = (!pgtbl_en) ? addr_a
    :((lvl == 0) ? `PTE2PA(pte_a, `VA2OFF(addr_a)): pte_addr_a);
  /* verilator lint_on WIDTHEXPAND */

  wire phymem_read_a = (!pgtbl_en) ? mem_read_a
    :((lvl == 0) ? mem_read_a: 1);

  wire phymem_write_a = (!pgtbl_en) ? mem_write_a
    :((lvl == 0) ? mem_write_a: 0);

  wire `W(`BWLEN) phymem_bw_a = (!pgtbl_en) ? bw_a
    :((lvl == 0) ? bw_a: `BW_DBLWORD);

  // for pgtbl walk, sign extend, data in doesnt matter 
  wire phymem_sign_extend_a = sign_extend_a;
  wire `W(`DLEN) phymem_data_in_a = data_in_a;
  assign data_out_a = phymem_data_out_a;

  // Port B
  /* verilator lint_off WIDTHEXPAND */
  wire `W(`DLEN) phymem_addr_b = (!pgtbl_en) ? addr_b
    :((lvl == 0) ? `PTE2PA(pte_b, `VA2OFF(addr_b)): pte_addr_b);
  /* verilator lint_on WIDTHEXPAND */

  wire phymem_read_b = (!pgtbl_en) ? mem_read_b
    :((lvl == 0) ? mem_read_b: 1);

  wire phymem_write_b = (!pgtbl_en) ? mem_write_b
    :((lvl == 0) ? mem_write_b: 0);

  wire `W(`BWLEN) phymem_bw_b = (!pgtbl_en) ? bw_b
    :((lvl == 0) ? bw_b: `BW_DBLWORD);

  // for pgtbl walk, sign extend, data in doesnt matter 
  wire phymem_sign_extend_b = sign_extend_b;
  wire `W(`DLEN) phymem_data_in_b = data_in_b;
  assign data_out_b = phymem_data_out_b;

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
