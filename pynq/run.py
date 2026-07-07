from pynq import Overlay, allocate
import time
import struct

overlay = Overlay("design_1.bit")
kb = overlay.kb.channel1
kb_valid = overlay.kb_valid.channel1
rst = overlay.core_rst.channel1
phy_ps_addr = overlay.phy_ps_addr.channel1

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

SHIFT_KEYS = (42, 54)

format_string = 'iiHHi'
event_size = struct.calcsize(format_string)
device_path = '/dev/input/event0' 
shift_pressed = False

# allocate memory and run the core
rst.write(1, 0xFFFFFFFF)

buffer = allocate(shape=(4194304,), dtype='u4', cacheable=False)
phymem_address = buffer.physical_address

phy_ps_addr.write(phymem_address, 0xFFFFFFFF)

try:
    with open('prog.hex', 'r') as f:
        instructions = [
            int(line.strip(), 16)
            for line in f
            if line.strip()
        ]
except FileNotFoundError:
    print("Error: 'instructions.hex' not found. Please make sure you have shifted instructions.hex to the board.")
    rst.write(1, 0xFFFFFFFF)
    buffer.freebuffer()
    exit(1)

for i, instr in enumerate(instructions):
    buffer[i] = instr

buffer.flush()
time.sleep(1)
print("starting core...")
rst.write(0, 0xFFFFFFFF)

try:
    with open(device_path, 'rb') as f:
        while True:
            data = f.read(event_size)
            if data:
                tv_sec, tv_usec, ev_type, code, value = struct.unpack(format_string, data)
                
                if ev_type == 1:
                    if code in SHIFT_KEYS:
                        if value == 1:
                            shift_pressed = True
                        elif value == 0:
                            shift_pressed = False
                            
                    elif value == 1:
                        if code == 1: # escape key pressed
                            print("\nExiting...")
                            break
                            
                        if code in keymap:
                            mux_select = 1 if shift_pressed else 0
                            ascii_val = keymap[code][mux_select]
                            kb.write(ascii_val, 0xFF)
                            kb_valid.write(1, 0xFF)
                            time.sleep(0.01)
                            kb_valid.write(0, 0xFF)

except PermissionError:
    print("\nPermission denied!")
except KeyboardInterrupt:
    print("\nProgram interrupted!")
    
rst.write(1, 0xFFFFFFFF)
buffer.invalidate()
buffer.close()
