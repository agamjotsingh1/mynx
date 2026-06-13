`include "defs.vh"
`include "modules/csrmap.v"

module csrfile (
	input wire clk,
  input wire rst,

	// read port #1
	input wire `W(`CSRLEN)  read_csr,
	output wire `W(`DLEN)   read_data,

	// write port
	input wire              write_en,
	input wire `W(`CSRLEN)  write_csr,
	input wire `W(`DLEN)    write_data
);
  wire `W(`CSRMAPLEN) read_csrmap, write_csrmap;

  csrmap csrmap_read_instance (
    .csr(read_csr),
    .csrmap(read_csrmap)
  );

  csrmap csrmap_write_instance (
    .csr(write_csr),
    .csrmap(write_csrmap)
  );
  
  integer i;
	reg `W(`DLEN) csr_array [(2**(`CSRMAPLEN)- 1):0];
	
	always @(negedge clk) begin
    if(rst) begin
      for(i = 0; i < 2**(`CSRMAPLEN); i = i + 1) begin
        csr_array[i] <= 0;
      end
    end
    else if(write_en) begin
      csr_array[write_csrmap] <= write_data;
    end
	end

	assign read_data = csr_array[read_csrmap];
endmodule
