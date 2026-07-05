set origin_dir "."

create_project mynx ./vivado/mynx -part xc7z020clg400-1 -force
set local_board_repo [file normalize "$origin_dir/board_files"]
set_property board_part_repo_paths $local_board_repo [current_project]
set_property board_part tul.com.tw:pynq-z2:part0:1.0 [current_project]

set_property ip_repo_paths [file normalize "$origin_dir/rgb2dvi"] [current_project]
update_ip_catalog

add_files [glob -nocomplain $origin_dir/core/modules/*.v]
add_files [glob -nocomplain $origin_dir/core/pipeline/*.v]
add_files $origin_dir/core/core.v
add_files $origin_dir/core/defs.vh
set_property is_global_include true [get_files $origin_dir/core/defs.vh]
add_files [glob -nocomplain $origin_dir/pynq/ip/*/*.xci]
add_files -fileset constrs_1 $origin_dir/pynq/constraints/constraints.xdc

source $origin_dir/pynq/bd/bd.tcl

make_wrapper -files [get_files design_1.bd] -top -import
set_property top design_1_wrapper [current_fileset]
