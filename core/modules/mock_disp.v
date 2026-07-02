`timescale 1ns / 1ps

(* DONT_TOUCH = "yes" *)
module mock_disp (
    input  wire clk,
    input  wire rstn,
    (* DONT_TOUCH = "yes" *) output reg  valid,
    (* DONT_TOUCH = "yes" *) output reg  [7:0] char
);

    // "Hello FPGA!" is 11 characters
    localparam MSG_LEN = 11;
    
    (* DONT_TOUCH = "yes" *) reg [1:0] state;
    (* DONT_TOUCH = "yes" *) reg [7:0] delay_cnt;
    (* DONT_TOUCH = "yes" *) reg [3:0] index;


    // FSM States
    localparam S_INIT = 2'd0;
    localparam S_SEND = 2'd1;
    localparam S_DONE = 2'd2;

    // Combinational ROM for the message
    // Vivado will synthesize this directly into Look-Up Tables (LUTs)
    reg [7:0] next_char;
    always @(*) begin
        case(index)
            4'd0:  next_char = "H";
            4'd1:  next_char = "e";
            4'd2:  next_char = "l";
            4'd3:  next_char = "l";
            4'd4:  next_char = "o";
            4'd5:  next_char = " ";
            4'd6:  next_char = "F";
            4'd7:  next_char = "P";
            4'd8:  next_char = "G";
            4'd9:  next_char = "A";
            4'd10: next_char = "!";
            default: next_char = 8'h00;
        endcase
    end

    always @(posedge clk) begin
        if (!rstn) begin
            state     <= S_INIT;
            delay_cnt <= 8'd0;
            index     <= 4'd0;
            valid     <= 1'b0;
            char      <= 8'h00;
        end else begin
            case (state)
                S_INIT: begin
                    // Wait a few cycles after reset before blasting data.
                    // This ensures the BRAM and display driver are fully awake.
                    valid <= 1'b0;
                    if (delay_cnt == 8'hFF) begin
                        state <= S_SEND;
                    end else begin
                        delay_cnt <= delay_cnt + 1;
                    end
                end

                S_SEND: begin
                    // Write one character per clock cycle until finished
                    if (index < MSG_LEN) begin
                        valid <= 1'b1;
                        char  <= next_char;
                        index <= index + 1;
                    end else begin
                        valid <= 1'b0;
                        state <= S_DONE;
                    end
                end

                S_DONE: begin
                    // Halt and hold outputs low forever
                    valid <= 1'b0;
                    char  <= 8'h00;
                end
                
                default: state <= S_INIT;
            endcase
        end
    end


    (* mark_debug = "true" *) wire dbg_valid = valid;
    (* mark_debug = "true" *) wire [7:0] dbg_char = char;
endmodule
