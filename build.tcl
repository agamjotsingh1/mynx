open_project vivado/mynx/mynx.xpr

# run synth
launch_runs synth_1 -jobs 2
wait_on_run synth_1

if {[get_property PROGRESS [get_runs synth_1]] != "100%"} {
    error "ERROR: Synthesis failed."
}

# run impl and gen bitstream
launch_runs impl_1 -to_step write_bitstream -jobs 2
wait_on_run impl_1

if {[get_property PROGRESS [get_runs impl_1]] != "100%"} {
    error "ERROR: Implementation or bitstream generation failed."
}

close_project
