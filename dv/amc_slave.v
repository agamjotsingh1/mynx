`include "defs.vh"

// SIMULATION ONLY
// Mock dual-port AXI4 slave for the two AMC masters (core/modules/amc.v).
/* verilator lint_off UNUSEDSIGNAL */
module amc_slave (
  input wire clk,
  input wire rst,

  /* Port A */
  // AR
  input  wire a_axi_arvalid,
  output reg  a_axi_arready,
  input  wire `W(`AXI_ADDRLEN)  a_axi_araddr,
  input  wire `W(`AXI_BURSTLEN) a_axi_arburst,
  input  wire `W(`AXI_LOCKLEN)  a_axi_arlock,
  input  wire `W(`AXI_SIZELEN)  a_axi_arsize,
  input  wire `W(`AXI_PROTLEN)  a_axi_arprot,
  input  wire `W(`AXI_CACHELEN) a_axi_arcache,
  input  wire `W(`AXI_LENLEN)   a_axi_arlen,
  input  wire `W(`AXI_QOSLEN)   a_axi_arqos,
  input  wire `W(`AXI_IDLEN)    a_axi_arid,
  // R
  output reg  a_axi_rlast,
  output reg  a_axi_rvalid,
  input  wire a_axi_rready,
  output reg  `W(`AXI_DATALEN) a_axi_rdata,
  output reg  `W(`AXI_RESPLEN) a_axi_rresp,
  output reg  `W(`AXI_IDLEN)   a_axi_rid,
  // AW
  input  wire a_axi_awvalid,
  output reg  a_axi_awready,
  input  wire `W(`AXI_ADDRLEN)  a_axi_awaddr,
  input  wire `W(`AXI_BURSTLEN) a_axi_awburst,
  input  wire `W(`AXI_LOCKLEN)  a_axi_awlock,
  input  wire `W(`AXI_SIZELEN)  a_axi_awsize,
  input  wire `W(`AXI_PROTLEN)  a_axi_awprot,
  input  wire `W(`AXI_CACHELEN) a_axi_awcache,
  input  wire `W(`AXI_LENLEN)   a_axi_awlen,
  input  wire `W(`AXI_QOSLEN)   a_axi_awqos,
  input  wire `W(`AXI_IDLEN)    a_axi_awid,
  // W
  input  wire a_axi_wlast,
  input  wire a_axi_wvalid,
  output reg  a_axi_wready,
  input  wire `W(`AXI_DATALEN) a_axi_wdata,
  input  wire `W(`AXI_STRBLEN) a_axi_wstrb,
  input  wire `W(`AXI_IDLEN)   a_axi_wid,
  // B
  output reg  a_axi_bvalid,
  input  wire a_axi_bready,
  output reg  `W(`AXI_RESPLEN) a_axi_bresp,
  output reg  `W(`AXI_IDLEN)   a_axi_bid,

  /* Port B */
  // AR
  input  wire b_axi_arvalid,
  output reg  b_axi_arready,
  input  wire `W(`AXI_ADDRLEN)  b_axi_araddr,
  input  wire `W(`AXI_BURSTLEN) b_axi_arburst,
  input  wire `W(`AXI_LOCKLEN)  b_axi_arlock,
  input  wire `W(`AXI_SIZELEN)  b_axi_arsize,
  input  wire `W(`AXI_PROTLEN)  b_axi_arprot,
  input  wire `W(`AXI_CACHELEN) b_axi_arcache,
  input  wire `W(`AXI_LENLEN)   b_axi_arlen,
  input  wire `W(`AXI_QOSLEN)   b_axi_arqos,
  input  wire `W(`AXI_IDLEN)    b_axi_arid,
  // R
  output reg  b_axi_rlast,
  output reg  b_axi_rvalid,
  input  wire b_axi_rready,
  output reg  `W(`AXI_DATALEN) b_axi_rdata,
  output reg  `W(`AXI_RESPLEN) b_axi_rresp,
  output reg  `W(`AXI_IDLEN)   b_axi_rid,
  // AW
  input  wire b_axi_awvalid,
  output reg  b_axi_awready,
  input  wire `W(`AXI_ADDRLEN)  b_axi_awaddr,
  input  wire `W(`AXI_BURSTLEN) b_axi_awburst,
  input  wire `W(`AXI_LOCKLEN)  b_axi_awlock,
  input  wire `W(`AXI_SIZELEN)  b_axi_awsize,
  input  wire `W(`AXI_PROTLEN)  b_axi_awprot,
  input  wire `W(`AXI_CACHELEN) b_axi_awcache,
  input  wire `W(`AXI_LENLEN)   b_axi_awlen,
  input  wire `W(`AXI_QOSLEN)   b_axi_awqos,
  input  wire `W(`AXI_IDLEN)    b_axi_awid,
  // W
  input  wire b_axi_wlast,
  input  wire b_axi_wvalid,
  output reg  b_axi_wready,
  input  wire `W(`AXI_DATALEN) b_axi_wdata,
  input  wire `W(`AXI_STRBLEN) b_axi_wstrb,
  input  wire `W(`AXI_IDLEN)   b_axi_wid,
  // B
  output reg  b_axi_bvalid,
  input  wire b_axi_bready,
  output reg  `W(`AXI_RESPLEN) b_axi_bresp,
  output reg  `W(`AXI_IDLEN)   b_axi_bid
);
  localparam BYTE_OFF   = $clog2(`DLEN/`BYTE);
  localparam MEM_IDXLEN = $clog2(`DEPTH);

  reg `W(`DLEN) mem [0:`DEPTH-1];

  localparam R_IDLE = 1'b0, R_DATA = 1'b1;
  localparam W_IDLE = 2'd0, W_DATA = 2'd1, W_RESP = 2'd2;

  /* Port A read channel */
  reg a_rstate;
  reg `W(MEM_IDXLEN)  a_ridx;
  reg `W(`AXI_LENLEN+1) a_rbeats;

  always @(posedge clk) begin
    if (rst) begin
      a_rstate      <= R_IDLE;
      a_axi_arready <= 0;
      a_axi_rvalid  <= 0;
      a_axi_rlast   <= 0;
      a_axi_rresp   <= `AXI_RESP_OKAY;
      a_axi_rid     <= 0;
    end
    else begin
      case (a_rstate)
        R_IDLE: begin
          a_axi_rvalid  <= 0;
          a_axi_rlast   <= 0;
          a_axi_arready <= 1;
          if (a_axi_arvalid && a_axi_arready) begin
            a_axi_arready <= 0;
            a_ridx   <= a_axi_araddr[BYTE_OFF +: MEM_IDXLEN] + 1;
            a_rbeats <= {1'b0, a_axi_arlen};
            a_axi_rid    <= a_axi_arid;
            a_axi_rvalid <= 1;
            a_axi_rresp  <= `AXI_RESP_OKAY;
            a_axi_rdata  <= mem[a_axi_araddr[BYTE_OFF +: MEM_IDXLEN]];
            a_axi_rlast  <= (a_axi_arlen == 0);
            a_rstate <= R_DATA;
          end
        end
        R_DATA: begin
          if (a_axi_rvalid && a_axi_rready) begin
            if (a_rbeats == 0) begin
              a_axi_rvalid  <= 0;
              a_axi_rlast   <= 0;
              a_axi_arready <= 1;
              a_rstate      <= R_IDLE;
            end
            else begin
              a_ridx   <= a_ridx + 1;
              a_rbeats <= a_rbeats - 1;
              a_axi_rdata <= mem[a_ridx];
              a_axi_rlast <= (a_rbeats == 1);
            end
          end
        end
        default: a_rstate <= R_IDLE;
      endcase
    end
  end

  /* Port B read channel */
  reg b_rstate;
  reg `W(MEM_IDXLEN)  b_ridx;
  reg `W(`AXI_LENLEN+1) b_rbeats;

  always @(posedge clk) begin
    if (rst) begin
      b_rstate      <= R_IDLE;
      b_axi_arready <= 0;
      b_axi_rvalid  <= 0;
      b_axi_rlast   <= 0;
      b_axi_rresp   <= `AXI_RESP_OKAY;
      b_axi_rid     <= 0;
    end
    else begin
      case (b_rstate)
        R_IDLE: begin
          b_axi_rvalid  <= 0;
          b_axi_rlast   <= 0;
          b_axi_arready <= 1;
          if (b_axi_arvalid && b_axi_arready) begin
            b_axi_arready <= 0;
            b_ridx   <= b_axi_araddr[BYTE_OFF +: MEM_IDXLEN] + 1;
            b_rbeats <= {1'b0, b_axi_arlen};
            b_axi_rid    <= b_axi_arid;
            b_axi_rvalid <= 1;
            b_axi_rresp  <= `AXI_RESP_OKAY;
            b_axi_rdata  <= mem[b_axi_araddr[BYTE_OFF +: MEM_IDXLEN]];
            b_axi_rlast  <= (b_axi_arlen == 0);
            b_rstate <= R_DATA;
          end
        end
        R_DATA: begin
          if (b_axi_rvalid && b_axi_rready) begin
            if (b_rbeats == 0) begin
              b_axi_rvalid  <= 0;
              b_axi_rlast   <= 0;
              b_axi_arready <= 1;
              b_rstate      <= R_IDLE;
            end
            else begin
              b_ridx   <= b_ridx + 1;
              b_rbeats <= b_rbeats - 1;
              b_axi_rdata <= mem[b_ridx];
              b_axi_rlast <= (b_rbeats == 1);
            end
          end
        end
        default: b_rstate <= R_IDLE;
      endcase
    end
  end

  /* Single write channel */
  reg [1:0] a_wstate, b_wstate;
  reg `W(MEM_IDXLEN) a_widx, b_widx;

  integer ba, bb;
  always @(posedge clk) begin
    if (rst) begin
      a_wstate      <= W_IDLE;
      a_axi_awready <= 0;
      a_axi_wready  <= 0;
      a_axi_bvalid  <= 0;
      a_axi_bresp   <= `AXI_RESP_OKAY;
      a_axi_bid     <= 0;

      b_wstate      <= W_IDLE;
      b_axi_awready <= 0;
      b_axi_wready  <= 0;
      b_axi_bvalid  <= 0;
      b_axi_bresp   <= `AXI_RESP_OKAY;
      b_axi_bid     <= 0;
    end
    else begin
      // Port A write
      case (a_wstate)
        W_IDLE: begin
          a_axi_bvalid  <= 0;
          a_axi_awready <= 1;
          if (a_axi_awvalid && a_axi_awready) begin
            a_axi_awready <= 0;
            a_widx    <= a_axi_awaddr[BYTE_OFF +: MEM_IDXLEN];
            a_axi_bid <= a_axi_awid;
            a_axi_wready <= 1;
            a_wstate <= W_DATA;
          end
        end
        W_DATA: begin
          a_axi_wready <= 1;
          if (a_axi_wvalid && a_axi_wready) begin
            for (ba = 0; ba < `AXI_STRBLEN; ba = ba + 1) begin
              if (a_axi_wstrb[ba])
                mem[a_widx][ba*`BYTE +: `BYTE] <= a_axi_wdata[ba*`BYTE +: `BYTE];
            end
            a_widx <= a_widx + 1;
            if (a_axi_wlast) begin
              a_axi_wready <= 0;
              a_axi_bvalid <= 1;
              a_axi_bresp  <= `AXI_RESP_OKAY;
              a_wstate <= W_RESP;
            end
          end
        end
        W_RESP: begin
          if (a_axi_bvalid && a_axi_bready) begin
            a_axi_bvalid  <= 0;
            a_axi_awready <= 1;
            a_wstate <= W_IDLE;
          end
        end
        default: a_wstate <= W_IDLE;
      endcase

      // Port B write
      case (b_wstate)
        W_IDLE: begin
          b_axi_bvalid  <= 0;
          b_axi_awready <= 1;
          if (b_axi_awvalid && b_axi_awready) begin
            b_axi_awready <= 0;
            b_widx    <= b_axi_awaddr[BYTE_OFF +: MEM_IDXLEN];
            b_axi_bid <= b_axi_awid;
            b_axi_wready <= 1;
            b_wstate <= W_DATA;
          end
        end
        W_DATA: begin
          b_axi_wready <= 1;
          if (b_axi_wvalid && b_axi_wready) begin
            for (bb = 0; bb < `AXI_STRBLEN; bb = bb + 1) begin
              if (b_axi_wstrb[bb])
                mem[b_widx][bb*`BYTE +: `BYTE] <= b_axi_wdata[bb*`BYTE +: `BYTE];
            end
            b_widx <= b_widx + 1;
            if (b_axi_wlast) begin
              b_axi_wready <= 0;
              b_axi_bvalid <= 1;
              b_axi_bresp  <= `AXI_RESP_OKAY;
              b_wstate <= W_RESP;
            end
          end
        end
        W_RESP: begin
          if (b_axi_bvalid && b_axi_bready) begin
            b_axi_bvalid  <= 0;
            b_axi_awready <= 1;
            b_wstate <= W_IDLE;
          end
        end
        default: b_wstate <= W_IDLE;
      endcase
    end
  end
endmodule
/* verilator lint_on UNUSEDSIGNAL */
