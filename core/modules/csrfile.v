`include "defs.vh"
`include "modules/csrmap.v"

// TODO! implement WARL/WPRI functionality
// TODO! implement CSR_WRITE in ctl_bus to make sure "phantom writes" dont occur, instructions like CSSRS x5, mstatus, x0 will not even try to write to mstatus

// CSR Fields
// 1. WARL -> Write Any, Read Legal
// ..Ignore all illegal writes, preserve the values in these fields
// ..but dont generate exceptions when software tries to write to them
// 2. WPRI -> Write Preserves, Read Ignores
// ..Writes are ignored, preserved for later use
// 3. WLRL -> Write Legal, Read Legal
// ..Software can write whatever it wants
// ..but its the job of software to ensure legality,
// ..hardware has nothing to do with this
module csrfile (
	input wire clk,
  input wire rst,
  input wor  hard_stall,
  input wor `W(`STLEN) stall,
  output reg illegal_csr,

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
  // CSRs
  reg `W(`DLEN) mstatus;
  reg `W(`DLEN) mepc;
  reg `W(`DLEN) mhartid;
  reg `W(`DLEN) medeleg;
  reg `W(`DLEN) mideleg;
  reg `W(`DLEN) mie;
  reg `W(`DLEN) mip;
  reg `W(`DLEN) mtvec;
  reg `W(`DLEN) mscratch;
  reg `W(`DLEN) mcause;
  reg `W(`DLEN) mtval;
  reg `W(`DLEN) sepc;
  reg `W(`DLEN) satp;
  reg `W(`DLEN) stvec;
  reg `W(`DLEN) sscratch;
  reg `W(`DLEN) scause;
  reg `W(`DLEN) stval;
  reg `W(`DLEN) sip;
  reg `W(`DLEN) pmpcfg0;
  reg `W(`DLEN) pmpaddr0;

  // buffers to handle negedge/posedge mismatch
  reg `W(`TRAPMODELEN) trap_mode_buf;
  reg `W(`DLEN)        mstatus_buf;
  reg `W(`DLEN)        cause_buf;
  reg `W(`DLEN)        epc_buf;
  
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

  wire is_trap_buf_m = (trap_mode_buf == `TRAPMODE_MINTR || trap_mode_buf == `TRAPMODE_MXCEP);
  wire is_trap_buf_s = (trap_mode_buf == `TRAPMODE_SINTR || trap_mode_buf == `TRAPMODE_SXCEP);

  wire is_trap_m = (trap_mode == `TRAPMODE_MINTR || trap_mode == `TRAPMODE_MXCEP);
  // wire is_trap_s = (trap_mode == `TRAPMODE_SINTR || trap_mode == `TRAPMODE_SXCEP);
	
	always @(negedge clk) begin
    if(!hard_stall) begin
      if(rst) begin
        mstatus <= `MSTATUS_RST;
        mepc <= `MEPC_RST;
        sepc <= `SEPC_RST;
        mhartid <= `MHARTID_RST;
        medeleg <= `MEDELEG_RST;
        mideleg <= `MIDELEG_RST;
        mie <= `MIE_RST;
      end
      else if(trap_mode_buf != `TRAPMODE_NONE) begin
        // trust all buffers
        // as hardware will write it
        mstatus  <= mstatus_buf;

        if(is_trap_buf_m) begin
          mcause <= cause_buf;
          mepc   <= epc_buf;
        end
        else if(is_trap_buf_s) begin
          scause <= cause_buf;
          sepc   <= epc_buf;
        end
      end
      /* verilator lint_off WIDTHTRUNC */
      else if(write_en && (!(stall & `STALL_CSRFILE))) begin
      /* verilator lint_on WIDTHTRUNC */
        case(write_csr)
          `CSR_MSTATUS: mstatus <= (write_data & `MSTATUS_MASK) | (mstatus & (~`MSTATUS_MASK));
          `CSR_SSTATUS: mstatus <= (write_data & `SSTATUS_MASK) | (mstatus & (~`SSTATUS_MASK));
          `CSR_MEPC   : mepc    <= (write_data & `MEPC_MASK)    | (mepc    & (~`MEPC_MASK));
          `CSR_SEPC   : sepc    <= (write_data & `SEPC_MASK)    | (sepc    & (~`SEPC_MASK));
          `CSR_MEDELEG: medeleg <= (write_data & `MEDELEG_MASK) | (medeleg & (~`MEDELEG_MASK));
          `CSR_MIDELEG: mideleg <= (write_data & `MIDELEG_MASK) | (mideleg & (~`MIDELEG_MASK));
          `CSR_MIE    : mie     <= (write_data & `MIE_MASK)     | (mie     & (~`MIE_MASK));
          `CSR_SIE    : mie     <= (write_data & `SIE_MASK)     | (mie     & (~`SIE_MASK));
        endcase
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
