`include "defs.vh"

// SIMULATION ONLY
// zero cycle delay, true dual port
// results in no pipeline stalls
// write priority for collision: c > b > a
module mem_bank (
  input wire clk,

  // Port A
  input wire `W(`BANK_ADDRLEN)  addr_a,
  input wire                    mem_read_a,
  input wire                    mem_write_a,
  input wire `W(`BANKLEN)       data_in_a,
  output reg `W(`BANKLEN)       data_out_a,

  // Port B
  input wire `W(`BANK_ADDRLEN)  addr_b,
  input wire                    mem_read_b,
  input wire                    mem_write_b,
  input wire `W(`BANKLEN)       data_in_b,
  output reg `W(`BANKLEN)       data_out_b,

  // Port C
  input wire `W(`BANK_ADDRLEN)  addr_c,
  input wire                    mem_read_c,
  input wire                    mem_write_c,
  input wire `W(`BANKLEN)       data_in_c,
  output reg `W(`BANKLEN)       data_out_c
);
  reg `W(`BANKLEN) bank [0:`DEPTH-1] /* verilator public */;
    
  always @(*) begin
    // port a read
    if (mem_read_a)
      data_out_a = bank[addr_a];
    else
      data_out_a = 0;
      
    // port b read
    if (mem_read_b)
      data_out_b = bank[addr_b];
    else
      data_out_b = 0;

    // port c read
    if (mem_read_c)
      data_out_c = bank[addr_c];
    else
      data_out_c = 0;
  end

  always @(posedge clk) begin
    // port c write
    if(mem_write_c) begin
      bank[addr_c] <= data_in_c;
    end

    // port b write
    if (mem_write_b && !(addr_b == addr_c && mem_write_c)) begin
      bank[addr_b] <= data_in_b;
    end

    // port a write
    if (
      mem_write_a &&
      !(addr_a == addr_c && mem_write_c) &&
      !(addr_a == addr_b && mem_write_b)
    ) begin
      bank[addr_a] <= data_in_a;
    end
  end
endmodule
