`include "defs.vh"

module clint (
  input wire clk,
  input wire rst,

  // MMIO 
  input wire mmio_write_en,
  /* verilator lint_off UNUSEDSIGNAL */
  input wire mmio_read_en,
  /* verilator lint_on UNUSEDSIGNAL */
  input wire `W(`DLEN) mmio_addr,
  input wire `W(`DLEN) mmio_write_data,
  output reg `W(`DLEN) mmio_read_data,

  output wire irq
);
  reg `W(`DLEN) mtime, mtimecmp;

  always @(posedge clk) begin
    if(rst) begin
      mtime <= 0;
      mtimecmp <= 0;
    end
    else begin
      if(mmio_write_en) begin
        /* verilator lint_off CASEINCOMPLETE */
        case(mmio_addr)
          `CLINT_MTIME   : mtime    <= mmio_write_data;
          `CLINT_MTIMECMP: mtimecmp <= mmio_write_data;
          default        : mtime    <= mtime + 1;
        endcase
        /* verilator lint_on CASEINCOMPLETE */
      end

      else mtime <= mtime + 1;
    end
  end

  always @(*) begin
    /* verilator lint_off CASEINCOMPLETE */
    case(mmio_addr)
      `CLINT_MTIME   : mmio_read_data = mtime;
      `CLINT_MTIMECMP: mmio_read_data = mtimecmp;
      default        : mmio_read_data = 0;
    endcase
    /* verilator lint_on CASEINCOMPLETE */
  end

  assign irq = (mtime >= mtimecmp) && (mtimecmp != 0);

  // always @(posedge clk) begin
  //   $display("%d", irq);
  // end
endmodule
