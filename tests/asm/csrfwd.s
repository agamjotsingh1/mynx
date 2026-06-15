.section .text
.globl _start

_start:
  addi x1, x0, 0x630
  addi x2, x0, 0x564
  csrrw x3, mscratch, x1
  csrrw x1, mscratch, x2
  csrrw x7, mscratch, x1

loop:
  beq x0, x0, loop

