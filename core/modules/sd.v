`include "defs.vh"

// Interface with ASDC to give normal/DMA access to SD card
module sd (
  input wire clk,
  input wire rst,

  // MMIO interface
  input wire mmio_read_en,
  input wire mmio_write_en,
  input wire `W(`DLEN) mmio_addr,
  input wire `W(`DLEN) mmio_write_data,
  output reg `W(`DLEN) mmio_read_data,

  // interrupt request
  output reg irq,

  // take the external spi clock slow during init process
  output wire slow_sel,

  // ASDC ports
  output wire __asdc_read_en,
  output wire __asdc_write_en,
  output wire  `W(`ASDC_ADDRLEN)  __asdc_addr,
  output wire  `W(`ASDC_DATALEN)  __asdc_data_in,
  input  wire  `W(`ASDC_DATALEN)  __asdc_data_out,
  input  wire  __asdc_data_out_valid,
  input  wire  __asdc_busy,
  input  wire  __asdc_err
);
  // MMIO regs
  reg `W(`DLEN) cfg;
  reg `W(`DLEN) addr;
  reg `W(`DLEN) data;
  reg `W(`DLEN) reply; // read-only
  reg `W(`DLEN) done;  // read-only

  always @(*) begin
    case(mmio_addr)
      `SD_MMIO_CFG  : mmio_read_data = cfg;
      `SD_MMIO_ADDR : mmio_read_data = addr;
      `SD_MMIO_REPLY: mmio_read_data = reply;
      `SD_MMIO_DONE : mmio_read_data = done;
      default       : mmio_read_data = 0;
    endcase
  end
  
  assign slow_sel = ~`SD_CFG_INITD(cfg);

  reg [2:0] state;
  localparam IDLE    = 3'b000;
  localparam NORMALR = 3'b001;
  localparam NORMALW = 3'b010;
  localparam WAIT    = 3'b100;
  localparam DMA     = 3'b101;

  always @(posedge clk) begin
    if(rst) begin
      state <= IDLE;
      cfg <= 0;
      addr <= 0;
      data <= 0;
      reply <= 0;
      done <= 0;
      irq <= 0;
    end
    else begin
      if(__asdc_data_out_valid)
        reply <= __asdc_data_out;

      // clear interrupt request if mmio acknowledges by reading reply
      if(mmio_read_en && mmio_addr == `SD_MMIO_DONE) begin
        done <= 0;
      end

      case(state)
        IDLE: begin

          if(`SD_CFG_FIRE(cfg)) begin
            if(`SD_CFG_DMA(cfg)) state <= DMA;
            else begin
              state <= `SD_CFG_RE(cfg)
                ? NORMALR
                : (`SD_CFG_WE(cfg) ? NORMALW: IDLE);
            end
          end
          else if(mmio_write_en) begin
            case(mmio_addr)
              `SD_MMIO_CFG : cfg  <= mmio_write_data;
              `SD_MMIO_ADDR: addr <= mmio_write_data;
              `SD_MMIO_DATA: data <= mmio_write_data;
            endcase
          end
        end

        NORMALR, NORMALW: begin
          if(__asdc_busy) begin
            state <= WAIT;
          end
        end

        WAIT: begin
          if(!__asdc_busy) begin
            done <= 1;
            state <= IDLE;
            `SD_CFG_FIRE(cfg) <= 0;
          end
        end

        DMA: begin
          // TODO! unimplemented
          state <= IDLE;
        end
      endcase
    end
  end

  assign __asdc_read_en  = (state == NORMALR);
  assign __asdc_write_en = (state == NORMALW);
  assign __asdc_addr     = addr;
  assign __asdc_data_in  = data;
endmodule
