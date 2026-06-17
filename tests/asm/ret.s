.global _start
.section .text

_start:
  li a0, 0             
  li a1, 0             

  la t0, return_target
  csrw mepc, t0

  # Set MPIE (bit 7) = 1
  # Set MPP (bits 12:11) = 3 (Machine Mode)
  # Value = (1 << 7) | (3 << 11) = 0x80 | 0x1800 = 0x1880
  li t1, 0x1880
  csrw mstatus, t1
  mret

  li a0, 0xBAD
end_fail:
  j end_fail

return_target:
  li a0, 0x600D
  csrr a1, mstatus

end_pass:
  j end_pass