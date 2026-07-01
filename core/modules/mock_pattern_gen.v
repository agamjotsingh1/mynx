module mock_pattern_gen (
    input wire clk, // Connect to 74.25 MHz pixel clock
    input wire rst_n, // Active low reset
    
    // Inputs from VTC
    input wire hsync_in,
    input wire vsync_in,
    input wire active_video_in,
    
    // Outputs to rgb2dvi
    output wire [23:0] rgb_out,
    output wire hsync_out,
    output wire vsync_out,
    output wire active_video_out
);

    // Pass timing signals straight through to the output
    assign hsync_out = hsync_in;
    assign vsync_out = vsync_in;
    assign active_video_out = active_video_in;

    // Coordinate trackers (STAYS THE SAME)
    // These must run to manage the 720p grid
    reg [11:0] x_pos;
    reg [11:0] y_pos;

    always @(posedge clk) begin
        if (!rst_n) begin
            x_pos <= 0;
            y_pos <= 0;
        end else if (active_video_in) begin
            if (x_pos == 1279) begin  // End of a 720p line
                x_pos <= 0;
                y_pos <= (y_pos == 719) ? 0 : y_pos + 1; // End of frame
            end else begin
                x_pos <= x_pos + 1;
            end
        end else if (vsync_in) begin
            // Reset coordinates when vertical sync goes high
            x_pos <= 0;
            y_pos <= 0;
        end
    end

    // ***********************************************
    // THE DEMO MODIFICATION
    // Drawing lines based on X/Y counters
    // ***********************************************

    // Draw a bright crosshair on a dark gray background
    // Bright cyan: 24'h00FFFF
    // Dark background: 24'h202020

    assign rgb_out = active_video_in ? (
        // Condition 1: Current pixel is on the horizontal centerline (Y=360)
        // Condition 2: Current pixel is on the vertical centerline (X=640)
        ((y_pos == 360) || (x_pos == 640)) ? 24'h00FFFF : 24'h202020
    ) : 24'h000000; // Standby is black

endmodule
