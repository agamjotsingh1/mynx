/* AI GENERATED TESTBENCH */

.section .text
.global _start

_start:
    # 1. Set up the trap vector
    la t0, trap_vector
    csrw mtvec, t0
    li t5, 0

    # 2. Execute an instruction that is completely illegal, but looks 
    # like an unaligned Load Word if the EX stage blindly parses it.
    # Fake Instruction format: 
    # imm = 0xFFF (-1), rs1 = x0, func3 = 010 (Word), rd = x0, opcode = 0x7F (Custom/Illegal)
    # Target address calculated by ALU: 0 + (-1) = 0xFFFFFFFF (Unaligned)
    # Machine code: 0xFFF0207F
double_fault_inst:
    .word 0xFFF0207F

    # 3. If we reach here, we failed to trap
    li t5, -1
fail_loop:
    j fail_loop

.align 4
trap_vector:
    # 4. We trapped. Now we verify WHICH exception the pipeline reported.
    csrr t1, mcause
    
    # Check for Cause 4 (Load Address Misaligned)
    li t2, 4
    beq t1, t2, fail_loop  # If mcause == 4, the EX stage overwrote the ID stage exception!
    
    # Check for Cause 2 (Illegal Instruction)
    li t3, 2
    bne t1, t3, fail_loop  # If mcause != 2, something else broke.

    # 5. Test Passed (Priority is correct)
    li t5, 1
success_loop:
    j success_loop