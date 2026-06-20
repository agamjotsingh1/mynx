/* AI GENERATED TESTBENCH */

.section .text
.global _start

_start:
  la t0, trap_vector
  csrw mtvec, t0
  li t5, 0

illegal_inst:
  .word 0x00208053 # illegal instr
  li t5, -1               # Test failed (failed to trap)

fail_loop:
  j fail_loop

.align 4
trap_vector:
  csrr t1, mcause
  li t2, 2
  bne t1, t2, fail_loop   # If mcause != 2, fail the test
  csrr t3, mepc
  la t4, illegal_inst
  bne t3, t4, fail_loop   # If mepc != address of illegal_inst, fail the test
  li t5, 1

success_loop:
    j success_loop