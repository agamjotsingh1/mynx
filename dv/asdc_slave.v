`include "defs.vh"

/* 
* WARNING to anyone viewing this code: this is completely AI generated and
* not human checked. Big TODO to check it and validate it but in the interest
* of time it still remains a TODO.
*/

import "DPI-C" context function longint host_disk_read_word (input int sector, input int word_offset);
import "DPI-C" context function void    host_disk_write_word(input int sector, input int word_offset, input longint data);

// SIMULATION ONLY
// Mock AXI4-Lite slave for ASDC
/* verilator lint_off UNUSEDSIGNAL */
module asdc_slave (
  input wire clk,
  input wire rst,

  // AR - Address Read
  input  wire s_axi_arvalid,
  output reg  s_axi_arready,
  input  wire `W(`ASDC_ADDRLEN) s_axi_araddr,
  input  wire `W(`ASDC_PROTLEN) s_axi_arprot,

  // R - Read
  output reg  s_axi_rvalid,
  input  wire s_axi_rready,
  output reg  `W(`ASDC_DATALEN) s_axi_rdata,
  output reg  `W(`ASDC_RESPLEN) s_axi_rresp,

  // AW - Address Write
  input  wire s_axi_awvalid,
  output reg  s_axi_awready,
  input  wire `W(`ASDC_ADDRLEN) s_axi_awaddr,
  input  wire `W(`ASDC_PROTLEN) s_axi_awprot,

  // W - Write
  input  wire s_axi_wvalid,
  output reg  s_axi_wready,
  input  wire `W(`AXI_DATALEN) s_axi_wdata,
  input  wire `W(`AXI_STRBLEN) s_axi_wstrb,

  // B - Write Response
  output reg  s_axi_bvalid,
  input  wire s_axi_bready,
  output reg  `W(`AXI_RESPLEN) s_axi_bresp
);
  localparam [6:0] SPISRR  = 7'h40;
  localparam [6:0] SPICR   = 7'h60;
  localparam [6:0] SPISR   = 7'h64;
  localparam [6:0] SPIDTR  = 7'h68;
  localparam [6:0] SPIDRR  = 7'h6C;
  localparam [6:0] SPISSR  = 7'h70;

  reg `W(`ASDC_DATALEN) spicr;
  reg `W(`ASDC_DATALEN) spissr;

  reg [7:0] rx_data;
  reg       rx_empty;

  // SR:
  // bit0 = rx fifo empty
  // bit1 = rx full
  // bit2 = tx fifo empty
  // bit3 = tx full
  wire `W(`ASDC_DATALEN) spisr_val = {28'b0, 1'b0, 1'b1, 1'b0, rx_empty};

  // handshake between the AXI side and the sd card model
  reg       xfer;      // one SPI byte was pushed into DTR
  reg [7:0] mosi;
  reg       drr_pop;   // DRR was read
  reg       srr_reset; // soft reset was written to SRR

  /* ---------------- SD card model (SPI mode) ---------------- */
  localparam [2:0] SD_IDLE     = 3'd0;
  localparam [2:0] SD_CMD      = 3'd1; // collecting arg + crc bytes
  localparam [2:0] SD_RESP     = 3'd2; // draining the response queue
  localparam [2:0] SD_RD       = 3'd3; // token + 512 data + 2 crc
  localparam [2:0] SD_WR_TOKEN = 3'd4; // waiting for 0xFE
  localparam [2:0] SD_WR_DATA  = 3'd5; // 512 data + 2 crc
  localparam [2:0] SD_WR_RESP  = 3'd6; // data response token

  reg [2:0]  sd_state;
  reg        card_idle;
  reg [5:0]  cmd;
  reg [31:0] cmd_arg;
  reg [2:0]  cmd_cnt;

  // response queue (R1 followed by up to 4 trailing bytes)
  reg [7:0]  respq [0:4];
  reg [2:0]  resp_cnt;
  reg [2:0]  resp_idx;

  // block data phase
  reg [31:0] blk;     // 512 byte SD block number
  reg [9:0]  blk_idx;

  // fs.img is addressed by soc_tb in 1024 byte sectors of 128 x 64 bit words,
  // so one 512 byte SD block is half a sector (64 words).
  wire [9:0]  rd_byte    = blk_idx - 1; // SD_RD: blk_idx 0 is the start token
  wire [31:0] dpi_sector = blk >> 1;
  wire [31:0] dpi_wbase  = {25'b0, blk[0], 6'b0};
  wire [31:0] dpi_word_r = dpi_wbase + {26'b0, rd_byte[8:3]};
  wire [31:0] dpi_word_w = dpi_wbase + {26'b0, blk_idx[8:3]};

  // byte lane of the 64 bit word currently being read / written
  wire [5:0]  rd_shift = {rd_byte[2:0], 3'b0};
  wire [5:0]  wr_shift = {blk_idx[2:0], 3'b0};

  wire [63:0] rd_word  = host_disk_read_word(dpi_sector, dpi_word_r);
  wire [7:0]  rd_data  = rd_word[rd_shift +: 8];

  // read modify write: only the addressed byte lane changes
  wire [63:0] wr_word  = (host_disk_read_word(dpi_sector, dpi_word_w) & ~(64'hFF << wr_shift))
                       | ({56'b0, mosi} << wr_shift);

  integer i;

  always @(posedge clk) begin
    if(rst || srr_reset) begin
      sd_state  <= SD_IDLE;
      card_idle <= 1;
      cmd       <= 0;
      cmd_arg   <= 0;
      cmd_cnt   <= 0;
      resp_cnt  <= 0;
      resp_idx  <= 0;
      blk       <= 0;
      blk_idx   <= 0;
      rx_data   <= 8'hFF;
      rx_empty  <= 1;

      for(i = 0; i < 5; i = i + 1) respq[i] <= 8'hFF;
    end
    else begin
      if(drr_pop) rx_empty <= 1;

      // one SPI byte: consume mosi, drive rx_data with the miso byte
      if(xfer) begin
        rx_data  <= 8'hFF; // overridden below by whatever the card replies
        rx_empty <= 0;

        case(sd_state)
          SD_IDLE: begin
            if(mosi[7:6] == 2'b01) begin
              cmd      <= mosi[5:0];
              cmd_arg  <= 0;
              cmd_cnt  <= 5; // 4 arg bytes + crc
              sd_state <= SD_CMD;
            end
          end

          SD_CMD: begin
            cmd_arg <= {cmd_arg[23:0], mosi};
            cmd_cnt <= cmd_cnt - 1;

            // this byte is the crc, the 4 arg bytes are already in cmd_arg
            if(cmd_cnt == 1) begin
              resp_idx <= 0;
              resp_cnt <= 1;
              respq[0] <= 8'h00;
              sd_state <= SD_RESP;

              case(cmd)
                6'd0: begin // GO_IDLE_STATE
                  card_idle <= 1;
                  respq[0]  <= 8'h01;
                end
                6'd8: begin // SEND_IF_COND -> R7
                  respq[0] <= 8'h01;
                  respq[1] <= 8'h00;
                  respq[2] <= 8'h00;
                  respq[3] <= 8'h01;
                  respq[4] <= 8'hAA;
                  resp_cnt <= 5;
                end
                6'd55: begin // APP_CMD
                  respq[0] <= card_idle ? 8'h01 : 8'h00;
                end
                6'd41: begin // ACMD41 - card leaves idle immediately
                  card_idle <= 0;
                end
                6'd58: begin // READ_OCR -> R3, CCS set (block addressing)
                  respq[1] <= 8'hC0;
                  respq[2] <= 8'hFF;
                  respq[3] <= 8'h80;
                  respq[4] <= 8'h00;
                  resp_cnt <= 5;
                end
                6'd17, 6'd24: begin // READ_SINGLE_BLOCK / WRITE_BLOCK
                  blk     <= cmd_arg;
                  blk_idx <= 0;
                end
                default: ;
              endcase
            end
          end

          SD_RESP: begin
            rx_data  <= respq[resp_idx];
            resp_idx <= resp_idx + 1;

            // response drained, enter a data phase if the command needs one
            if(resp_idx == resp_cnt - 1) begin
              if(cmd == 6'd17)      sd_state <= SD_RD;
              else if(cmd == 6'd24) sd_state <= SD_WR_TOKEN;
              else                  sd_state <= SD_IDLE;
            end
          end

          SD_RD: begin
            blk_idx <= blk_idx + 1;

            if(blk_idx == 0) begin
              rx_data <= 8'hFE; // data start token
            end
            else if(blk_idx <= 512) begin
              rx_data <= rd_data;
            end
            else begin
              // 2 crc bytes (rx_data stays 0xFF)
              if(blk_idx == 514) sd_state <= SD_IDLE;
            end
          end

          SD_WR_TOKEN: begin
            if(mosi == 8'hFE) begin
              blk_idx  <= 0;
              sd_state <= SD_WR_DATA;
            end
          end

          SD_WR_DATA: begin
            blk_idx <= blk_idx + 1;

            if(blk_idx < 512) begin
              host_disk_write_word(dpi_sector, dpi_word_w, wr_word);
            end
            // 2 crc bytes
            else if(blk_idx == 513) sd_state <= SD_WR_RESP;
          end

          SD_WR_RESP: begin
            rx_data  <= 8'h05; // data accepted, next bytes read 0xFF (not busy)
            sd_state <= SD_IDLE;
          end

          default: sd_state <= SD_IDLE;
        endcase
      end
    end
  end

  /* ---------------- AXI-Lite slave ---------------- */
  localparam [2:0] IDLE   = 3'd0;
  localparam [2:0] R_ACC  = 3'd1;
  localparam [2:0] R_RESP = 3'd2;
  localparam [2:0] W_ACC  = 3'd3;
  localparam [2:0] W_RESP = 3'd4;

  reg [2:0] state;
  reg `W(`ASDC_ADDRLEN) araddr_l;
  reg `W(`ASDC_ADDRLEN) awaddr_l;
  reg [31:0] wdata_l;

  always @(posedge clk) begin
    if(rst) begin
      state         <= IDLE;
      s_axi_arready <= 0;
      s_axi_rvalid  <= 0;
      s_axi_rdata   <= 0;
      s_axi_rresp   <= `AXI_RESP_OKAY;
      s_axi_awready <= 0;
      s_axi_wready  <= 0;
      s_axi_bvalid  <= 0;
      s_axi_bresp   <= `AXI_RESP_OKAY;

      araddr_l  <= 0;
      awaddr_l  <= 0;
      wdata_l   <= 0;

      spicr     <= 0;
      spissr    <= 32'hFFFFFFFF;

      xfer      <= 0;
      mosi      <= 0;
      drr_pop   <= 0;
      srr_reset <= 0;
    end
    else begin
      xfer      <= 0;
      drr_pop   <= 0;
      srr_reset <= 0;

      case(state)
        IDLE: begin
          // writes win over reads, the master only ever issues one at a time
          if(s_axi_awvalid && s_axi_wvalid) begin
            s_axi_awready <= 1;
            s_axi_wready  <= 1;
            awaddr_l      <= s_axi_awaddr;
            wdata_l       <= s_axi_wdata[31:0];
            state         <= W_ACC;
          end
          else if(s_axi_arvalid) begin
            s_axi_arready <= 1;
            araddr_l      <= s_axi_araddr;
            state         <= R_ACC;
          end
        end

        R_ACC: begin
          s_axi_arready <= 0;
          s_axi_rvalid  <= 1;
          s_axi_rresp   <= `AXI_RESP_OKAY;
          state         <= R_RESP;

          case(araddr_l)
            SPICR : s_axi_rdata <= spicr;
            SPISR : s_axi_rdata <= spisr_val;
            SPISSR: s_axi_rdata <= spissr;
            SPIDRR: begin
              s_axi_rdata <= {24'b0, rx_data};
              drr_pop     <= 1;
            end
            default: s_axi_rdata <= 0;
          endcase
        end

        R_RESP: begin
          if(s_axi_rready) begin
            s_axi_rvalid <= 0;
            state        <= IDLE;
          end
        end

        W_ACC: begin
          s_axi_awready <= 0;
          s_axi_wready  <= 0;
          s_axi_bvalid  <= 1;
          s_axi_bresp   <= `AXI_RESP_OKAY;
          state         <= W_RESP;

          case(awaddr_l)
            SPICR : spicr  <= wdata_l;
            SPISSR: spissr <= wdata_l;
            SPIDTR: begin
              xfer <= 1;
              mosi <= wdata_l[7:0];
            end
            SPISRR: begin
              // 0x0A = soft reset, clears fifos and config
              if(wdata_l[3:0] == 4'hA) begin
                spicr     <= 0;
                spissr    <= 32'hFFFFFFFF;
                srr_reset <= 1;
              end
            end
            default: ;
          endcase
        end

        W_RESP: begin
          if(s_axi_bready) begin
            s_axi_bvalid <= 0;
            state        <= IDLE;
          end
        end

        default: state <= IDLE;
      endcase
    end
  end
endmodule
/* verilator lint_on UNUSEDSIGNAL */
