`timescale 1ns / 1ps

module core_vip;

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
    
    
        task zero_ps_memory(input [31:0] start_addr, input [31:0] length_bytes);
            integer i;
            begin
                for (i = 0; i < length_bytes; i = i + 4) begin
                    uut.design_1_i.processing_system7_0.inst.write_mem(
                        32'h00000000, 
                        start_addr + i, 
                        4
                    );
                end
            end
        endtask


    reg [31:0] firmware [0:368];
    integer i;

    initial begin
firmware[0]  = 32'h00001137;
firmware[1]  = 32'h0011011b;
firmware[2]  = 32'h01311113;
firmware[3]  = 32'h0010029b;
firmware[4]  = 32'h03e29293;
firmware[5]  = 32'hfff28293;
firmware[6]  = 32'h3b029073;
firmware[7]  = 32'h3a07d073;
firmware[8]  = 32'h430000ef;
firmware[9]  = 32'h0000006f;
firmware[10] = 32'hf8010113;
firmware[11] = 32'h00112023;
firmware[12] = 32'h00512223;
firmware[13] = 32'h00612423;
firmware[14] = 32'h00712623;
firmware[15] = 32'h00a12823;
firmware[16] = 32'h00b12a23;
firmware[17] = 32'h00c12c23;
firmware[18] = 32'h00d12e23;
firmware[19] = 32'h02e12023;
firmware[20] = 32'h02f12223;
firmware[21] = 32'h03012423;
firmware[22] = 32'h03112623;
firmware[23] = 32'h03c12823;
firmware[24] = 32'h03d12a23;
firmware[25] = 32'h03e12c23;
firmware[26] = 32'h03f12e23;
firmware[27] = 32'h38c000ef;
firmware[28] = 32'h00012083;
firmware[29] = 32'h00412283;
firmware[30] = 32'h00812303;
firmware[31] = 32'h00c12383;
firmware[32] = 32'h01012503;
firmware[33] = 32'h01412583;
firmware[34] = 32'h01812603;
firmware[35] = 32'h01c12683;
firmware[36] = 32'h02012703;
firmware[37] = 32'h02412783;
firmware[38] = 32'h02812803;
firmware[39] = 32'h02c12883;
firmware[40] = 32'h03012e03;
firmware[41] = 32'h03412e83;
firmware[42] = 32'h03812f03;
firmware[43] = 32'h03c12f83;
firmware[44] = 32'h08010113;
firmware[45] = 32'h30200073;
firmware[46] = 32'hfd010113;
firmware[47] = 32'h02113423;
firmware[48] = 32'h02813023;
firmware[49] = 32'h03010413;
firmware[50] = 32'hfca43c23;
firmware[51] = 32'hfcb43823;
firmware[52] = 32'hfe043423;
firmware[53] = 32'h0380006f;
firmware[54] = 32'hfd043783;
firmware[55] = 32'h0017f793;
firmware[56] = 32'h00078a63;
firmware[57] = 32'hfe843703;
firmware[58] = 32'hfd843783;
firmware[59] = 32'h00f707b3;
firmware[60] = 32'hfef43423;
firmware[61] = 32'hfd843783;
firmware[62] = 32'h00179793;
firmware[63] = 32'hfcf43c23;
firmware[64] = 32'hfd043783;
firmware[65] = 32'h0017d793;
firmware[66] = 32'hfcf43823;
firmware[67] = 32'hfd043783;
firmware[68] = 32'hfc0794e3;
firmware[69] = 32'hfe843783;
firmware[70] = 32'h00078513;
firmware[71] = 32'h02813083;
firmware[72] = 32'h02013403;
firmware[73] = 32'h03010113;
firmware[74] = 32'h00008067;
firmware[75] = 32'hfc010113;
firmware[76] = 32'h02113c23;
firmware[77] = 32'h02813823;
firmware[78] = 32'h04010413;
firmware[79] = 32'hfca43423;
firmware[80] = 32'hfcb43023;
firmware[81] = 32'hfc043783;
firmware[82] = 32'h00079663;
firmware[83] = 32'hfff00793;
firmware[84] = 32'h0980006f;
firmware[85] = 32'hfe043423;
firmware[86] = 32'hfe043023;
firmware[87] = 32'h03f00793;
firmware[88] = 32'hfcf42e23;
firmware[89] = 32'h0740006f;
firmware[90] = 32'hfe043783;
firmware[91] = 32'h00179793;
firmware[92] = 32'hfef43023;
firmware[93] = 32'hfdc42783;
firmware[94] = 32'h00078713;
firmware[95] = 32'hfc843783;
firmware[96] = 32'h00e7d7b3;
firmware[97] = 32'h0017f793;
firmware[98] = 32'hfe043703;
firmware[99] =32'h000f767b3;
firmware[100] =32'hfef43023;
firmware[101] =32'hfe043703;
firmware[102] =32'hfc043783;
firmware[103] =32'h02f76863;
firmware[104] =32'hfe043703;
firmware[105] =32'hfc043783;
firmware[106] =32'h40f707b3;
firmware[107] =32'hfef43023;
firmware[108] =32'hfdc42783;
firmware[109] =32'h00078713;
firmware[110] =32'h00100793;
firmware[111] =32'h00e797b3;
firmware[112] =32'hfe843703;
firmware[113] =32'h00f767b3;
firmware[114] =32'hfef43423;
firmware[115] =32'hfdc42783;
firmware[116] =32'hfff7879b;
firmware[117] =32'hfcf42e23;
firmware[118] =32'hfdc42783;
firmware[119] =32'h0007879b;
firmware[120] =32'hf807d4e3;
firmware[121] =32'hfe843783;
firmware[122] =32'h00078513;
firmware[123] =32'h03813083;
firmware[124] =32'h03013403;
firmware[125] =32'h04010113;
firmware[126] =32'h00008067;
firmware[127] =32'hfd010113;
firmware[128] =32'h02113423;
firmware[129] =32'h02813023;
firmware[130] =32'h03010413;
firmware[131] =32'hfca43c23;
firmware[132] =32'hfcb43823;
firmware[133] =32'hfd043783;
firmware[134] =32'h00079663;
firmware[135] =32'hfd843783;
firmware[136] =32'h0780006f;
firmware[137] =32'hfe043423;
firmware[138] =32'h03f00793;
firmware[139] =32'hfef42223;
firmware[140] =32'h0580006f;
firmware[141] =32'hfe843783;
firmware[142] =32'h00179793;
firmware[143] =32'hfef43423;
firmware[144] =32'hfe442783;
firmware[145] =32'h00078713;
firmware[146] =32'hfd843783;
firmware[147] =32'h00e7d7b3;
firmware[148] =32'h0017f793;
firmware[149] =32'hfe843703;
firmware[150] =32'h00f767b3;
firmware[151] =32'hfef43423;
firmware[152] =32'hfe843703;
firmware[153] =32'hfd043783;
firmware[154] =32'h00f76a63;
firmware[155] =32'hfe843703;
firmware[156] =32'hfd043783;
firmware[157] =32'h40f707b3;
firmware[158] =32'hfef43423;
firmware[159] =32'hfe442783;
firmware[160] =32'hfff7879b;
firmware[161] =32'hfef42223;
firmware[162] =32'hfe442783;
firmware[163] =32'h0007879b;
firmware[164] =32'hfa07d2e3;
firmware[165] =32'hfe843783;
firmware[166] =32'h00078513;
firmware[167] =32'h02813083;
firmware[168] =32'h02013403;
firmware[169] =32'h03010113;
firmware[170] =32'h00008067;
firmware[171] =32'hfd010113;
firmware[172] =32'h02113423;
firmware[173] =32'h02813023;
firmware[174] =32'h03010413;
firmware[175] =32'hfca43c23;
firmware[176] =32'hfcb43823;
firmware[177] =32'h00100793;
firmware[178] =32'hfef42623;
firmware[179] =32'hfd843783;
firmware[180] =32'h0007de63;
firmware[181] =32'hfd843783;
firmware[182] =32'h40f007b3;
firmware[183] =32'hfcf43c23;
firmware[184] =32'hfec42783;
firmware[185] =32'h40f007bb;
firmware[186] =32'hfef42623;
firmware[187] =32'hfd043783;
firmware[188] =32'h0007de63;
firmware[189] =32'hfd043783;
firmware[190] =32'h40f007b3;
firmware[191] =32'hfcf43823;
firmware[192] =32'hfec42783;
firmware[193] =32'h40f007bb;
firmware[194] =32'hfef42623;
firmware[195] =32'hfd843783;
firmware[196] =32'hfd043703;
firmware[197] =32'h00070593;
firmware[198] =32'h00078513;
firmware[199] =32'he11ff0ef;
firmware[200] =32'h00050793;
firmware[201] =32'hfef43023;
firmware[202] =32'hfec42783;
firmware[203] =32'h0007879b;
firmware[204] =32'h00f04863;
firmware[205] =32'hfe043783;
firmware[206] =32'h40f007b3;
firmware[207] =32'h0080006f;
firmware[208] =32'hfe043783;
firmware[209] =32'h00078513;
firmware[210] =32'h02813083;
firmware[211] =32'h02013403;
firmware[212] =32'h03010113;
firmware[213] =32'h00008067;
firmware[214] =32'hfd010113;
firmware[215] =32'h02113423;
firmware[216] =32'h02813023;
firmware[217] =32'h03010413;
firmware[218] =32'hfca43c23;
firmware[219] =32'hfcb43823;
firmware[220] =32'h00100793;
firmware[221] =32'hfef42623;
firmware[222] =32'hfd843783;
firmware[223] =32'h0007de63;
firmware[224] =32'hfd843783;
firmware[225] =32'h40f007b3;
firmware[226] =32'hfcf43c23;
firmware[227] =32'hfec42783;
firmware[228] =32'h40f007bb;
firmware[229] =32'hfef42623;
firmware[230] =32'hfd043783;
firmware[231] =32'h0007d863;
firmware[232] =32'hfd043783;
firmware[233] =32'h40f007b3;
firmware[234] =32'hfcf43823;
firmware[235] =32'hfd843783;
firmware[236] =32'hfd043703;
firmware[237] =32'h00070593;
firmware[238] =32'h00078513;
firmware[239] =32'he41ff0ef;
firmware[240] =32'h00050793;
firmware[241] =32'hfef43023;
firmware[242] =32'hfec42783;
firmware[243] =32'h0007879b;
firmware[244] =32'h00f04863;
firmware[245] =32'hfe043783;
firmware[246] =32'h40f007b3;
firmware[247] =32'h0080006f;
firmware[248] =32'hfe043783;
firmware[249] =32'h00078513;
firmware[250] =32'h02813083;
firmware[251] =32'h02013403;
firmware[252] =32'h03010113;
firmware[253] =32'h00008067;
firmware[254] =32'h342022f3;
firmware[255] =32'h00f00313;
firmware[256] =32'h800603b7;
firmware[257] =32'h80080e37;
firmware[258] =32'h00629c63;
firmware[259] =32'h0000ceb7;
firmware[260] =32'habee8e9b;
firmware[261] =32'h01d3b023;
firmware[262] =32'h000e3023;
firmware[263] =32'h0000006f;
firmware[264] =32'h0000eeb7;
firmware[265] =32'heade8e9b;
firmware[266] =32'h0053b023;
firmware[267] =32'h000e3023;
firmware[268] =32'h0000006f;
firmware[269] =32'h00000013;
firmware[270] =32'h000022b7;
firmware[271] =32'h0002b303;
firmware[272] =32'h0000d3b7;
firmware[273] =32'hafe3839b;
firmware[274] =32'h0072b023;
firmware[275] =32'h00000013;
firmware[276] =32'hfc010113;
firmware[277] =32'h02113c23;
firmware[278] =32'h02813823;
firmware[279] =32'h04010413;
firmware[280] =32'h00000797;
firmware[281] =32'hf9878793;
firmware[282] =32'h30579073;
firmware[283] =32'h080017b7;
firmware[284] =32'h00479793;
firmware[285] =32'hfef43023;
firmware[286] =32'h040017b7;
firmware[287] =32'h00579793;
firmware[288] =32'hfcf43c23;
firmware[289] =32'h080037b7;
firmware[290] =32'h00479793;
firmware[291] =32'hfcf43823;
firmware[292] =32'hfd843783;
firmware[293] =32'h00c7d793;
firmware[294] =32'h00a79793;
firmware[295] =32'h0017e713;
firmware[296] =32'hfe043783;
firmware[297] =32'h00e7b023;
firmware[298] =32'hfd043783;
firmware[299] =32'h00c7d793;
firmware[300] =32'h00a79793;
firmware[301] =32'h0017e713;
firmware[302] =32'hfd843783;
firmware[303] =32'h00e7b023;
firmware[304] =32'hfd043783;
firmware[305] =32'h00878793;
firmware[306] =32'h20010737;
firmware[307] =32'h0df70713;
firmware[308] =32'h00e7b023;
firmware[309] =32'hfd043783;
firmware[310] =32'h01078793;
firmware[311] =32'h20014737;
firmware[312] =32'h0d370713;
firmware[313] =32'h00e7b023;
firmware[314] =32'h080057b7;
firmware[315] =32'h00479793;
firmware[316] =32'h00000717;
firmware[317] =32'h0c870713;
firmware[318] =32'h00073703;
firmware[319] =32'h00e7b023;
firmware[320] =32'h020017b7;
firmware[321] =32'h00679793;
firmware[322] =32'hfcf43423;
firmware[323] =32'hfe042623;
firmware[324] =32'h0340006f;
firmware[325] =32'hfec42783;
firmware[326] =32'hfc843703;
firmware[327] =32'h00f707b3;
firmware[328] =32'h00000697;
firmware[329] =32'hf1868693;
firmware[330] =32'hfec42703;
firmware[331] =32'h00e68733;
firmware[332] =32'h00074703;
firmware[333] =32'h00e78023;
firmware[334] =32'hfec42783;
firmware[335] =32'h0017879b;
firmware[336] =32'hfef42623;
firmware[337] =32'hfec42703;
firmware[338] =32'h00000697;
firmware[339] =32'hf0468693;
firmware[340] =32'h00000797;
firmware[341] =32'hee878793;
firmware[342] =32'h40f687b3;
firmware[343] =32'hfaf74ce3;
firmware[344] =32'hfe043783;
firmware[345] =32'h00c7d713;
firmware[346] =32'hfff00793;
firmware[347] =32'h03f79793;
firmware[348] =32'h00f767b3;
firmware[349] =32'hfcf43023;
firmware[350] =32'hfc043783;
firmware[351] =32'h0000100f;
firmware[352] =32'h18079073;
firmware[353] =32'h12000073;
firmware[354] =32'h000022b7;
firmware[355] =32'h8002829b;
firmware[356] =32'h3002b073;
firmware[357] =32'h000012b7;
firmware[358] =32'h34129073;
firmware[359] =32'h30200073;
firmware[360] =32'h00000013;
firmware[361] =32'h03813083;
firmware[362] =32'h03013403;
firmware[363] =32'h04010113;
firmware[364] =32'h00008067;
firmware[365] =32'h00000000;
firmware[366] =32'hcafebabe;
firmware[367] =32'hdeadbeef;

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
//        // Clear Page Tables (Root, L1, L0) - 0x80010000 translates to 0x10010000
//        zero_ps_memory(ALLOCATED_PS_ADDR + 32'h00010000, 32'h1000); 
        
//        // Clear Payload regions - 0x80040000 translates to 0x10040000
//        zero_ps_memory(ALLOCATED_PS_ADDR + 32'h00040000, 32'h10000); 
//        zero_ps_memory(ALLOCATED_PS_ADDR + 32'h00050000, 32'h10000); 
        
//        // Clear Status/Evict regions - 0x80060000 translates to 0x10060000
//        zero_ps_memory(ALLOCATED_PS_ADDR + 32'h00060000, 32'h10000); 
//        zero_ps_memory(ALLOCATED_PS_ADDR + 32'h00080000, 32'h10000); 
        zero_ps_memory(ALLOCATED_PS_ADDR, 32'h00100000);
        
        // Clear main firmware execution space
        zero_ps_memory(ALLOCATED_PS_ADDR, 32'h2000);
        
        $display("Loading custom instructions into PS Memory...");
        for (i = 0; i < 368; i = i + 1) begin
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

        #700000000;
        $finish;
    end

endmodule
