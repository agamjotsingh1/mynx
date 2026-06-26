`include "defs.vh"

// ARM AMBA AXI overview: https://www.youtube.com/watch?v=LTNz8xNhBpg
// AXI Burst has to be used with one cache line being read/written
//
// controller protocol (as seen from the cache):
// read  -> must accept the 'data_out' serially after data_out_valid is set
//..........until data_out_last is active (at the last read value)
//
// write -> must send in data serially indexing data_in_index
//..........until data_in_last is active (for the last written value)
//
// err returns if there was any sort of hardware txn error (of any type)
module axi_mem_controller (
  input wire clk,
  input wire rst,

  input wire  `W(`ADDRLEN)  addr,
  input wire                mem_read,
  input wire                mem_write,
  input wire  `W(`DLEN)     data_in,
  output wire `W($clog2(`AXI_AWLEN)) data_in_index,
  output wire               data_in_last,
  output wire `W(`DLEN)     data_out,
  output wire               data_out_valid,
  output wire               data_out_last,
  output reg                busy,
  output reg                err,

  /* AXI interface */
  // exposed to the AXI HP ports

  // AR - Address Read
  output reg  __axi_arvalid,
  input  wire __axi_arready,
  output reg  `W(AXI_ADDRLEN)  __axi_araddr,
  output wire `W(AXI_BURSTLEN) __axi_arburst,
  output wire `W(AXI_LOCKLEN)  __axi_arlock,
  output wire `W(AXI_SIZELEN)  __axi_arsize,
  output wire `W(AXI_PROTLEN)  __axi_arprot,
  output wire `W(AXI_CACHELEN) __axi_arcache,
  output wire `W(AXI_LENLEN)   __axi_arlen,
  output wire `W(AXI_QOSLEN)   __axi_arqos,
  output wire `W(AXI_IDLEN)    __axi_arid,

  // R - Read
  input  wire  __axi_rlast,
  input  wire  __axi_rvalid,
  output reg   __axi_rready,
  input  wire `W(AXI_DATALEN) __axi_rdata,
  input  wire `W(AXI_RESPLEN) __axi_rresp,
  input  wire `W(AXI_IDLEN)   __axi_rid,

  // AW - Address Write
  output reg  __axi_awvalid,
  input  wire __axi_awready,
  output reg  `W(AXI_ADDRLEN)  __axi_awaddr,
  output wire `W(AXI_BURSTLEN) __axi_awburst,
  output wire `W(AXI_LOCKLEN)  __axi_awlock,
  output wire `W(AXI_SIZELEN)  __axi_awsize,
  output wire `W(AXI_PROTLEN)  __axi_awprot,
  output wire `W(AXI_CACHELEN) __axi_awcache,
  output wire `W(AXI_LENLEN)   __axi_awlen,
  output wire `W(AXI_QOSLEN)   __axi_awqos,
  output wire `W(AXI_IDLEN)    __axi_awid,

  // W - Write
  output wire __axi_wlast,
  output reg  __axi_wvalid,
  input  wire __axi_wready,
  output reg  `W(AXI_DATALEN) __axi_wdata,
  output wire `W(AXI_RESPLEN) __axi_wstrb,
  output wire `W(AXI_IDLEN)   __axi_wid,

  // B - Write Response
  input  wire __axi_bvalid,
  output reg  __axi_bready,
  input  wire `W(AXI_RESPLEN) __axi_bresp,
  input  wire `W(AXI_IDLEN)   __axi_bid
);
  // AR config
  assign __axi_arqos   = `AXI_ARQOS;
  assign __axi_arlen   = `AXI_ARLEN;
  assign __axi_arlock  = `AXI_ARLOCK;
  assign __axi_arid    = `AXI_ARID;
  assign __axi_arprot  = `AXI_ARPROT;
  assign __axi_arcache = `AXI_ARCACHE;
  assign __axi_arburst = `AXI_ARBURST;
  assign __axi_arsize  = `AXI_ARSIZE;

  // AW config
  assign __axi_awqos   = `AXI_AWQOS;
  assign __axi_awlen   = `AXI_AWLEN;
  assign __axi_awlock  = `AXI_AWLOCK;
  assign __axi_awid    = `AXI_AWID;
  assign __axi_awprot  = `AXI_AWPROT;
  assign __axi_awcache = `AXI_AWCACHE;
  assign __axi_awburst = `AXI_AWBURST;
  assign __axi_awsize  = `AXI_AWSIZE;

  // W config
  assign __axi_wstrb   = `AXI_WSTRB;
  assign __axi_wid     = `AXI_WID;

  // states - gray code as im feeling fancy
  reg [2:0] state;
  localparam IDLE   = 3'b000;
  localparam AR_TXN = 3'b001;
  localparam AW_TXN = 3'b011;
  localparam R_TXN  = 3'b010;
  localparam W_TXN  = 3'b110;
  localparam B_TXN  = 3'b111;

  // write counter for sending serial write data
  reg `W($clog2(`AXI_AWLEN)) wcntr;

  always @(posedge clk) begin
    if(rst) begin
      state <= IDLE;
      busy  <= 0;
      err   <= 0;
      wcntr <= 0;

      __axi_arvalid <= 0;
      __axi_awvalid <= 0;
      __axi_rready  <= 0;
    end
    else begin
      case(state)
        IDLE: begin
          // TODO set the offset according to what the PS says
          if(mem_read) begin
            state <= AR_TXN;
            busy  <= 1;
            __axi_arvalid <= 1;
            __axi_araddr  <= $unsigned(addr);
          end
          else if(mem_write) begin
            state <= AW_TXN;
            busy  <= 1;
            __axi_awvalid <= 1;
            __axi_awaddr  <= $unsigned(addr);
          end

          err <= 0;
        end
        AR_TXN: begin
          if(__axi_arready && __axi_arvalid) begin
            state <= R_TXN;
            __axi_arvalid <= 0;
            __axi_rready  <= 1;
          end
        end
        R_TXN: begin
          if(__axi_rready && __axi_rvalid) begin
            if(__axi_rlast) begin
              state <= IDLE;
              __axi_rready <= 0;
              busy <= 0;
            end

            if(__axi_rresp != `AXI_RRESP_OKAY) begin
              err <= 1;
            end
          end
        end
        AW_TXN: begin
          if(__axi_awready && __axi_awvalid) begin
            state <= W_TXN;
            wcntr <= wcntr + 1;
            __axi_awvalid <= 0;
            __axi_wvalid  <= 1;
            __axi_wdata   <= data_in;
          end
        end
        W_TXN: begin
          if(__axi_wready && __axi_wvalid) begin
            if(__axi_wlast) begin
              state <= B_TXN;
              wcntr <= 0;
              __axi_wvalid <= 0;
              __axi_bready <= 1;
            end
            else begin
              wcntr <= wcntr + 1;
              __axi_wdata <= data_in;
            end
          end
        end
        B_TXN: begin
          if(__axi_bready && __axi_bvalid) begin
            state <= IDLE;
            busy <= 0;
            __axi_bready <= 0;

            if(__axi_bresp != `AXI_RESP_OKAY) begin
              err <= 1;
            end
          end
        end
        default: begin
          state <= IDLE;
        end
      endcase
    end
  end

  assign __axi_wlast = (&wcntr);

  assign data_out = __axi_rdata;

  assign data_out_valid =
    (state == R_TXN) &&
    __axi_rready &&
    __axi_rvalid;

  assign data_out_last =
    data_out_valid &&
    __axi_rlast;

  assign data_in_index = wcntr;
  assign data_in_last  = __axi_wlast;
  
endmodule
