`include "defs.vh"

// TODO make bram pipelined, at the expense of 1 clock cycle for first access
//
// FIXME support non aligned addresses
// one cycle delay for both write and read
// Interface:
//
module cache (
  input wire clk,
  input wire rst,

  // only make entry whenever you miss and have to look in the memory
  input wire entry,
  input wire last_entry,

  // mem ports
  input wire  `W(`ADDRLEN)  addr,
  input wire                mem_read,
  input wire                mem_write,
  input wire                sign_extend,
  input wire  `W(`BWLEN)    bw,
  input wire  `W(`DLEN)     data_in,
  output wire `W(`DLEN)     data_out,

  output wire hit,
  output wire dirty,
  output wire  `W(`ADDRLEN)  evict_addr,

  // BRAM ports
  output wire __bram_en,
  output wire `W(`BRAM_ADDRLEN) __bram_addr,
  output wire `W(`BRAM_DLEN)    __bram_din,
  input  wire `W(`BRAM_DLEN)    __bram_dout,
  output reg  `W(`BRAM_WEALEN)  __bram_wea
);
  // Note: BRAMs have one cycle delay
  // BRAM quirks
  // 64 bit/8 byte addressable
  // 1 cycle delay for both r/w

  // use distributed ram for large metadata info
  // and comparison of tag bits is faster due to silicon muxes
  (* ram_style = "distributed" *) reg `W(`CACHE_METALEN) meta [0:`CACHE_DEPTH-1];

  // synthesizable initial block because of distributed ram blocks
  integer i;
  initial begin
    for(i = 0; i < `CACHE_DEPTH; i = i + 1)
      meta[i] = 0;
  end

  /* --- write enable (we) logic --- */
  // here bram A port is the start, bram B port is the spillover (if happens)
  reg `W(`BRAM_WELEN) __bram_we;
  reg `W(`BRAM_WELEN) __bram_wea, __bram_web;

  wire `W($clog2(`BRAM_DATA_BYTELEN)) shift_off_a =
    addr[0 +: $clog2(`BRAM_DATA_BYTELEN)];

  wire `W($clog2(`BRAM_DATA_BYTELEN)) shift_off_b =
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

    if(entry && mem_write) begin
      // whenever entry is happening, you never touch BRAM port B
      __bram_wea = `BRAM_WEA_DBLWORD;
      __bram_web = `BRAM_WEA_NONE;
    end
    else if(hit && mem_write) begin
      __bram_wea = __bram_we >> shift_off_a;
      __bram_web = __bram_we << shift_off_b;
    end
    else __bram_wea = `BRAM_WEA_NONE;
  end 
  /* ------------------------------ */

  wire `W(`CACHE_TAGLEN) tag = `CACHE_TAG(addr); 
  wire `W(`CACHE_INDEXLEN) index = `CACHE_INDEX(addr); 
  wire `W(`CACHE_OFFLEN) off = `CACHE_OFF(addr); 

  wire hit =
    (`CACHE_META_TAG(meta[index]) == `CACHE_TAG(addr)) &&
    `CACHE_META_VALID(meta[index]) &&
    (~entry);

  wire dirty =
    `CACHE_META_DIRTY(meta[index]) &&
    `CACHE_META_VALID(meta[index]);

  // evict addr is normal (non 64 bit aligned)
  wire `W(`ADDRLEN) evict_addr =
    {`CACHE_META_TAG(meta[index]), index, {`CACHE_OFFLEN{1'b0}}};

  /* --- spill logic --- */
  wire __bram_spill = (__bram_web != `BRAM_WE_NONE);

  // line spillover happens if bram spills and
  // if the bram spill happens when off (except the shift_off part) is all ones (max)
  wire line_spill   = __bram_spill && (&off[(`CACHE_OFFLEN-1):$clog2(`BRAM_DATA_BYTELEN)]);

  // this may wrap around
  wire `W(`CACHE_INDEXLEN) spill_index = (index + 1);
  wire `W(`CACHE_TAGLEN)   spill_tag   = (&index) ? (tag + 1): tag;

  wire spill_hit =
    (`CACHE_META_TAG(meta[spill_index]) == spill_tag) &&
    `CACHE_META_VALID(meta[spill_index]) &&
    (~entry);

  wire spill_dirty =
    `CACHE_META_DIRTY(meta[spill_index]) &&
    `CACHE_META_VALID(meta[spill_index]);

  wire `W(`ADDRLEN) spill_evict_addr =
    {`CACHE_META_TAG(meta[spill_index]), spill_index, {`CACHE_OFFLEN{1'b0}}};
  /* ------------------- */

  /* --- BRAM ports --- */
  wire __bram_ena = (hit | entry) && (mem_read | mem_write);
  wire __bram_enb = (spill_hit) && (mem_read | mem_write);

  wire `W(BRAM_ADDRLEN) __bram_addra = $unsigned({index, `CACHE_OFF(addr)}) >> $clog2(`BRAM_DATA_BYTELEN);
  wire `W(BRAM_ADDRLEN) __bram_addrb = ($unsigned({spill_index, `CACHE_OFF(addr)}) >> $clog2(`BRAM_DATA_BYTELEN)) + 1;

  wire `W(`DLEN) data_shift_off_a =
    $unsigned(shift_off_a) << $clog2(`BYTE);

  wire `W(`DLEN) data_shift_off_b =
    $unsigned(shift_off_b) << $clog2(`BYTE);

  wire `W(`BRAM_DLEN) __bram_dina  = data_in >> data_shift_off_a;
  wire `W(`BRAM_DLEN) __bram_dinb  = data_in << data_shift_off_b;
  wire `W(`BRAM_DLEN) __bram_douta, __bram_doutb;
  /* ----------------- */


  /* --- BRAM output stitching --- */
  wire `W(`DLEN) data_out_rotated =
    (__bram_douta << data_shift_off_a) |
    (__bram_doutb >> data_shift_off_b);

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
      default:      data_out_a = 0;
    endcase
  end
  /* ----------------------------- */

  always @(posedge clk) begin
    if(entry && last_entry) begin
      `CACHE_META_VALID(meta[index]) <= 1;
      `CACHE_META_DIRTY(meta[index]) <= 0;
      `CACHE_META_TAG(meta[index])   <= `CACHE_TAG(addr);
    end
    else if(hit && mem_write) begin
      `CACHE_META_DIRTY(meta[index]) <= 1;
    end
  end

//   wire `W($clog2(`NBANKS)) start_bank_a    = addr_a[0 +: $clog2(`NBANKS)];
//   wire `W(`BANK_ADDRLEN) start_bank_addr_a = addr_a[$clog2(`NBANKS) +: `BANK_ADDRLEN];

//   reg `W(`NBANKS) bank_enmask_unrotated_a;

//   always @(*) begin
//     case (bw_a)
//       `BW_BYTE:     bank_enmask_unrotated_a = `BW_BYTE_ENMASK;
//       `BW_HALFWORD: bank_enmask_unrotated_a = `BW_HALFWORD_ENMASK;
//       `BW_WORD:     bank_enmask_unrotated_a = `BW_WORD_ENMASK;
//       `BW_DBLWORD:  bank_enmask_unrotated_a = `BW_DBLWORD_ENMASK;
//       default:      bank_enmask_unrotated_a = `BW_NULL_ENMASK;
//     endcase
//   end

//   // circular left shift to find actual enables
//   // may spill over to the next bank addr
//   wire `W(`NBANKS) bank_enmask_a =
//     (bank_enmask_unrotated_a << start_bank_a) |
//     (bank_enmask_unrotated_a >> (`NBANKS - start_bank_a));

//   // pad to integer to avoid length infers
//   wire `W(`DLEN) data_in_rotated_a =
//     (data_in_a << ({32'd0, start_bank_a} << $clog2(`BANKLEN))) |
//     (data_in_a >> ((`NBANKS - {32'd0, start_bank_a}) << $clog2(`BANKLEN)));

//   wire `W(`DLEN) data_out_rotated_a;
//   wire `W(`DLEN) data_out_unrotated_a;

//   // circular right shift to get unrotated (actual) data out
//   assign data_out_unrotated_a =
//     (data_out_rotated_a >> ({32'd0, start_bank_a} << $clog2(`BANKLEN))) |
//     (data_out_rotated_a << ((`NBANKS - {32'd0, start_bank_a}) << $clog2(`BANKLEN)));

//   always @(*) begin
//     case(bw_a)
//       `BW_BYTE:     data_out_a = {{(`DLEN - `BYTE){sign_extend_a ? data_out_unrotated_a[`BYTE-1]: 1'b0}}, data_out_unrotated_a[0 +: `BYTE]};
//       `BW_HALFWORD: data_out_a = {{(`DLEN - `HALFWORD){sign_extend_a ? data_out_unrotated_a[`HALFWORD-1]: 1'b0}}, data_out_unrotated_a[0 +: `HALFWORD]};
//       `BW_WORD:     data_out_a = {{(`DLEN - `WORD){sign_extend_a ? data_out_unrotated_a[`WORD-1]: 1'b0}}, data_out_unrotated_a[0 +: `WORD]};
//       `BW_DBLWORD:  data_out_a = {{(`DLEN - `DBLWORD){sign_extend_a ? data_out_unrotated_a[`DBLWORD-1]: 1'b0}}, data_out_unrotated_a[0 +: `DBLWORD]};
//       default:      data_out_a = 0;
//     endcase
//   end
//   // --------------

endmodule

