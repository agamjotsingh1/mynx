.global _start
.section .text

_start:
    la t0, m_trap_handler
    csrw mtvec, t0
    la t1, s_trap_handler
    csrw stvec, t1
    li t2, 0x200
    csrw medeleg, t2
    la t3, s_mode_execution
    csrw mepc, t3
    li t4, 0x0800
    csrw mstatus, t4
    mret
s_mode_execution:
    ecall

fail_no_trap:
    j fail_no_trap

.align 2
m_trap_handler:
    li a0, 0xBAD
    j m_trap_handler

.align 2
s_trap_handler:
    csrr a1, scause
    li a0, 0x600D
pass_loop:
    j pass_loop