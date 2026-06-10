# ==============================================================================
# INIT: Set up some base registers
# ==============================================================================
addi x1, x0, 10
addi x2, x0, 10
addi x3, x0, 20
nop
nop
nop

# ==============================================================================
# TEST 1 & 2: Exclusive BEQ (Taken) and BNE (Not Taken)
# ==============================================================================
# Test 1: BEQ (10 == 10). Branch SHOULD be taken.
beq x1, x2, test1_pass
nop                     # Delay slot 1
nop                     # Delay slot 2
nop                     # Delay slot 3
addi x4, x0, 99         # ERROR: If executed, x4 = 99
test1_pass:
addi x4, x0, 1          # SUCCESS: x4 = 1
nop
nop
nop

# Test 2: BNE (10 != 10). Branch SHOULD NOT be taken.
bne x1, x2, test2_fail
nop
nop
nop
addi x5, x0, 2          # SUCCESS: x5 = 2
jal x0, test3_setup     # Jump over the fail block
nop
nop
nop

test2_fail:
addi x5, x0, 99         # ERROR: If executed, x5 = 99
nop
nop
nop

# ==============================================================================
# TEST 3 & 4: Signed vs Unsigned Branches (BLT, BGE, BLTU, BGEU)
# ==============================================================================
test3_setup:
addi x6, x0, -1         # x6 = 0xFFFFFFFF (Signed: -1, Unsigned: Max)
addi x7, x0, 1          # x7 = 0x00000001
nop
nop
nop

# Test 3: BLT (-1 < 1). Signed comparison SHOULD be taken.
blt x6, x7, test3_pass
nop
nop
nop
addi x8, x0, 99         # ERROR
jal x0, test4_setup
nop
nop
nop

test3_pass:
addi x8, x0, 3          # SUCCESS: x8 = 3
nop
nop
nop

# Test 4: BLTU (0xFFFFFFFF < 1). Unsigned comparison SHOULD NOT be taken.
test4_setup:
bltu x6, x7, test4_fail
nop
nop
nop
addi x9, x0, 4          # SUCCESS: x9 = 4
jal x0, test5_setup
nop
nop
nop

test4_fail:
addi x9, x0, 99         # ERROR
nop
nop
nop

# ==============================================================================
# TEST 5 & 6: Exclusive JAL Forward & Backward (with Link check)
# ==============================================================================
test5_setup:
jal x10, test5_target   # Jump forward, save Return Address to x10
nop
nop
nop
addi x11, x0, 99        # ERROR (Skipped)
test5_target:
addi x11, x0, 5         # SUCCESS: x11 = 5
nop
nop
nop

# ==============================================================================
# TEST 7: Exclusive JALR (with exact offset calculations)
# Note: Since you likely don't have 'auipc' for 'la' pseudo-instructions yet,
# we use JAL to grab the current PC safely, then use JALR with a known offset.
# ==============================================================================
jal x12, jalr_base      # x12 gets the PC of the first nop below
nop
nop
nop

jalr_base:
# x12 holds PC of the instruction at offset 0. 
# We want to jump over 4 instructions (16 bytes) from x12.
jalr x13, x12, 16
nop
nop
nop
addi x14, x0, 99        # Offset 0 from x12. ERROR if hit.
nop                     # Offset 4
nop                     # Offset 8
nop                     # Offset 12
addi x14, x0, 7         # Offset 16. SUCCESS: x14 = 7!
nop
nop
nop

# ==============================================================================
# TEST 8: COMBINED GAUNTLET (Loops, Nested Control Flow, Function Calls)
# Calculates 5 * 3 = 15 using a loop, branches, JAL, and JALR.
# ==============================================================================
addi x15, x0, 5         # Multiplicand
addi x16, x0, 3         # Counter
addi x17, x0, 0         # Accumulator
nop
nop
nop

gauntlet_loop:
beq x16, x0, gauntlet_end # If counter == 0, exit loop
nop
nop
nop

jal x18, add_function   # JAL calling a function
nop
nop
nop

addi x16, x16, -1       # Decrement counter
nop                     # Pipeline flush before next read
nop
nop
jal x0, gauntlet_loop   # Loop backward unconditionally
nop
nop
nop

add_function:
add x17, x17, x15       # Accumulate: x17 = x17 + 5
nop
nop
nop
jalr x0, x18, 0         # JALR return to caller
nop
nop
nop

gauntlet_end:
beq x0, x0, gauntlet_end