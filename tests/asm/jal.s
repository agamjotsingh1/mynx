addi x1, x0, 10
nop
nop
nop
nop
jal x2, foo 

bar:
  addi x1, x1, 30
  beq x0, x0, loop

foo:
  addi x1, x1, 20
  beq x0, x0, loop

loop:
  beq x0, x0, loop

