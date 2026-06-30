`include "defs.vh"

// TODO make bram pipelined, at the expense of 1 clock cycle for first access
// one cycle delay for both write and read
module cache (
  input wire clk,

  // only make entry whenever you miss and have to look in the memory
  input wire entry,
  input wire last_entry, // last entry into cache

  // flushing
  input wire flush,
  input wire last_flush, // last flush (to clear dirty)

  // mem ports
  input wire  `W(`ADDRLEN)  addr,
  input wire                mem_read,
  input wire                mem_write,
  input wire                sign_extend,
  input wire  `W(`BWLEN)    bw,
  input wire  `W(`DLEN)     data_in,
  output reg  `W(`DLEN)     data_out,

  output wire hit,
  output wire dirty,
  output wire  `W(`ADDRLEN) evict_addr,

  output wire line_spill,
  output wire spill_hit,
  output wire spill_dirty,
  output wire  `W(`ADDRLEN) spill_evict_addr
);
  // Note: BRAMs have one cycle delay
  // BRAM quirks
  // 64 bit/8 byte addressable
  // 1 cycle delay for both r/w

  // use distributed ram for large metadata info
  // and comparison of tag bits is faster due to silicon muxes
  // distributed ram only has one write port
  // so even/odd split is done
  (* ram_style = "distributed" *) reg `W(`CACHE_METALEN) meta_even [0:(`CACHE_DEPTH/2)-1];
  (* ram_style = "distributed" *) reg `W(`CACHE_METALEN) meta_odd  [0:(`CACHE_DEPTH/2)-1];

  // **synthesizable** initial block because of distributed ram blocks
  integer i;
  initial begin
    for(i = 0; i < (`CACHE_DEPTH/2); i = i + 1) begin
      meta_odd[i] = 0;
      meta_even[i] = 0;
    end
  end

  wire actual_flush;

  /* --- write enable (we) logic --- */
  // here bram A port is the start, bram B port is the spillover (if happens)
  reg `W(`BRAM_WELEN) __bram_we;
  reg `W(`BRAM_WELEN) __bram_wea, __bram_web;

  wire `W($clog2(`BRAM_DATA_BYTELEN)) shift_off_a =
    addr[0 +: $clog2(`BRAM_DATA_BYTELEN)];

  wire `W($clog2(`BRAM_DATA_BYTELEN) + 1) shift_off_b =
    (`BRAM_DATA_BYTELEN - shift_off_a);

  always @(*) begin
    __bram_we  = `BRAM_WE_NONE;
    __bram_wea = `BRAM_WE_NONE;
    __bram_web = `BRAM_WE_NONE;

    case(bw)
      `BW_BYTE    : __bram_we = `BRAM_WE_BYTE;
      `BW_HALFWORD: __bram_we = `BRAM_WE_HALFWORD;
      `BW_WORD    : __bram_we = `BRAM_WE_WORD;
      `BW_DBLWORD : __bram_we = `BRAM_WE_DBLWORD;
      default     : __bram_we = `BRAM_WE_NONE;
    endcase

    if(actual_flush) begin
      __bram_wea = `BRAM_WE_NONE;
      __bram_web = `BRAM_WE_NONE;
    end
    else if(entry) begin
      // whenever entry is happening, you never touch BRAM port B
      __bram_wea = mem_read ? `BRAM_WE_NONE: `BRAM_WE_DBLWORD;
      __bram_web = `BRAM_WE_NONE;
    end
    else if(hit && mem_write) begin
      __bram_wea = __bram_we << shift_off_a;
      __bram_web = __bram_we >> shift_off_b;
    end
  end 
  /* ------------------------------ */

  wire `W(`CACHE_TAGLEN) tag = `CACHE_TAG(addr); 
  wire `W(`CACHE_INDEXLEN) index = `CACHE_INDEX(addr); 
  wire `W(`CACHE_OFFLEN) off = `CACHE_OFF(addr); 

  wire `W(`CACHE_INDEXLEN-1) index_top = index[`CACHE_INDEXLEN-1 : 1];
  wire `W(`CACHE_METALEN) meta_primary = index[0] ? meta_odd[index_top]: meta_even[index_top];

  assign hit =
    (`CACHE_META_TAG(meta_primary) == `CACHE_TAG(addr)) &&
    `CACHE_META_VALID(meta_primary) &&
    (~entry);

  assign dirty =
    `CACHE_META_DIRTY(meta_primary) &&
    `CACHE_META_VALID(meta_primary);

  assign actual_flush = flush && dirty;

  // evict addr is normal (non 64 bit aligned)
  assign evict_addr =
    {`CACHE_META_TAG(meta_primary), index, {`CACHE_OFFLEN{1'b0}}};

  /* --- spill logic --- */
  wire __bram_spill = ((__bram_we >> shift_off_b) != `BRAM_WE_NONE);

  // line spillover happens if bram spills and
  // if the bram spill happens when off (except the shift_off part) is all ones (max)
  assign line_spill   = __bram_spill && (&off[(`CACHE_OFFLEN-1):$clog2(`BRAM_DATA_BYTELEN)]);

  // this may wrap around
  wire `W(`CACHE_INDEXLEN) spill_index = (index + $unsigned(line_spill));
  wire `W(`CACHE_TAGLEN)   spill_tag   = (tag + $unsigned((&index) & line_spill));

  wire `W(`CACHE_INDEXLEN-1) spill_index_top = spill_index[`CACHE_INDEXLEN-1 : 1];
  wire `W(`CACHE_METALEN) meta_spill = spill_index[0] ? meta_odd[spill_index_top]: meta_even[spill_index_top];

  assign spill_hit =
    (`CACHE_META_TAG(meta_spill) == spill_tag) &&
    `CACHE_META_VALID(meta_spill) &&
    (~entry) && (~actual_flush);

  assign spill_dirty =
    `CACHE_META_DIRTY(meta_spill) &&
    `CACHE_META_VALID(meta_spill) &&
    (~entry) && (~actual_flush);

  assign spill_evict_addr =
    {`CACHE_META_TAG(meta_spill), spill_index, {`CACHE_OFFLEN{1'b0}}};
  /* ------------------- */

  /* --- BRAM ports --- */
  wire __bram_ena = (hit | entry | actual_flush) && (mem_read | mem_write);
  wire __bram_enb = (spill_hit && __bram_spill) && (mem_read | mem_write);

  wire `W(`BRAM_ADDRLEN) __bram_addra = $unsigned({index, `CACHE_OFF(addr)}) >> $clog2(`BRAM_DATA_BYTELEN);
  wire `W(`BRAM_ADDRLEN) __bram_addrb = __bram_addra + 1;

  wire `W(`DLEN) data_shift_off_a =
    $unsigned(shift_off_a) << $clog2(`BYTE);

  wire `W(`DLEN) data_shift_off_b =
    $unsigned(shift_off_b) << $clog2(`BYTE);

  wire `W(`BRAM_DLEN) __bram_dina  = (entry | actual_flush) ? data_in: data_in << data_shift_off_a;
  wire `W(`BRAM_DLEN) __bram_dinb  = data_in >> data_shift_off_b;
  wire `W(`BRAM_DLEN) __bram_douta, __bram_doutb;
  /* ----------------- */


  /* --- BRAM output stitching --- */
  wire `W(`DLEN) shifted_data_out_b = (data_shift_off_b >= `DLEN) ? {`DLEN{1'b0}} : (__bram_doutb << data_shift_off_b);

  wire `W(`DLEN) data_out_rotated =
    (__bram_douta >> data_shift_off_a) | shifted_data_out_b;

  always @(*) begin
    case(bw)
      `BW_BYTE:
        data_out = {{(`DLEN - `BYTE){sign_extend ? data_out_rotated[`BYTE-1]: 1'b0}}, data_out_rotated[0 +: `BYTE]};
      `BW_HALFWORD:
        data_out = {{(`DLEN - `HALFWORD){sign_extend ? data_out_rotated[`HALFWORD-1]: 1'b0}}, data_out_rotated[0 +: `HALFWORD]};
      `BW_WORD:
        data_out = {{(`DLEN - `WORD){sign_extend ? data_out_rotated[`WORD-1]: 1'b0}}, data_out_rotated[0 +: `WORD]};
      `BW_DBLWORD:
        data_out = {{(`DLEN - `DBLWORD){sign_extend ? data_out_rotated[`DBLWORD-1]: 1'b0}}, data_out_rotated[0 +: `DBLWORD]};
      default:
        data_out = 0;
    endcase
  end
  /* ----------------------------- */

  reg meta_even_we;
  reg `W(`CACHE_INDEXLEN-1) meta_even_waddr;
  reg `W(`CACHE_METALEN) meta_even_wdata;

  reg meta_odd_we;
  reg `W(`CACHE_INDEXLEN-1) meta_odd_waddr;
  reg `W(`CACHE_METALEN) meta_odd_wdata;

  // TODO improve this by adding macros for meta valid, dirty and tag
  always @(*) begin
    meta_even_we = 1'b0;
    meta_even_waddr = 0;
    meta_even_wdata = 0;

    meta_odd_we = 1'b0;
    meta_odd_waddr = 0;
    meta_odd_wdata = 0;

    if(actual_flush && last_flush) begin
      if(index[0]) begin
        meta_odd_we = 1'b1;
        meta_odd_waddr = index_top;
        meta_odd_wdata = {1'b0, 1'b0, tag};
      end else begin
        meta_even_we = 1'b1;
        meta_even_waddr = index_top;
        meta_even_wdata = {1'b0, 1'b0, tag};
      end
    end
    else if(entry && last_entry) begin
      if(index[0]) begin
        meta_odd_we = 1'b1;
        meta_odd_waddr = index_top;
        meta_odd_wdata = {1'b1, 1'b0, tag};
      end else begin
        meta_even_we = 1'b1;
        meta_even_waddr = index_top;
        meta_even_wdata = {1'b1, 1'b0, tag};
      end
    end
    else if(mem_write) begin
      if(hit) begin
        if(index[0]) begin
          meta_odd_we = 1'b1;
          meta_odd_waddr = index_top;
          meta_odd_wdata = {1'b1, 1'b1, tag};
        end else begin
          meta_even_we = 1'b1;
          meta_even_waddr = index_top;
          meta_even_wdata = {1'b1, 1'b1, tag};
        end
      end

      if(spill_hit && line_spill) begin
        if(spill_index[0]) begin
          meta_odd_we = 1'b1;
          meta_odd_waddr = spill_index_top;
          meta_odd_wdata = {1'b1, 1'b1, spill_tag};
        end else begin
          meta_even_we = 1'b1;
          meta_even_waddr = spill_index_top;
          meta_even_wdata = {1'b1, 1'b1, spill_tag};
        end
      end
    end
  end

  always @(posedge clk) begin
    if (meta_odd_we) begin
      meta_odd[meta_odd_waddr] <= meta_odd_wdata;
    end
    if (meta_even_we) begin
      meta_even[meta_even_waddr] <= meta_even_wdata;
    end
  end

  // // slices are not assigned because of distributed ram not being inferred
  // always @(posedge clk) begin
  //   // outer module is supposed to handle evictions and dirty block writing
  //   if(entry && last_entry) begin
  //     if(index[0]) begin
  //       // valid, not dirty
  //       meta_odd[index_top] <= {1'b1, 1'b0, tag};
  //     end
  //     else begin
  //       // valid, not dirty
  //       meta_even[index_top] <= {1'b1, 1'b0, tag};
  //     end
  //   end
  //   else if(mem_write) begin
  //     if(hit) begin
  //       if(index[0])
  //         // valid, dirty
  //         meta_odd[index_top] <= {1'b1, 1'b1, tag};
  //       else
  //         // valid, dirty
  //         meta_even[index_top] <= {1'b1, 1'b1, tag};
  //     end

  //     if(spill_hit && line_spill) begin
  //       if(spill_index[0])
  //         // valid, dirty
  //         meta_odd[spill_index_top] <= {1'b1, 1'b1, spill_tag};
  //       else
  //         // valid, dirty
  //         meta_even[spill_index_top] <= {1'b1, 1'b1, spill_tag};
  //     end
  //   end
  // end

  cache_bram cache_bram_instance (
    // port a
    .clka(clk),
    .addra(__bram_addra),
    .dina(__bram_dina),
    .douta(__bram_douta),
    .ena(__bram_ena),
    .wea(__bram_wea),

    // port b
    .clkb(clk),
    .addrb(__bram_addrb),
    .dinb(__bram_dinb),
    .doutb(__bram_doutb),
    .enb(__bram_enb),
    .web(__bram_web)
  );
endmodule

