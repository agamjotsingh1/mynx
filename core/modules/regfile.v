`include "defs.vh"

module regfile (
  output wor `W(`STLEN) stall,

	input wire clk,
  input wire rst,

	// read port #1
	input wire `W(`RLEN)  read_addr1,
	output wire `W(`DLEN) read_data1,

	// read port #2
	input wire `W(`RLEN)  read_addr2,
	output wire `W(`DLEN) read_data2,

	// write port
	input wire            write_en,
	input wire `W(`RLEN)  write_addr,
	input wire `W(`DLEN)  write_data
);
  assign stall = `STALL_NONE;

	// 32 registers are x0, x1, x2 ... x31
  integer i;
	reg `W(`DLEN) reg_array [(2**(`RLEN)- 1):0];
	
	always @(negedge clk) begin
    if(rst) begin
      for(i = 0; i < 2**(`RLEN); i = i + 1) begin
        reg_array[i] <= 0;
      end
    end
    // dont write if write_en is low
    // or if writing to x0 (always 0)
    else if(write_en & write_addr != 0) begin
      reg_array[write_addr] <= write_data;
    end
	end

	assign read_data1 = reg_array[read_addr1];
	assign read_data2 = reg_array[read_addr2];
endmodule
