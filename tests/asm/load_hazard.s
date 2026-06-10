addi x1, x0, 0x300
addi x2, x0, 0x630
sd x2, 0(x1)
ld x2, 0(x1)
add x2, x2, x2
add x2, x2, x1
