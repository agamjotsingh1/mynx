`include "defs.vh"

// bench top: one submem (identical module for port A and port B) wired to the
// real amc and a behavioral AXI3 slave. the C++ driver plays the role of the
// mmu/pipeline: issues ops, drops en mid-transaction (trap abort), churns the
// address lines while busy, runs fence.i-style flushes, and checks every read
// and the post-flush DRAM image against a reference model.
module submem_tb (
  input wire clk,
  input wire rst,

  // mem port (drives what mmu drives)
  input wire  `W(`ADDRLEN)  addr,
  input wire                mem_read,
  input wire                mem_write,
  input wire  `W(`BWLEN)    bw,
  input wire  `W(`DLEN)     data_in,
  output wire `W(`DLEN)     data_out,
  output wire               busy,
  input wire                flush,
  output wire               flush_done,

  input wire [31:0] rng_seed,

  // slave RAM backdoor for the checker
  input  wire [31:0] bd_addr,
  output wire [63:0] bd_data
);
  // submem <-> amc
  wire `W(`ADDRLEN) s_amc_addr;
  wire s_amc_mem_read, s_amc_mem_write;
  wire `W(`DLEN) s_amc_data_in, s_amc_data_out;
  wire `W($clog2(`AXI_AWLEN)) s_amc_data_in_index, s_amc_data_out_index;
  wire s_amc_data_in_last, s_amc_data_in_valid;
  wire s_amc_data_out_valid, s_amc_data_out_last;
  wire s_amc_busy, s_amc_err;

  // amc <-> slave
  wire arvalid, arready, rlast, rvalid, rready;
  wire awvalid, awready, wlast, wvalid, wready, bvalid, bready;
  wire `W(`AXI_ADDRLEN) araddr, awaddr;
  wire `W(`AXI_BURSTLEN) arburst, awburst;
  wire `W(`AXI_LOCKLEN) arlock, awlock;
  wire `W(`AXI_SIZELEN) arsize, awsize;
  wire `W(`AXI_PROTLEN) arprot, awprot;
  wire `W(`AXI_CACHELEN) arcache, awcache;
  wire `W(`AXI_LENLEN) arlen, awlen;
  wire `W(`AXI_QOSLEN) arqos, awqos;
  wire `W(`AXI_IDLEN) arid, rid, awid, wid, bid;
  wire `W(`AXI_DATALEN) rdata, wdata;
  wire `W(`AXI_RESPLEN) rresp, bresp;
  wire `W(`AXI_STRBLEN) wstrb;

  assign rid = 0;
  assign bid = 0;

  submem dut (
    .clk(clk),
    .rst(rst),
    .addr(addr),
    .mem_read(mem_read),
    .mem_write(mem_write),
    .sign_extend(1'b0),
    .bw(bw),
    .data_in(data_in),
    .data_out(data_out),
    .busy(busy),
    .flush(flush),
    .flush_done(flush_done),
    .__amc_addr(s_amc_addr),
    .__amc_mem_read(s_amc_mem_read),
    .__amc_mem_write(s_amc_mem_write),
    .__amc_data_in(s_amc_data_in),
    .__amc_data_in_index(s_amc_data_in_index),
    .__amc_data_in_last(s_amc_data_in_last),
    .__amc_data_in_valid(s_amc_data_in_valid),
    .__amc_data_out(s_amc_data_out),
    .__amc_data_out_index(s_amc_data_out_index),
    .__amc_data_out_valid(s_amc_data_out_valid),
    .__amc_data_out_last(s_amc_data_out_last),
    .__amc_busy(s_amc_busy),
    .__amc_err(s_amc_err)
  );

  amc amc_instance (
    .clk(clk),
    .rst(rst),
    .addr(s_amc_addr),
    .mem_read(s_amc_mem_read),
    .mem_write(s_amc_mem_write),
    .data_in(s_amc_data_in),
    .data_in_index(s_amc_data_in_index),
    .data_in_last(s_amc_data_in_last),
    .data_in_valid(s_amc_data_in_valid),
    .data_out(s_amc_data_out),
    .data_out_index(s_amc_data_out_index),
    .data_out_valid(s_amc_data_out_valid),
    .data_out_last(s_amc_data_out_last),
    .busy(s_amc_busy),
    .err(s_amc_err),

    .phy_ps_addr(32'h0),

    .m_axi_arvalid(arvalid), .m_axi_arready(arready), .m_axi_araddr(araddr),
    .m_axi_arburst(arburst), .m_axi_arlock(arlock), .m_axi_arsize(arsize),
    .m_axi_arprot(arprot), .m_axi_arcache(arcache), .m_axi_arlen(arlen),
    .m_axi_arqos(arqos), .m_axi_arid(arid),

    .m_axi_rlast(rlast), .m_axi_rvalid(rvalid), .m_axi_rready(rready),
    .m_axi_rdata(rdata), .m_axi_rresp(rresp), .m_axi_rid(rid),

    .m_axi_awvalid(awvalid), .m_axi_awready(awready), .m_axi_awaddr(awaddr),
    .m_axi_awburst(awburst), .m_axi_awlock(awlock), .m_axi_awsize(awsize),
    .m_axi_awprot(awprot), .m_axi_awcache(awcache), .m_axi_awlen(awlen),
    .m_axi_awqos(awqos), .m_axi_awid(awid),

    .m_axi_wlast(wlast), .m_axi_wvalid(wvalid), .m_axi_wready(wready),
    .m_axi_wdata(wdata), .m_axi_wstrb(wstrb), .m_axi_wid(wid),

    .m_axi_bvalid(bvalid), .m_axi_bready(bready), .m_axi_bresp(bresp),
    .m_axi_bid(bid)
  );

  axi_slave_beh slave (
    .clk(clk),
    .rst(rst),
    .rng_seed(rng_seed),

    .arvalid(arvalid), .arready(arready), .araddr(araddr),
    .arlen(arlen), .arsize(arsize),

    .rvalid(rvalid), .rlast(rlast), .rready(rready),
    .rdata(rdata), .rresp(rresp),

    .awvalid(awvalid), .awready(awready), .awaddr(awaddr),
    .awlen(awlen), .awsize(awsize),

    .wvalid(wvalid), .wlast(wlast), .wready(wready),
    .wdata(wdata), .wstrb(wstrb),

    .bvalid(bvalid), .bready(bready), .bresp(bresp),

    .bd_addr(bd_addr), .bd_data(bd_data)
  );
endmodule
