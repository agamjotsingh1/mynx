#!/usr/bin/env python3

# please note that the spinner part is completely AI generated
import sys
import subprocess
import re
import os
import threading
import time

if len(sys.argv) != 4:
    sys.exit(1)

def red(text):   return "\033[91m" + text + "\033[0m"
def green(text): return "\033[92m" + text + "\033[0m"
def cyan(text):  return "\033[96m" + text + "\033[0m"

class Spinner:
    def __init__(self, message):
        self.message = message
        self.running = False
        self.thread = None

    def _spin(self):
        chars = ['\u280b',
                 '\u2819',
                 '\u2839',
                 '\u2838',
                 '\u283c',
                 '\u2834',
                 '\u2826',
                 '\u2827',
                 '\u2807',
                '\u280f']
        i = 0
        while self.running:
            sys.stdout.write(f"\r{cyan(chars[i % len(chars)])} {self.message}")
            sys.stdout.flush()
            time.sleep(0.08)
            i += 1

    def __enter__(self):
        self.running = True
        self.thread = threading.Thread(target=self._spin, daemon=True)
        self.thread.start()
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        self.running = False
        if self.thread:
            self.thread.join()
        sys.stdout.write('\r\033[K')
        sys.stdout.flush()

elf_file  = sys.argv[1]
hex_file  = sys.argv[2]
vcore_bin = sys.argv[3]

MAX_INSTRS = 15000000
MEM_DEPTH  = 16777216 
TIMEOUT    = 100

def get_spike_state():
    cmds = f"r {MAX_INSTRS}\nreg 0\n"
    MEM_DEPTH_WORD = int(MEM_DEPTH/4);

    for offset in range(0, MEM_DEPTH_WORD, 8):
        cmds += f"mem {0x80000000 + offset:x}\n"

    cmds += "q\n"
    
    with open("spike.cmd", "w") as f:
        f.write(cmds)
    
    cmd = ['spike', '--isa=rv64i_zicclsm', '-d', '--debug-cmd=spike.cmd', '-m0x80000000:0x4000000', '--pc=0x80000000', elf_file]
    
    try:
        res = subprocess.run(cmd, text=True, capture_output=True, timeout=TIMEOUT)
    except subprocess.TimeoutExpired:
        print(f"\r\033[K{red('\u2717')} Spike simulator hung (timeout).")
        sys.exit(1)
        
    output = res.stderr 
    regs, mem = {}, {}

    abi_names = [
        "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
        "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
        "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
        "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
    ]
    
    for i, name in enumerate(abi_names):
        m = re.search(rf'{name}\s*:\s*0x([0-9a-fA-F]+)', output)
        if m: regs[i] = int(m.group(1), 16)
            
    parsed_any_mem = False
    current_offset = 0
    
    for line in output.split('\n'):
        line = line.strip()
        if re.match(r'^0x[0-9a-fA-F]{16}$', line):
            val = int(line, 16)
            for b in range(8):
                mem[current_offset + b] = (val >> (b * 8)) & 0xFF
            current_offset += 8
            parsed_any_mem = True

    if os.path.exists("spike.cmd"):
        os.remove("spike.cmd")

    if len(regs) == 0:
        print(f"\r\033[K{red('\u2717')} Spike failed to start. Crash Log:\n{output}")
        sys.exit(1)
        
    if not parsed_any_mem:
        print(f"\r\033[K{red('\u2717')} Spike memory hexdump failed to parse.")
        sys.exit(1)
        
    return regs, mem

def get_vcore_state():
    try:
        args = [vcore_bin, '--PROGFILE', hex_file, '--LOOPBRK', '1', '--LOG', '1']
        res = subprocess.run(args, text=True, capture_output=True, timeout=TIMEOUT)
    except subprocess.TimeoutExpired:
        print(f"\r\033[K{red('\u2717')} Vsoc simulation hung (timeout).")
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

error_logs = []
passed = True
mismatches = 0

with Spinner(f"verifying {hex_file}..."):
    spike_regs, spike_mem = get_spike_state()
    vcore_regs, vcore_mem = get_vcore_state()

    for i in range(32):
        s_val, v_val = spike_regs.get(i, 0), vcore_regs.get(i, 0)
        if s_val != v_val:
            error_logs.append(f"  Reg x{i}: Spike=0x{s_val:016x}, Vsoc=0x{v_val:016x}")
            passed = False

    all_addrs = set(spike_mem.keys()).union(set(vcore_mem.keys()))
    for addr in sorted(list(all_addrs)):
        s_val, v_val = spike_mem.get(addr, 0), vcore_mem.get(addr, 0)
        if s_val != v_val:
            error_logs.append(f"  Mem 0x{addr:04x}: Spike=0x{s_val:02x}, Vsoc=0x{v_val:02x}")
            mismatches += 1
            passed = False
        if mismatches > 15:
            error_logs.append("  ... truncated further memory mismatches ...")
            break

if passed:
    print(f"{green('\u2714')} test {hex_file} done")
    sys.exit(0)
else:
    print(f"{red('\u2717')} test {hex_file} failed")
    for err in error_logs:
        print(red(err))
    sys.exit(1)
