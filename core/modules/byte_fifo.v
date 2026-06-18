// standard Nx8 buffer
// N bytes with each element being 1 byte
// basically a ring buffer with r/w pointers
module byte_fifo #(
  // NOTE: N must be a power of 2
  parameter N = 16
) (
  input  wire  clk,
  input  wire  rst,
  input  wire  en, // when en is low it is basically a singular buffer
  input  wire  write_en,
  input  wire  read_en,

  input  wire `W(`BYTE) data_in,
  output wire `W(`BYTE) data_out,

  output wire  full,
  output wire `W($clog2(N) + 1) bufcount
);
  reg `W(`BYTE) buffer [0:N-1];

  // extra bit (MSB) for full/empty differentiation
  reg `W($clog2(N) + 1) write_ptr;
  reg `W($clog2(N) + 1) read_ptr;
  assign bufcount = write_ptr - read_ptr;

  assign full = en
    ? (write_ptr[$clog2(N)] != read_ptr[$clog2(N)]) &&
      (write_ptr[$clog2(N)-1:0] == read_ptr[$clog2(N)-1:0])
    : (bufcount == 1);

  wire empty = (write_ptr == read_ptr);

  always @(posedge clk) begin
    if (rst) begin
      write_ptr <= 0;
    end
    else if (write_en) begin
      buffer[write_ptr[$clog2(N)-1:0]] <= data_in;
      write_ptr <= write_ptr + 1;
    end
  end

  always @(posedge clk) begin
    if (rst) begin
      read_ptr <= 0;
    end
    else if (read_en && !empty) begin
      read_ptr <= read_ptr + 1;
    end
    else if (write_en && full) begin
      // overrun: fifo is full we are writing but not reading
      read_ptr <= read_ptr + 1;
    end
  end

  assign data_out = buffer[read_ptr[$clog2(N)-1:0]];
endmodule
