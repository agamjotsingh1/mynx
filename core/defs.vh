`ifndef DEFS_VH
`define DEFS_VH

`define W(width) [(width)-1:0]

// System Constants
`define DLEN              64 // data width
`define ILEN              32 // instruction width
`define RLEN              5  // register index width

// OPcodes
`define OP_LUI            7'b0110111
`define OP_AUIPC          7'b0010111
`define OP_JAL            7'b1101111
`define OP_R_TYPE         7'b0110011

// ALU OPCodes (custom defined)
`define ALU_OP_W          4

`define ALU_OP_ADD        4'h0
`define ALU_OP_SUB        4'h1
`define ALU_OP_XOR        4'h2
`define ALU_OP_OR         4'h3
`define ALU_OP_AND        4'h4
`define ALU_OP_SLL        4'h5
`define ALU_OP_SRL        4'h6
`define ALU_OP_SRA        4'h7
`define ALU_OP_SLT        4'h8
`define ALU_OP_SLTU       4'h9

`endif
