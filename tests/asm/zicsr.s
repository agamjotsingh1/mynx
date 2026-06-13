.global _start
.section .text

_start:
    # ---------------------------------------------------------
    # SETUP
    # ---------------------------------------------------------
    li t1, 0x12345678        # Target test value
    li t2, 0x0000FFFF        # Mask for setting bits
    li t3, 0x0000000F        # Mask for clearing bits

    # ---------------------------------------------------------
    # TEST 1: csrrw (CSR Read/Write)
    # ---------------------------------------------------------
    csrrw a0, mscratch, t1   # mscratch = 0x12345678, a0 = 0
    csrrs a1, mscratch, zero # a1 = 0x12345678

    # ---------------------------------------------------------
    # TEST 2: csrrs (CSR Read/Set Bits)
    # ---------------------------------------------------------
    csrrs a2, mscratch, t2   # a2 = 0x12345678 (old value)
    csrrs a3, mscratch, zero # a3 = 0x1234FFFF

    # ---------------------------------------------------------
    # TEST 3: csrrc (CSR Read/Clear Bits)
    # ---------------------------------------------------------
    csrrc a4, mscratch, t3   # a4 = 0x1234FFFF (old value)
    csrrs a5, mscratch, zero # a5 = 0x1234FFF0

    # ---------------------------------------------------------
    # TEST 4: csrrwi (CSR Read/Write Immediate)
    # ---------------------------------------------------------
    csrrwi a6, mepc, 11      # mepc = 11, a6 = 0
    csrrs a7, mepc, zero     # a7 = 11

    # ---------------------------------------------------------
    # TEST 5: csrrsi (CSR Read/Set Immediate)
    # ---------------------------------------------------------
    csrrsi t4, mepc, 16      # t4 = 11 (old value)
    csrrs t5, mepc, zero     # t5 = 27

    # ---------------------------------------------------------
    # TEST 6: csrrci (CSR Read/Clear Immediate)
    # ---------------------------------------------------------
    csrrci t6, mepc, 3       # t6 = 27 (old value)
    csrrs t0, mepc, zero     # t0 = 24  <--- FIXED: Used t0 instead of t7

    # ---------------------------------------------------------
    # END OF TEST
    # ---------------------------------------------------------
end_loop:
    j end_loop               
    nop
    nop

.end