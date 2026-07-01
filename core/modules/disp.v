`include "defs.vh"

// display driver with text interface
module disp (
  // input wire clk,       // 1 MHz clock
  input wire pixel_clk, // ~75 MHz clock
  input wire rstn,
  // input wire valid,
  // input wire  `W(`BYTE) char,
  output wire `W(`RGBLEN) rgb,
  output reg active_video,
  output reg hsync,
  output reg vsync
);
  reg `W(`POSLEN) vtc_x, vtc_y;
  reg `W(`POSLEN) x, y;
  wire vtc_active_video;
  wire vtc_hsync, vtc_vsync;

  reg [7:0] ascii_cntr;

  always @(posedge pixel_clk) begin
    if(!rstn) begin
      vtc_x <= 0;
      vtc_y <= 0;
    end
    else if(vtc_active_video) begin
      // end of 720p horizontal line
      if(vtc_x == `XPIXELS - 1) begin
        vtc_x <= 0;
        vtc_y <= (vtc_y == `YPIXELS - 1) ? 0: (vtc_y + 1);
      end
      else begin
        vtc_x <= vtc_x + 1;
      end
    end
    // complete reset of coordinates
    else if(vtc_vsync) begin
      vtc_x <= 0;
      vtc_y <= 0;
    end
  end

  always @(posedge pixel_clk) begin
    if(!rstn) begin
      active_video <= 0;
      ascii_cntr <= 0;
      hsync <= 0;
      vsync <= 0;
      x <= 0;
      y <= 0;
    end
    else begin
      ascii_cntr <= ascii_cntr + 1;
      active_video <= vtc_active_video;
      hsync <= vtc_hsync;
      vsync <= vtc_vsync;
      x <= vtc_x;
      y <= vtc_y;
    end
  end

  wire `W(`FONTROM_ADDRLEN) fontrom_addr;
  wire `W(`FONTROM_DATALEN) fontrom_data;

  // corresponds to 'a'
  assign fontrom_addr = {ascii_cntr, vtc_y[$clog2(`FONT_Y)-1:0]};

  fontrom fontrom_instance (
    .clk(pixel_clk),
    .addr(fontrom_addr),
    .data(fontrom_data)
  );

  assign rgb = active_video
    ? ((fontrom_data[~(x[$clog2(`FONT_X)-1:0])]) ? `COLOR_WHITE: `COLOR_BLACK)
    : `COLOR_BLACK;

  vtc vtc_instance (
    .clk(pixel_clk),
    .clken(1'b1),
    .gen_clken(1'b1),
    .sof_state(1'b0),
    .resetn(rstn),
    .active_video_out(vtc_active_video),
    .hsync_out(vtc_hsync),
    .vsync_out(vtc_vsync)
  );
endmodule
