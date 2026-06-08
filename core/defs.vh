`ifndef DEFS_VH
`define DEFS_VH

`define W(width) [(width)-1:0]

// System Constants
`define DLEN              64
`define ILEN              32

// OPcodes
`define OP_LUI            7'b0110111
`define OP_AUIPC          7'b0010111
`define OP_JAL            7'b1101111
`define OP_R_TYPE         7'b0110011

// ALU Control Codes
`define ALU_OP_W          4

`define ALU_OP_ADD        4'b0000
`define ALU_OP_SUB        4'b0001
`define ALU_OP_MUL        4'b0010
`define ALU_OP_DIV        4'b0011

`define ALU_OP_XOR        4'b0100
`define ALU_OP_OR         4'b0101
`define ALU_OP_AND        4'b0110

`define ALU_OP_SLL        4'b0111
`define ALU_OP_SRL        4'b1000
`define ALU_OP_SRA        4'b1001

`define ALU_OP_SLT        4'b1010
`define ALU_OP_SLTU       4'b1011

`endif