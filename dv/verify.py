#!/usr/bin/env python3
import sys
import subprocess
import re
import os

if len(sys.argv) != 4:
    print("Usage: verify.py <elf_file> <hex_file> <vcore_bin>")
    sys.exit(1)

def red(str):
    return "\033[91m" + str + "\033[0m"

def green(str):
    return "\033[92m" + str + "\033[0m"

elf_file = sys.argv[1]
hex_file = sys.argv[2]
vcore_bin = sys.argv[3]
max_instructions = 15000000
timeout = 100

def get_spike_state():
    cmds = f"r {max_instructions}\nreg 0\n"
    for offset in range(0, 1024 * 8, 8):
        cmds += f"mem {0x80000000 + offset:x}\n"
    cmds += "q\n"
    
    with open("spike.cmd", "w") as f:
        f.write(cmds)
    
    cmd = ['spike', '--isa=rv64i_zicclsm', '-d', '--debug-cmd=spike.cmd', '-m0x80000000:0x2000', '--pc=0x80000000', elf_file]
    
    try:
        res = subprocess.run(cmd, text=True, capture_output=True, timeout=timeout)
    except subprocess.TimeoutExpired:
        print(f"[{red("CRITICAL")}] Spike simulator hung (timeout after {timeout}s).")
        sys.exit(1)
        
    output = res.stderr 
    
    regs, mem = {}, {}

    abi_names = [
        "zero", "ra", "sp", "gp",
        "tp", "t0", "t1", "t2",
        "s0", "s1", "a0", "a1",
        "a2", "a3", "a4", "a5",
        "a6", "a7", "s2", "s3",
        "s4", "s5", "s6", "s7",
        "s8", "s9", "s10", "s11",
        "t3", "t4", "t5", "t6"
    ]
    
    for i, name in enumerate(abi_names):
        m = re.search(rf'{name}\s*:\s*0x([0-9a-fA-F]+)', output)
        if m:
            val = int(m.group(1), 16)
            regs[i] = val
            
    parsed_any_mem = False
    current_offset = 0
    
    for line in output.split('\n'):
        line = line.strip()
        # Spike drops memory values sequentially without addresses,
        # strictly match isolated 64-bit hex strings using regex
        if re.match(r'^0x[0-9a-fA-F]{16}$', line):
            val = int(line, 16)

            for b in range(8):
                mem[current_offset + b] = (val >> (b * 8)) & 0xFF
            
            current_offset += 8
            parsed_any_mem = True

    if os.path.exists("spike.cmd"):
        os.remove("spike.cmd")

    if len(regs) == 0:
        print(f"[{red("CRITICAL")}] Spike failed to start. Crash Log:")
        print(output)
        sys.exit(1)
        
    if not parsed_any_mem:
        print(f"[{red("WARNING")}] Spike memory hexdump failed to parse.")
        print("--- RAW SPIKE OUTPUT ---")
        print(output)
        sys.exit(1)
        
    return regs, mem

def get_vcore_state():
    try:
        res = subprocess.run([vcore_bin, hex_file], text=True, capture_output=True, timeout=timeout)
    except subprocess.TimeoutExpired:
        print(f"[{red("CRITICAL")}] Vcore simulation hung (timeout after {timeout}s).")
        sys.exit(1)
        
    output = res.stdout
    
    regs, mem = {}, {}
    for i in range(32):
        m = re.search(rf'x{i}\s*:\s*0x([0-9a-fA-F]+)', output)
        if m: regs[i] = int(m.group(1), 16)
        
    for line in output.split('\n'):
        if " | " in line and line.strip().startswith("0x"):
            addr_str, hex_str = line.split(" | ")[:2]
            try:
                base = int(addr_str.strip(), 16)
                hex_bytes = [b for b in hex_str.strip().split() if len(b) == 2]
                for i, b in enumerate(hex_bytes):
                    mem[base + i] = int(b, 16)
            except ValueError:
                pass
    return regs, mem

print(f"Comparing execution of {hex_file}...")

print("-> Simulating with Spike...", flush=True)
spike_regs, spike_mem = get_spike_state()

print("-> Simulating with Verilator (HW)...", flush=True)
vcore_regs, vcore_mem = get_vcore_state()

print("-> Analyzing diff...", flush=True)
passed = True

for i in range(32):
    s_val, v_val = spike_regs.get(i, 0), vcore_regs.get(i, 0)
    if s_val != v_val:
        print(f"[FAIL] Register x{i}: Spike=0x{s_val:016x}, Vcore=0x{v_val:016x}")
        passed = False

all_addrs = set(spike_mem.keys()).union(set(vcore_mem.keys()))
mismatches = 0
for addr in sorted(list(all_addrs)):
    s_val, v_val = spike_mem.get(addr, 0), vcore_mem.get(addr, 0)
    if s_val != v_val:
        print(f"[FAIL] Memory 0x{addr:04x}: Spike=0x{s_val:02x}, Vcore=0x{v_val:02x}")
        mismatches += 1
        passed = False
    if mismatches > 15:
        print("... truncated further memory mismatches ...")
        break

if passed:
    print(f"[{green("SUCCESS")}] Verification Passed! Registers and Memory map exactly match Spike.\n")
    sys.exit(0)
else:
    print(f"[{red("FAILED")}] Hardware differes from Spike.\n")
    sys.exit(1)