`include "defs.vh"

// when a hit happens,
// mem_read and mem_write (along with other inputs) SHOULD NOT CHANGE
module cache (
  input wire clk,
  input wire rst,

  // input ports
  input wire  `W(`ADDRLEN)  addr,
  input wire                mem_read,
  input wire                mem_write,
  input wire                sign_extend,
  input wire  `W(`BWLEN)    bw,
  input wire  `W(`DLEN)     data_in,
  output reg  `W(`DLEN)     data_out,

  output wire hit,

  // BRAM ports output wire __bram_en,
  output wire `W(`BRAM_ADDRLEN) __bram_addr,
  output wire `W(`BRAM_DLEN)    __bram_din,
  input  wire `W(`BRAM_DLEN)    __bram_dout,
  output reg  `W(`BRAM_WEALEN)  __bram_wea
);
  // assuming VIVADO BRAMs always have one cycle delay
  
  reg state;
  localparam IDLE   = 1'b0;
  localparam WRITE  = 1'b1;

  // use distributed ram for large metadata info
  // and comparison of tag bits is faster due to silicon muxes
  (* ram_style = "distributed" *) reg `W(`CACHE_METALEN) meta [0:`CACHE_DEPTH-1];

  wire `W(`CACHE_INDEXLEN) index = `CACHE_INDEX(addr); 

  assign hit = (`CACHE_META_TAG(meta[index]) == `CACHE_TAG(addr)) && `CACHE_META_VALID(meta[index]);

  assign __bram_en   = hit && (mem_read | mem_write);
  assign __bram_addr = index;
  assign __bram_din  = data_in;
  assign data_out    = __bram_dout;

  always @(*) begin
    if(state == IDLE) begin
      __bram_wea = `BRAM_WEA_NONE;
    end
    else if(state == WRITE) begin
      case(bw) begin
        `BW_BYTE    : __bram_wea = `BRAM_WEA_BYTE;
        `BW_HALFWORD: __bram_wea = `BRAM_WEA_HALFWORD;
        `BW_WORD    : __bram_wea = `BRAM_WEA_WORD;
        `BW_DBLWORD : __bram_wea = `BRAM_WEA_DBLWORD;
        default     : __bram_wea = `BRAM_WEA_NONE;
      end
    end
  end

  always @(posedge clk) begin
    if(rst) begin
      state <= IDLE;
    end
    else begin
      if(state == IDLE) begin
        if(hit && mem_write) state <= WRITE;
      end
      else if(state == WRITE) begin
        state <= IDLE;
      end
    end
  end
endmodule

