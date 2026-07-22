`include "defs.vh"

// Axi Memory Controller (AMC)
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
/* verilator lint_off UNUSEDSIGNAL */
module amc (
  input wire clk,
  input wire rst,

  input wire  `W(`ADDRLEN)  addr,
  input wire                mem_read,
  input wire                mem_write,
  input wire  `W(`DLEN)     data_in,
  output wire `W($clog2(`AXI_AWLEN)) data_in_index,
  output wire               data_in_last,
  output wire               data_in_valid,
  output wire `W(`DLEN)     data_out,
  output wire `W($clog2(`AXI_AWLEN)) data_out_index,
  output wire               data_out_valid,
  output wire               data_out_last,
  output reg                busy,
  output reg                err,

  /* -- AXI interface -- */

  input wire `W(`AXI_ADDRLEN) phy_ps_addr,
  // exposed to the AXI HP ports
  // AR - Address Read
  output reg  m_axi_arvalid,
  input  wire m_axi_arready,
  output reg  `W(`AXI_ADDRLEN)  m_axi_araddr,
  output wire `W(`AXI_BURSTLEN) m_axi_arburst,
  output wire `W(`AXI_LOCKLEN)  m_axi_arlock,
  output wire `W(`AXI_SIZELEN)  m_axi_arsize,
  output wire `W(`AXI_PROTLEN)  m_axi_arprot,
  output wire `W(`AXI_CACHELEN) m_axi_arcache,
  output wire `W(`AXI_LENLEN)   m_axi_arlen,
  output wire `W(`AXI_QOSLEN)   m_axi_arqos,
  output wire `W(`AXI_IDLEN)    m_axi_arid,

  // R - Read
  input  wire  m_axi_rlast,
  input  wire  m_axi_rvalid,
  output reg   m_axi_rready,
  input  wire `W(`AXI_DATALEN) m_axi_rdata,
  input  wire `W(`AXI_RESPLEN) m_axi_rresp,
  input  wire `W(`AXI_IDLEN)   m_axi_rid,

  // AW - Address Write
  output reg  m_axi_awvalid,
  input  wire m_axi_awready,
  output reg  `W(`AXI_ADDRLEN)  m_axi_awaddr,
  output wire `W(`AXI_BURSTLEN) m_axi_awburst,
  output wire `W(`AXI_LOCKLEN)  m_axi_awlock,
  output wire `W(`AXI_SIZELEN)  m_axi_awsize,
  output wire `W(`AXI_PROTLEN)  m_axi_awprot,
  output wire `W(`AXI_CACHELEN) m_axi_awcache,
  output wire `W(`AXI_LENLEN)   m_axi_awlen,
  output wire `W(`AXI_QOSLEN)   m_axi_awqos,
  output wire `W(`AXI_IDLEN)    m_axi_awid,

  // W - Write
  output wire m_axi_wlast,
  output reg  m_axi_wvalid,
  input  wire m_axi_wready,
  output wire `W(`AXI_DATALEN) m_axi_wdata,
  output wire `W(`AXI_STRBLEN) m_axi_wstrb,
  output wire `W(`AXI_IDLEN)   m_axi_wid,

  // B - Write Response
  input  wire m_axi_bvalid,
  output reg  m_axi_bready,
  input  wire `W(`AXI_RESPLEN) m_axi_bresp,
  input  wire `W(`AXI_IDLEN)   m_axi_bid
);
  // AR config
  assign m_axi_arqos   = `AXI_ARQOS;
  assign m_axi_arlen   = `AXI_ARLEN;
  assign m_axi_arlock  = `AXI_ARLOCK;
  assign m_axi_arid    = `AXI_ARID;
  assign m_axi_arprot  = `AXI_ARPROT;
  assign m_axi_arcache = `AXI_ARCACHE;
  assign m_axi_arburst = `AXI_ARBURST;
  assign m_axi_arsize  = `AXI_ARSIZE;

  // AW config
  assign m_axi_awqos   = `AXI_AWQOS;
  assign m_axi_awlen   = `AXI_AWLEN;
  assign m_axi_awlock  = `AXI_AWLOCK;
  assign m_axi_awid    = `AXI_AWID;
  assign m_axi_awprot  = `AXI_AWPROT;
  assign m_axi_awcache = `AXI_AWCACHE;
  assign m_axi_awburst = `AXI_AWBURST;
  assign m_axi_awsize  = `AXI_AWSIZE;

  // W config
  assign m_axi_wstrb   = `AXI_WSTRB;
  assign m_axi_wid     = `AXI_WID;

  // states - gray code as im feeling fancy
  reg [2:0] state;
  localparam IDLE   = 3'b000;
  localparam AR_TXN = 3'b001;
  localparam AW_TXN = 3'b011;
  localparam R_TXN  = 3'b010;
  localparam W_TXN  = 3'b110;
  localparam B_TXN  = 3'b111;

  // write counter for sending serial write data
  reg `W($clog2(`AXI_AWLEN)) cntr;

  always @(posedge clk) begin
    if(rst) begin
      state <= IDLE;
      busy  <= 0;
      err   <= 0;
      cntr <= 0;

      m_axi_arvalid <= 0;
      m_axi_awvalid <= 0;
      m_axi_wvalid  <= 0;
      m_axi_rready  <= 0;
      m_axi_bready  <= 0;
    end
    else begin
      /* verilator lint_off WIDTHEXPAND */
      case(state)
        IDLE: begin
          if(mem_read) begin
            state <= AR_TXN;
            busy  <= 1;
            m_axi_arvalid <= 1;
            m_axi_araddr  <= $unsigned(addr) + phy_ps_addr;
          end
          else if(mem_write) begin
            state <= AW_TXN;
            busy  <= 1;
            m_axi_awvalid <= 1;
            m_axi_wvalid  <= 1;
            m_axi_awaddr  <= $unsigned(addr) + phy_ps_addr;
          end

          err <= 0;
        end
        AR_TXN: begin
          if(m_axi_arready && m_axi_arvalid) begin
            state <= R_TXN;
            m_axi_arvalid <= 0;
            m_axi_rready  <= 1;
          end
        end
        R_TXN: begin
          if(m_axi_rready && m_axi_rvalid) begin
            if(m_axi_rlast) begin
              state <= IDLE;
              m_axi_rready <= 0;
              busy <= 0;
              cntr <= 0;
            end
            else begin
              cntr <= cntr + 1;
            end

            if(m_axi_rresp != `AXI_RESP_OKAY) begin
              err <= 1;
            end
          end
        end
        AW_TXN: begin
          if(m_axi_wready && m_axi_wvalid) begin
            if(m_axi_wlast) begin
              m_axi_wvalid <= 0;
            end
            else begin
              cntr <= cntr + 1;
            end
          end

          if(m_axi_awready && m_axi_awvalid) begin
            m_axi_awvalid <= 0;
            if (m_axi_wvalid == 0 || (m_axi_wready && m_axi_wvalid && m_axi_wlast)) begin
              // both AW and W are done
              state <= B_TXN;
              cntr <= 0;
              m_axi_wvalid <= 0;
              m_axi_bready <= 1;
            end else begin
              // AW done, W still ongoing
              state <= W_TXN;
            end
          end
        end
        W_TXN: begin
          // W channel only, AW is already done
          if(m_axi_wready && m_axi_wvalid) begin
            if(m_axi_wlast) begin
              state <= B_TXN;
              cntr <= 0;
              m_axi_wvalid <= 0;
              m_axi_bready <= 1;
            end
            else begin
              cntr <= cntr + 1;
            end
          end
        end
        B_TXN: begin
          if(m_axi_bready && m_axi_bvalid) begin
            state <= IDLE;
            busy <= 0;
            m_axi_bready <= 0;

            if(m_axi_bresp != `AXI_RESP_OKAY) begin
              err <= 1;
            end
          end
        end
        default: begin
          state <= IDLE;
        end
      endcase
      /* verilator lint_on WIDTHEXPAND */
    end
  end

  assign m_axi_wlast = (&cntr);
  assign m_axi_wdata = data_in;

  assign data_out = m_axi_rdata;

  assign data_out_valid =
    (state == R_TXN) &&
    m_axi_rready &&
    m_axi_rvalid;

  assign data_out_last =
    data_out_valid &&
    m_axi_rlast;

  assign data_in_index = cntr;
  assign data_out_index = cntr;
  assign data_in_last  = m_axi_wlast && m_axi_wready && m_axi_wvalid;
  assign data_in_valid = ((state == W_TXN) || (state == AW_TXN)) && m_axi_wready && m_axi_wvalid;
endmodule
/* verilator lint_on UNUSEDSIGNAL */

