`include "defs.vh"

module mock_axi_mem_controller_tb (
  input  wire clk,
  input  wire rst,

  output reg  `W(`ADDRLEN)  addr,
  output reg                mem_read,
  output reg                mem_write,
  output wire `W(`DLEN)     data_in,
  
  input  wire `W($clog2(`AXI_AWLEN)) data_in_index,
  input  wire               data_in_last,
  input  wire `W(`DLEN)     data_out,
  input  wire               data_out_valid,
  input  wire               data_out_last,
  input  wire               busy,
  input  wire               err,
  
  input  wire `W(`AXI_ADDRLEN) phy_ps_addr
);
  reg [3:0] state;
  reg `W(`DLEN) base_data;
  reg `W(`DLEN) read_capture;

  assign data_in = base_data + data_in_index;

  localparam S_W1_REQ  = 4'd0;
  localparam S_W1_WAIT = 4'd1;
  localparam S_W2_REQ  = 4'd2;
  localparam S_W2_WAIT = 4'd3;
  localparam S_R1_REQ  = 4'd4;
  localparam S_R1_WAIT = 4'd5;
  localparam S_R2_REQ  = 4'd6;
  localparam S_R2_WAIT = 4'd7;
  localparam S_DONE    = 4'd8;
  localparam S_ERR     = 4'd9;

  always @(posedge clk) begin
    if (rst) begin
      state        <= S_W1_REQ;
      mem_read     <= 1'b0;
      mem_write    <= 1'b0;
      addr         <= 0;
      base_data    <= 0;
      read_capture <= 0;
    end else if (err) begin
      state     <= S_ERR;
      mem_read  <= 1'b0;
      mem_write <= 1'b0;
    end else begin
      mem_read  <= 1'b0;
      mem_write <= 1'b0;

      if (data_out_valid) begin
        read_capture <= data_out;
      end

      case (state)
        S_W1_REQ: begin
          if (!busy) begin
            mem_write <= 1'b1;
            addr      <= 'h100;
            base_data <= 'hAAAA_0000;
            state     <= S_W1_WAIT;
          end
        end
        
        S_W1_WAIT: begin
          if (data_in_last) begin
            state <= S_W2_REQ;
          end
        end
        
        S_W2_REQ: begin
          if (!busy) begin
            mem_write <= 1'b1;
            addr      <= 'h200;
            base_data <= 'hBBBB_0000;
            state     <= S_W2_WAIT;
          end
        end
        
        S_W2_WAIT: begin
          if (data_in_last) begin
            state <= S_R1_REQ;
          end
        end
        
        S_R1_REQ: begin
          if (!busy) begin
            mem_read <= 1'b1;
            addr     <= 'h100;
            state    <= S_R1_WAIT;
          end
        end
        
        S_R1_WAIT: begin
          if (data_out_last) begin
            state <= S_R2_REQ;
          end
        end
        
        S_R2_REQ: begin
          if (!busy) begin
            mem_read <= 1'b1;
            addr     <= 'h200;
            state    <= S_R2_WAIT;
          end
        end
        
        S_R2_WAIT: begin
          if (data_out_last) begin
            state <= S_DONE;
          end
        end
        
        S_DONE: begin
          state <= S_DONE;
        end
        
        S_ERR: begin
          state <= S_ERR;
        end
        
        default: state <= S_W1_REQ;
      endcase
    end
  end

endmodule
