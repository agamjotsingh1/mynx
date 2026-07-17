`include "defs.vh"

// chooses the slow clock when slow_sel goes high
module spi_clkmux (
  input  wire clk,
  input  wire rst,
  input  wire slow_sel,
  output wire ext_spi_clk
);
  reg [$clog2(`SPI_CLKDIV)-1:0] cnt;
  reg slow_raw;

  // divide the clock by (2*SPI_CLKDIV)
  always @(posedge clk) begin
    if (rst) begin
      cnt      <= 0;
      slow_raw <= 0;
    end
    else if (cnt == `SPI_CLKDIV-1) begin
      cnt      <= 0;
      slow_raw <= ~slow_raw;
    end
    else cnt <= cnt + 1;
  end

  wire slow_clk;

  BUFG u_slow_bufg (
    .I(slow_raw),
    .O(slow_clk)
  );

  BUFGMUX_CTRL u_mux (.I0(clk),
    .I1(slow_clk),
    .S(slow_sel),
    .O(ext_spi_clk)
  );
endmodule
