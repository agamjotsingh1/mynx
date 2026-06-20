# C runtime

.section .text
.global _start
_start:
    li sp, 0x80080000
    li t0, 0x3fffffffffffffff
    csrw pmpaddr0, t0
    csrw pmpcfg0, 0xf
    call main
loop:
    j loop