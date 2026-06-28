`include "defs.vh"

// sub memory for different ports with their own caches
module submem (
  input wire clk,
  input wire rst,

  // Mem Port
  input wire  `W(`ADDRLEN)  addr,
  input wire                mem_read,
  input wire                mem_write,
  input wire                sign_extend,
  input wire  `W(`BWLEN)    bw,
  input wire  `W(`DLEN)     data_in,
  output wire `W(`DLEN)     data_out,
  output wire               busy,

  // AMC ports
  output wire  `W(`ADDRLEN)  __amc_addr,
  output wire                __amc_mem_read,
  output wire                __amc_mem_write,
  output wire  `W(`DLEN)     __amc_data_in,
  input  wire `W($clog2(`AXI_AWLEN)) __amc_data_in_index,
  input  wire               __amc_data_in_last,
  input  wire               __amc_data_in_valid,
  input  wire `W(`DLEN)     __amc_data_out,
  input  wire `W($clog2(`AXI_AWLEN)) __amc_data_out_index,
  input  wire               __amc_data_out_valid,
  input  wire               __amc_data_out_last,
  input  wire               __amc_busy,
  input  wire               __amc_err
);

  reg [2:0] state;
  localparam IDLE     = 3'h0;
  localparam DIRTYBUF = 3'h1;
  localparam DIRTY    = 3'h2;
  localparam LOAD     = 3'h4;

  wire en = mem_read | mem_write;
  reg `W(`ADDRLEN) evict_addr;

  wire cache_dirty, cache_hit;
  reg cache_mem_read, cache_mem_write, cache_entry;
  reg `W(`ADDRLEN) cache_addr;
  wire `W(`ADDRLEN) cache_evict_addr;
  reg `W(`DLEN) cache_data_in;
  reg `W(`BWLEN) cache_bw;

  wire cache_last_entry = __amc_data_out_last;

  always @(*) begin
    cache_addr = addr;
    cache_mem_read = 0;
    cache_mem_write = 0;
    cache_data_in = data_in;
    cache_entry = 0;
    cache_bw = bw;

    case(state)
      IDLE : begin
        cache_addr = addr;
        cache_mem_read  = mem_read;
        cache_mem_write = mem_write;
        cache_data_in = data_in;
        cache_entry = 0;
        cache_bw = bw;
      end
      DIRTYBUF: begin
        cache_addr = evict_addr;
        cache_mem_read = 1;
        cache_mem_write = 0;
        cache_entry = 0;
      end
      DIRTY: begin
        cache_addr = `CACHE_LINE(evict_addr) + ($unsigned(__amc_data_in_index + (__amc_data_in_valid)) << $clog2(`DLEN/`BYTE));
        cache_mem_read  = !__amc_data_in_last;
        cache_mem_write = 0;
        cache_data_in = data_in; // doesnt matter 
        cache_entry = 0;
        cache_bw = `BW_DBLWORD;
      end
      LOAD : begin
        cache_addr = `CACHE_LINE(addr) + ($unsigned(__amc_data_out_index) << $clog2(`DLEN/`BYTE));
        cache_mem_read  = 0;
        cache_mem_write = __amc_data_out_valid;
        cache_data_in = __amc_data_out;
        cache_entry = 1;
        cache_bw = `BW_DBLWORD;
      end
      default: begin
        cache_addr = addr;
        cache_mem_read  = 0;
        cache_mem_write = 0;
        cache_data_in = data_in; 
        cache_entry = 0;
        cache_bw = bw;
      end
    endcase
  end

  wire `W(`DLEN) cache_data_out;

  reg hit_wait;
  assign busy = (state != IDLE) || (state == IDLE && en && (!cache_hit || !hit_wait));

  always @(posedge clk) begin
    if(rst) begin
      state <= IDLE;
      hit_wait <= 0;
    end
    else begin
      if (state == IDLE && en && cache_hit && !hit_wait) begin
        hit_wait <= 1;
      end else begin
        hit_wait <= 0;
      end

      case(state)
        IDLE: begin
          if(en && (!cache_hit)) begin
            if(cache_dirty) begin
              state <= DIRTYBUF;
              evict_addr <= cache_evict_addr;
            end
            else state <= LOAD;
          end
        end
        DIRTYBUF: state <= DIRTY;
        DIRTY: begin
          if(__amc_data_in_last) state <= LOAD;
        end
        LOAD: begin
          if(__amc_data_out_last) state <= IDLE;
        end
      endcase
    end
  end

  cache cache_instance (
    .clk(clk),
    .rst(rst),
    .entry(cache_entry),
    .addr(cache_addr),
    .mem_read(cache_mem_read),
    .mem_write(cache_mem_write),
    .bw(cache_bw),
    .data_in(cache_data_in),
    .data_out(cache_data_out),
    .dirty(cache_dirty),
    .last_entry(cache_last_entry),
    .evict_addr(cache_evict_addr),
    .hit(cache_hit)
  );

  assign __amc_addr = `CACHE_LINE((state == DIRTY) ? evict_addr : addr);
  assign __amc_mem_read = (state == LOAD);
  assign __amc_mem_write = (state == DIRTY);
  assign __amc_data_in = cache_data_out;
  assign data_out = cache_data_out;
endmodule

