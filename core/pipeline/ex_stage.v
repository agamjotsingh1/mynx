`include "defs.vh"
`include "modules/alu.v"

module ex_stage (
  input wire `W(`DLEN)       pc,
  input wire `W(`DLEN)       regdata1,
  input wire `W(`DLEN)       regdata2,
  input wire `W(`DLEN)       csrdata,
  input wire `W(`DLEN)       imm,
  input wire `W(`ALU_OPLEN)  alu_op,

  /* verilator lint_off UNUSEDSIGNAL */
  input wire `W(`CTL_BUSLEN) ctl_bus,
  /* verilator lint_on UNUSEDSIGNAL */

  output wire `W(`DLEN) mem_data,
  output wire `W(`DLEN) ex_res,
  output wire `W(`DLEN) csr_write_data,

  // fwd controls
  input wire `W(`FWDLEN)     fwd1,
  input wire `W(`FWDLEN)     fwd2,

  // fwd inputs
  input wire `W(`DLEN)       __mem_ex_res,
  input wire `W(`DLEN)       __wb_write_data
);
  wire `W(`DLEN) alu_res;
  reg  `W(`DLEN) alu_in1, alu_in2;

  wire `W(`DLEN) regdata1_fwded = 
    (fwd1 == `FWD_EX_MEM) ? __mem_ex_res:
    ((fwd1 == `FWD_MEM_WB) ? __wb_write_data: regdata1);

  wire `W(`DLEN) regdata2_fwded = 
    (fwd2 == `FWD_EX_MEM) ? __mem_ex_res:
    ((fwd2 == `FWD_MEM_WB) ? __wb_write_data: regdata2);

  always @(*) begin
    case(`ZICSR_OP(ctl_bus)) 
      `ZICSR_OP_CSRRW : begin
        alu_in1 = 0;
        alu_in2 = regdata1_fwded;
      end
      `ZICSR_OP_CSRRS : begin 
        alu_in1 = csrdata;
        alu_in2 = regdata1_fwded;
      end
      `ZICSR_OP_CSRRC : begin 
        alu_in1 = csrdata;
        alu_in2 = ~regdata1_fwded;
      end
      `ZICSR_OP_CSRRWI: begin
        alu_in1 = 0;
        alu_in2 = imm;
      end
      `ZICSR_OP_CSRRSI: begin 
        alu_in1 = csrdata;
        alu_in2 = imm;
      end
      `ZICSR_OP_CSRRCI: begin 
        alu_in1 = csrdata;
        alu_in2 = ~imm;
      end
      default: begin
        alu_in1 = regdata1_fwded;
        if(`ALU_SRC(ctl_bus)) alu_in2 = imm;
        else alu_in2 = regdata2_fwded;
      end
    endcase
  end

  assign mem_data = regdata2_fwded;

  alu alu_instance (
    .alu_op(alu_op),
    .in1(alu_in1),
    .in2(alu_in2),
    .out(alu_res)
  );

  assign ex_res =
    (`JAL(ctl_bus) | `JALR(ctl_bus)) ? pc + 4: 
    (`LUI(ctl_bus) ? imm:
    (`AUIPC(ctl_bus) ? pc + imm:
    (`WORDTRUNC(ctl_bus) ? {{32{alu_res[31]}}, alu_res[31:0]}:
    (`ZICSR_OP(ctl_bus) != `ZICSR_OP_NONE ? csrdata:
    alu_res))));

  assign csr_write_data = alu_res;
endmodule
