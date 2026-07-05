`include "defs.vh"

// Axi SD Card Controller (ASDC)
// ARM AMBA AXI overview: https://www.youtube.com/watch?v=LTNz8xNhBpg
// This is barebones simple AXI Lite with no bursts
// Meant to interface with AXI Quad SPI IP
module asdc (
  input wire clk,
  input wire rst,

  input wire `W(`ASDC_ADDRLEN)  addr,
  input wire read_en,
  input wire write_en,
  input wire `W(`WORD) data_in,
  output wire `W(`WORD) data_out,
  output wire data_out_valid,
  output reg busy,
  output reg err,

  /* -- AXI interface -- */

  // exposed to the AXI HP ports
  // AR - Address Read
  output reg  m_axi_arvalid,
  input  wire m_axi_arready,
  output reg  `W(`ASDC_ADDRLEN)  m_axi_araddr,
  output wire `W(`ASDC_PROTLEN)  m_axi_arprot,

  // R - Read
  input  wire  m_axi_rvalid,
  output reg   m_axi_rready,
  input  wire `W(`ASDC_DATALEN) m_axi_rdata,
  input  wire `W(`ASDC_RESPLEN) m_axi_rresp,

  // AW - Address Write
  output reg  m_axi_awvalid,
  input  wire m_axi_awready,
  output reg  `W(`ASDC_ADDRLEN)  m_axi_awaddr,
  output wire `W(`ASDC_PROTLEN)  m_axi_awprot,

  // W - Write
  output reg  m_axi_wvalid,
  input  wire m_axi_wready,
  output wire `W(`AXI_DATALEN) m_axi_wdata,
  output wire `W(`AXI_STRBLEN) m_axi_wstrb,

  // B - Write Response
  input  wire m_axi_bvalid,
  output reg  m_axi_bready,
  input  wire `W(`AXI_RESPLEN) m_axi_bresp
);
  // AR config
  assign m_axi_arprot  = `AXI_ARPROT;

  // AW config
  assign m_axi_awprot  = `AXI_AWPROT;

  // W config
  assign m_axi_wstrb   = `ASDC_WSTRB;

  reg [2:0] state;
  localparam IDLE   = 3'b000;
  localparam AR_TXN = 3'b001;
  localparam AW_TXN = 3'b011;
  localparam R_TXN  = 3'b010;
  localparam W_TXN  = 3'b110;
  localparam B_TXN  = 3'b111;

  always @(posedge clk) begin
    if(rst) begin
      state <= IDLE;
      busy  <= 0;
      err   <= 0;

      m_axi_arvalid <= 0;
      m_axi_awvalid <= 0;
      m_axi_wvalid  <= 0;
      m_axi_rready  <= 0;
      m_axi_bready  <= 0;
    end
    else begin
      case(state)
        IDLE: begin
          if(read_en) begin
            state <= AR_TXN;
            busy  <= 1;
            m_axi_arvalid <= 1;
            m_axi_araddr  <= addr;
          end
          else if(write_en) begin
            state <= AW_TXN;
            busy  <= 1;
            m_axi_awvalid <= 1;
            m_axi_awaddr  <= addr;
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
            state <= IDLE;
            m_axi_rready <= 0;
            busy <= 0;
            
            if(m_axi_rresp != `AXI_RESP_OKAY) begin
              err <= 1;
            end
          end
        end
        AW_TXN: begin
          if(m_axi_awready && m_axi_awvalid) begin
            state <= W_TXN;
            m_axi_awvalid <= 0;
            m_axi_wvalid  <= 1;
          end
        end
        W_TXN: begin
          if(m_axi_wready && m_axi_wvalid) begin
            state <= B_TXN;
            m_axi_wvalid <= 0;
            m_axi_bready <= 1;
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
    end
  end

  assign m_axi_wdata = data_in;
  assign data_out = m_axi_rdata;

  assign data_out_valid =
    (state == R_TXN) &&
    m_axi_rready &&
    m_axi_rvalid;
endmodule
