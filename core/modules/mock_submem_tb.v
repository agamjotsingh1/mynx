`include "defs.vh"

(* DONT_TOUCH = "yes" *)
module mock_submem_tb (
  input wire clk,
  input wire rst,

  output wire  `W(`ADDRLEN)             __amc_addr,
  output wire                           __amc_mem_read,
  output wire                           __amc_mem_write,
  output wire  `W(`DLEN)                __amc_data_in,
  input  wire `W($clog2(`AXI_AWLEN))    __amc_data_in_index,
  input  wire                           __amc_data_in_last,
  input  wire                           __amc_data_in_valid,
  input  wire `W(`DLEN)                 __amc_data_out,
  input  wire `W($clog2(`AXI_AWLEN))    __amc_data_out_index,
  input  wire                           __amc_data_out_valid,
  input  wire                           __amc_data_out_last,
  input  wire                           __amc_busy,
  input  wire                           __amc_err,

  output wire                           tb_done,
  output wire `W(`DLEN)                 tb_data_out
);

  reg  `W(`ADDRLEN)  mem_addr;
  reg                mem_read;
  reg                mem_write;
  reg                mem_sign_extend;
  reg  `W(`BWLEN)    mem_bw;
  reg  `W(`DLEN)     mem_data_in;
  wire `W(`DLEN)     mem_data_out;
  wire               mem_busy;

  assign tb_data_out = mem_data_out;

  submem uut (
    .clk(clk),
    .rst(rst),
    
    .addr(mem_addr),
    .mem_read(mem_read),
    .mem_write(mem_write),
    .sign_extend(mem_sign_extend),
    .bw(mem_bw),
    .data_in(mem_data_in),
    .data_out(mem_data_out),
    .busy(mem_busy),

    .__amc_addr(__amc_addr),
    .__amc_mem_read(__amc_mem_read),
    .__amc_mem_write(__amc_mem_write),
    .__amc_data_in(__amc_data_in),
    .__amc_data_in_index(__amc_data_in_index),
    .__amc_data_in_last(__amc_data_in_last),
    .__amc_data_in_valid(__amc_data_in_valid),
    .__amc_data_out(__amc_data_out),
    .__amc_data_out_index(__amc_data_out_index),
    .__amc_data_out_valid(__amc_data_out_valid),
    .__amc_data_out_last(__amc_data_out_last),
    .__amc_busy(__amc_busy),
    .__amc_err(__amc_err)
  );

  (* keep = "true" *) reg [2:0] state;
  (* keep = "true" *) reg [3:0] test_step;

  localparam S_INIT          = 3'd0;
  localparam S_SETUP_CMD     = 3'd1;
  localparam S_WAIT_COMPLETE = 3'd2;
  localparam S_WAIT_RECOVERY = 3'd3;
  localparam S_DONE          = 3'd4;

  localparam LINE_STRIDE = (1 << (`CACHE_OFFLEN + `CACHE_INDEXLEN));

  assign tb_done = (state == S_DONE);

  always @(posedge clk) begin
    if (rst) begin
      state           <= S_INIT;
      test_step       <= 4'd0;
      mem_addr        <= 0;
      mem_read        <= 1'b0;
      mem_write       <= 1'b0;
      mem_sign_extend <= 1'b0;
      mem_bw          <= `BW_DBLWORD; 
      mem_data_in     <= 0;
    end else begin
      case (state)
        S_INIT: begin
          if (mem_busy == 1'b1) begin
            state <= S_SETUP_CMD;
          end
        end

        S_SETUP_CMD: begin
          case (test_step)
            4'd0: begin
              mem_addr    <= 'h100;
              mem_write   <= 1'b1;
              mem_read    <= 1'b0;
              mem_bw      <= `BW_DBLWORD;
              mem_data_in <= 'hDEADBEEF;
            end
            4'd1: begin
              mem_addr    <= 'h100 + LINE_STRIDE;
              mem_write   <= 1'b1;
              mem_read    <= 1'b0;
              mem_bw      <= `BW_DBLWORD;
              mem_data_in <= 'hCAFEBABE;
            end
            4'd2: begin
              mem_addr    <= 'h100 + (2 * LINE_STRIDE);
              mem_write   <= 1'b1;
              mem_read    <= 1'b0;
              mem_bw      <= `BW_DBLWORD;
              mem_data_in <= 'hBEEFCAFE;
            end
            4'd3: begin
              mem_addr    <= 'h100 + (3 * LINE_STRIDE);
              mem_write   <= 1'b1;
              mem_read    <= 1'b0;
              mem_bw      <= `BW_DBLWORD;
              mem_data_in <= 'h11223344;
            end
            4'd4: begin
              mem_addr    <= 'h100;
              mem_write   <= 1'b0;
              mem_read    <= 1'b1;
              mem_bw      <= `BW_DBLWORD;
            end
            4'd5: begin
              mem_addr    <= 'h200;
              mem_write   <= 1'b1;
              mem_read    <= 1'b0;
              mem_bw      <= `BW_DBLWORD;
              mem_data_in <= 'hAABBCCDD;
            end
            4'd6: begin
              mem_addr    <= 'h200 + LINE_STRIDE;
              mem_write   <= 1'b1;
              mem_read    <= 1'b0;
              mem_bw      <= `BW_DBLWORD;
              mem_data_in <= 'h55667788;
            end
            4'd7: begin
              mem_addr    <= 'h200;
              mem_write   <= 1'b0;
              mem_read    <= 1'b1;
              mem_bw      <= `BW_DBLWORD;
            end
            4'd8: begin
              mem_addr    <= 'h138;
              mem_write   <= 1'b1;
              mem_read    <= 1'b0;
              mem_bw      <= `BW_DBLWORD;
              mem_data_in <= 'h12345678;
            end
            4'd9: begin
              mem_addr    <= 'h138 + LINE_STRIDE;
              mem_write   <= 1'b1;
              mem_read    <= 1'b0;
              mem_bw      <= `BW_DBLWORD;
              mem_data_in <= 'h87654321;
            end
            4'd10: begin
              mem_addr    <= 'h138;
              mem_write   <= 1'b0;
              mem_read    <= 1'b1;
              mem_bw      <= `BW_DBLWORD;
            end
            default: begin
              state <= S_DONE;
            end
          endcase

          if (test_step < 4'd11) begin
            state <= S_WAIT_COMPLETE;
          end
        end

        S_WAIT_COMPLETE: begin
          if (mem_busy == 1'b0) begin
            mem_write <= 1'b0;
            mem_read  <= 1'b0;
            state     <= S_WAIT_RECOVERY;
          end
        end

        S_WAIT_RECOVERY: begin
          if (mem_busy == 1'b1) begin
            test_step <= test_step + 4'd1;
            state     <= S_SETUP_CMD;
          end
        end

        S_DONE: begin
          mem_write <= 1'b0;
          mem_read  <= 1'b0;
        end
      endcase
    end
  end
endmodule
