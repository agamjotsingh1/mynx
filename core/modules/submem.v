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
  localparam IDLE         = 3'h0;
  localparam DIRTY        = 3'h1; // dirty block with a miss => write to amc
  localparam DIRTY_SPILL  = 3'h2; // dirty spill block with a miss => write to amc
  localparam LOAD         = 3'h3; // load block from amc
  localparam LOAD_SPILL   = 3'h4; // load spill block from amc
  localparam AMC_WAIT     = 3'h5; // wait for the amc to completely finish pending txn

  wire en = (mem_read | mem_write);

  reg dirty, hit, spill_hit, spill_dirty, line_spill;
  reg `W(`ADDRLEN) evict_addr, spill_evict_addr;

  wire cache_dirty, cache_hit;
  reg cache_mem_read, cache_mem_write, cache_entry;
  reg `W(`ADDRLEN) cache_addr;
  wire `W(`ADDRLEN) cache_evict_addr;
  reg `W(`DLEN) cache_data_in;
  reg `W(`BWLEN) cache_bw;

  wire cache_miss = !cache_hit || !(cache_line_spill & cache_spill_hit);

  wire cache_last_entry = __amc_data_out_last;

  wire `W(`ADDRLEN) spill_addr = addr + (1 << `CACHE_OFFLEN);

  always @(*) begin
    cache_addr = addr;
    cache_mem_read = 0;
    cache_mem_write = 0;
    cache_data_in = data_in;
    cache_entry = 0;
    cache_bw = `BW_DBLWORD;

    // Note: AMC indexes are 64 bit addressable
    // in simple words, each index increment results in an 8 byte
    // actual address increment
    case(state)
      IDLE : begin
        cache_addr = addr;
        cache_mem_read  = mem_read & (~cache_miss);
        cache_mem_write = mem_write & (~cache_miss);
        cache_data_in = data_in;
        cache_entry = 0;
        cache_bw = bw;
      end
      // DIRTY and DIRTY_SPILL rely upon the fact that AMC takes
      // atleast 1 cycle for the AW TXN to complete
      // note: we have to prefetch cache addresses as bram takes one extra clock cycle
      DIRTY: begin
        cache_addr =
          `CACHE_LINE(evict_addr) +
          `AMC_INDEX2ADDR($unsigned(__amc_data_in_index + __amc_data_in_valid));

        cache_mem_read  = !__amc_data_in_last;
      end
      DIRTY_SPILL: begin
        cache_addr =
          `CACHE_LINE(spill_evict_addr) +
          `AMC_INDEX2ADDR($unsigned(__amc_data_in_index + __amc_data_in_valid));

        cache_mem_read  = !__amc_data_in_last;
      end
      LOAD: begin
        cache_addr =
          `CACHE_LINE(addr) +
          `AMC_INDEX2ADDR($unsigned(__amc_data_out_index));

        cache_mem_write = __amc_data_out_valid;
        cache_data_in = __amc_data_out;
        cache_entry = __amc_data_out_valid;
      end
      LOAD_SPILL: begin
        // TODO temporary patch, move into cache.v
        cache_addr =
          `CACHE_LINE(spill_addr) +
          `AMC_INDEX2ADDR($unsigned(__amc_data_out_index));

        cache_mem_write = __amc_data_out_valid;
        cache_data_in = __amc_data_out;
        cache_entry = __amc_data_out_valid;
      end
      default: begin
        // AMC_WAIT
        cache_addr = addr;
        cache_mem_read = 0;
        cache_mem_write = 0;
        cache_data_in = data_in;
        cache_entry = 0;
        cache_bw = `BW_DBLWORD;
      end
    endcase
  end

  wire `W(`DLEN) cache_data_out;

  always @(posedge clk) begin
    if(rst) begin
      state <= IDLE;
      busy <= 1;
    end
    else begin
      case(state)
        IDLE: begin
          if(en && busy) begin
            if(cache_miss) begin
              hit <= cache_hit;
              dirty <= cache_dirty;
              spill_hit <= cache_spill_hit;
              spill_dirty <= cache_spill_dirty;
              line_spill <= cache_line_spill;
              evict_addr <= cache_evict_addr;
              spill_evict_addr <= cache_spill_evict_addr;

              if(cache_dirty) state <= DIRTY;
              else if(cache_line_spill && cache_spill_dirty) state <= DIRTY_SPILL;
              else if(!cache_hit) state <= LOAD;
              else if(!(cache_line_spill & cache_spill_hit)) state <= LOAD_SPILL;
            end
            else busy <= 0;
          end
          else busy <= 1;
        end
        DIRTY: begin
          if(__amc_data_in_last) begin
            if(line_spill & spill_dirty) state <= DIRTY_SPILL;
            else state <= LOAD;
          end
        end
        DIRTY_SPILL: begin
          if(__amc_data_in_last) begin
            if(!hit) state <= LOAD;
            else if(!(line_spill & spill_hit)) state <= LOAD_SPILL;
          end
        end
        LOAD: begin
          if(__amc_data_out_last) begin
            if(!(line_spill & spill_hit)) state <= LOAD_SPILL;
            else state <= AMC_WAIT;
          end
        end
        LOAD_SPILL: begin
          if(__amc_data_out_last) state <= AMC_WAIT;
        end
        AMC_WAIT: begin
          if(!__amc_busy) state <= IDLE;
        end
      endcase
    end
  end

  cache cache_instance (
    .clk(clk),
    .entry(cache_entry),
    .last_entry(cache_last_entry),

    .addr(cache_addr),
    .mem_read(cache_mem_read),
    .mem_write(cache_mem_write),
    .sign_extend(sign_extend),
    .bw(cache_bw),
    .data_in(cache_data_in),
    .data_out(cache_data_out),

    .hit(cache_hit),
    .dirty(cache_dirty),
    .evict_addr(cache_evict_addr),
    .line_spill(cache_line_spill),
    .spill_hit(cache_spill_hit),
    .spill_dirty(cache_spill_dirty),
    .spill_evict_addr(cache_spill_evict_addr)
  );

  reg `W(`ADDRLEN) __amc_addr_unlined;

  always @(*) begin
    case(state)
      IDLE       : __amc_addr_unlined = addr;
      DIRTY      : __amc_addr_unlined = evict_addr;
      DIRTY_SPILL: __amc_addr_unlined = spill_evict_addr;
      LOAD       : __amc_addr_unlined = addr;
      LOAD_SPILL : __amc_addr_unlined = spill_addr;
      default    : __amc_addr_unlined = addr;
    endcase
  end

  assign __amc_addr = `CACHE_LINE(__amc_addr_unlined);
  assign __amc_mem_read = (state == LOAD) || (state == LOAD_SPILL);
  assign __amc_mem_write = (state == DIRTY) || (state == DIRTY_SPILL);
  assign __amc_data_in = cache_data_out;
  assign data_out = cache_data_out;
endmodule

