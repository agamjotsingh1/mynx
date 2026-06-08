`ifndef DEFS_VH
`define DEFS_VH

// Utility definitions
`define W(width) [(width)-1:0]

// System Constants
`define DLEN              64 // data width
`define ILEN              32 // instruction width
`define RLEN              5  // register index width
`define OLEN              7  // opcode width
`define F3LEN             3  // funct3 width
`define F7LEN             7  // funct7 width

`define OSTART            0  // start bit index of opcode
`define F3START           12 // start bit index of funct3
`define F7START           25 // start bit index of funct7

// Bunch opcodes (BOPcodes)
// bunch is defined as {opcode, funct3, funct7}
// 'z' will be used in casez for control sigs
`define BOP_ADD           17'b0110011_000_0000000
`define BOP_ADDI          17'b0010011_000_zzzzzzz
`define BOP_LB            17'b0000011_000_zzzzzzz
`define BOP_LH            17'b0000011_001_zzzzzzz
`define BOP_LW            17'b0000011_010_zzzzzzz
`define BOP_LD            17'b0000011_011_zzzzzzz
`define BOP_LBU           17'b0000011_100_zzzzzzz
`define BOP_LHU           17'b0000011_101_zzzzzzz
`define BOP_SB            17'b0100011_000_zzzzzzz
`define BOP_SH            17'b0100011_001_zzzzzzz
`define BOP_SW            17'b0100011_010_zzzzzzz
`define BOP_SD            17'b0100011_011_zzzzzzz
`define BOP_SUB           17'b0110011_000_0100000
`define BOP_SLT           17'b0110011_010_0000000
`define BOP_SLTU          17'b0110011_011_0000000
`define BOP_SLL           17'b0110011_001_0000000
`define BOP_SRL           17'b0110011_101_0000000
`define BOP_SRA           17'b0110011_101_0100000
`define BOP_XOR           17'b0110011_100_0000000
`define BOP_OR            17'b0110011_110_0000000
`define BOP_AND           17'b0110011_111_0000000
`define BOP_SLTI          17'b0010011_010_zzzzzzz
`define BOP_SLTIU         17'b0010011_011_zzzzzzz
`define BOP_SLLI          17'b0010011_001_zzzzzzz
`define BOP_SRLI          17'b0010011_101_zzzzzzz 
`define BOP_SRAI          17'b0010011_101_zzzzzzz // difference comes in imm
`define BOP_XORI          17'b0010011_100_zzzzzzz
`define BOP_ORI           17'b0010011_110_zzzzzzz
`define BOP_ANDI          17'b0010011_111_zzzzzzz

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
