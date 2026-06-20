/* AI GENERATED TESTBENCH */

.global _start
.section .text

_start:
    # ---------------------------------------------------------
    # 1. MACHINE MODE SETUP
    # ---------------------------------------------------------
    # Set up the M-mode trap vector so we can catch our final U-mode violation
    la t0, m_trap_handler
    csrw mtvec, t0

    # We want to use MRET to jump to S-mode.
    # Set mstatus.MPP = 01 (Supervisor mode)
    # MPP is bits [12:11]. (1 << 11) = 0x0800
    li t1, 0x0800
    csrw mstatus, t1

    # Set mepc to the start of our S-mode code
    la t2, s_mode_entry
    csrw mepc, t2

    # Execute MRET. This should drop privileges to S-mode and jump to s_mode_entry
    mret

    # --- If mret fails to jump, we fall through and get stuck here ---
fail_mret:
    j fail_mret


    # ---------------------------------------------------------
    # 2. SUPERVISOR MODE EXECUTION
    # ---------------------------------------------------------
s_mode_entry:
    # If we reached here, MRET worked! 
    # Now let's drop to U-mode using SRET.

    # Set sstatus.SPP = 0 (User mode)
    # SPP is bit 8. Writing 0 to sstatus clears SPP.
    li t0, 0x0
    csrw sstatus, t0

    # Set sepc to the start of our U-mode code
    la t1, u_mode_entry
    csrw sepc, t1

    # Execute SRET. This should drop privileges to U-mode and jump to u_mode_entry
    sret

    # --- If sret fails to jump, we fall through and get stuck here ---
fail_sret:
    j fail_sret


    # ---------------------------------------------------------
    # 3. USER MODE EXECUTION
    # ---------------------------------------------------------
u_mode_entry:
    # If we reached here, SRET worked! We are now in U-mode.
    # To PROVE we are actually in U-mode, let's try to access a Machine-mode CSR.
    # This is strictly forbidden and should immediately trigger an
    # Illegal Instruction exception, sending us straight to m_trap_handler.

    li a0, 0xDEAD 
    csrw mstatus, a0 # <--- THIS SHOULD TRAP!

    # --- If the core fails to trap (meaning we mistakenly stayed in M-mode), it gets stuck here ---
fail_trap:
    j fail_trap


    # ---------------------------------------------------------
    # 4. M-MODE TRAP HANDLER (The Final Verification)
    # ---------------------------------------------------------
.align 2
m_trap_handler:
    # We trapped! Let's check mcause.
    # Illegal Instruction has an exception code of 2.
    csrr a1, mcause
    
    li t0, 2
    bne a1, t0, fail_wrong_cause

    # SUCCESS!
    li a0, 0x600D
pass_loop:
    j pass_loop

fail_wrong_cause:
    j fail_wrong_cause