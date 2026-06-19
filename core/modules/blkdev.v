// defined in verilator cpp code
import "DPI-C" context function longint host_disk_read_word (input int sector, input int word_offset);
import "DPI-C" context function void    host_disk_write_word(input int sector, input int word_offset, input longint data);

// SIMULATION ONLY
// mocks disk (block device)
module blkdev (
  input wire clk,
  input wire rst,

  // MMIO (core -> block dev)
  input wire mmio_write_en,
  input wire mmio_read_en,
  input wire `W(`DLEN) mmio_addr,
  input wire `W(`DLEN) mmio_write_data,
  output reg `W(`DLEN) mmio_read_data,

  // DMA (block dev -> mem)
  output reg dma_write_en,
  output reg dma_read_en,
  output reg `W(`DLEN) dma_addr,
  output reg `W(`DLEN) dma_write_data,
  input wire `W(`DLEN) dma_read_data,
  
  // interrupt request
  output reg irq
);
  // MMIO regs
  reg `W(`DLEN) sector;
  reg `W(`DLEN) mem_addr;
  reg `W(`DLEN) status;

  // DMA FSM
  localparam STATELEN = 3;
  reg `W(STATELEN) state;
  localparam STATE_IDLE          = 3'd0;
  localparam STATE_READ_DISK     = 3'd1; // disk -> mem
  localparam STATE_WRITE_RAM_REQ = 3'd2; // mem -> disk (req)
  localparam STATE_WRITE_RAM_ACK = 3'd3; // mem -> disk (ack and write)

  // counts 0 to 63 (64 words * 8 bytes = 512 bytes = 1 sector)
  reg `W($clog2(`SECTOR_WORDCOUNT) + 1) word_count;

  // MMIO read
  always @(*) begin
    case (mmio_addr)
      `BLKDEV_STATUS  : mmio_read_data = status;
      `BLKDEV_SECTOR  : mmio_read_data = sector;
      `BLKDEV_MEM_ADDR: mmio_read_data = mem_addr;
      default         : mmio_read_data = 0;
    endcase
  end

  always @(posedge clk) begin
    if (rst) begin
      sector <= 0;
      mem_addr <= 0;
      status <= 0;
      irq <= 0;
      dma_addr <= 0;
      dma_write_data <= 0;
      dma_write_en <= 0;
      dma_read_en <= 0;
      state <= STATE_IDLE;
      word_count <= 0;
    end else begin
      // clear interrupt on read
      if(irq && mmio_read_en && mmio_addr == `BLKDEV_STATUS) begin
        irq <= 0;
      end

      case(state)
        STATE_IDLE: begin
          dma_write_en <= 0;
          dma_read_en <= 0;
          
          if(mmio_write_en) begin
            case (mmio_addr)
              `BLKDEV_SECTOR  : sector   <= mmio_write_data;
              `BLKDEV_MEM_ADDR: mem_addr <= mmio_write_data;
              `BLKDEV_CMD: begin
                if(status == `BLKDEV_IDLE) begin
                  status <= `BLKDEV_BUSY;
                  word_count <= 0;
                  if(mmio_write_data == `BLKDEV_CMD_READ)
                    state <= STATE_READ_DISK;
                  if(mmio_write_data == `BLKDEV_CMD_WRITE)
                    state <= STATE_WRITE_RAM_REQ;
                end
              end
            endcase
          end
        end

        //  disk -> mem transfer
        STATE_READ_DISK: begin
          if(word_count < `SECTOR_WORDCOUNT) begin
            dma_write_en <= 1;
            dma_addr <= mem_addr + {word_count, 3'b000}; // word_count * 8 (64 bit write)
            // fetch (instant) the 64-bit word from cpp 
            // sector address -> word (4 bytes)
            dma_write_data <= host_disk_read_word(sector[`WORD-1:0], $unsigned(word_count));
            word_count <= word_count + 1;
          end else begin
            state <= STATE_IDLE;
            status <= `BLKDEV_IDLE;
            irq <= 1; // sector written => raise intr
            dma_write_en <= 0;
            word_count <= 0;
          end
        end

        // mem -> disk transfer (request)
        STATE_WRITE_RAM_REQ: begin
          if (word_count < `SECTOR_WORDCOUNT) begin
            dma_read_en <= 1;
            dma_addr <= mem_addr + {word_count, 3'b000};  // word_count * 8 (64 bit write)
            state <= STATE_WRITE_RAM_ACK;
          end else begin
            dma_read_en <= 0;
            irq <= 1; // done writing, raise interrupt
            state <= STATE_IDLE;
            status <= `BLKDEV_IDLE;
            word_count <= 0;
          end
        end

        // acknowledge the mem->disk transfer and write to disk
        STATE_WRITE_RAM_ACK: begin
          dma_read_en <= 0;
          // send the dma data out to the C++ testbench
          host_disk_write_word(sector[`WORD-1:0], $unsigned(word_count), dma_read_data);
          word_count <= word_count + 1;
          state <= STATE_WRITE_RAM_REQ;
        end
      endcase
    end
  end
endmodule
