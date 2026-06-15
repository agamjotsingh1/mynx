`include "defs.vh"
`include "modules/csrmap.v"

// TODO! implement WARL/WPRI functionality
module csrfile (
	input wire clk,
  input wire rst,
  input wor  hard_stall,
  input wor `W(`STLEN) stall,

	// standard read port
	input wire  `W(`CSRLEN) read_csr,
	output wire `W(`DLEN)   read_data,

  // satp read port (mmu -> pagetable ppn fetching)
  output wire `W(`DLEN)   satp,

	// standard write port
	input wire              write_en,
	input wire `W(`CSRLEN)  write_csr,
	input wire `W(`DLEN)    write_data,

  // trap handling ports
  input wire  `W(`TRAPMODELEN) trap_mode,
  output wire `W(`DLEN)        read_mip,
  output wire `W(`DLEN)        read_mstatus,
  output wire `W(`DLEN)        read_mie,
  output wire `W(`DLEN)        read_vec,
  output wire `W(`DLEN)        read_mideleg,
  output wire `W(`DLEN)        read_medeleg,
  input  wire `W(`DLEN)        write_mstatus,
  input  wire `W(`DLEN)        write_cause,
  input  wire `W(`DLEN)        write_epc
);
  wire `W(`CSRMAPLEN) read_csrmap, write_csrmap;
  wire is_trap_m = (trap_mode == `TRAPMODE_MINTR || trap_mode == `TRAPMODE_MXCEP);
  wire is_trap_s = (trap_mode == `TRAPMODE_SINTR || trap_mode == `TRAPMODE_SXCEP);

  // buffers to handle negedge/posedge mismatch
  reg `W(`TRAPMODELEN) trap_mode_buf;
  reg `W(`DLEN)        mstatus_buf;
  reg `W(`DLEN)        cause_buf;
  reg `W(`DLEN)        epc_buf;

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

  always @(posedge clk) begin
    if(!hard_stall) begin
      if(rst || (trap_mode == `TRAPMODE_NONE)) begin
        trap_mode_buf <= 0;
        mstatus_buf <= 0;
        cause_buf <= 0;
        epc_buf <= 0;
      end
      else begin
        trap_mode_buf <= trap_mode;
        mstatus_buf <= write_mstatus;
        cause_buf <= write_cause;
        epc_buf <= write_epc;
      end
    end
  end
	
	always @(negedge clk) begin
    if(!hard_stall) begin
      if(rst) begin
        for(i = 0; i < 2**(`CSRMAPLEN); i = i + 1) begin
          csr_array[i] <= 0;
        end
      end
      else if(trap_mode_buf != `TRAPMODE_NONE) begin
        csr_array[`CSRMAP_MSTATUS] <= mstatus_buf;

        if(is_trap_m) begin
          csr_array[`CSRMAP_MCAUSE] <= cause_buf;
          csr_array[`CSRMAP_MEPC]   <= epc_buf;
        end
        else if(is_trap_s) begin
          csr_array[`CSRMAP_SCAUSE] <= cause_buf;
          csr_array[`CSRMAP_SEPC]   <= epc_buf;
        end
      end
      /* verilator lint_off WIDTHTRUNC */
      else if(write_en && (!(stall & `STALL_CSRFILE))) begin
      /* verilator lint_on WIDTHTRUNC */
        csr_array[write_csrmap] <= write_data;
      end
    end
	end

	assign read_data    = csr_array[read_csrmap];
  assign satp         = csr_array[`CSRMAP_SATP];
  assign read_mip     = csr_array[`CSRMAP_MIP];
  assign read_mstatus = csr_array[`CSRMAP_MSTATUS];
  assign read_mie     = csr_array[`CSRMAP_MIE];
  assign read_vec     = is_trap_m ? csr_array[`CSRMAP_MTVEC]: csr_array[`CSRMAP_STVEC];
  assign read_mideleg = csr_array[`CSRMAP_MIDELEG];
  assign read_medeleg = csr_array[`CSRMAP_MEDELEG];
endmodule
