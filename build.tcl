set origin_dir [file dirname [file normalize [info script]]]
if {$origin_dir eq ""} { set origin_dir [pwd] }
set local_board_repo [file normalize "$origin_dir/pynq/board_files"]
set_param board.repoPaths [list $local_board_repo]
open_project vivado/mynx/mynx.xpr
update_compile_order -fileset sources_1

set num_jobs 1
if {$argc >= 1} {
    set num_jobs [lindex $argv 0]
}
if {![string is integer -strict $num_jobs] || $num_jobs < 1} {
    puts stderr "WARNING: invalid jobs value '$num_jobs', defaulting to 1"
    set num_jobs 1
}

set synth_phases {
    {Starting synth_design}                      2
    {Starting RTL Elaboration}                   8
    {Finished RTL Elaboration}                  20
    {Start Handling Custom Attributes}          24
    {Start Loading Part and Timing Information} 28
    {Start Applying 'set_property' XDC}         32
    {Start RTL Component Statistics}            36
    {Start Part Resource Summary}               38
    {Start Cross Boundary and Area Optim}       42
    {Start Applying XDC Timing Constraints}     55
    {Start Timing Optimization}                 65
    {Start Technology Mapping}                  74
    {Start IO Insertion}                        80
    {Start Renaming Generated Instances}        84
    {Start Rebuilding User Hierarchy}           87
    {Start Renaming Generated Ports}            89
    {Start Renaming Generated Nets}             91
    {Start Writing Synthesis Report}            95
    {Synthesis finished}                        99
}

set impl_phases {
    {Starting Logic Optimization Task}           5
    {Starting Placer Task}                      20
    {Phase 3 Detail Placement}                  35
    {Starting Physical Synthesis Task}          45
    {Starting Routing Task}                     52
    {Phase 4 Rip-up And Reroute}                65
    {Phase 10 Post Router Timing}               78
    {Starting Post-Route Physical Synthesis}    82
    {Command: write_bitstream}                  90
    {Writing bitstream}                         95
    {write_bitstream completed successfully}    99
}

proc bar_width {} {
    set cols 80
    if {![catch {exec stty size < /dev/tty} res]} {
        set cols [lindex $res 1]
    } elseif {[info exists ::env(COLUMNS)] && $::env(COLUMNS) ne ""} {
        set cols $::env(COLUMNS)
    }
    # reserve room for label (16) + " [" + "] 100%"
    set w [expr {$cols - 24}]
    if {$w < 10} { set w 10 }
    return $w
}

proc draw_bar {label pct} {
    set width [bar_width]
    set filled [expr {int($pct * $width / 100.0)}]
    set empty  [expr {$width - $filled}]
    set bar "[string repeat "#" $filled][string repeat "-" $empty]"
    # stderr: stdout is /dev/null'd by the Makefile to mute Vivado's chatter
    puts -nonewline stderr [format "\r%-16s \[%s\] %3d%%" $label $bar $pct]
    flush stderr
}

# highest numbered phase whose marker has appeared in the log so far
proc log_pct {logfile phases} {
    if {![file exists $logfile]} { return 0 }
    if {[catch {open $logfile r} fh]} { return 0 }
    set text [read $fh]
    close $fh
    set pct 0
    foreach {pat val} $phases {
        if {[string first $pat $text] >= 0 && $val > $pct} { set pct $val }
    }
    return $pct
}

proc run_is_alive {dir} {
    return [expr {[llength [glob -nocomplain -directory $dir __*_is_running__]] > 0}]
}

proc monitor_run {run label phases launch_args} {
    reset_run $run
    launch_runs $run {*}$launch_args

    set dir     [get_property DIRECTORY [get_runs $run]]
    set logfile [file join $dir runme.log]
    set pct     0
    set seen    0
    set waited  0

    draw_bar $label 0
    while {1} {
        after 2000
        incr waited 2

        if {[run_is_alive $dir]} {
            set seen 1
        } elseif {$seen || $waited > 120} {
            break
        }

        set new [log_pct $logfile $phases]
        if {$new > $pct} {
            set pct $new
            draw_bar $label $pct
        }
    }

    wait_on_run $run
    draw_bar $label 100
    puts stderr ""
}

# synthesis
monitor_run synth_1 "Synthesis" $synth_phases [list -jobs $num_jobs]
set synth_status [get_property STATUS [get_runs synth_1]]
if {![string match "*Complete*" $synth_status]} {
    puts stderr "ERROR: Synthesis failed with status: $synth_status"
    puts stderr "Check the log at: vivado/mynx/mynx.runs/synth_1/runme.log"
    exit 1
}

# implementation + bitstream
monitor_run impl_1 "Impl + Bitstream" $impl_phases [list -jobs $num_jobs -to_step write_bitstream]
set bit_status [get_property STATUS [get_runs impl_1]]
if {![string match "*write_bitstream Complete*" $bit_status] && ![string match "*Complete*" $bit_status]} {
    puts stderr "ERROR: Bitstream generation failed with status: $bit_status"
    puts stderr "Check the log at: vivado/mynx/mynx.runs/impl_1/runme.log"
    exit 1
}

close_project
