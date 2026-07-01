`include "defs.vh"

// display driver with text interface
module disp (
  // input wire clk,       // 1 MHz clock
  input wire pixel_clk, // ~75 MHz clock
  input wire rstn,
  // input wire valid,
  // input wire  `W(`BYTE) char,
  output wire `W(`RGBLEN) rgb,
  output wire active_video,
  output wire hsync,
  output wire vsync
);
  reg `W(`POSLEN) x, y;

  always @(posedge pixel_clk) begin
    if(!rstn) begin
      x <= 0;
      y <= 0;
    end
    else if(active_video) begin
      // end of 720p horizontal line
      if(x == `XPIXELS - 1) begin
        x <= 0;
        y <= (y == `YPIXELS - 1) ? 0: (y + 1);
      end
      else begin
        x <= x + 1;
      end
    end
    // complete reset of coordinates
    else if(vsync) begin
      x <= 0;
      y <= 0;
    end
  end

  assign rgb = active_video
    ? ((x[0] ^ y[0]) ? `COLOR_WHITE: `COLOR_BLACK)
    : `COLOR_BLACK;

  vtc vtc_instance (
    .clk(pixel_clk),
    .clken(1'b1),
    .gen_clken(1'b1),
    .sof_state(1'b0),
    .resetn(rstn),
    .active_video_out(active_video),
    .hsync_out(hsync),
    .vsync_out(vsync)
  );
endmodule
