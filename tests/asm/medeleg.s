.global _start
.section .text

_start:
    # ---------------------------------------------------------
    # 1. SETUP DELEGATION AND VECTORS
    # ---------------------------------------------------------
    # Set M-mode trap handler
    la t0, m_trap_handler
    csrw mtvec, t0

    # Set S-mode trap handler (Where we WANT to go)
    la t1, s_trap_handler
    csrw stvec, t1

    # Delegate "Environment Call from S-mode" (Cause 9) to S-mode
    # 1 << 9 = 0x200
    li t2, 0x200
    csrw medeleg, t2

    # ---------------------------------------------------------
    # 2. DROP TO S-MODE
    # ---------------------------------------------------------
    la t3, s_mode_execution
    csrw mepc, t3
    li t4, 0x0800  # Set MPP to S-mode
    csrw mstatus, t4
    mret

    # ---------------------------------------------------------
    # 3. S-MODE EXECUTION
    # ---------------------------------------------------------
s_mode_execution:
    # We are in S-mode. Let's trigger an ECALL!
    # Because we delegated Cause 9, this should jump to stvec, NOT mtvec.
    ecall

    # If ecall doesn't trap at all, we get stuck here.
fail_no_trap:
    j fail_no_trap

    # ---------------------------------------------------------
    # 4. TRAP HANDLERS
    # ---------------------------------------------------------
.align 2
m_trap_handler:
    # FAILURE: We should NOT be here. The exception was delegated!
    li a0, 0xBAD
    j m_trap_handler

.align 2
s_trap_handler:
    # SUCCESS: The delegation logic worked!
    # Check if scause recorded Cause 9 (S-mode ecall)
    csrr a1, scause
    li a0, 0x600D
pass_loop:
    j pass_loop