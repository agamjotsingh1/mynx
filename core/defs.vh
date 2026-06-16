`ifndef DEFS_VH
`define DEFS_VH

// WARNING! comment while generating bitstream
`define SIM

// Memory defs
`define MEMBASE           64'h0000_0000_8000_0000 // memory base 
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
`define RLEN              5  // register index width

`define RSTPC             `MEMBASE // pc when processor resets
`define RSTINSTR          0        // instr when processor resets

// slices from instructions
`define OSLICE            [6:0]   // opcode
`define F3SLICE           [14:12] // funct3
`define F7SLICE           [31:25] // funct7
`define RS1SLICE          [19:15] // rs1
`define RS2SLICE          [24:20] // rs2
`define RDSLICE           [11:7]  // rd
`define CSRSLICE          [31:20]  // csr
`define WSLICE            [31:0]  // word

// OPcodes wrt instruction format
`define OP_SYS            7'b1110011
`define OP_R              7'b0110011
`define OP_RW             7'b0111011 // word instrs (like addw)
`define OP_I              7'b0010011 // standard I format
`define OP_IW             7'b0011011 // word instrs (like addiw)
`define OP_I_LOAD         7'b0000011
`define OP_I_JALR         7'b1100111
`define OP_I_ECALL        7'b1110011
`define OP_S              7'b0100011
`define OP_B              7'b1100011
`define OP_U_LUI          7'b0110111
`define OP_U_AUIPC        7'b0010111
`define OP_J              7'b1101111
`define OP_NULL           7'b0000000

// TODO! add underscore as im kinda getting triggered
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
`define F3CSRRW           3'h1
`define F3CSRRS           3'h2
`define F3CSRRC           3'h3
`define F3CSRRWI          3'h5
`define F3CSRRSI          3'h6
`define F3CSRRCI          3'h7

// Bunch opcodes (BOPcodes)
// bunch is defined as {opcode, funct3, funct7}
// 'z' will be used in casez for alu control sigs

// TODO! merge opcode and bopcode defs
`define BOP_ADD           17'b0110011_000_0000000
`define BOP_ADDW          17'b0111011_000_0000000
`define BOP_ADDI          17'b0010011_000_zzzzzzz
`define BOP_ADDIW         17'b0011011_000_zzzzzzz
`define BOP_LB            17'b0000011_000_zzzzzzz
`define BOP_LH            17'b0000011_001_zzzzzzz
`define BOP_LW            17'b0000011_010_zzzzzzz
`define BOP_LD            17'b0000011_011_zzzzzzz
`define BOP_LBU           17'b0000011_100_zzzzzzz
`define BOP_LHU           17'b0000011_101_zzzzzzz
`define BOP_LWU           17'b0000011_110_zzzzzzz
`define BOP_SB            17'b0100011_000_zzzzzzz
`define BOP_SH            17'b0100011_001_zzzzzzz
`define BOP_SW            17'b0100011_010_zzzzzzz
`define BOP_SD            17'b0100011_011_zzzzzzz
`define BOP_SUB           17'b0110011_000_0100000
`define BOP_SUBW          17'b0111011_000_0100000
`define BOP_SLT           17'b0110011_010_0000000
`define BOP_SLTU          17'b0110011_011_0000000
`define BOP_SLL           17'b0110011_001_0000000
`define BOP_SRL           17'b0110011_101_0000000
`define BOP_SRA           17'b0110011_101_0100000
`define BOP_SLLW          17'b0111011_001_0000000
`define BOP_SRLW          17'b0111011_101_0000000
`define BOP_SRAW          17'b0111011_101_0100000
`define BOP_XOR           17'b0110011_100_0000000
`define BOP_OR            17'b0110011_110_0000000
`define BOP_AND           17'b0110011_111_0000000
`define BOP_SLTI          17'b0010011_010_zzzzzzz
`define BOP_SLTIU         17'b0010011_011_zzzzzzz
`define BOP_SLLI          17'b0010011_001_zzzzzzz
`define BOP_SRLI          17'b0010011_101_zzzzzzz 
`define BOP_SRAI          17'b0010011_101_zzzzzzz // same as SRLI except upper bits of imm
`define BOP_SLLIW         17'b0011011_001_zzzzzzz
`define BOP_SRLIW         17'b0011011_101_zzzzzzz 
`define BOP_SRAIW         17'b0011011_101_zzzzzzz // same as SRLIW except upper bits of imm
`define BOP_XORI          17'b0010011_100_zzzzzzz
`define BOP_ORI           17'b0010011_110_zzzzzzz
`define BOP_ANDI          17'b0010011_111_zzzzzzz
`define BOP_CSRRW         17'b1110011_001_zzzzzzz
`define BOP_CSRRS         17'b1110011_010_zzzzzzz
`define BOP_CSRRC         17'b1110011_011_zzzzzzz
`define BOP_CSRRWI        17'b1110011_101_zzzzzzz
`define BOP_CSRRSI        17'b1110011_110_zzzzzzz
`define BOP_CSRRCI        17'b1110011_111_zzzzzzz

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
// these 3 have different alu opcodes
// for support of word truncated ops
`define ALU_OP_SLLW       4'ha
`define ALU_OP_SRLW       4'hb
`define ALU_OP_SRAW       4'hc

// Branching ctl sigs
`define BRLEN             3
`define BR_NONE           3'h0
`define BR_BEQ            3'h1
`define BR_BNE            3'h2
`define BR_BLT            3'h3
`define BR_BGE            3'h4
`define BR_BLTU           3'h5
`define BR_BGEU           3'h6

// ZICSR based ctl signals
`define ZICSR_OPLEN       3
`define ZICSR_OP_NONE     3'h0
`define ZICSR_OP_CSRRW    3'h1
`define ZICSR_OP_CSRRS    3'h2
`define ZICSR_OP_CSRRC    3'h3
`define ZICSR_OP_CSRRWI   3'h4
`define ZICSR_OP_CSRRSI   3'h5
`define ZICSR_OP_CSRRCI   3'h6

// Control (ctl) signals
`define CTL_BUSLEN            20
`define ALU_SRC(ctl_bus)      ctl_bus[0]     // 1 for imm, 0 for reg
`define REG_WRITE(ctl_bus)    ctl_bus[1]     // 1 for reg to be written
`define MEM_WRITE(ctl_bus)    ctl_bus[2]     // 1 for mem to be written
`define MEM_READ(ctl_bus)     ctl_bus[3]     // 1 for mem to be read 
`define MEM_TO_REG(ctl_bus)   ctl_bus[4]     // 1 for mem reads to be written to reg
`define BW(ctl_bus)           ctl_bus[6:5]   // bitwidth for memory ops
`define SIGN_EXTEND(ctl_bus)  ctl_bus[7]     // 1 if sign extend for memory ops
`define BR(ctl_bus)           ctl_bus[10:8]  // branching ctl sigs
`define JAL(ctl_bus)          ctl_bus[11]    // 1 if instr is jal
`define JALR(ctl_bus)         ctl_bus[12]    // 1 if instr is jalr
`define LUI(ctl_bus)          ctl_bus[13]    // 1 if instr is lui
`define AUIPC(ctl_bus)        ctl_bus[14]    // 1 if instr is auipc 
`define WORDTRUNC(ctl_bus)    ctl_bus[15]    // 1 if instr does word trunc ops (like addiw)
`define ZICSR_OP(ctl_bus)     ctl_bus[18:16] // Zicsr op signals
`define ILLEGAL(ctl_bus)      ctl_bus[19]    // 1 if instr is illegal

// Pipeline stalling signals
// "stall" is wor type bus
`define STLEN                 7
`define STALL_PC              7'b0000001
`define STALL_IF_ID           7'b0000010
`define STALL_CSRFILE         7'b0000100
`define STALL_REGFILE         7'b0001000
`define STALL_ID_EX           7'b0010000
`define STALL_EX_MEM          7'b0100000
`define STALL_MEM_WB          7'b1000000
`define STALL_ALL             7'b1111111
`define STALL_NONE            7'b0000000

// Pipeline nop inserting signals
// "nopi" is wor type bus
`define NOPILEN               5
`define NOPI_PC               5'b00001
`define NOPI_IF_ID            5'b00010
`define NOPI_ID_EX            5'b00100
`define NOPI_EX_MEM           5'b01000
`define NOPI_MEM_WB           5'b10000
`define NOPI_ALL              5'b11111
`define NOPI_NONE             5'b00000

// forwarding defs
`define FWDLEN                2
`define FWD_NONE              2'h0
`define FWD_ID_EX             2'h1
`define FWD_EX_MEM            2'h2
`define FWD_MEM_WB            2'h3

// trap mode defs
`define TRAPMODELEN           3
`define TRAPMODE_NONE         3'b000
`define TRAPMODE_SXCEP        3'b001
`define TRAPMODE_MXCEP        3'b010
`define TRAPMODE_SINTR        3'b101
`define TRAPMODE_MINTR        3'b110

// xcep bus defs
`define XCEP(xcep)            xcep[63]   // is it exception or not
`define XCEP_CAUSE(xcep)      xcep[62:0] // cause is always 63 bits
`define XCEP_INST_ADDR_MISALIGNED       63'd0
`define XCEP_INST_ACCESS_FAULT          63'd1
`define XCEP_ILLEGAL_INSTRUCTION        63'd2
`define XCEP_BREAKPOINT                 63'd3
`define XCEP_LOAD_ADDR_MISALIGNED       63'd4
`define XCEP_LOAD_ACCESS_FAULT          63'd5
`define XCEP_STORE_AMO_ADDR_MISALIGNED  63'd6
`define XCEP_STORE_AMO_ACCESS_FAULT     63'd7
`define XCEP_ECALL_FROM_U_MODE          63'd8
`define XCEP_ECALL_FROM_S_MODE          63'd9
`define XCEP_ECALL_FROM_VS_MODE         63'd10
`define XCEP_ECALL_FROM_M_MODE          63'd11
`define XCEP_INST_PAGE_FAULT            63'd12
`define XCEP_LOAD_PAGE_FAULT            63'd13
`define XCEP_STORE_AMO_PAGE_FAULT       63'd15
`define XCEP_INST_GUEST_PAGE_FAULT      63'd16
`define XCEP_LOAD_GUEST_PAGE_FAULT      63'd20
`define XCEP_VIRTUAL_INSTRUCTION        63'd21
`define XCEP_STORE_GUEST_PAGE_FAULT     63'd22

// S/M interrupt causes
// intentionally kept 63 bits long
// as cause regs MSB bit is for intr/xcep specification
`define MICAUSE_EXT            63'd11
`define MICAUSE_TIMER          63'd7
`define MICAUSE_SOFT           63'd3
`define SICAUSE_EXT            63'd9
`define SICAUSE_TIMER          63'd5
`define SICAUSE_SOFT           63'd1

// Pgtbl defs (Sv39 format)
`define PGTBL_LVLS            3
`define PALEN                 56
`define OFFLEN                12
`define VA2VPN(va, lvl)      {((lvl == 3) ? va[38:30]: ((lvl == 2) ? va[29:21]: va[20:12])), 3'b0}
`define VA2OFF(va)           va[11:0]

// SATP defs
`define SATP_MODE(satp)       satp[63:60]
`define SATP_MODE_BAREMETAL   4'h0
`define SATP_MODE_SV39        4'h8
`define SATP_PPN(satp)        satp[43:0]

// PTE defs
`define PTELEN                64
`define PTE2PA(pte, off)      {pte[53:10], off}

// PTEF (Page table entry flags)
`define PTEFLEN               10
`define PTEF_V                10'b0000000001
`define PTEF_R                10'b0000000010
`define PTEF_W                10'b0000000100
`define PTEF_X                10'b0000001000
`define PTEF_U                10'b0000010000
`define PTEF_G                10'b0000100000
`define PTEF_A                10'b0001000000
`define PTEF_D                10'b0010000000
`define PTEF_RSW              10'b1100000000

// Priviledge levels
`define PRIVLEN               2
`define PRIVU                 2'b00
`define PRIVS                 2'b01
`define PRIVM                 2'b11

// CSR read/write perms
`define CSR_PERMLEN           2
`define CSR_PERM_RO           2'b11
`define CSR_PERM_RW           2'b00, 2'b01, 2'b10

// CSR addresses
`define CSRLEN                12
`define CSR_MSTATUS           12'h300
`define CSR_MEPC              12'h341
`define CSR_MHARTID           12'hf14
`define CSR_MEDELEG           12'h302
`define CSR_MIDELEG           12'h303
`define CSR_MIE               12'h304
`define CSR_MIP               12'h344
`define CSR_MTVEC             12'h305
`define CSR_MSCRATCH          12'h340
`define CSR_MCAUSE            12'h342
`define CSR_MTVAL             12'h343
`define CSR_SSTATUS           12'h100
`define CSR_SEPC              12'h141
`define CSR_SATP              12'h180
`define CSR_STVEC             12'h105
`define CSR_SSCRATCH          12'h140
`define CSR_SCAUSE            12'h142
`define CSR_STVAL             12'h143
`define CSR_SIE               12'h104
`define CSR_SIP               12'h144
`define CSR_PMPCFG0           12'h3a0
`define CSR_PMPADDR0          12'h3b0

// CSR Maps
`define CSRMAPLEN             5 // change this len whenever adding more CSRs
`define CSRMAP_MSTATUS        5'd0
`define CSRMAP_MEPC           5'd1
`define CSRMAP_MHARTID        5'd2
`define CSRMAP_MEDELEG        5'd3
`define CSRMAP_MIDELEG        5'd4
`define CSRMAP_MIE            5'd5
`define CSRMAP_MIP            5'd6
`define CSRMAP_MTVEC          5'd7
`define CSRMAP_MSCRATCH       5'd8
`define CSRMAP_MCAUSE         5'd9
`define CSRMAP_MTVAL          5'd10
`define CSRMAP_SSTATUS        5'd11
`define CSRMAP_SEPC           5'd12
`define CSRMAP_SATP           5'd13
`define CSRMAP_STVEC          5'd14
`define CSRMAP_SSCRATCH       5'd15
`define CSRMAP_SCAUSE         5'd16
`define CSRMAP_STVAL          5'd17
`define CSRMAP_SIE            5'd18
`define CSRMAP_SIP            5'd19
`define CSRMAP_PMPCFG0        5'd20
`define CSRMAP_PMPADDR0       5'd21

// MSTATUS fields
`define MSTATUS_RST           64'h0000_000A_0000_0000
`define MSTATUS_MASK          64'h0000_0000_007E_19AA
`define MSTATUS_SD(val)       val[63]
`define MSTATUS_WPRI_5(val)   val[62:43] // Reserved (WPRI)
`define MSTATUS_MDT(val)      val[42]
`define MSTATUS_MPELP(val)    val[41]
`define MSTATUS_WPRI_4(val)   val[40]    // Reserved (WPRI)
`define MSTATUS_MPV(val)      val[39]
`define MSTATUS_GVA(val)      val[38]
`define MSTATUS_MBE(val)      val[37]
`define MSTATUS_SBE(val)      val[36]
`define MSTATUS_SXL(val)      val[35:34]
`define MSTATUS_UXL(val)      val[33:32]
`define MSTATUS_WPRI_3(val)   val[31:25] // Reserved (WPRI)
`define MSTATUS_SDT(val)      val[24]
`define MSTATUS_SPELP(val)    val[23]
`define MSTATUS_TSR(val)      val[22]
`define MSTATUS_TW(val)       val[21]
`define MSTATUS_TVM(val)      val[20]
`define MSTATUS_MXR(val)      val[19]
`define MSTATUS_SUM(val)      val[18]
`define MSTATUS_MPRV(val)     val[17]
`define MSTATUS_XS(val)       val[16:15]
`define MSTATUS_FS(val)       val[14:13]
`define MSTATUS_MPP(val)      val[12:11]
`define MSTATUS_VS(val)       val[10:9]
`define MSTATUS_SPP(val)      val[8]
`define MSTATUS_MPIE(val)     val[7]
`define MSTATUS_UBE(val)      val[6]
`define MSTATUS_SPIE(val)     val[5]
`define MSTATUS_WPRI_2(val)   val[4]     // Reserved (WPRI)
`define MSTATUS_MIE(val)      val[3]
`define MSTATUS_WPRI_1(val)   val[2]     // Reserved (WPRI)
`define MSTATUS_SIE(val)      val[1]
`define MSTATUS_WPRI_0(val)   val[0]     // Reserved (WPRI)

// SSTATUS (same fields as MSTATUS but restricted view)
`define SSTATUS_MASK          64'h0000_0000_000C_0122

// MIP defs
`define MIP_MMASK             64'h0000_0000_0000_0888
`define MIP_SMASK             64'h0000_0000_0000_0222

// get S/M interrupt cause from mip (assumes there is an interrupt, atleast a software one)
`define MIP_GET_MICAUSE(mip) \
  (mip[11] ? `MICAUSE_EXT : \
  (mip[3]  ? `MICAUSE_SOFT: `MICAUSE_TIMER))

`define MIP_GET_SICAUSE(mip) \
  (mip[9]  ? `SICAUSE_EXT : \
  (mip[1]  ? `SICAUSE_SOFT: `SICAUSE_TIMER))

// MIE defs
`define MIE_MMASK             64'h0000_0000_0000_0888
`define MIE_SMASK             64'h0000_0000_0000_0222

// (S/M)TVEC defs
`define VEC_MASK              64'hFFFF_FFFF_FFFF_FFFC

`endif
