`include "defs.vh"

// SIMULATION ONLY
// "cache_bram" IP (blk_mem_gen) mock
module cache_bram (
  // port a
  input  wire                    clka,
  input  wire                    ena,
  input  wire `W(`BRAM_WELEN)    wea,
  input  wire `W(`BRAM_ADDRLEN)  addra,
  input  wire `W(`BRAM_DLEN)     dina,
  output reg  `W(`BRAM_DLEN)     douta,

  // port b
  /* verilator lint_off UNUSEDSIGNAL */
  input  wire                    clkb, // placeholder, driven only by clka
  /* verilator lint_on UNUSEDSIGNAL */
  input  wire                    enb,
  input  wire `W(`BRAM_WELEN)    web,
  input  wire `W(`BRAM_ADDRLEN)  addrb,
  input  wire `W(`BRAM_DLEN)     dinb,
  output reg  `W(`BRAM_DLEN)     doutb
);
  reg `W(`BRAM_DLEN) mem [0:`BRAM_DEPTH-1];

  integer i;
  initial begin
    for (i = 0; i < `BRAM_DEPTH; i = i + 1) mem[i] = 0;
  end

  integer ba, bb;

  always @(posedge clka) begin
    // port a
    if (ena) begin
      douta <= mem[addra];
      for (ba = 0; ba < `BRAM_WELEN; ba = ba + 1) begin
        if (wea[ba])
          mem[addra][ba*`BYTE +: `BYTE] <= dina[ba*`BYTE +: `BYTE];
      end
    end
    // port b
    if (enb) begin
      doutb <= mem[addrb];
      for (bb = 0; bb < `BRAM_WELEN; bb = bb + 1) begin
        if (web[bb])
          mem[addrb][bb*`BYTE +: `BYTE] <= dinb[bb*`BYTE +: `BYTE];
      end
    end
  end
endmodule
