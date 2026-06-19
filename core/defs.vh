`ifndef DEFS_VH
`define DEFS_VH

// WARNING! comment while generating bitstream
`define SIM

// Memory defs
`define MEMBASE           64'h0000_0000_8000_0000 // memory base 
`define NBANKS            8    // number of banks (bytes per word)
`define BANKLEN           8    // width of each bank (8 bits <=> 1 Byte)
`define DEPTH             524288 // number of 64 bit doublewords
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
`define F12LEN            12  // funct12 width
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
`define F12SLICE          [31:20] // funct12
`define RS1SLICE          [19:15] // rs1
`define RS2SLICE          [24:20] // rs2
`define RDSLICE           [11:7]  // rd
`define CSRSLICE          [31:20] // csr
`define WSLICE            [31:0]  // word
`define CSRPERMSLICE      [11:10] // csr read only or not (perm)
`define CSRPRIVSLICE      [9:8]   // csr privilege 

// OPcodes wrt instruction format
`define OP_SYS            7'b1110011
`define OP_R              7'b0110011
`define OP_RW             7'b0111011 // word instrs (like addw)
`define OP_I              7'b0010011 // standard I format
`define OP_IW             7'b0011011 // word instrs (like addiw)
`define OP_I_LOAD         7'b0000011
`define OP_I_JALR         7'b1100111
`define OP_S              7'b0100011
`define OP_B              7'b1100011
`define OP_U_LUI          7'b0110111
`define OP_U_AUIPC        7'b0010111
`define OP_J              7'b1101111
`define OP_NULL           7'b0000000

// TODO! add underscore as im kinda getting triggered
// funct3 defs
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
`define F3NULL            3'h0

// funct7 defs
`define F7SFENCEVMA       7'h09

// funct12 defs
`define F12ECALL          12'b000000000000
`define F12MRET           12'b001100000010
`define F12SRET           12'b000100000010
`define F12ECALL          12'b000000000000
`define F12EBREAK         12'b000000000001

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
`define BOP_SRLI          17'b0010011_101_0000000 
`define BOP_SRAI          17'b0010011_101_0100000
`define BOP_SLLIW         17'b0011011_001_zzzzzzz
`define BOP_SRLIW         17'b0011011_101_0000000
`define BOP_SRAIW         17'b0011011_101_0100000
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
`define ALU_OP_ILLEGAL    4'hd

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
`define CTL_BUSLEN            26
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
`define CSR_WRITE(ctl_bus)    ctl_bus[19]    // 1 if csr is to be written to
`define MRET(ctl_bus)         ctl_bus[20]    // 1 if instr is mret
`define SRET(ctl_bus)         ctl_bus[21]    // 1 if instr is sret
`define ECALL(ctl_bus)        ctl_bus[22]    // 1 if instr is ecall
`define EBREAK(ctl_bus)       ctl_bus[23]    // 1 if instr is ebreak
`define SFENCEVMA(ctl_bus)    ctl_bus[24]    // 1 if instr is sfence.vma
`define ILLEGAL(ctl_bus)      ctl_bus[25]    // 1 if instr is illegal

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
`define TRAPMODELEN           6
`define TRAPMODE_NONE         6'b000000
`define TRAPMODE_SXCEP        6'b000001
`define TRAPMODE_MXCEP        6'b000010
`define TRAPMODE_SINTR        6'b000100
`define TRAPMODE_MINTR        6'b001000
`define TRAPMODE_MRET         6'b010000
`define TRAPMODE_SRET         6'b100000

`define TRAP_TAKEN(trap_mode) (|trap_mode)
`define TRAP_RET(trap_mode)   (trap_mode[5] | trap_mode[4])
`define TRAP_INTR(trap_mode)  (trap_mode[3] | trap_mode[2])
`define TRAP_XCEP(trap_mode)  (trap_mode[1] | trap_mode[0])
// only for intr/xceps
`define TRAP_M(trap_mode)     (trap_mode[1] | trap_mode[3])
`define TRAP_S(trap_mode)     (trap_mode[0] | trap_mode[2])

// xcep bus defs
`define XCEP_CAUSELEN         63
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

// PTE defs
`define PTELEN                64
`define PTE2PA(pte, off)      {pte[53:10], off}

// PTEF (Page table entry flags)
`define PTEFLEN               10
`define PTEF(pte)             pte[9:0]
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
// `define CSR_MTVAL             12'h343
`define CSR_SSTATUS           12'h100
`define CSR_SEPC              12'h141
`define CSR_SATP              12'h180
`define CSR_STVEC             12'h105
`define CSR_SSCRATCH          12'h140
`define CSR_SCAUSE            12'h142
// `define CSR_STVAL             12'h143
`define CSR_SIE               12'h104
`define CSR_SIP               12'h144
`define CSR_PMPCFG0           12'h3a0
`define CSR_PMPADDR0          12'h3b0

// MSTATUS/SSTATUS fields
// SSTATUS is just restrictively masked MSTATUS
`define SSTATUS_MASK          64'h0000_0000_000C_0122
`define MSTATUS_RST           64'h0000_000A_0000_0000
`define MSTATUS_MASK          64'h0000_0000_007E_19AA
`define MSTATUS_MPP(val)      val[12:11]
`define MSTATUS_SPP(val)      val[8]
`define MSTATUS_MPIE(val)     val[7]
`define MSTATUS_SPIE(val)     val[5]
`define MSTATUS_MIE(val)      val[3]
`define MSTATUS_SIE(val)      val[1]

// MEPC/SEPC defs
`define MEPC_RST              64'h0000_0000_0000_0000
`define SEPC_RST              64'h0000_0000_0000_0000
`define MEPC_MASK             64'hFFFF_FFFF_FFFF_FFFC
`define SEPC_MASK             64'hFFFF_FFFF_FFFF_FFFC

// MHARTID defs
`define MHARTID_RST           64'h0000_0000_0000_0000

// MEDELEG defs
`define MEDELEG_RST           64'h0000_0000_0000_0000
`define MEDELEG_MASK          64'h0000_0000_0000_B3FF

// MIDELEG defs
`define MIDELEG_RST           64'h0000_0000_0000_0000
`define MIDELEG_MASK          64'h0000_0000_0000_0222

// MIE/SIE defs
// SIE is just restrictively masked MIE
`define MIE_RST               64'h0000_0000_0000_0000
`define MIE_MASK              64'h0000_0000_0000_0AAA
`define SIE_MASK              64'h0000_0000_0000_0222

// MIP/SIP defs
// SIP is just restrictively masked MIP
`define MIP_RST               64'h0000_0000_0000_0000
`define MIP_MASK              64'h0000_0000_0000_0022
`define MIP_MEIP_POS          11
`define MIP_SEIP_POS          9
`define MIP_MTIP_POS          7
`define MIP_STIP_POS          5
`define SIP_MASK              64'h0000_0000_0000_0002
`define SIP_READ_MASK         64'h0000_0000_0000_0222
// get S/M interrupt cause from mip (assumes there is an interrupt, atleast a software one)
// FIXME! add other s-mode interrupt causes
`define MIP_GET_MICAUSE(mip) \
  (mip[11] ? `MICAUSE_EXT : \
  (mip[9]  ? `SICAUSE_EXT : \
  (mip[3]  ? `MICAUSE_SOFT: `MICAUSE_TIMER)))

`define MIP_GET_SICAUSE(mip) \
  (mip[9]  ? `SICAUSE_EXT : \
  (mip[1]  ? `SICAUSE_SOFT: `SICAUSE_TIMER))

// (S/M)TVEC defs
`define MTVEC_RST             `RSTPC
`define STVEC_RST             `RSTPC
`define VEC_MASK              64'hFFFF_FFFF_FFFF_FFFC
`define MTVEC_MASK            `VEC_MASK
`define STVEC_MASK            `VEC_MASK

// (S/M)SCRATCH defs
`define MSCRATCH_RST          64'h0000_0000_0000_0000
`define SSCRATCH_RST          64'h0000_0000_0000_0000

// (S/M)CAUSE defs
`define MCAUSE_RST            64'h0000_0000_0000_0000
`define SCAUSE_RST            64'h0000_0000_0000_0000

// PMPCFG0 defs
`define PMPCFG0_RST           64'h0000_0000_0000_0000
`define PMPCFG0_MASK          64'h9F9F_9F9F_9F9F_9F9F

// PMPADDR0 defs
`define PMPADDR0_RST          64'h0000_0000_0000_0000
`define PMPADDR0_MASK         64'h003F_FFFF_FFFF_FFFF

// SATP defs
`define SATP_RST              64'h0000_0000_0000_0000
// only SV39/baremetal is allowed, WARL fields!
`define SATP_MASK             64'h8FFF_FFFF_FFFF_FFFF
`define SATP_MODE(satp)       satp[63:60]
`define SATP_MODE_BAREMETAL   4'h0
`define SATP_MODE_SV39        4'h8
`define SATP_PPN(satp)        satp[43:0]

// PMP defs
`define PMPADDRSHIFT          2
`define PMPCFG_R(pmpcfg0)     pmpcfg0[0]
`define PMPCFG_W(pmpcfg0)     pmpcfg0[1]
`define PMPCFG_X(pmpcfg0)     pmpcfg0[2]
`define PMPCFG_L(pmpcfg0)     pmpcfg0[7]

// UART defs
`define UARTBASE              64'h0000_0000_1000_0000
`define UARTTOP               64'h0000_0000_1000_0111
`define UART_ADDRLEN          3
// read mode
`define UART_READ_RHR         3'b000
`define UART_READ_ISR         3'b010
`define UART_READ_LSR         3'b101
`define UART_READ_SCR         3'b111 // scratch
// write mode
`define UART_WRITE_THR        3'b000
`define UART_WRITE_IER        3'b001
`define UART_WRITE_FCR        3'b010
`define UART_WRITE_LCR        3'b011
`define UART_WRITE_SCR        3'b111 // scratch
// fifo defs
`define UART_FIFOLEN          16
// fcr defs
`define UART_FCR_EN(fcr)      fcr[0]
`define UART_FCR_RST(fcr)     fcr[1]
`define UART_FCR_RSTMASK      8'h02
`define UART_FCR_TRIG(fcr)    fcr[7:6]
`define UART_FCR_TRIG_1       2'b00
`define UART_FCR_TRIG_4       2'b01
`define UART_FCR_TRIG_8       2'b10
`define UART_FCR_TRIG_14      2'b11
// ier defs
`define UART_IER_RX_INTR(ier) ier[0]
`define UART_IER_TX_INTR(ier) ier[1]
// isr defs
`define UART_INTRIDLEN              3
`define UART_INTRID_DATA_READY      3'b010
`define UART_INTRID_TX_EMPTY        3'b001

// BLKDEV defs
`define BLKDEVBASE            64'h0000_0000_2000_0000
`define BLKDEVTOP             64'h0000_0000_2000_0018
`define BLKDEV_STATUS         64'h0000_0000_0000_0000
`define BLKDEV_SECTOR         64'h0000_0000_0000_0008
`define BLKDEV_MEM_ADDR       64'h0000_0000_0000_0010
`define BLKDEV_CMD            64'h0000_0000_0000_0018
`define SECTOR_WORDCOUNT      64 // 512 bytes (64*8 bytes) = 1 sector

`define BLKDEV_IDLE           64'd0
`define BLKDEV_BUSY           64'd1
`define BLKDEV_ERROR          64'd2

`define BLKDEV_CMD_READ       64'd1
`define BLKDEV_CMD_WRITE      64'd2

// PLIC defs
`define PLICBASE              64'h0000_0000_3000_0000
`define PLICTOP               64'h0000_0000_3000_0000
`define PLIC_IRQ_NONE         64'd0
`define PLIC_IRQ_UART         64'd1
`define PLIC_IRQ_BLKDEV       64'd2

// CLINT defs
`define CLINTBASE             64'h0000_0000_4000_0000
`define CLINTTOP              64'h0000_0000_4000_0008
`define CLINT_MTIME           64'h0000_0000_0000_0000
`define CLINT_MTIMECMP        64'h0000_0000_0000_0008


`endif
