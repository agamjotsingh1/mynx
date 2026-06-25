import time

REG_SOFTRST = 0x40
REG_CONTROL = 0x60
REG_SLAVE_SELECT = 0x70
REG_STATUS = 0x64
REG_TX = 0x68
REG_RX = 0x6C

def spi_init():
    # hard reset the SPI module
    # 0x0A is magic number
    spi.write(REG_SOFTRST, 0x0A)
    time.sleep(0.05)
    
    # 1. turn the SPI module on
    # 2. instruct the module to act as "master"
    # 3. manual slave select enable
    # 4. reset TX and RX fifos
    spi.write(REG_CONTROL, 0xE6) 
    time.sleep(0.01)
    
    # 1, 2, 3 but not 4
    spi.write(REG_CONTROL, 0x86)

def spi_transfer(tx_byte):
    spi.write(REG_SLAVE_SELECT, 0xFE)
    spi.write(REG_TX, tx_byte)

    # 0x00 means byte has been sent
    while (spi.read(REG_STATUS) & 0x01): 
        pass
        
    rx_byte = spi.read(REG_RX)
    spi.write(REG_SLAVE_SELECT, 0xFF)
    return rx_byte

def send_cmd(cmd_list):
    """Sends a command and waits for a valid response with a timeout."""
    spi.write(0x70, 0xFE)
    for byte in cmd_list:
        spi_transfer(byte)
        
    resp = 0xFF
    for _ in range(100):
        resp = spi_transfer(0xFF)
        if resp != 0xFF:
            break
            
    spi.write(0x70, 0xFF)
    spi_transfer(0xFF) 
    return resp

def wake_sd_card():
    print("--- RUNNING SD CARD WAKEUP SEQUENCE ---")
    spi_init()
    
    # 74+ dummy clocks, CS HIGH
    spi.write(0x70, 0xFF) 
    for _ in range(15):
        spi_transfer(0xFF)
        
    time.sleep(0.05)
    
    print("Sending CMD0...")
    if send_cmd([0x40, 0x00, 0x00, 0x00, 0x00, 0x95]) != 0x01:
        print("Failed to enter IDLE state.")
        return False

    print("Sending CMD8...")
    send_cmd([0x48, 0x00, 0x00, 0x01, 0xAA, 0x87])

    print("Initializing Card (CMD55 + ACMD41)...")
    for attempt in range(100):
        send_cmd([0x77, 0x00, 0x00, 0x00, 0x00, 0x01])
        resp2 = send_cmd([0x69, 0x40, 0x00, 0x00, 0x00, 0x01])
        
        if resp2 == 0x00:
            print("SUCCESS: Card is READY (0x00).")
            return True
            
        time.sleep(0.01)

    print(f"Error: Card initialization timeout. Last response: {hex(resp2)}")
    return False

def wait_for_response(expected=0x00, retries=100):
    for _ in range(retries):
        if spi_transfer(0xFF) == expected:
            return True
    return False

def write_block(block_addr, test_byte):
    spi.write(0x70, 0xFE) 
    
    # CMD24
    cmd24 = [0x58, (block_addr >> 24) & 0xFF, (block_addr >> 16) & 0xFF, 
             (block_addr >> 8) & 0xFF, block_addr & 0xFF, 0xFF]
    
    for byte in cmd24:
        spi_transfer(byte)
        
    if not wait_for_response(0x00):
        print("Error: Card rejected CMD24")
        spi.write(0x70, 0xFF)
        return False
        
    spi_transfer(0xFF)
    spi_transfer(0xFE) # Data start token
    
    for i in range(512):
        spi_transfer(test_byte if i == 0 else 0x00)
        
    # Dummy CRC
    spi_transfer(0xFF)
    spi_transfer(0xFF)
    
    # Verify Data Response token
    if (spi_transfer(0xFF) & 0x1F) != 0x05:
        print("Error: Data rejected")
        spi.write(0x70, 0xFF)
        return False
        
    # Wait while flash memory is busy
    while spi_transfer(0xFF) == 0x00:
        pass
        
    spi.write(0x70, 0xFF)
    return True

def read_block(block_addr):
    spi.write(0x70, 0xFE)
    
    # CMD17
    cmd17 = [0x51, (block_addr >> 24) & 0xFF, (block_addr >> 16) & 0xFF, 
             (block_addr >> 8) & 0xFF, block_addr & 0xFF, 0xFF]
    
    for byte in cmd17:
        spi_transfer(byte)
        
    if not wait_for_response(0x00):
        print("Error: Card rejected CMD17")
        spi.write(0x70, 0xFF)
        return None
        
    # Wait for Data Start token (0xFE)
    if not wait_for_response(0xFE, retries=1000):
        print("Error: Timeout waiting for data")
        spi.write(0x70, 0xFF)
        return None
        
    data = []
    for _ in range(512):
        data.append(spi_transfer(0xFF))
        
    # Discard CRC
    spi_transfer(0xFF)
    spi_transfer(0xFF)
    
    spi.write(0x70, 0xFF)
    return data

# ==========================================
# EXECUTION
# ==========================================
if wake_sd_card():
    target_block = 0x00000001
    test_data_byte = 0xAB

    print(f"\n--- RUNNING SD CARD READ/WRITE TEST ---")
    print(f"Writing test byte {hex(test_data_byte)} to Block {target_block}...")

    if write_block(target_block, test_data_byte):
        print("Write complete. Reading block back...")
        read_data = read_block(target_block)
        
        if read_data:
            read_byte = read_data[0]
            
            print(f"\nSent Byte: {hex(test_data_byte)}")
            print(f"Read Byte: {hex(read_byte)}")
            
            if test_data_byte == read_byte:
                print("SUCCESS! Data successfully written to and read from flash memory.")
            else:
                print("FAILED! Data mismatch. Flash memory read/write error.")
