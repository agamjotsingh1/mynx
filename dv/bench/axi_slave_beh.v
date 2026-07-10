`include "defs.vh"

// behavioral AXI3 slave standing in for the Zynq PS HP port (dv/bench only).
// 1MB of 64-bit RAM, single outstanding read + single outstanding write
// (all the amc ever issues). every handshake delay is randomized from an
// LFSR so the amc/submem prefetch timing gets hit with:
//   - arready / awready delays (including awready AFTER all W beats)
//   - rvalid gaps mid-burst
//   - wready gaps mid-burst and wready high immediately
//   - bvalid delay
// protocol violations from the master $fatal immediately: wrong beat count,
// wlast on wrong beat, unaligned or out-of-range burst address.
module axi_slave_beh #(
  parameter MEM_BYTES = 1048576
) (
  input wire clk,
  input wire rst,
  input wire [31:0] rng_seed,

  // AR
  input  wire        arvalid,
  output reg         arready,
  input  wire `W(`AXI_ADDRLEN) araddr,
  input  wire `W(`AXI_LENLEN)  arlen,
  input  wire `W(`AXI_SIZELEN) arsize,

  // R
  output reg         rvalid,
  output reg         rlast,
  input  wire        rready,
  output reg  [63:0] rdata,
  output wire `W(`AXI_RESPLEN) rresp,

  // AW
  input  wire        awvalid,
  output reg         awready,
  input  wire `W(`AXI_ADDRLEN) awaddr,
  input  wire `W(`AXI_LENLEN)  awlen,
  input  wire `W(`AXI_SIZELEN) awsize,

  // W
  input  wire        wvalid,
  input  wire        wlast,
  output reg         wready,
  input  wire [63:0] wdata,
  input  wire `W(`AXI_STRBLEN) wstrb,

  // B
  output reg         bvalid,
  input  wire        bready,
  output wire `W(`AXI_RESPLEN) bresp,

  // backdoor for the checker (combinational)
  input  wire [31:0] bd_addr,
  output wire [63:0] bd_data
);
  localparam MEM_WORDS = MEM_BYTES / 8;

  reg [63:0] ram [0:MEM_WORDS-1];

  // init pattern must match f(i) in submem_tb.cpp
  integer i;
  reg [63:0] i64;
  initial begin
    for(i = 0; i < MEM_WORDS; i = i + 1) begin
      i64 = i;
      ram[i] = (i64 * 64'h9E3779B97F4A7C15) ^ 64'hA5A5DEADBEEF5A5A;
    end
  end

  assign rresp = `AXI_RESP_OKAY;
  assign bresp = `AXI_RESP_OKAY;
  assign bd_data = ram[bd_addr[19:3]];

  // xorshift rng
  reg [31:0] rng;
  wire [31:0] rng_next1 = rng ^ (rng << 13);
  wire [31:0] rng_next2 = rng_next1 ^ (rng_next1 >> 17);
  wire [31:0] rng_next  = rng_next2 ^ (rng_next2 << 5);

  always @(posedge clk) begin
    if(rst) rng <= (rng_seed == 0) ? 32'h1 : rng_seed;
    else    rng <= rng_next;
  end

  /* ---------------- read channel ---------------- */
  reg [1:0] rstate;
  localparam R_IDLE = 2'd0;
  localparam R_DELAY = 2'd1;
  localparam R_BURST = 2'd2;

  reg [31:0] raddr_q;
  reg [2:0]  rbeat;
  reg [2:0]  rdelay;

  always @(posedge clk) begin
    if(rst) begin
      rstate  <= R_IDLE;
      arready <= 0;
      rvalid  <= 0;
      rlast   <= 0;
      rbeat   <= 0;
    end
    else begin
      case(rstate)
        R_IDLE: begin
          rvalid <= 0;
          rlast  <= 0;
          if(arvalid && arready) begin
            arready <= 0;
            if(arlen != 4'd7 || arsize != 3'b011)
              $fatal(1, "AXI: bad arlen/arsize %0d/%0d", arlen, arsize);
            if(araddr[5:0] != 0 || araddr >= MEM_BYTES)
              $fatal(1, "AXI: bad araddr %h", araddr);
            raddr_q <= araddr;
            rbeat   <= 0;
            rdelay  <= {1'b0, rng[1:0]}; // 0..3 dead cycles before first beat
            rstate  <= R_DELAY;
          end
          else if(arvalid) begin
            // random accept delay 0..3
            if(rng[1:0] == 0 || arready) arready <= 1;
          end
        end
        R_DELAY: begin
          if(rdelay == 0) begin
            rvalid <= 1;
            rdata  <= ram[{raddr_q[19:6], rbeat}];
            rlast  <= (rbeat == 3'd7);
            rstate <= R_BURST;
          end
          else rdelay <= rdelay - 1;
        end
        R_BURST: begin
          if(rvalid && rready) begin
            if(rbeat == 3'd7) begin
              rvalid <= 0;
              rlast  <= 0;
              rstate <= R_IDLE;
            end
            else begin
              rbeat <= rbeat + 1;
              if(rng[2:0] < 5) begin
                // next beat immediately
                rdata <= ram[{raddr_q[19:6], rbeat + 3'd1}];
                rlast <= (rbeat == 3'd6);
              end
              else begin
                // gap mid-burst
                rvalid <= 0;
                rlast  <= 0;
                rdelay <= {1'b0, rng[4:3]};
                rstate <= R_DELAY;
              end
            end
          end
        end
        default: rstate <= R_IDLE;
      endcase
    end
  end

  /* ---------------- write channel ---------------- */
  reg        aw_done;
  reg [31:0] waddr_q;
  reg [2:0]  wbeat;
  reg        w_done;
  reg [63:0] wbuf [0:7];
  reg [7:0]  wstrb_q [0:7];
  reg [3:0]  bdelay;
  reg        b_pending;
  reg [2:0]  awdelay;
  reg        aw_late; // hold awready until all W beats collected

  integer wi, wb;
  always @(posedge clk) begin
    if(rst) begin
      aw_done   <= 0;
      awready   <= 0;
      wready    <= 0;
      wbeat     <= 0;
      w_done    <= 0;
      bvalid    <= 0;
      b_pending <= 0;
      aw_late   <= 0;
      awdelay   <= 0;
    end
    else begin
      // AW accept
      if(awvalid && awready) begin
        awready <= 0;
        if(awlen != 4'd7 || awsize != 3'b011)
          $fatal(1, "AXI: bad awlen/awsize %0d/%0d", awlen, awsize);
        if(awaddr[5:0] != 0 || awaddr >= MEM_BYTES)
          $fatal(1, "AXI: bad awaddr %h", awaddr);
        waddr_q <= awaddr;
        aw_done <= 1;
      end
      else if(awvalid && !aw_done && !b_pending && !bvalid) begin
        if(!aw_late && awdelay == 0) begin
          // new AW: choose accept style once
          if(rng[7:5] == 0) aw_late <= 1;           // accept only after wlast
          else awdelay <= {1'b0, rng[9:8]} + 1;      // accept after 1..4 cycles
        end
        else if(aw_late) begin
          if(w_done) begin aw_late <= 0; awready <= 1; end
        end
        else begin
          awdelay <= awdelay - 1;
          if(awdelay == 1) awready <= 1;
        end
      end

      // W beats: wready randomized every cycle while burst incomplete
      if(!w_done && !b_pending && !bvalid)
        wready <= (rng[12:10] < 6); // ~75% high
      else
        wready <= 0;

      if(wvalid && wready && !w_done) begin
        wbuf[wbeat]    <= wdata;
        wstrb_q[wbeat] <= wstrb;
        if(wlast != (wbeat == 3'd7))
          $fatal(1, "AXI: wlast on beat %0d", wbeat);
        if(wbeat == 3'd7) w_done <= 1;
        else wbeat <= wbeat + 1;
      end

      // commit + B response
      if(aw_done && w_done && !b_pending && !bvalid) begin
        for(wi = 0; wi < 8; wi = wi + 1)
          for(wb = 0; wb < 8; wb = wb + 1)
            if(wstrb_q[wi][wb])
              ram[{waddr_q[19:6], wi[2:0]}][8*wb +: 8] <= wbuf[wi][8*wb +: 8];
        b_pending <= 1;
        bdelay    <= {1'b0, rng[15:13]}; // 0..7
      end

      if(b_pending) begin
        if(bdelay == 0) begin
          bvalid    <= 1;
          b_pending <= 0;
        end
        else bdelay <= bdelay - 1;
      end

      if(bvalid && bready) begin
        bvalid  <= 0;
        aw_done <= 0;
        w_done  <= 0;
        wbeat   <= 0;
      end
    end
  end
endmodule
