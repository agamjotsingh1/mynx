// behavioral model of the Vivado BMG cache_bram (dv/bench only, never synthesized)
// matches the .xci config: true dual port, 16384 x 64, byte write enables,
// READ_LATENCY = 1, WRITE_FIRST on both ports, output holds when en is low.
// contents init to 0xCC.. garbage (adversarial: catches any read-before-entry
// reliance; the real BRAM powers up to zeros which can hide that).
module cache_bram (
  input  wire        clka,
  input  wire [13:0] addra,
  input  wire [63:0] dina,
  output reg  [63:0] douta,
  input  wire        ena,
  input  wire [7:0]  wea,

  input  wire        clkb,
  input  wire [13:0] addrb,
  input  wire [63:0] dinb,
  output reg  [63:0] doutb,
  input  wire        enb,
  input  wire [7:0]  web
);
  reg [63:0] mem [0:16383] /*verilator public_flat_rd*/;

  integer i;
  initial begin
    for(i = 0; i < 16384; i = i + 1)
      mem[i] = 64'hCCCC_CCCC_CCCC_CCCC;
  end

  integer j;
  always @(posedge clka) begin
    if(ena) begin
      for(j = 0; j < 8; j = j + 1) begin
        if(wea[j]) mem[addra][8*j +: 8] <= dina[8*j +: 8];
        // WRITE_FIRST: dout shows the new data on written bytes
        douta[8*j +: 8] <= wea[j] ? dina[8*j +: 8] : mem[addra][8*j +: 8];
      end
    end
  end

  integer k;
  always @(posedge clkb) begin
    if(enb) begin
      for(k = 0; k < 8; k = k + 1) begin
        if(web[k]) mem[addrb][8*k +: 8] <= dinb[8*k +: 8];
        doutb[8*k +: 8] <= web[k] ? dinb[8*k +: 8] : mem[addrb][8*k +: 8];
      end
    end
  end
endmodule
