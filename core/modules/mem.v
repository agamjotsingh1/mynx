// SIMULATION ONLY
// 2 port memory
// dynamic interleaved design
// supports parallel access different bit widths
module mem (
  input wire clk,

  // Port A
  input wire  `W(`ADDRLEN)  addr_a,
  input wire                mem_read_a,
  input wire                mem_write_a,
  input wire                sign_extend_a,
  input wire  `W(`BWLEN)    bw_a,
  input wire  `W(`DLEN)     data_in_a,
  output reg  `W(`DLEN)     data_out_a,

  // Port B
  input wire  `W(`ADDRLEN)  addr_b,
  input wire                mem_read_b,
  input wire                mem_write_b,
  input wire                sign_extend_b,
  input wire  `W(`BWLEN)    bw_b,
  input wire  `W(`DLEN)     data_in_b,
  output reg  `W(`DLEN)     data_out_b,

  // DMA access for disk operations
  // address must be 64 bit aligned
  input wire dma_write_en,
  input wire dma_read_en,
  input wire `W(`DLEN) dma_addr,
  input wire `W(`DLEN) dma_write_data,
  output wire `W(`DLEN) dma_read_data
);
  // --- PORT A ---
  wire `W($clog2(`NBANKS)) start_bank_a    = addr_a[0 +: $clog2(`NBANKS)];
  wire `W(`BANK_ADDRLEN) start_bank_addr_a = addr_a[$clog2(`NBANKS) +: `BANK_ADDRLEN];

  reg `W(`NBANKS) bank_enmask_unrotated_a;

  always @(*) begin
    case (bw_a)
      `BW_BYTE:     bank_enmask_unrotated_a = `BW_BYTE_ENMASK;
      `BW_HALFWORD: bank_enmask_unrotated_a = `BW_HALFWORD_ENMASK;
      `BW_WORD:     bank_enmask_unrotated_a = `BW_WORD_ENMASK;
      `BW_DBLWORD:  bank_enmask_unrotated_a = `BW_DBLWORD_ENMASK;
      default:      bank_enmask_unrotated_a = `BW_NULL_ENMASK;
    endcase
  end

  // circular left shift to find actual enables
  // may spill over to the next bank addr
  wire `W(`NBANKS) bank_enmask_a =
    (bank_enmask_unrotated_a << start_bank_a) |
    (bank_enmask_unrotated_a >> (`NBANKS - start_bank_a));

  // pad to integer to avoid length infers
  wire `W(`DLEN) data_in_rotated_a =
    (data_in_a << ({32'd0, start_bank_a} << $clog2(`BANKLEN))) |
    (data_in_a >> ((`NBANKS - {32'd0, start_bank_a}) << $clog2(`BANKLEN)));

  wire `W(`DLEN) data_out_rotated_a;
  wire `W(`DLEN) data_out_unrotated_a;

  // circular right shift to get unrotated (actual) data out
  assign data_out_unrotated_a =
    (data_out_rotated_a >> ({32'd0, start_bank_a} << $clog2(`BANKLEN))) |
    (data_out_rotated_a << ((`NBANKS - {32'd0, start_bank_a}) << $clog2(`BANKLEN)));

  always @(*) begin
    case(bw_a)
      `BW_BYTE:     data_out_a = {{(`DLEN - `BYTE){sign_extend_a ? data_out_unrotated_a[`BYTE-1]: 1'b0}}, data_out_unrotated_a[0 +: `BYTE]};
      `BW_HALFWORD: data_out_a = {{(`DLEN - `HALFWORD){sign_extend_a ? data_out_unrotated_a[`HALFWORD-1]: 1'b0}}, data_out_unrotated_a[0 +: `HALFWORD]};
      `BW_WORD:     data_out_a = {{(`DLEN - `WORD){sign_extend_a ? data_out_unrotated_a[`WORD-1]: 1'b0}}, data_out_unrotated_a[0 +: `WORD]};
      `BW_DBLWORD:  data_out_a = {{(`DLEN - `DBLWORD){sign_extend_a ? data_out_unrotated_a[`DBLWORD-1]: 1'b0}}, data_out_unrotated_a[0 +: `DBLWORD]};
      default:      data_out_a = 0;
    endcase
  end
  // --------------

  // --- PORT B ---
  wire `W($clog2(`NBANKS)) start_bank_b    = addr_b[0 +: $clog2(`NBANKS)];
  wire `W(`BANK_ADDRLEN) start_bank_addr_b = addr_b[$clog2(`NBANKS) +: `BANK_ADDRLEN];

  reg `W(`NBANKS) bank_enmask_unrotated_b;

  always @(*) begin
    case (bw_b)
      `BW_BYTE:     bank_enmask_unrotated_b = `BW_BYTE_ENMASK;
      `BW_HALFWORD: bank_enmask_unrotated_b = `BW_HALFWORD_ENMASK;
      `BW_WORD:     bank_enmask_unrotated_b = `BW_WORD_ENMASK;
      `BW_DBLWORD:  bank_enmask_unrotated_b = `BW_DBLWORD_ENMASK;
      default:      bank_enmask_unrotated_b = `BW_NULL_ENMASK;
    endcase
  end

  // circular left shift to find actual enables
  // may spill over to the next bank addr
  wire `W(`NBANKS) bank_enmask_b =
    (bank_enmask_unrotated_b << start_bank_b) |
    (bank_enmask_unrotated_b >> (`NBANKS - start_bank_b));

  // pad to integer to avoid length infers
  wire `W(`DLEN) data_in_rotated_b =
    (data_in_b << ({32'd0, start_bank_b} << $clog2(`BANKLEN))) |
    (data_in_b >> ((`NBANKS - {32'd0, start_bank_b}) << $clog2(`BANKLEN)));

  wire `W(`DLEN) data_out_rotated_b;
  wire `W(`DLEN) data_out_unrotated_b;

  // circular right shift to get unrotated (actual) data out
  assign data_out_unrotated_b =
    (data_out_rotated_b >> ({32'd0, start_bank_b} << $clog2(`BANKLEN))) |
    (data_out_rotated_b << ((`NBANKS - {32'd0, start_bank_b}) << $clog2(`BANKLEN)));

  always @(*) begin
    case(bw_b)
      `BW_BYTE:     data_out_b = {{(`DLEN - `BYTE){sign_extend_b ? data_out_unrotated_b[`BYTE-1]: 1'b0}}, data_out_unrotated_b[0 +: `BYTE]};
      `BW_HALFWORD: data_out_b = {{(`DLEN - `HALFWORD){sign_extend_b ? data_out_unrotated_b[`HALFWORD-1]: 1'b0}}, data_out_unrotated_b[0 +: `HALFWORD]};
      `BW_WORD:     data_out_b = {{(`DLEN - `WORD){sign_extend_b ? data_out_unrotated_b[`WORD-1]: 1'b0}}, data_out_unrotated_b[0 +: `WORD]};
      `BW_DBLWORD:  data_out_b = {{(`DLEN - `DBLWORD){sign_extend_b ? data_out_unrotated_b[`DBLWORD-1]: 1'b0}}, data_out_unrotated_b[0 +: `DBLWORD]};
      default:      data_out_b = 0;
    endcase
  end
  // --------------

  genvar i;
  generate
    for(i = 0; i < `NBANKS; i = i + 1) begin: mem_banks
      mem_bank mem_bank_instance (
        .clk(clk),

        // PORT A
        .addr_a(start_bank_addr_a + (i < start_bank_a)),
        .mem_read_a(bank_enmask_a[i] & mem_read_a),
        .mem_write_a(bank_enmask_a[i] & mem_write_a),
        .data_in_a(data_in_rotated_a[(i << $clog2(`BANKLEN)) +: `BANKLEN]),
        .data_out_a(data_out_rotated_a[(i << $clog2(`BANKLEN)) +: `BANKLEN]),

        // PORT B
        .addr_b(start_bank_addr_b + (i < start_bank_b)),
        .mem_read_b(bank_enmask_b[i] & mem_read_b),
        .mem_write_b(bank_enmask_b[i] & mem_write_b),
        .data_in_b(data_in_rotated_b[(i << $clog2(`BANKLEN)) +: `BANKLEN]),
        .data_out_b(data_out_rotated_b[(i << $clog2(`BANKLEN)) +: `BANKLEN]),

        // PORT C
        /* verilator lint_off WIDTHTRUNC */
        .addr_c(dma_addr >> $clog2(`BYTE)),
        /* verilator lint_on WIDTHTRUNC */
        .mem_read_c(dma_read_en),
        .mem_write_c(dma_write_en),
        .data_in_c(dma_write_data[(i << $clog2(`BANKLEN)) +: `BANKLEN]),
        .data_out_c(dma_read_data[(i << $clog2(`BANKLEN)) +: `BANKLEN])
      );
    end
  endgenerate
endmodule
