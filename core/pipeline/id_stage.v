`include "defs.vh"
`include "modules/regfile.v"
`include "modules/immgen.v"
`include "modules/alu_ctl.v"
`include "modules/ctl.v"
`include "modules/csrfile.v"

module id_stage (
  input wire           clk,
  input wire           rst,
  input wire `W(`DLEN) pc,
  input wire `W(`ILEN) instr,
  input wor `W(`STLEN) stall, // for csr

  // parsing results
  output wire `W(`RLEN)   rs1,
  output wire `W(`RLEN)   rs2,
  output wire `W(`RLEN)   rd,
  output reg  `W(`DLEN)   csr_data,  // data to pass to EX-stage to update rd
  output wire `W(`DLEN)   satp,
  output wire `W(`DLEN)   regdata1,
  output wire `W(`DLEN)   regdata2,
  output wire `W(`DLEN)   imm,

  // alu control outputs
  output wire `W(`ALU_OPLEN) alu_op,

  // control outputs
  output wire `W(`CTL_BUSLEN) ctl_bus,

  // branch taken or not (for both branch and jal instr)
  output reg branch_taken,

  // next pc (for branching/jal)
  output reg `W(`DLEN) next_pc,

  // regwrites from wb stage
  input wire `W(`RLEN) __wb_rd,
  input wire           __wb_reg_write,

  // fwd controls
  input wire `W(`FWDLEN)  fwd1,
  input wire `W(`FWDLEN)  fwd2,

  // fwd inputs
  input wire `W(`DLEN)    __mem_ex_res,
  input wire `W(`DLEN)    __wb_write_data
);
  // instruction parsing
  assign rs1 = instr`RS1SLICE;
  assign rs2 = instr`RS2SLICE;
  assign rd  = instr`RDSLICE;
  assign csr = instr`CSRSLICE;

  regfile regfile_instance (
    .clk(clk),
    .rst(rst),

    .read_addr1(rs1),
    .read_data1(regdata1),

    .read_addr2(rs2),
    .read_data2(regdata2),

    .write_en(__wb_reg_write),
    .write_addr(__wb_rd),
    .write_data(__wb_write_data)
  );

  immgen immgen_instance (
    .instr(instr),
    .imm(imm)
  );

  alu_ctl alu_ctl_instance (
    .instr(instr),
    .alu_op(alu_op)
  );

  ctl ctl_instance (
    .instr(instr),
    .ctl_bus(ctl_bus)
  );

  wire `W(`DLEN) regdata1_fwded = 
    (fwd1 == `FWD_EX_MEM) ? __mem_ex_res:
    ((fwd1 == `FWD_MEM_WB) ? __wb_write_data: regdata1);

  wire `W(`DLEN) regdata2_fwded = 
    (fwd2 == `FWD_EX_MEM) ? __mem_ex_res:
    ((fwd2 == `FWD_MEM_WB) ? __wb_write_data: regdata2);

  // branching logic comparator
  wire zero = (regdata1_fwded == regdata2_fwded);
  wire lt   = ($signed(regdata1_fwded) < $signed(regdata2_fwded));
  wire ltu  = ($unsigned(regdata1_fwded) < $unsigned(regdata2_fwded));

  // branching logic
  always @(*) begin
    case (`BR(ctl_bus))
      `BR_NONE: branch_taken = 0;
      `BR_BEQ:  branch_taken = zero;
      `BR_BNE:  branch_taken = ~zero;
      `BR_BLT:  branch_taken = lt;
      `BR_BGE:  branch_taken = ~lt;
      `BR_BLTU: branch_taken = ltu;
      `BR_BGEU: branch_taken = ~ltu;
      default:  branch_taken = 0;
    endcase

    branch_taken |= (`JAL(ctl_bus) | `JALR(ctl_bus));
  end

  // shift is implicitly added in the immgen block
  // TODO! optimize this to take the alu output instead of an extra adder here
  assign next_pc = (`JALR(ctl_bus) ? regdata1_fwded: pc) + imm;

  // finish the csr reading/writing task in ID stage only
  wire `W(`CSRLEN) csr;
  wire `W(`DLEN) csr_read_data;
  // TODO! move away ZICSR_OP from ctl module to optimize ctl_bus passthroughs
  /* verilator lint_off WIDTHTRUNC */
  wire csr_write_en = (`ZICSR_OP(ctl_bus) != `ZICSR_OP_NONE) && (!(stall & `STALL_CSRFILE));
  /* verilator lint_on WIDTHTRUNC */
  reg `W(`DLEN) csr_write_data;

  always @(*) begin
    case(`ZICSR_OP(ctl_bus)) 
      `ZICSR_OP_NONE  : csr_write_data = 0;
      `ZICSR_OP_CSRRW : csr_write_data = regdata1_fwded;
      `ZICSR_OP_CSRRS : csr_write_data = csr_read_data | regdata1_fwded;
      `ZICSR_OP_CSRRC : csr_write_data = csr_read_data & (~regdata1_fwded);
      `ZICSR_OP_CSRRWI: csr_write_data = imm;
      `ZICSR_OP_CSRRSI: csr_write_data = csr_read_data | imm;
      `ZICSR_OP_CSRRCI: csr_write_data = csr_read_data & (~imm);
      default:          csr_write_data = 0;
    endcase
  end

  // csrfile is negedge so this same stage writing works out
  csrfile csrfile_instance (
    .clk(clk),
    .rst(rst),
    .read_csr(csr),
    .read_data(csr_read_data),
    .satp(satp),
    .write_en(csr_write_en),
    .write_csr(csr),
    .write_data(csr_write_data)
  );

  always @(negedge clk) csr_data <= csr_read_data;
endmodule
