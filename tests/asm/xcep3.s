.section .text
.global _start

_start:
    # 1. Set up the trap vector
    la t0, trap_vector
    csrw mtvec, t0
    li t5, 0

    # 2. Put a known "safe" value into t1 (x6)
    li t1, 0xDEADBEEF

    # 3. Execute an illegal CSR read targeting t1
    # Instruction: csrr t1, 0x999 (0x999 is an invalid/unimplemented CSR)
    # Machine code: 0x99902373
illegal_target:
    .word 0x99902373

    # 4. If we reach here, we failed to trap
    li t5, -1
fail_loop:
    j fail_loop

.align 4
trap_vector:
    # 5. We trapped! Now check if t1 was corrupted by the faulting instruction
    li t2, 0xDEADBEEF
    bne t1, t2, fail_loop  # If t1 != 0xDEADBEEF, poisoned writeback bug exists!

    # 6. Test Passed
    li t5, 1
success_loop:
    j success_loop