_start:
    # Initialize status registers
    li x10, 0       # Overall success flag (0 = fail, 1 = pass)
    li x1, 0        # Clear link register for JAL
    li x2, 0        # Clear link register for JALR

    # ==========================================
    # 1. Test JAL (Jump and Link)
    # ==========================================
jal_pc:
    jal x1, jal_target    # Jump to jal_target, save PC+4 in x1
    j fail_loop           # Overjumped? Failed.

jal_target:
    # Verify JAL Link Register: x1 must be exactly jal_pc + 4
    # Since jal_target is exactly 4 bytes after jal_pc:
    # x1 should equal the current PC!
    
    jal x3, get_pc_1      # x3 = current PC
get_pc_1:
    bne x1, x3, fail_loop # If x1 != current PC, JAL linking failed

    # ==========================================
    # 2. Test JALR (Jump and Link Register)
    # ==========================================
    # We want to jump to 'jalr_target'. 
    # Let's dynamically calculate its address using JAL to get the current PC
    # without using auipc or 'la'.
    
jalr_setup:
    jal x5, get_pc_2      # x5 = address of get_pc_2
get_pc_2:
    # jalr_target is exactly 24 bytes (6 instructions) ahead of get_pc_2.
    # Let's add 24 to x5 to point straight to jalr_target.
    addi x5, x5, 24       

    # Force the lowest bit of the target address to be 1 (odd address)
    # JALR must clear this bit to 0 before jumping!
    ori  x5, x5, 1        

jalr_pc:
    jalr x2, 0(x5)        # Jump to x5, save PC+4 in x2
    j fail_loop           # If JALR didn't jump, we fail

    # Space filler to ensure our 24-byte math matches exactly
    nop                   
    nop