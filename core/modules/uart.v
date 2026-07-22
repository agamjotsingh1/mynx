`include "defs.vh"

// mocks uart 16650 hardware
// registers are byte sized
// DALB is not enabled
// reference: http://byterunner.com/16550.html
// TODO! enable fifo triggers (set to default 1)
module uart (
  input wire clk,
  input wire rst,
  input wire read_en,
  input wire write_en,
  
  input wire `W(`UART_ADDRLEN)  addr, 
  input wire `W(`BYTE)          write_data,     
  output reg `W(`BYTE)          read_data,

  output wire irq,

  // tx, goes to disp driver
  output wire           tx_valid,
  input  wire           tx_ready,
  output wire `W(`BYTE) tx_data,

  input wire           rx_valid,
  input wire `W(`BYTE) rx_data
);
  // write mode regs
  /* verilator lint_off UNUSEDSIGNAL */
  reg `W(`BYTE) ier;
  reg `W(`BYTE) fcr;
  /* verilator lint_on UNUSEDSIGNAL */

  // read/write scratch
  reg `W(`BYTE) scr;

  // rx fifo
  wire `W(`BYTE) rhr;
  wire fifo_full;
  wire `W($clog2(`UART_FIFOLEN) + 1) fifo_bufcount;

  reg rx_valid_latched;

  always @(posedge clk) begin
    if(rst) rx_valid_latched <= 0;
    else if(!rx_valid && rx_valid_latched) rx_valid_latched <= 0;
    else if(rx_valid && !rx_valid_latched) rx_valid_latched <= 1;
  end

  // TODO make this fifo async with proper CDC guardrails
  wire rhr_read = read_en && (addr == `UART_READ_RHR);
  reg rhr_read_latched;
  always @(posedge clk) begin
    if(rst) rhr_read_latched <= 0;
    else rhr_read_latched <= rhr_read;
  end

  byte_fifo #(
    .N(`UART_FIFOLEN)
  ) byte_fifo_uart_rx_instance (
    .clk(clk),
    .rst(rst | (write_en && (addr == `UART_WRITE_FCR) && `UART_FCR_RST(write_data))),
    .en(`UART_FCR_EN(fcr)),
    .read_en(rhr_read && !rhr_read_latched),
    .write_en(rx_valid && !rx_valid_latched),
    .data_in(rx_data),
    .data_out(rhr),
    .full(fifo_full),
    .bufcount(fifo_bufcount)
  );

  // lsr fields
  wire data_ready = $unsigned(fifo_bufcount) > 0;
  wire thre = tx_ready; // always ready to send (transmit holding register empty)
  wire temt = tx_ready; // always done sending (transmitter empty)
  wire err_parity  = 0; // unimplemented
  wire err_framing = 0; // unimplemented
  wire break_intr  = 0; // unimplemented
  wire err_fifo    = 0; // no corrupted bits in fifo (ideal fifo)

  reg err_overrun;
  wire `W(`BYTE) lsr = {err_fifo, temt, thre, break_intr, err_framing, err_parity, err_overrun, data_ready};

  // ier/isr fields and interrupt raising
  wire rx_intr_en = `UART_IER_RX_INTR(ier);
  reg `W(`UART_INTRIDLEN) intrid;
  wire `W(`BYTE) isr = {{`UART_FCR_EN(fcr) ? 2'b11 : 2'b00}, 2'b11, intrid, ~irq};

  always @(*) begin
    intrid = 0;

    if(rx_intr_en && data_ready) begin
      intrid = `UART_INTRID_DATA_READY;
    end
  end

  assign tx_valid = (addr == `UART_WRITE_THR) && write_en;
  assign tx_data = write_data;

  always @(posedge clk) begin
    if (rst) begin
      ier <= 0;
      fcr <= 0;
      scr <= 0;
    end
    else if (write_en) begin
      // WRITE mode
      /* verilator lint_off CASEINCOMPLETE */
      case (addr)
        `UART_WRITE_IER: ier <= write_data;
        `UART_WRITE_FCR: fcr <= write_data & (~`UART_FCR_RSTMASK);
        `UART_WRITE_SCR: scr <= write_data;
      endcase
      /* verilator lint_on CASEINCOMPLETE */
    end

    if (rst) err_overrun <= 0;
    else if (fifo_full && rx_valid) err_overrun <= 1;
    else if (read_en && (addr == `UART_READ_LSR)) err_overrun <= 0;
  end

  assign irq = (rx_intr_en && data_ready);

  always @(*) begin
    read_data = 0;
    
    // READ mode
    if (read_en) begin
      /* verilator lint_off CASEINCOMPLETE */
      case (addr)
        `UART_READ_RHR: read_data = rhr;
        `UART_READ_ISR: read_data = isr;
        `UART_READ_LSR: read_data = lsr;
        `UART_READ_SCR: read_data = scr;
      endcase
      /* verilator lint_on CASEINCOMPLETE */
    end
  end
endmodule
