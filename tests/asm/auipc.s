_start:
    # -----------------------------------------------------------------
    # Test 1: Zero Immediate (Extract current PC)
    # auipc rd, imm -> rd = PC + (imm << 12)
    # With imm=0, t0 should hold the exact memory address of THIS instruction.
    # -----------------------------------------------------------------
    auipc t0, 0

    # -----------------------------------------------------------------
    # Test 2: Positive Immediate
    # imm=1 means we add (1 << 12) = 0x1000 to the PC.
    # t1 should hold: (address of this instruction) + 0x1000
    # -----------------------------------------------------------------
    auipc t1, 1

    # -----------------------------------------------------------------
    # Test 3: Negative Immediate (Sign-extension check)
    # imm=0xFFFFF is -1 as a 20-bit signed integer. 
    # This adds (-1 << 12) = -0x1000 to the PC.
    # t2 should hold: (address of this instruction) - 0x1000
    # NOTE: Failing this usually means your U-type sign-extension is bugged.
    # -----------------------------------------------------------------
    auipc t2, 0xFFFFF

    # Infinite loop to halt execution
end_loop:
    j end_loop