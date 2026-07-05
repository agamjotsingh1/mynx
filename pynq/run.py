from pynq import Overlay, allocate
import time
import struct

overlay = Overlay("design_1.bit")
kb = overlay.kb.channel1
kb_valid = overlay.kb_valid.channel1
rst = overlay.core_rst.channel1
phy_ps_addr = overlay.phy_ps_addr.channel1

instructions_text = """
00001137
0011011b
01311113
544000ef
0000006f
f8010113
00112023
00512223
00612423
00712623
00a12823
00b12a23
00c12c23
00d12e23
02e12023
02f12223
03012423
03112623
03c12823
03d12a23
03e12c23
03f12e23
444000ef
00012083
00412283
00812303
00c12383
01012503
01412583
01812603
01c12683
02012703
02412783
02812803
02c12883
03012e03
03412e83
03812f03
03c12f83
08010113
30200073
fd010113
02113423
02813023
03010413
fca43c23
fcb43823
fe043423
0380006f
fd043783
0017f793
00078a63
fe843703
fd843783
00f707b3
fef43423
fd843783
00179793
fcf43c23
fd043783
0017d793
fcf43823
fd043783
fc0794e3
fe843783
00078513
02813083
02013403
03010113
00008067
fc010113
02113c23
02813823
04010413
fca43423
fcb43023
fc043783
00079663
fff00793
0980006f
fe043423
fe043023
03f00793
fcf42e23
0740006f
fe043783
00179793
fef43023
fdc42783
00078713
fc843783
00e7d7b3
0017f793
fe043703
00f767b3
fef43023
fe043703
fc043783
02f76863
fe043703
fc043783
40f707b3
fef43023
fdc42783
00078713
00100793
00e797b3
fe843703
00f767b3
fef43423
fdc42783
fff7879b
fcf42e23
fdc42783
0007879b
f807d4e3
fe843783
00078513
03813083
03013403
04010113
00008067
fd010113
02113423
02813023
03010413
fca43c23
fcb43823
fd043783
00079663
fd843783
0780006f
fe043423
03f00793
fef42223
0580006f
fe843783
00179793
fef43423
fe442783
00078713
fd843783
00e7d7b3
0017f793
fe843703
00f767b3
fef43423
fe843703
fd043783
00f76a63
fe843703
fd043783
40f707b3
fef43423
fe442783
fff7879b
fef42223
fe442783
0007879b
fa07d2e3
fe843783
00078513
02813083
02013403
03010113
00008067
fd010113
02113423
02813023
03010413
fca43c23
fcb43823
00100793
fef42623
fd843783
0007de63
fd843783
40f007b3
fcf43c23
fec42783
40f007bb
fef42623
fd043783
0007de63
fd043783
40f007b3
fcf43823
fec42783
40f007bb
fef42623
fd843783
fd043703
00070593
00078513
e11ff0ef
00050793
fef43023
fec42783
0007879b
00f04863
fe043783
40f007b3
0080006f
fe043783
00078513
02813083
02013403
03010113
00008067
fd010113
02113423
02813023
03010413
fca43c23
fcb43823
00100793
fef42623
fd843783
0007de63
fd843783
40f007b3
fcf43c23
fec42783
40f007bb
fef42623
fd043783
0007d863
fd043783
40f007b3
fcf43823
fd843783
fd043703
00070593
00078513
e41ff0ef
00050793
fef43023
fec42783
0007879b
00f04863
fe043783
40f007b3
0080006f
fe043783
00078513
02813083
02013403
03010113
00008067
fe010113
00113c23
00813823
02010413
00050793
fef407a3
00000013
100007b7
00578793
0007c783
0ff7f793
0007879b
0207f793
0007879b
fe0782e3
100007b7
fef44703
00e78023
00000013
00000013
00000013
01813083
01013403
02010113
00008067
fe010113
00113c23
00813823
02010413
fea43423
01c0006f
fe843783
00178713
fee43423
0007c783
00078513
f71ff0ef
fe843783
0007c783
fe0790e3
00000013
00000013
01813083
01013403
02010113
00008067
fe010113
00113c23
00813823
02010413
342027f3
fef43423
fe843703
fff00793
03f79793
00978793
06f71c63
100007b7
00578793
0007c783
0ff7f793
0007879b
0017f793
0007879b
04078c63
100007b7
0007c783
fef403a3
fe744783
00078513
ee9ff0ef
fe744783
0ff7f713
00a00793
00f71863
00000517
0d850513
f31ff0ef
fe744783
0ff7f713
00300793
00f71a63
00000797
0dc78793
00100713
00e7a023
00000013
01813083
01013403
02010113
00008067
ff010113
00113423
00813023
01010413
100007b7
00278793
00100713
00e78023
100007b7
00178793
00100713
00e78023
00000797
a9478793
30579073
20000793
3047a073
00800793
3007a073
00000517
05450513
ea5ff0ef
0080006f
00000013
00000797
05878793
0007a783
fe0788e3
00000517
03850513
e81ff0ef
00100793
00078513
00813083
00013403
01010113
00008067
00000000
0000203e
00000000
00203e0a
00000000
676f7270
206d6172
656e6f64
0000000a
"""

keymap = {
    2: (ord('1'), ord('!')), 3: (ord('2'), ord('@')), 4: (ord('3'), ord('#')),
    5: (ord('4'), ord('$')), 6: (ord('5'), ord('%')), 7: (ord('6'), ord('^')),
    8: (ord('7'), ord('&')), 9: (ord('8'), ord('*')), 10: (ord('9'), ord('(')),
    11: (ord('0'), ord(')')), 12: (ord('-'), ord('_')), 13: (ord('='), ord('+')),
    
    16: (ord('q'), ord('Q')), 17: (ord('w'), ord('W')), 18: (ord('e'), ord('E')),
    19: (ord('r'), ord('R')), 20: (ord('t'), ord('T')), 21: (ord('y'), ord('Y')),
    22: (ord('u'), ord('U')), 23: (ord('i'), ord('I')), 24: (ord('o'), ord('O')),
    25: (ord('p'), ord('P')), 26: (ord('['), ord('{')), 27: (ord(']'), ord('}')),
    
    30: (ord('a'), ord('A')), 31: (ord('s'), ord('S')), 32: (ord('d'), ord('D')),
    33: (ord('f'), ord('F')), 34: (ord('g'), ord('G')), 35: (ord('h'), ord('H')),
    36: (ord('j'), ord('J')), 37: (ord('k'), ord('K')), 38: (ord('l'), ord('L')),
    39: (ord(';'), ord(':')), 40: (ord("'"), ord('"')), 43: (ord('\\'), ord('|')),
    
    44: (ord('z'), ord('Z')), 45: (ord('x'), ord('X')), 46: (ord('c'), ord('C')),
    47: (ord('v'), ord('V')), 48: (ord('b'), ord('B')), 49: (ord('n'), ord('N')),
    50: (ord('m'), ord('M')), 51: (ord(','), ord('<')), 52: (ord('.'), ord('>')),
    53: (ord('/'), ord('?')),
    
    57: (ord(' '), ord(' ')),
    28: (ord('\n'), ord('\n')),
    14: (ord('\b'), ord('\b')),
}

SHIFT_KEYS = (42, 54) # 42 is Left Shift, 54 is Right Shift

format_string = 'iiHHi'
event_size = struct.calcsize(format_string)
device_path = '/dev/input/event0' 
shift_pressed = False

# allocate memory and run the core
rst.write(1, 0xFFFFFFFF)

buffer = allocate(shape=(4194304,), dtype='u4', cacheable=False)
phymem_address = buffer.physical_address

phy_ps_addr.write(phymem_address, 0xFFFFFFFF)

instructions = [
    int(line.strip(), 16)
    for line in instructions_text.strip().split('\n')
    if line.strip()
]

for i, instr in enumerate(instructions):
    buffer[i] = instr

buffer.flush()
time.sleep(1)
rst.write(0, 0xFFFFFFFF)

try:
    with open(device_path, 'rb') as f:
        while True:
            data = f.read(event_size)
            if data:
                tv_sec, tv_usec, ev_type, code, value = struct.unpack(format_string, data)
                
                # We only care about Key Events (ev_type == 1)
                if ev_type == 1:
                    
                    # STATE MACHINE LOGIC: Update Shift state
                    if code in SHIFT_KEYS:
                        if value == 1: # Shift key pressed down
                            shift_pressed = True
                        elif value == 0: # Shift key released
                            shift_pressed = False
                            
                    # KEY PRESS LOGIC (value == 1 means key pressed)
                    elif value == 1:
                        if code == 1: # ESC key
                            print("\nExiting...")
                            break
                            
                        # If the key is in our dictionary...
                        if code in keymap:
                            # Act like a multiplexer: Select index 1 if Shift is high, else index 0
                            mux_select = 1 if shift_pressed else 0
                            ascii_val = keymap[code][mux_select]
                            
                            print(f"Typed: '{chr(ascii_val)}' -> Sending ASCII: {ascii_val}")
                            
                            # Push the 8-bit ASCII value to the PL
                            kb.write(ascii_val, 0xFF)
                            kb_valid.write(1, 0xFF)
                            time.sleep(0.01)
                            kb_valid.write(0, 0xFF)
                        else:
                            print(f"Ignored unmapped key (Code: {code})")
                            
except PermissionError:
    print(f"Permission Denied! Run: !sudo chmod a+rw {device_path}")
except KeyboardInterrupt:
    print("\nProgram stopped.")
    
rst.write(1, 0xFFFFFFFF)
buffer.invalidate()
buffer.close()
