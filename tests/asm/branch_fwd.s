addi x1, x0, 5
addi x2, x0, 5
nop
beq  x1, x2, success 

fail:
  addi x3, x0, 7
  beq x0, x0, loop

success:
  addi x3, x0, 27
  beq x0, x0, loop

loop:
  beq x0, x0, loop