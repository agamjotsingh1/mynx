.section .data
loc: .dword 0x0

.section .text
.globl _start

_start:
  la x1, loc
  sd x1, 0(x1)
  ld x2, 0(x1)
  beq  x1, x2, success 

fail:
  addi x3, x0, 7
  beq x0, x0, loop

success:
  addi x3, x0, 27
  beq x0, x0, loop

loop:
  beq x0, x0, loop