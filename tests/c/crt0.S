# C runtime

.section .text
.global _start
_start:
    li sp, 0x80080000
    call main
loop:
    j loop