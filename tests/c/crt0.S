# C runtime

.section .text
.global _start
_start:
    li sp, 0x80080000
    # la t0, loop
    # csrw mtvec, t0
    call main
loop:
    j loop