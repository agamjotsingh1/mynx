`timescale 1ns / 1ps

module tb_vip;

    localparam RST_GPIO_ADDR      = 32'h41210000;
    localparam PHY_ADDR_GPIO_ADDR = 32'h41200000;
    localparam ALLOCATED_PS_ADDR  = 32'h10000000;

    reg [1:0] resp;
    
    reg clk_stim = 0;
    reg porb_stim = 0;
    
    always #15 clk_stim = ~clk_stim;
    
    wire [14:0] DDR_addr;
    wire [2:0]  DDR_ba;
    wire        DDR_cas_n;
    wire        DDR_ck_n;
    wire        DDR_ck_p;
    wire        DDR_cke;
    wire        DDR_cs_n;
    wire [3:0]  DDR_dm;
    wire [31:0] DDR_dq;
    wire [3:0]  DDR_dqs_n;
    wire [3:0]  DDR_dqs_p;
    wire        DDR_odt;
    wire        DDR_ras_n;
    wire        DDR_reset_n;
    wire        DDR_we_n;
    wire        FIXED_IO_ddr_vrn;
    wire        FIXED_IO_ddr_vrp;
    wire [53:0] FIXED_IO_mio;
    wire        FIXED_IO_ps_srstb;
    
    wire        FIXED_IO_ps_clk;
    wire        FIXED_IO_ps_porb;

    assign FIXED_IO_ps_clk  = clk_stim;
    assign FIXED_IO_ps_porb = porb_stim;

    design_1_wrapper uut (
        .DDR_addr(DDR_addr),
        .DDR_ba(DDR_ba),
        .DDR_cas_n(DDR_cas_n),
        .DDR_ck_n(DDR_ck_n),
        .DDR_ck_p(DDR_ck_p),
        .DDR_cke(DDR_cke),
        .DDR_cs_n(DDR_cs_n),
        .DDR_dm(DDR_dm),
        .DDR_dq(DDR_dq),
        .DDR_dqs_n(DDR_dqs_n),
        .DDR_dqs_p(DDR_dqs_p),
        .DDR_odt(DDR_odt),
        .DDR_ras_n(DDR_ras_n),
        .DDR_reset_n(DDR_reset_n),
        .DDR_we_n(DDR_we_n),
        .FIXED_IO_ddr_vrn(FIXED_IO_ddr_vrn),
        .FIXED_IO_ddr_vrp(FIXED_IO_ddr_vrp),
        .FIXED_IO_mio(FIXED_IO_mio),
        .FIXED_IO_ps_clk(FIXED_IO_ps_clk),
        .FIXED_IO_ps_porb(FIXED_IO_ps_porb),
        .FIXED_IO_ps_srstb(FIXED_IO_ps_srstb)
    );

    reg [31:0] firmware [0:28];
    integer i;

    initial begin
        firmware[0]  = 32'h00100293;
        firmware[1]  = 32'h03e29293;
        firmware[2]  = 32'hfff28293;
        firmware[3]  = 32'h3b029073;
        firmware[4]  = 32'h00f00293;
        firmware[5]  = 32'h3a029073;
        firmware[6]  = 32'h00100293;
        firmware[7]  = 32'h01f29293;
        firmware[8]  = 32'h10028293;
        firmware[9]  = 32'h00004337;
        firmware[10] = 32'h0013031b;
        firmware[11] = 32'h01131313;
        firmware[12] = 32'h10030313;
        firmware[13] = 32'h000ab3b7;
        firmware[14] = 32'haab3839b;
        firmware[15] = 32'h00c39393;
        firmware[16] = 32'haaa38393;
        firmware[17] = 32'h0002fe37;
        firmware[18] = 32'heefe0e1b;
        firmware[19] = 32'h00ee1e13;
        firmware[20] = 32'hbbbe0e13;
        firmware[21] = 32'h000cdeb7;
        firmware[22] = 32'hccde8e9b;
        firmware[23] = 32'h00ce9e93;
        firmware[24] = 32'hccce8e93;
        firmware[25] = 32'h0072b023;
        firmware[26] = 32'h01c33023;
        firmware[27] = 32'h01d2b023;
        firmware[28] = 32'h0000006f;

        #100;
        porb_stim = 1;
        
        #1000;
        uut.design_1_i.processing_system7_0.inst.fpga_soft_reset(32'h0);
        #2000; 

//         $display("Loading custom instructions into PS Memory...");
//         for (i = 0; i < 29; i = i + 1) begin
//             uut.design_1_i.processing_system7_0.inst.write_data(
//                 ALLOCATED_PS_ADDR + (i * 4), 
//                 4, 
//                 firmware[i], 
//                 resp
//             );
//         end
//         $display("Instruction load complete.");

        $display("Zeroing out PS memory space...");
        for (i = 0; i < 1024; i = i + 1) begin
            uut.design_1_i.processing_system7_0.inst.write_mem(
                32'h00000000, 
                ALLOCATED_PS_ADDR + (i * 4), 
                4
            );
        end

        $display("Loading custom instructions into PS Memory...");
        for (i = 0; i < 29; i = i + 1) begin
            uut.design_1_i.processing_system7_0.inst.write_mem(
                firmware[i],
                ALLOCATED_PS_ADDR + (i * 4),
                4
            );
        end
        $display("Instruction load complete.");

        uut.design_1_i.processing_system7_0.inst.write_data(RST_GPIO_ADDR + 4, 4, 32'h00000000, resp);
        uut.design_1_i.processing_system7_0.inst.write_data(PHY_ADDR_GPIO_ADDR + 4, 4, 32'h00000000, resp);

        uut.design_1_i.processing_system7_0.inst.write_data(RST_GPIO_ADDR, 4, 32'h00000001, resp);
        uut.design_1_i.processing_system7_0.inst.write_data(PHY_ADDR_GPIO_ADDR, 4, ALLOCATED_PS_ADDR, resp);
        uut.design_1_i.processing_system7_0.inst.write_data(RST_GPIO_ADDR, 4, 32'h00000000, resp);

        #100000000;
        $finish;
    end

endmodule
