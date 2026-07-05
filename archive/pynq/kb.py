import sys
import tty
import termios
from pynq import Overlay
from pynq.lib import AxiGPIO

# 1. Load your synthesized design
overlay = Overlay("design_1.bit")
# Assuming an 8-bit AXI GPIO channel connected to your PL module
keyboard = overlay.keyboard
valid = overlay.valid

def get_char():
    """Reads a single character from standard input without waiting for Enter."""
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        # Set terminal to raw mode to capture single keystrokes instantly
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        # Restore normal terminal settings
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

print("Listening for ASCII input (Press Ctrl+C to exit)...")

try:
    while True:
        char = get_char()
        
        # Catch Ctrl+C (ASCII 3) to allow graceful exit from the loop
        if char == '\x03':
            print("\r\nExiting...")
            break
            
        # Convert the character to its integer ASCII representation
        ascii_val = ord(char)
        
        # Write the 8-bit ASCII value directly to the PL via AXI
        keyboard.write(ascii_val, 0xFF)
        valid.write(1, 0xFF)
        time.sleep(0.01)
        valid.write(0, 0xFF)
        
        # Optional: Print to terminal to verify what is being sent
        # (\r is used to return carriage in raw mode)
        print(f"\rSent: {char} (ASCII: {ascii_val})")

except KeyboardInterrupt:
    print("\r\nProgram Terminated.")

