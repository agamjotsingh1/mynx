`include "defs.vh"

// SIMULATION ONLY
// SoC wrapper for Verilator
module soc (
  input wire clk,
  input wire rst,

  output wire           tx_valid,
  input  wire           tx_ready,
  output wire `W(`BYTE) tx_data,

  input  wire           rx_valid,
  input  wire `W(`BYTE) rx_data
);
  /* core <-> AMC buses */
  // port A
  wire `W(`ADDRLEN) amc_addr_a;
  wire amc_mem_read_a, amc_mem_write_a;
  wire `W(`DLEN) amc_data_in_a;
  wire `W($clog2(`AXI_AWLEN)) amc_data_in_index_a;
  wire amc_data_in_last_a, amc_data_in_valid_a;
  wire `W(`DLEN) amc_data_out_a;
  wire `W($clog2(`AXI_AWLEN)) amc_data_out_index_a;
  wire amc_data_out_valid_a, amc_data_out_last_a;
  wire amc_busy_a, amc_err_a;
  // port B
  wire `W(`ADDRLEN) amc_addr_b;
  wire amc_mem_read_b, amc_mem_write_b;
  wire `W(`DLEN) amc_data_in_b;
  wire `W($clog2(`AXI_AWLEN)) amc_data_in_index_b;
  wire amc_data_in_last_b, amc_data_in_valid_b;
  wire `W(`DLEN) amc_data_out_b;
  wire `W($clog2(`AXI_AWLEN)) amc_data_out_index_b;
  wire amc_data_out_valid_b, amc_data_out_last_b;
  wire amc_busy_b, amc_err_b;

  /* AMC master <-> slave AXI (port A) */
  wire a_arvalid, a_arready;
  wire `W(`AXI_ADDRLEN)  a_araddr;
  wire `W(`AXI_BURSTLEN) a_arburst;
  wire `W(`AXI_LOCKLEN)  a_arlock;
  wire `W(`AXI_SIZELEN)  a_arsize;
  wire `W(`AXI_PROTLEN)  a_arprot;
  wire `W(`AXI_CACHELEN) a_arcache;
  wire `W(`AXI_LENLEN)   a_arlen;
  wire `W(`AXI_QOSLEN)   a_arqos;
  wire `W(`AXI_IDLEN)    a_arid;
  wire a_rlast, a_rvalid, a_rready;
  wire `W(`AXI_DATALEN) a_rdata;
  wire `W(`AXI_RESPLEN) a_rresp;
  wire `W(`AXI_IDLEN)   a_rid;
  wire a_awvalid, a_awready;
  wire `W(`AXI_ADDRLEN)  a_awaddr;
  wire `W(`AXI_BURSTLEN) a_awburst;
  wire `W(`AXI_LOCKLEN)  a_awlock;
  wire `W(`AXI_SIZELEN)  a_awsize;
  wire `W(`AXI_PROTLEN)  a_awprot;
  wire `W(`AXI_CACHELEN) a_awcache;
  wire `W(`AXI_LENLEN)   a_awlen;
  wire `W(`AXI_QOSLEN)   a_awqos;
  wire `W(`AXI_IDLEN)    a_awid;
  wire a_wlast, a_wvalid, a_wready;
  wire `W(`AXI_DATALEN) a_wdata;
  wire `W(`AXI_STRBLEN) a_wstrb;
  wire `W(`AXI_IDLEN)   a_wid;
  wire a_bvalid, a_bready;
  wire `W(`AXI_RESPLEN) a_bresp;
  wire `W(`AXI_IDLEN)   a_bid;

  /* AMC master <-> slave AXI (port B) */
  wire b_arvalid, b_arready;
  wire `W(`AXI_ADDRLEN)  b_araddr;
  wire `W(`AXI_BURSTLEN) b_arburst;
  wire `W(`AXI_LOCKLEN)  b_arlock;
  wire `W(`AXI_SIZELEN)  b_arsize;
  wire `W(`AXI_PROTLEN)  b_arprot;
  wire `W(`AXI_CACHELEN) b_arcache;
  wire `W(`AXI_LENLEN)   b_arlen;
  wire `W(`AXI_QOSLEN)   b_arqos;
  wire `W(`AXI_IDLEN)    b_arid;
  wire b_rlast, b_rvalid, b_rready;
  wire `W(`AXI_DATALEN) b_rdata;
  wire `W(`AXI_RESPLEN) b_rresp;
  wire `W(`AXI_IDLEN)   b_rid;
  wire b_awvalid, b_awready;
  wire `W(`AXI_ADDRLEN)  b_awaddr;
  wire `W(`AXI_BURSTLEN) b_awburst;
  wire `W(`AXI_LOCKLEN)  b_awlock;
  wire `W(`AXI_SIZELEN)  b_awsize;
  wire `W(`AXI_PROTLEN)  b_awprot;
  wire `W(`AXI_CACHELEN) b_awcache;
  wire `W(`AXI_LENLEN)   b_awlen;
  wire `W(`AXI_QOSLEN)   b_awqos;
  wire `W(`AXI_IDLEN)    b_awid;
  wire b_wlast, b_wvalid, b_wready;
  wire `W(`AXI_DATALEN) b_wdata;
  wire `W(`AXI_STRBLEN) b_wstrb;
  wire `W(`AXI_IDLEN)   b_wid;
  wire b_bvalid, b_bready;
  wire `W(`AXI_RESPLEN) b_bresp;
  wire `W(`AXI_IDLEN)   b_bid;

  /* core <-> ASDC bus */
  wire asdc_read_en, asdc_write_en;
  wire `W(`ASDC_ADDRLEN) asdc_addr;
  wire `W(`ASDC_DATALEN) asdc_data_in;
  wire `W(`ASDC_DATALEN) asdc_data_out;
  wire asdc_data_out_valid, asdc_busy, asdc_err;

  /* ASDC master <-> slave AXI-Lite */
  wire sd_arvalid, sd_arready;
  wire `W(`ASDC_ADDRLEN) sd_araddr;
  wire `W(`ASDC_PROTLEN) sd_arprot;
  wire sd_rvalid, sd_rready;
  wire `W(`ASDC_DATALEN) sd_rdata;
  wire `W(`ASDC_RESPLEN) sd_rresp;
  wire sd_awvalid, sd_awready;
  wire `W(`ASDC_ADDRLEN) sd_awaddr;
  wire `W(`ASDC_PROTLEN) sd_awprot;
  wire sd_wvalid, sd_wready;
  wire `W(`AXI_DATALEN) sd_wdata;
  wire `W(`AXI_STRBLEN) sd_wstrb;
  wire sd_bvalid, sd_bready;
  wire `W(`AXI_RESPLEN) sd_bresp;

  core u_core (
    .clk(clk),
    .rst(rst),

    // AMC port A
    .__amc_addr_a(amc_addr_a),
    .__amc_mem_read_a(amc_mem_read_a),
    .__amc_mem_write_a(amc_mem_write_a),
    .__amc_data_in_a(amc_data_in_a),
    .__amc_data_in_index_a(amc_data_in_index_a),
    .__amc_data_in_last_a(amc_data_in_last_a),
    .__amc_data_in_valid_a(amc_data_in_valid_a),
    .__amc_data_out_a(amc_data_out_a),
    .__amc_data_out_index_a(amc_data_out_index_a),
    .__amc_data_out_valid_a(amc_data_out_valid_a),
    .__amc_data_out_last_a(amc_data_out_last_a),
    .__amc_busy_a(amc_busy_a),
    .__amc_err_a(amc_err_a),

    // AMC port B
    .__amc_addr_b(amc_addr_b),
    .__amc_mem_read_b(amc_mem_read_b),
    .__amc_mem_write_b(amc_mem_write_b),
    .__amc_data_in_b(amc_data_in_b),
    .__amc_data_in_index_b(amc_data_in_index_b),
    .__amc_data_in_last_b(amc_data_in_last_b),
    .__amc_data_in_valid_b(amc_data_in_valid_b),
    .__amc_data_out_b(amc_data_out_b),
    .__amc_data_out_index_b(amc_data_out_index_b),
    .__amc_data_out_valid_b(amc_data_out_valid_b),
    .__amc_data_out_last_b(amc_data_out_last_b),
    .__amc_busy_b(amc_busy_b),
    .__amc_err_b(amc_err_b),

    // ASDC (SD)
    .__asdc_read_en(asdc_read_en),
    .__asdc_write_en(asdc_write_en),
    .__asdc_addr(asdc_addr),
    .__asdc_data_in(asdc_data_in),
    .__asdc_data_out(asdc_data_out),
    .__asdc_data_out_valid(asdc_data_out_valid),
    .__asdc_busy(asdc_busy),
    .__asdc_err(asdc_err),

    // UART
    .tx_valid(tx_valid),
    .tx_ready(tx_ready),
    .tx_data(tx_data),
    .rx_valid(rx_valid),
    .rx_data(rx_data)
  );

  amc u_amc_a (
    .clk(clk),
    .rst(rst),

    .addr(amc_addr_a),
    .mem_read(amc_mem_read_a),
    .mem_write(amc_mem_write_a),
    .data_in(amc_data_in_a),
    .data_in_index(amc_data_in_index_a),
    .data_in_last(amc_data_in_last_a),
    .data_in_valid(amc_data_in_valid_a),
    .data_out(amc_data_out_a),
    .data_out_index(amc_data_out_index_a),
    .data_out_valid(amc_data_out_valid_a),
    .data_out_last(amc_data_out_last_a),
    .busy(amc_busy_a),
    .err(amc_err_a),

    .phy_ps_addr(`AXI_ADDRLEN'b0),

    // AR
    .m_axi_arvalid(a_arvalid),
    .m_axi_arready(a_arready),
    .m_axi_araddr(a_araddr),
    .m_axi_arburst(a_arburst),
    .m_axi_arlock(a_arlock),
    .m_axi_arsize(a_arsize),
    .m_axi_arprot(a_arprot),
    .m_axi_arcache(a_arcache),
    .m_axi_arlen(a_arlen),
    .m_axi_arqos(a_arqos),
    .m_axi_arid(a_arid),
    // R
    .m_axi_rlast(a_rlast),
    .m_axi_rvalid(a_rvalid),
    .m_axi_rready(a_rready),
    .m_axi_rdata(a_rdata),
    .m_axi_rresp(a_rresp),
    .m_axi_rid(a_rid),
    // AW
    .m_axi_awvalid(a_awvalid),
    .m_axi_awready(a_awready),
    .m_axi_awaddr(a_awaddr),
    .m_axi_awburst(a_awburst),
    .m_axi_awlock(a_awlock),
    .m_axi_awsize(a_awsize),
    .m_axi_awprot(a_awprot),
    .m_axi_awcache(a_awcache),
    .m_axi_awlen(a_awlen),
    .m_axi_awqos(a_awqos),
    .m_axi_awid(a_awid),
    // W
    .m_axi_wlast(a_wlast),
    .m_axi_wvalid(a_wvalid),
    .m_axi_wready(a_wready),
    .m_axi_wdata(a_wdata),
    .m_axi_wstrb(a_wstrb),
    .m_axi_wid(a_wid),
    // B
    .m_axi_bvalid(a_bvalid),
    .m_axi_bready(a_bready),
    .m_axi_bresp(a_bresp),
    .m_axi_bid(a_bid)
  );

  amc u_amc_b (
    .clk(clk),
    .rst(rst),

    .addr(amc_addr_b),
    .mem_read(amc_mem_read_b),
    .mem_write(amc_mem_write_b),
    .data_in(amc_data_in_b),
    .data_in_index(amc_data_in_index_b),
    .data_in_last(amc_data_in_last_b),
    .data_in_valid(amc_data_in_valid_b),
    .data_out(amc_data_out_b),
    .data_out_index(amc_data_out_index_b),
    .data_out_valid(amc_data_out_valid_b),
    .data_out_last(amc_data_out_last_b),
    .busy(amc_busy_b),
    .err(amc_err_b),

    .phy_ps_addr(`AXI_ADDRLEN'b0),

    // AR
    .m_axi_arvalid(b_arvalid),
    .m_axi_arready(b_arready),
    .m_axi_araddr(b_araddr),
    .m_axi_arburst(b_arburst),
    .m_axi_arlock(b_arlock),
    .m_axi_arsize(b_arsize),
    .m_axi_arprot(b_arprot),
    .m_axi_arcache(b_arcache),
    .m_axi_arlen(b_arlen),
    .m_axi_arqos(b_arqos),
    .m_axi_arid(b_arid),
    // R
    .m_axi_rlast(b_rlast),
    .m_axi_rvalid(b_rvalid),
    .m_axi_rready(b_rready),
    .m_axi_rdata(b_rdata),
    .m_axi_rresp(b_rresp),
    .m_axi_rid(b_rid),
    // AW
    .m_axi_awvalid(b_awvalid),
    .m_axi_awready(b_awready),
    .m_axi_awaddr(b_awaddr),
    .m_axi_awburst(b_awburst),
    .m_axi_awlock(b_awlock),
    .m_axi_awsize(b_awsize),
    .m_axi_awprot(b_awprot),
    .m_axi_awcache(b_awcache),
    .m_axi_awlen(b_awlen),
    .m_axi_awqos(b_awqos),
    .m_axi_awid(b_awid),
    // W
    .m_axi_wlast(b_wlast),
    .m_axi_wvalid(b_wvalid),
    .m_axi_wready(b_wready),
    .m_axi_wdata(b_wdata),
    .m_axi_wstrb(b_wstrb),
    .m_axi_wid(b_wid),
    // B
    .m_axi_bvalid(b_bvalid),
    .m_axi_bready(b_bready),
    .m_axi_bresp(b_bresp),
    .m_axi_bid(b_bid)
  );

  amc_slave u_amc_slave (
    .clk(clk),
    .rst(rst),

    // Port A (read+write)
    .a_axi_arvalid(a_arvalid),
    .a_axi_arready(a_arready),
    .a_axi_araddr(a_araddr),
    .a_axi_arburst(a_arburst),
    .a_axi_arlock(a_arlock),
    .a_axi_arsize(a_arsize),
    .a_axi_arprot(a_arprot),
    .a_axi_arcache(a_arcache),
    .a_axi_arlen(a_arlen),
    .a_axi_arqos(a_arqos),
    .a_axi_arid(a_arid),
    .a_axi_rlast(a_rlast),
    .a_axi_rvalid(a_rvalid),
    .a_axi_rready(a_rready),
    .a_axi_rdata(a_rdata),
    .a_axi_rresp(a_rresp),
    .a_axi_rid(a_rid),
    .a_axi_awvalid(a_awvalid),
    .a_axi_awready(a_awready),
    .a_axi_awaddr(a_awaddr),
    .a_axi_awburst(a_awburst),
    .a_axi_awlock(a_awlock),
    .a_axi_awsize(a_awsize),
    .a_axi_awprot(a_awprot),
    .a_axi_awcache(a_awcache),
    .a_axi_awlen(a_awlen),
    .a_axi_awqos(a_awqos),
    .a_axi_awid(a_awid),
    .a_axi_wlast(a_wlast),
    .a_axi_wvalid(a_wvalid),
    .a_axi_wready(a_wready),
    .a_axi_wdata(a_wdata),
    .a_axi_wstrb(a_wstrb),
    .a_axi_wid(a_wid),
    .a_axi_bvalid(a_bvalid),
    .a_axi_bready(a_bready),
    .a_axi_bresp(a_bresp),
    .a_axi_bid(a_bid),

    // Port B (read+write)
    .b_axi_arvalid(b_arvalid),
    .b_axi_arready(b_arready),
    .b_axi_araddr(b_araddr),
    .b_axi_arburst(b_arburst),
    .b_axi_arlock(b_arlock),
    .b_axi_arsize(b_arsize),
    .b_axi_arprot(b_arprot),
    .b_axi_arcache(b_arcache),
    .b_axi_arlen(b_arlen),
    .b_axi_arqos(b_arqos),
    .b_axi_arid(b_arid),
    .b_axi_rlast(b_rlast),
    .b_axi_rvalid(b_rvalid),
    .b_axi_rready(b_rready),
    .b_axi_rdata(b_rdata),
    .b_axi_rresp(b_rresp),
    .b_axi_rid(b_rid),
    .b_axi_awvalid(b_awvalid),
    .b_axi_awready(b_awready),
    .b_axi_awaddr(b_awaddr),
    .b_axi_awburst(b_awburst),
    .b_axi_awlock(b_awlock),
    .b_axi_awsize(b_awsize),
    .b_axi_awprot(b_awprot),
    .b_axi_awcache(b_awcache),
    .b_axi_awlen(b_awlen),
    .b_axi_awqos(b_awqos),
    .b_axi_awid(b_awid),
    .b_axi_wlast(b_wlast),
    .b_axi_wvalid(b_wvalid),
    .b_axi_wready(b_wready),
    .b_axi_wdata(b_wdata),
    .b_axi_wstrb(b_wstrb),
    .b_axi_wid(b_wid),
    .b_axi_bvalid(b_bvalid),
    .b_axi_bready(b_bready),
    .b_axi_bresp(b_bresp),
    .b_axi_bid(b_bid)
  );

  asdc u_asdc (
    .clk(clk),
    .rst(rst),

    .addr(asdc_addr),
    .read_en(asdc_read_en),
    .write_en(asdc_write_en),
    .data_in(asdc_data_in),
    .data_out(asdc_data_out),
    .data_out_valid(asdc_data_out_valid),
    .busy(asdc_busy),
    .err(asdc_err),

    // AR
    .m_axi_arvalid(sd_arvalid),
    .m_axi_arready(sd_arready),
    .m_axi_araddr(sd_araddr),
    .m_axi_arprot(sd_arprot),
    // R
    .m_axi_rvalid(sd_rvalid),
    .m_axi_rready(sd_rready),
    .m_axi_rdata(sd_rdata),
    .m_axi_rresp(sd_rresp),
    // AW
    .m_axi_awvalid(sd_awvalid),
    .m_axi_awready(sd_awready),
    .m_axi_awaddr(sd_awaddr),
    .m_axi_awprot(sd_awprot),
    // W
    .m_axi_wvalid(sd_wvalid),
    .m_axi_wready(sd_wready),
    .m_axi_wdata(sd_wdata),
    .m_axi_wstrb(sd_wstrb),
    // B
    .m_axi_bvalid(sd_bvalid),
    .m_axi_bready(sd_bready),
    .m_axi_bresp(sd_bresp)
  );

  asdc_slave u_asdc_slave (
    .clk(clk),
    .rst(rst),

    // AR
    .s_axi_arvalid(sd_arvalid),
    .s_axi_arready(sd_arready),
    .s_axi_araddr(sd_araddr),
    .s_axi_arprot(sd_arprot),
    // R
    .s_axi_rvalid(sd_rvalid),
    .s_axi_rready(sd_rready),
    .s_axi_rdata(sd_rdata),
    .s_axi_rresp(sd_rresp),
    // AW
    .s_axi_awvalid(sd_awvalid),
    .s_axi_awready(sd_awready),
    .s_axi_awaddr(sd_awaddr),
    .s_axi_awprot(sd_awprot),
    // W
    .s_axi_wvalid(sd_wvalid),
    .s_axi_wready(sd_wready),
    .s_axi_wdata(sd_wdata),
    .s_axi_wstrb(sd_wstrb),
    // B
    .s_axi_bvalid(sd_bvalid),
    .s_axi_bready(sd_bready),
    .s_axi_bresp(sd_bresp)
  );
endmodule
