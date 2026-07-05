# HDMI TX Constraints
set_property -dict { PACKAGE_PIN L17   IOSTANDARD TMDS_33 } [get_ports { hdmi_tx_clk_n }];
set_property -dict { PACKAGE_PIN L16   IOSTANDARD TMDS_33 } [get_ports { hdmi_tx_clk_p }];
set_property -dict { PACKAGE_PIN K18   IOSTANDARD TMDS_33 } [get_ports { hdmi_tx_data_n[0] }];
set_property -dict { PACKAGE_PIN K17   IOSTANDARD TMDS_33 } [get_ports { hdmi_tx_data_p[0] }];
set_property -dict { PACKAGE_PIN J19   IOSTANDARD TMDS_33 } [get_ports { hdmi_tx_data_n[1] }];
set_property -dict { PACKAGE_PIN K19   IOSTANDARD TMDS_33 } [get_ports { hdmi_tx_data_p[1] }];
set_property -dict { PACKAGE_PIN H18   IOSTANDARD TMDS_33 } [get_ports { hdmi_tx_data_n[2] }];
set_property -dict { PACKAGE_PIN J18   IOSTANDARD TMDS_33 } [get_ports { hdmi_tx_data_p[2] }];

set_property -dict { PACKAGE_PIN W14 IOSTANDARD LVCMOS33 } [get_ports { spi_sd_ss_io[0] }]
set_property -dict { PACKAGE_PIN Y14 IOSTANDARD LVCMOS33 } [get_ports { spi_sd_io0_io }]
set_property -dict { PACKAGE_PIN T11 IOSTANDARD LVCMOS33 } [get_ports { spi_sd_io1_io }]
set_property -dict { PACKAGE_PIN T10 IOSTANDARD LVCMOS33 } [get_ports { spi_sd_sck_io }]

set_property -dict { PACKAGE_PIN H16   IOSTANDARD LVCMOS33 } [get_ports { sys_clock }];
create_clock -add -name sys_clk_pin -period 8.00 -waveform {0 4.00} [get_ports { sys_clock }];
set_false_path -to [get_cells -hierarchical *top_row_sync1_reg*]
