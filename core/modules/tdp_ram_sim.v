// `include "../defs.vh"

// WARNING! SIMULATION ONLY
// 2 port memory
module mem (
  input wire clk,

  // Port A
  input wire `W(`ADDRLEN)  addr_a,
  input wire               mem_read_a,
  input wire               mem_write_a,
  input wire `W(`DLEN)     data_in_a,
  output reg `W(`DLEN)     data_out_a,

  // Port B
  input wire `W(`ADDRLEN)  addr_b,
  input wire               mem_read_b,
  input wire               mem_write_b,
  input wire `W(`DLEN)     data_in_b,
  output reg `W(`DLEN)     data_out_b,
);
  reg `W(`DLEN) memory [0:(1<<`ADDRLEN)-1];
    
  // Port A Read
  always @(*) begin
    if (mem_read_a)
      data_out_a = memory[addr_a];
    else
      data_out_a = {DATA_WIDTH{1'b0}};
  end

  // Port B Read
  always @(*) begin
    if (mem_read_b)
      data_out_b = memory[addr_b];
    else
      data_out_b = {DATA_WIDTH{1'b0}};
  end

  always @(posedge clk) begin
    if (mem_write_a) begin
      memory[addr_a] <= data_in_a;
    end
    
    if (mem_write_b) begin
      memory[addr_b] <= data_in_b;
    end
  end

  initial begin
    $readmemh("../../dv/sim_instrs.hex", memory);
  end

endmodule

// // WARNING! SIMULATION ONLY
// // true dual port ram
// // two simultaneous (read/write) ops can happen parallely
// module tdp_ram_sim (
//     input  wire                     clk_a,
//     input  wire                     en_a,   // Port A Enable
//     input  wire `W(NCOL)            we_a,   // Port A Write Strobe (Byte Enable)
//     input  wire [$clogz(DEPTH)-1:0] addr_a, // Port A Address (Doubleword aligned)
//     input  wire [NCOL*WCOL-1:0]     din_a,  // Port A Data In (64-bit)
//     output reg  [NCOL*WCOL-1:0]     dout_a, // Port A Data Out (64-bit)



//     input  wire                     clk_b,
//     input  wire                     en_b,   // Port B Enable
//     input  wire [NCOL-1:0]        we_b,   // Port B Write Strobe (Byte Enable)
//     input  wire [$clogz(DEPTH)-1:0] addr_b, // Port B Address (Doubleword aligned)
//     input  wire [NCOL*WCOL-1:0] din_b,  // Port B Data In (64-bit)
//     output reg  [NCOL*WCOL-1:0] dout_b  // Port B Data Out (64-bit)
// );

//     // The actual memory array: 1024 rows of 64 bits
//     reg [NCOL*WCOL-1:0] ram_block [0:DEPTH-1];

//     integer i;

//     // port a
//     always @(posedge clk_a) begin
//       if (en_a) begin
//         // Write Logic: Loop through each byte lane.
//         // If the corresponding bit in the write strobe (we_a) is high, write that byte.
//         for (i = 0; i < NCOL; i = i + 1) begin
//           if (we_a[i]) begin
//             ram_block[addr_a][(i*WCOL) +: WCOL] <= din_a[(i*WCOL) +: WCOL];
//           end
//         end
//         // Read Logic: Always output the current data at the address
//         dout_a <= ram_block[addr_a];
//       end
//     end

//     // -------------------------------------------------------------------------
//     // PORT B
//     // -------------------------------------------------------------------------
//     always @(posedge clk_b) begin
//         if (en_b) begin
//             for (i = 0; i < NCOL; i = i + 1) begin
//                 if (we_b[i]) begin
//                     ram_block[addr_b][(i*WCOL) +: WCOL] <= din_b[(i*WCOL) +: WCOL];
//                 end
//             end
//             dout_b <= ram_block[addr_b];
//         end
//     end

// endmodule