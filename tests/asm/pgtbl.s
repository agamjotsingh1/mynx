# RISC-V 64-bit Assembly Testbench for Sv39 MMU
# Assumes boot happens at physical address 0x8000_0000 in M-Mode (SATP = 0)

.section .text
.globl _start

_start:
    # ==========================================
    # 1. SETUP TRAP HANDLER
    # ==========================================
    la t0, trap_vector
    csrw mtvec, t0          # Set M-mode trap vector

    # ==========================================
    # 2. BUILD SV39 PAGE TABLES IN PHYSICAL MEMORY
    # ==========================================
    # We will build:
    # - Root PT (Level 2) at PA 0x8001_0000
    # - Level 1 PT        at PA 0x8002_0000
    # - Level 0 PT        at PA 0x8003_0000

    # -- Root (L2) Page Table --
    # Index 0. Points to L1 PT (PA: 0x8002_0000 -> PPN: 0x80020)
    # PTE = (0x80020 << 10) | V(1) = 0x2000_8001
    li t0, 0x80010000       # Root PT Address
    li t1, 0x20008001       # Intermediate PTE (R=0,W=0,X=0,V=1)
    sd t1, 0(t0)            

    # -- Level 1 Page Table --
    # Index 0. Points to L0 PT (PA: 0x8003_0000 -> PPN: 0x80030)
    # PTE = (0x80030 << 10) | V(1) = 0x2000_C001
    li t0, 0x80020000       # L1 PT Address
    li t1, 0x2000C001       # Intermediate PTE
    sd t1, 0(t0)

    # -- Level 0 Page Table --
    li t0, 0x80030000       # L0 PT Base Address

    # Mapping 1: VA 0x0000_1000 -> PA 0x8004_0000
    li t1, 0x200100DF       # RWX + U + V + A + D
    sd t1, 8(t0)            

    # Mapping 2: VA 0x0000_2000 -> PA 0x8005_0000
    li t1, 0x200140D3       # R-Only + U + V + A + D
    sd t1, 16(t0)       # Store at index 2


    # ==========================================
    # 3. RELOCATE PAYLOAD TO MAPPED PHYSICAL PAGE
    # ==========================================
    # We copy the 'user_payload' code to PA 0x8004_0000 
    # so it exists where VA 0x1000 points.
    la t0, user_payload
    li t1, 0x80040000       # Physical destination
    li t2, 6                # Number of instructions to copy
copy_loop:
    lw t3, 0(t0)            # Read 32-bit instruction
    sw t3, 0(t1)            # Write 32-bit instruction to destination
    addi t0, t0, 4
    addi t1, t1, 4
    addi t2, t2, -1
    bnez t2, copy_loop

    # Write some dummy data to the Read-Only page (PA 0x8005_0000)
    li t0, 0x80050000
    li t1, 0xDEADBEEF
    sd t1, 0(t0)


    # ==========================================
    # 4. ENABLE MMU (WRITE SATP)
    # ==========================================
    # SATP = (MODE_SV39 << 60) | (Root PPN)
    # MODE_SV39 = 8. Root PPN = 0x80010.
    li t0, 8
    slli t0, t0, 60         # 8 << 60
    li t1, 0x80010          # Root PPN
    or t0, t0, t1           # SATP Value
    csrw satp, t0           # Turn on MMU!
    # sfence.vma              # Flush TLBs/MMU internal state


    # ==========================================
    # 5. CONTEXT SWITCH TO USER MODE
    # ==========================================
    # Clear mstatus.MPP (bits 12:11) to drop to User Mode (0b00)
    li t0, 0x00001800
    csrc mstatus, t0

    # Set Return Address (mepc) to our mapped Virtual Address
    li t0, 0x1000
    csrw mepc, t0

    # Execute MRET. Core jumps to VA 0x1000 in U-Mode!
    mret 


# ==========================================
# 6. USER PAYLOAD (Executes at VA 0x1000)
# ==========================================
user_payload:
    # Test 1: Valid Read
    li t0, 0x2000           # Load Virtual Address 0x2000 (R-Only Page)
    ld t1, 0(t0)            # This should SUCCEED and fetch 0xDEADBEEF

    # Test 2: Trigger Page Fault
    li t2, 0xCAFE
    sd t2, 0(t0)            # Attempt to WRITE to Read-Only page
                            # <--- MMU SHOULD THROW EXCEPTION HERE --->

    # If the MMU fails to trap, we end up in an infinite loop of failure
fail_loop:
    j fail_loop


# ==========================================
# 7. TRAP HANDLER (Catches the Page Fault)
# ==========================================
.align 4
trap_vector:
    # We arrive here in M-Mode (MMU automatically bypassed for M-mode fetches)
    csrr t0, mcause         # Get Exception Cause
    
    # Check if cause == 15 (Store/AMO Page Fault)
    li t1, 15
    bne t0, t1, test_failed

    # Optional: Verify mtval contains the faulting virtual address (0x2000)
    # csrr t0, mtval
    # li t1, 0x2000
    # bne t0, t1, test_failed

test_passed:
    # Write a magic success code to a known register (e.g., x31 / t6)
    # so you can observe the success state in your waveform viewer
    li x31, 0x0000BABE
halt_pass:
    j halt_pass             # Simulation completed successfully

test_failed:
    # Write a magic failure code
    li x31, 0xDEADDEAD
halt_fail:
    j halt_fail             # Simulation failed