`include "../defs.vh"

// SIMULATION ONLY
// one cycle delay, true dual port
// results in no pipeline stalls
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
  output reg `W(`BANKLEN)       data_out_b
);
  reg `W(`BANKLEN) bank [0:`DEPTH-1];
    
  always @(*) begin
    // Port A Read
    if (mem_read_a)
      data_out_a = bank[addr_a];
    else
      data_out_a = 0;
      
    // Port B Read
    if (mem_read_b)
      data_out_b = bank[addr_b];
    else
      data_out_b = 0;
  end

  always @(posedge clk) begin
    // Port A Write
    if (mem_write_a) begin
      bank[addr_a] <= data_in_a;
    end
    
    // Port B Write
    if (mem_write_b) begin
      bank[addr_b] <= data_in_b;
    end
  end
endmodule