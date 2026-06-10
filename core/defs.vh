`ifndef DEFS_VH
`define DEFS_VH

// WARNING! comment while generating bitstream
`define SIM

// Memory defs
`define NBANKS            8    // number of banks (bytes per word)
`define BANKLEN           8    // width of each bank (8 bits <=> 1 Byte)
`define DEPTH             1024 // number of 64 bit doublewords
`define BYTE              8
`define HALFWORD          16
`define WORD              32
`define DBLWORD           64

// BitWidth Codes for memory access
`define BWLEN               2
`define BW_BYTE             2'h0 // 8 bits (byte)
`define BW_HALFWORD         2'h1 // 16 bits (half word)
`define BW_WORD             2'h2 // 32 bits (word)
`define BW_DBLWORD          2'h3 // 64 bits (double word)
`define BW_NULL_ENMASK      8'b00000000
`define BW_BYTE_ENMASK      8'b00000001
`define BW_HALFWORD_ENMASK  8'b00000011
`define BW_WORD_ENMASK      8'b00001111
`define BW_DBLWORD_ENMASK   8'b11111111

// Utility definitions
`define W(width) [(width)-1:0]

// System Constants
`define DLEN              64 // data width
`define ILEN              32 // instruction width
`define RLEN              5  // register index width
`define OLEN              7  // opcode width
`define F3LEN             3  // funct3 width
`define F7LEN             7  // funct7 width
`define MLEN              8  // byte addressable mem => 8 bits = 1 byte
`define ADDRLEN           $clog2(`DEPTH*`NBANKS)    // mem addr width
`define BANK_ADDRLEN      $clog2(`DEPTH) // bank addr width

`define RSTPC             0  // pc when processor resets
`define RSTINSTR          0  // instr when processor resets

// slices from instructions
`define OSLICE            [6:0]   // opcode
`define F3SLICE           [14:12] // funct3
`define F7SLICE           [31:25] // funct7
`define RS1SLICE          [19:15] // rs1
`define RS2SLICE          [24:20] // rs2
`define RDSLICE           [11:7]  // rd

// OPcodes wrt instruction format
`define OP_R              7'b0110011
`define OP_I              7'b0010011 // standard I format
`define OP_I_LOAD         7'b0000011
`define OP_I_JALR         7'b1100111
`define OP_I_ECALL        7'b1110011
`define OP_S              7'b0100011
`define OP_B              7'b1100011
`define OP_U_LUI          7'b0110111
`define OP_U_AUIPC        7'b0010111
`define OP_J              7'b1101111

// Some useful funct3 defs
`define F3LB              3'h0
`define F3LH              3'h1
`define F3LW              3'h2
`define F3LD              3'h3
`define F3LBU             3'h4
`define F3LHU             3'h5
`define F3LWU             3'h6
`define F3SB              3'h0
`define F3SH              3'h1
`define F3SW              3'h2
`define F3SD              3'h3
`define F3BEQ             3'h0
`define F3BNE             3'h1
`define F3BLT             3'h4
`define F3BGE             3'h5
`define F3BLTU            3'h6
`define F3BGEU            3'h7

// Bunch opcodes (BOPcodes)
// bunch is defined as {opcode, funct3, funct7}
// 'z' will be used in casez for alu control sigs
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
`define BOP_SRAI          17'b0010011_101_zzzzzzz // same as SRLI except upper bits of imm
`define BOP_XORI          17'b0010011_100_zzzzzzz
`define BOP_ORI           17'b0010011_110_zzzzzzz
`define BOP_ANDI          17'b0010011_111_zzzzzzz

// ALU OPCodes (custom defined)
`define ALU_OPLEN         4

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

// Branching ctl sigs
`define BRLEN             3
`define BR_NONE           3'h0
`define BR_BEQ            3'h1
`define BR_BNE            3'h2
`define BR_BLT            3'h3
`define BR_BGE            3'h4
`define BR_BLTU           3'h5
`define BR_BGEU           3'h6

// Control (ctl) signals
`define CTL_BUSLEN            12

`define ALU_SRC(ctl_bus)      ctl_bus[0]    // 1 for imm, 0 for reg
`define REG_WRITE(ctl_bus)    ctl_bus[1]    // 1 for reg to be written
`define MEM_WRITE(ctl_bus)    ctl_bus[2]    // 1 for mem to be written
`define MEM_READ(ctl_bus)     ctl_bus[3]    // 1 for mem to be read 
`define MEM_TO_REG(ctl_bus)   ctl_bus[4]    // 1 for mem reads to be written to reg
`define BW(ctl_bus)           ctl_bus[6:5]  // bitwidth for memory ops
`define SIGN_EXTEND(ctl_bus)  ctl_bus[7]    // 1 if sign extend for memory ops
`define BR(ctl_bus)           ctl_bus[10:8] // branching ctl sigs
`define JAL(ctl_bus)          ctl_bus[11]   // 1 if the instruction jal

// Pipeline stalling signals
// "stall" is wor type bus
`define STLEN                 5
`define STALL_PC              5'b00001
`define STALL_IF_ID           5'b00010
`define STALL_ID_EX           5'b00100
`define STALL_EX_MEM          5'b01000
`define STALL_MEM_WB          5'b10000
`define STALL_ALL             5'b11111
`define STALL_NONE            5'b00000

`endif
