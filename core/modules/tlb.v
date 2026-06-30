`include "defs.vh"

module tlb (
  input wire clk,
  input wire rst,
  input wire flush,
  input wire pgtbl_en,
  input wire update_en,
  input wire `W(`DLEN) pte_update,
  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`DLEN) va,
  /* verilator lint_on UNUSEDSIGNAL */

  output wire hit,
  output wire `W(`PTELEN) pte
);
  wire `W(`TLB_INDEXLEN) index = `TLB_INDEX(va);
  wire `W(`TLB_TAGLEN)   tag   = `TLB_TAG(va);

  reg                 tlb_valid [0:`TLB_ENTRIES-1];
  reg `W(`TLB_TAGLEN) tlb_tag   [0:`TLB_ENTRIES-1];
  reg `W(`PTELEN)     tlb_pte   [0:`TLB_ENTRIES-1];

  integer i;
  always @(posedge clk) begin
    if (rst || flush) begin
      for(i = 0; i < `TLB_ENTRIES; i = i + 1)
        tlb_valid[i] <= 0;
    end
    else if(update_en) begin
      tlb_valid[index] <= 1;
      tlb_tag[index]   <= tag;
      tlb_pte[index]   <= pte_update;
    end
  end

  assign hit = tlb_valid[index] && (tlb_tag[index] == tag) && (pgtbl_en) && (!flush);
  assign pte = tlb_pte[index];
endmodule
