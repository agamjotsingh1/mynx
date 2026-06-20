addi x5, x0, 5
addi x6, x0, 5
addi x7, x0, 10
addi x8, x0, -5 

addi x0, x0, 0
addi x0, x0, 0
addi x0, x0, 0

beq x5, x6, pass_beq
beq x0, x0, fail
pass_beq:

bne x5, x7, pass_bne
beq x0, x0, fail
pass_bne:

blt x8, x5, pass_blt
beq x0, x0, fail
pass_blt:

bge x5, x8, pass_bge
beq x0, x0, fail
pass_bge:

bltu x5, x8, pass_bltu
beq x0, x0, fail
pass_bltu:

bgeu x8, x5, pass_bgeu
beq x0, x0, fail
pass_bgeu:

addi x10, x0, 1
success_loop:
beq x0, x0, success_loop 

fail:
addi x10, x0, 0
fail_loop:
beq x0, x0, fail_loop