set origin_dir [file dirname [file normalize [info script]]]
if {$origin_dir eq ""} { set origin_dir [pwd] }
set local_board_repo [file normalize "$origin_dir/pynq/board_files"]
set_param board.repoPaths [list $local_board_repo]

open_project vivado/mynx/mynx.xpr

update_compile_order -fileset sources_1

launch_runs synth_1 -jobs 2
wait_on_run synth_1

set synth_status [get_property STATUS [get_runs synth_1]]
if {![string match "*Complete*" $synth_status]} {
    puts "ERROR: Synthesis failed with status: $synth_status"
    puts "Check the log at: vivado/mynx/mynx.runs/synth_1/runme.log"
    exit 1
}

launch_runs impl_1 -to_step write_bitstream -jobs 2
wait_on_run impl_1

set impl_status [get_property STATUS [get_runs impl_1]]
if {![string match "*Complete*" $impl_status]} {
    puts "ERROR: Implementation failed with status: $impl_status"
    puts "Check the log at: vivado/mynx/mynx.runs/impl_1/runme.log"
    exit 1
}

close_project
