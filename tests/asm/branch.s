# -------------------------------------------------------------------
# RISC-V Branch Logic Test (No J-Type)
# -------------------------------------------------------------------

# 1. Setup Initial Values (I-type)
addi x5, x0, 5      # x5 = 5
addi x6, x0, 5      # x6 = 5
addi x7, x0, 10     # x7 = 10
addi x8, x0, -5     # x8 = -5 (0xFFFFFFFB)

# 2. Hazard Padding (I-type)
addi x0, x0, 0
addi x0, x0, 0
addi x0, x0, 0

# -------------------------------------------------------------------
# 3. The Tests (B-type only)
# -------------------------------------------------------------------

# --- Test 1: BEQ (Branch Equal) ---
beq x5, x6, pass_beq  # 5 == 5, should branch
beq x0, x0, fail      # ALWAYS branches to fail if the above falls through
pass_beq:

# --- Test 2: BNE (Branch Not Equal) ---
bne x5, x7, pass_bne  # 5 != 10, should branch
beq x0, x0, fail
pass_bne:

# --- Test 3: BLT (Branch Less Than - Signed) ---
blt x8, x5, pass_blt  # -5 < 5, should branch
beq x0, x0, fail
pass_blt:

# --- Test 4: BGE (Branch Greater Than or Equal - Signed) ---
bge x5, x8, pass_bge  # 5 >= -5, should branch
beq x0, x0, fail
pass_bge:

# --- Test 5: BLTU (Branch Less Than Unsigned) ---
bltu x5, x8, pass_bltu # 5 < 0xFFFFFFFB, should branch
beq x0, x0, fail
pass_bltu:

# --- Test 6: BGEU (Branch Greater Than or Equal Unsigned) ---
bgeu x8, x5, pass_bgeu # 0xFFFFFFFB >= 5, should branch
beq x0, x0, fail
pass_bgeu:

# -------------------------------------------------------------------
# 4. Completion States
# -------------------------------------------------------------------

# --- SUCCESS ---
addi x10, x0, 1
success_loop:
beq x0, x0, success_loop  # Infinite loop using B-type

# --- FAIL ---
fail:
addi x10, x0, 0
fail_loop:
beq x0, x0, fail_loop     # Infinite loop using B-type