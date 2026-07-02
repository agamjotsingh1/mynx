`include "defs.vh"

// display driver with text interface
module disp (
  input wire clk,
  input wire valid,
  input wire rstn,
  input wire  `W(`BYTE) char,

  output wire __textram_clka,
  output wire `W(`TEXTRAM_ADDRLEN) __textram_addra,
  output wire __textram_ena,
  output wire __textram_wea,
  output wire `W(`TEXTRAM_DATALEN) __textram_dina,
  output wire __textram_clkb,
  output wire `W(`TEXTRAM_ADDRLEN) __textram_addrb,
  output wire __textram_enb,
  output wire __textram_web,
  input  wire `W(`TEXTRAM_DATALEN) __textram_doutb,

  input wire pixel_clk,
  input wire pixel_rstn,
  output wire `W(`RGBLEN) rgb,
  output wire active_video,
  output wire hsync,
  output wire vsync
);
  reg `W(`POSLEN) x, y;

  // --- vtc ---
  reg `W(`POSLEN) vtc_x, vtc_y;
  wire vtc_active_video;
  wire vtc_hsync, vtc_vsync;

  always @(posedge pixel_clk) begin
    if(!pixel_rstn) begin
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

  vtc vtc_instance (
    .clk(pixel_clk),
    .clken(1'b1),
    .gen_clken(1'b1),
    .sof_state(1'b0),
    .resetn(pixel_rstn),
    .active_video_out(vtc_active_video),
    .hsync_out(vtc_hsync),
    .vsync_out(vtc_vsync)
  );

  reg `W($clog2(`CHAR_ROWS)) write_row;
  reg `W($clog2(`CHAR_COLS)) write_col;
  reg scrolled;
  reg latched_valid;

  always @(posedge clk) begin
    if(!rstn) begin
      latched_valid <= 0;
      write_row <= 0;
      write_col <= 0;
      scrolled  <= 0;
    end
    else if(!valid && latched_valid) begin
      latched_valid <= 0;
    end
    else if(valid && !latched_valid) begin
      latched_valid <= 1;

      // end of current line
      if(write_col == `CHAR_COLS - 1) begin
        write_col <= 0;
        scrolled <= scrolled | (write_row == `CHAR_ROWS - 1);
        write_row <= (write_row == `CHAR_ROWS - 1) ? 0 : write_row + 1;
      end
      else begin
        write_col <= write_col + 1;
      end
    end
  end

//   wire `W($clog2(`CHAR_ROWS)) top_row =
//     write_row + $unsigned(scrolled);

  reg `W($clog2(`CHAR_ROWS)) top_row_50mhz_reg;
  always @(posedge clk) begin
    if (!rstn) top_row_50mhz_reg <= 0;
    else top_row_50mhz_reg <= write_row + $unsigned(scrolled);
  end

  (* ASYNC_REG = "TRUE" *) reg `W($clog2(`CHAR_ROWS)) top_row_sync1;
  (* ASYNC_REG = "TRUE" *) reg `W($clog2(`CHAR_ROWS)) top_row_sync2;

  always @(posedge pixel_clk) begin
    if(!pixel_rstn) begin
      top_row_sync1 <= 0;
      top_row_sync2 <= 0;
    end
    else begin
      top_row_sync1 <= top_row_50mhz_reg;
      top_row_sync2 <= top_row_sync1;
    end
  end

  // magic numbers 7 and 5
  // write_row << 7 + write_row << 5 = write_row * 160
  // where 160 is number of columns
  wire `W($clog2(`CHAR_TOTAL)) write_ptr =
    ($unsigned(write_row) << 7) +
    ($unsigned(write_row) << 5) +
    ($unsigned(write_col));

  // textram port A for clk writes
  assign __textram_clka = clk;
  assign __textram_wea = valid && !latched_valid;
  assign __textram_ena = valid && !latched_valid;
  assign __textram_dina  = char;
  assign __textram_addra = write_ptr;

  // textram port B for pixel_clk reads
  assign __textram_clkb = pixel_clk;
  assign __textram_web = 1'b0;
  assign __textram_enb = 1'b1;

  wire `W(`CHAR_ROWS) text_row = vtc_y`TEXT_ROWSLICE;
  wire `W(`CHAR_COLS) text_col = vtc_x`TEXT_COLSLICE;
  wire `W(`CHAR_ROWS) real_row = (text_row + top_row_sync2 >= `CHAR_ROWS)
    ? (text_row + top_row_sync2 - `CHAR_ROWS)
    : (text_row + top_row_sync2);

  assign __textram_addrb =
    ($unsigned(real_row) << 7) + 
    ($unsigned(real_row) << 5) + 
    (text_col);

  reg d1_active_video, d2_active_video;
  reg d1_hsync, d2_hsync;
  reg d1_vsync, d2_vsync;
  reg `W(`POSLEN) d1_x, d2_x;
  reg `W(`POSLEN) d1_y, d2_y;

  always @(posedge pixel_clk) begin
    if(!pixel_rstn) begin
      d1_active_video <= 0;
      d1_hsync <= 0;
      d1_vsync <= 0;
      d1_x <= 0;
      d1_y <= 0;

      d2_active_video <= 0;
      d2_hsync <= 0;
      d2_vsync <= 0;
      d2_x <= 0;
      d2_y <= 0;
    end
    else begin
      d1_active_video <= vtc_active_video;
      d1_hsync <= vtc_hsync;
      d1_vsync <= vtc_vsync;
      d1_x <= vtc_x;
      d1_y <= vtc_y;

      d2_active_video <= d1_active_video;
      d2_hsync <= d1_hsync;
      d2_vsync <= d1_vsync;
      d2_x <= d1_x;
      d2_y <= d1_y;
    end
  end

  wire `W(`FONTROM_ADDRLEN) fontrom_addr;
  wire `W(`FONTROM_DATALEN) fontrom_data;

  assign fontrom_addr = {__textram_doutb, d1_y[$clog2(`FONT_Y)-1:0]};

  fontrom fontrom_instance (
    .clk(pixel_clk),
    .addr(fontrom_addr),
    .data(fontrom_data)
  );

  assign rgb = d2_active_video
    ? ((fontrom_data[~(d2_x[$clog2(`FONT_X)-1:0])]) ? `COLOR_WHITE: `COLOR_BLACK)
    : `COLOR_BLACK;

  assign active_video = d2_active_video;
  assign hsync = d2_hsync;
  assign vsync = d2_vsync;

  (* mark_debug = "true" *) wire [7:0] dbg_bram_out = __textram_doutb;
endmodule
