`include "defs.vh"

module fontrom (
  input wire clk,
  input wire `W(`FONTROM_ADDRLEN) addr,
  output reg `W(`FONTROM_DATALEN) data
);
  (* rom_style = "distributed" *) reg `W(`FONTROM_DATALEN) rom [0:`FONTROM_DEPTH-1];

  initial begin
    $readmemh("font.hex", rom);
  end

  always @(posedge clk) begin
    data <= rom[addr];
  end
endmodule
