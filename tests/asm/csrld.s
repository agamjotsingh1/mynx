.section .data
loc: .dword 0x0

.section .text
.globl _start

_start:
  la x1, loc
  addi x2, x0, 0x630
  sd x2, 0(x1)
  ld x3, 0(x1)
  csrrw x4, mscratch, x3

loop:
  beq x0, x0, loop

