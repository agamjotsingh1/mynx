#include "env/encoding.h"

#define SD_CFG   (*(volatile uint64_t *) (SDBASE + 0x00))
#define SD_ADDR  (*(volatile uint64_t *) (SDBASE + 0x08))
#define SD_DATA  (*(volatile uint64_t *) (SDBASE + 0x10))
#define SD_REPLY (*(volatile uint64_t *) (SDBASE + 0x18))

#define PLIC_IRQ (*(volatile uint64_t *) (PLICBASE   + 0x00))

#define UART_RHR (*((volatile uint8_t *)(UARTBASE + 0x00)))
#define UART_THR (*((volatile uint8_t *)(UARTBASE + 0x00)))
#define UART_IER (*((volatile uint8_t *)(UARTBASE + 0x01)))
#define UART_FCR (*((volatile uint8_t *)(UARTBASE + 0x02)))
#define UART_LSR (*((volatile uint8_t *)(UARTBASE + 0x05)))

#define LSR_DATA_READY 0x01
#define LSR_THR_EMPTY  0x20
#define IER_RX_ENABLE  0x01
#define FCR_FIFO_EN    0x01

#define SPICR  0x60
#define SPISR  0x64
#define SPIDTR 0x68
#define SPIDRR 0x6C
#define SPISSR 0x70
#define SPISRR 0x40

extern void trapvec();

volatile int done;
volatile uint64_t reply;

void putc(char c) {
  while ((UART_LSR & LSR_THR_EMPTY) == 0);
  UART_THR = c;
}

void puts(const char* str) {
  while (*str) {
    putc(*str++);
  }
}

void trap_handler() {
  uint64_t mcause;
  csrr(mcause, mcause);

  // MSB=1 (Interrupt), Code=9 (S-External)
  if (mcause == 0x8000000000000009ULL) {
    if(PLIC_IRQ == 2) {
      done = 1;
      reply = SD_REPLY;
    }
  }
}

void sd_write(uint64_t addr, uint64_t data) {
  done = 0;
  SD_DATA = data;
  SD_ADDR = addr;
  SD_CFG  = 0b1001;
  while(done != 1)
    ;
  done = 0;
}

uint64_t sd_read(uint64_t addr) {
  done = 0;
  SD_ADDR = addr;
  SD_CFG  = 0b0101;
  while(done != 1)
    ;

  done = 0;
  return SD_REPLY;
}

void put_nibble(uint8_t n) {
  n &= 0x0F;
  if (n < 10) putc('0' + n);
  else        putc('a' + n - 10);
}

void put_hex8(uint8_t v) {
  put_nibble(v >> 4);
  put_nibble(v);
}

void put_hex32(uint64_t v) {
  puts("0x");
  put_hex8((v >> 24) & 0xFF);
  put_hex8((v >> 16) & 0xFF);
  put_hex8((v >>  8) & 0xFF);
  put_hex8( v        & 0xFF);
}

void spi_inhibit() {
  sd_write(SPICR, 0x00000186);
}

void spi_release() {
  sd_write(SPICR, 0x00000086);
}

void spi_cs_low() {
  sd_write(SPISSR, 0x00000000);
}

void spi_cs_high() {
  sd_write(SPISSR, 0xFFFFFFFF);
}

void spi_tx_wait() {
  // bit 2 says:
  // 1 for "tx fifo empty"
  // 0 for "tx fifo not empty"
  while ((sd_read(SPISR) & (1ULL << 2)) == 0)
    ;
}

void spi_rx_wait() {
  // bit 0 says:
  // 1 for "rx fifo empty"
  // 0 for "rx fifo not empty"
  while (sd_read(SPISR) & (1ULL << 0))
    ;
}

// transfer one byte
uint8_t spi_xfer(uint8_t byte) {
  spi_inhibit();
  sd_write(SPIDTR, byte);
  spi_release();
  spi_tx_wait();
  spi_rx_wait();
  return (uint8_t) sd_read(SPIDRR);
}

// clock the bus with dummy 0xFF (CS stays wherever it is)
uint8_t spi_dummy() {
  return spi_xfer(0xFF);
}

// send 6-byte SD command and return the R1 response
// keep CS asserted (low) throughout
uint8_t sd_cmd(uint8_t cmd, uint64_t arg, uint8_t crc) {
  spi_xfer(0x40 | cmd);
  spi_xfer((arg >> 24) & 0xFF);
  spi_xfer((arg >> 16) & 0xFF);
  spi_xfer((arg >>  8) & 0xFF);
  spi_xfer((arg >>  0) & 0xFF);
  spi_xfer(crc);

  uint8_t r;
  for (int i = 0; i < 255; i++) {
    // keep clock alive and poll for MSB 0 (R1) response
    r = spi_dummy();
    if ((r & 0x80) == 0) return r;
  }
  return r;
}

int sd_init(int *block_addressing) {
  // SPI core reset + setup
  // softreset the AXI Quad SPI IP (clears FIFOs + cfg)
  sd_write(SPISRR, 0x0000000A);

  spi_inhibit();
  spi_cs_high();

  // put alteast 74 dummy clocks
  for (int i = 0; i < 10; i++) {
    spi_dummy();
  }

  puts("dummy clocks done\n");

  // CMD0: go idle state
  spi_cs_low();
  // 0x95 is the CRC checksum
  uint8_t r1 = sd_cmd(0, 0x00000000, 0x95);
  spi_cs_high();
  spi_dummy();

  if (r1 != 0x01) {
    puts("CMD0 failed, R1=");
    put_hex8(r1);
    putc('\n');
    return 1;
  }
  puts("CMD0 ok (idle)\n");

  // CMD8 - send if condition (voltage check)
  spi_cs_low();
  // 0x87 is CRC checksum
  // 0xAA is random ping
  // 0x100 is voltage check (2.7V to 3.6V compatible)
  r1 = sd_cmd(8, 0x000001AA, 0x87);
  uint64_t cmd8_resp = 0;
  if (r1 <= 0x01) {
    // CMD8 gives R7 response
    // read 4-byte R7 tail
    // send continous dummy for response
    for (int i = 0; i < 4; i++)
      cmd8_resp = (cmd8_resp << 8) | spi_dummy();
  }
  spi_cs_high();
  spi_dummy();

  if (r1 > 0x01) {
    puts("CMD8 rejected (old card?), R1=");
    put_hex8(r1);
    putc('\n');
  } else {
    puts("CMD8 ok, R7=");
    put_hex32(cmd8_resp);
    putc('\n');
    if ((cmd8_resp & 0x1FF) != 0x1AA) {
      puts("voltage/pattern mismatch!\n");
      return 1;
    }
  }

  // CMD55 + ACMD41 loop - app send op condition
  int timeout = 10000;
  while (timeout > 0) {
    // CMD55 - next command is application-specific
    spi_cs_low();
    r1 = sd_cmd(55, 0x00000000, 0x01);
    spi_cs_high();
    spi_dummy();

    if (r1 > 0x01) {
      puts("CMD55 err, R1=");
      put_hex8(r1);
      putc('\n');
      return 1;
    }

    // ACMD41 - send HCS=1 (bit 30)
    // HCS bit set in ACMD41 arg for SDHC/SDXC support
    spi_cs_low();
    r1 = sd_cmd(41, 0x40000000, 0x01);
    spi_cs_high();
    spi_dummy();

    if (r1 == 0x00) break; // card ready
    timeout--;
  }

  if (timeout == 0) {
    puts("ACMD41 timed out\n");
    return 1;
  }
  puts("ACMD41 ok (card ready, out of idle state)\n");

  // CMD58 - read ocr
  // returns R3 response (5 bytes long)
  // R1 (byte) + OCR
  spi_cs_low();
  r1 = sd_cmd(58, 0x00000000, 0x01);
  uint64_t ocr = 0;
  for (int i = 0; i < 4; i++)
    ocr = (ocr << 8) | spi_xfer(0xFF);
  spi_cs_high();
  spi_dummy();

  puts("CMD58 OCR=");
  put_hex32(ocr);
  putc('\n');

  // CCS bit (bit 30 of OCR) - if set, card uses block addressing (SDHC/SDXC)
  *block_addressing = (ocr >> 30) & 1;
  if (*block_addressing)
    puts("SDHC/SDXC (block addressing)\n");
  else
    puts("SDSC (byte addressing)\n");

  // CMD16 - set blocklen (512) for SDSC cards
  if (!(*block_addressing)) {
    spi_cs_low();
    r1 = sd_cmd(16, 512, 0x01);
    spi_cs_high();
    spi_dummy();

    if (r1 != 0x00) {
      puts("CMD16 failed, R1=");
      put_hex8(r1);
      putc('\n');
      return 1;
    }
    puts("CMD16 ok (block len = 512)\n");
  }

  return 0;
}

int sd_write_blk(uint64_t block, uint8_t* data, int block_addressing) {
  uint64_t write_addr = block_addressing ? block : (block * 512);

  spi_cs_low();
  uint8_t r1 = sd_cmd(24, write_addr, 0x01);
  if (r1 != 0x00) {
    puts("CMD24 rejected, R1=");
    put_hex8(r1);
    putc('\n');
    spi_cs_high();
    spi_dummy();
    return 1;
  }

  // send start token
  spi_xfer(0xFE);

  // send data
  for (int i = 0; i < 512; i++) {
    spi_xfer(data[i]);
  }

  // dummy CRC (2 bytes)
  spi_xfer(0xFF);
  spi_xfer(0xFF);

  // read data response token: xxx0SSS1
  // S for status, x for dont care
  uint8_t dr = spi_xfer(0xFF) & 0x1F;
  if (dr != 0x05) {
    puts("write rejected, DR=");
    put_hex8(dr);
    putc('\n');
    spi_cs_high();
    spi_dummy();
    return 1;
  }

  // wait for card to finish programming (busy := MISO low -> reads 0x00)
  int timeout = 100000;
  while (timeout > 0) {
    if (spi_xfer(0xFF) != 0x00) break;
    timeout--;
  }
  spi_cs_high();
  spi_dummy();

  if (timeout == 0) {
    puts("write busy timeout\n");
    return 1;
  }

  return 0;
}

int sd_read_blk(uint64_t block, uint8_t* data, int block_addressing) {
  uint64_t read_addr = block_addressing ? block : (block * 512);
  spi_cs_low();
  uint8_t r1 = sd_cmd(17, read_addr, 0x01);

  if (r1 != 0x00) {
    puts("CMD17 rejected, R1=");
    put_hex8(r1);
    putc('\n');
    spi_cs_high();
    spi_dummy();
    return 1;
  }

  // wait for data start token (0xFE)
  int timeout = 100000;
  uint8_t token;
  while (timeout > 0) {
    token = spi_xfer(0xFF);
    if (token == 0xFE) break;
    if (token != 0xFF) {
      puts("read error token=");
      put_hex8(token);
      putc('\n');
      spi_cs_high();
      spi_dummy();
      return 1;
    }
    timeout--;
  }

  if (timeout == 0) {
    puts("read start token timeout\n");
    spi_cs_high();
    spi_dummy();
    return 1;
  }

  for (int i = 0; i < 512; i++)
    data[i] = spi_xfer(0xFF);

  // discard 2 CRC bytes
  spi_xfer(0xFF);
  spi_xfer(0xFF);

  spi_cs_high();
  spi_dummy();

  return 0;
}

int main() {
  done = 0;
  csrw(mtvec, trapvec);
  csrs(mie, 1 << 9);     // enable SEIP
  csrs(mstatus, 1 << 3); // enable global M-Mode interrupts

  puts("starting sd card txns\n");

  int block_addressing = 0;
  if (sd_init(&block_addressing) != 0) {
      puts("init sd card FAILED!\n");
      return 1;
  }
  puts("init sd card done!\n");

  uint64_t test_block = 100;
  uint8_t write_buf[512];
  const char* tag = "MYNXMYNXMYNXMYNX";

  for (int i = 0; i < 512; i++) {
    if (i < 16)
      write_buf[i] = (uint8_t)tag[i];
    else
      write_buf[i] = (uint8_t)(i & 0xFF);
  }

  puts("writing block 100...\n");
  if (sd_write_blk(test_block, write_buf, block_addressing) != 0) {
      puts("Write failed!\n");
      return 1;
  }
  puts("write done!\n");

  uint8_t buf[512]; // Read buffer
  puts("reading block 100...\n");
  if (sd_read_blk(test_block, buf, block_addressing) != 0) {
      puts("Read failed!\n");
      return 1;
  }
  puts("read done! first 32 bytes:\n");

  for (int i = 0; i < 32; i++) {
    put_hex8(buf[i]);
    putc(' ');
    if ((i & 0x0F) == 0x0F) putc('\n');
  }
  putc('\n');

  int errors = 0;
  for (int i = 0; i < 16; i++) {
    if (buf[i] != (uint8_t)tag[i]) errors++;
  }
  for (int i = 16; i < 512; i++) {
    if (buf[i] != (uint8_t)(i & 0xFF)) errors++;
  }

  if (errors == 0)
    puts("VERIFY OK! all 512 bytes match.\n");
  else {
    puts("VERIFY FAIL: ");
    put_hex32(errors);
    puts(" mismatches\n");
  }

  puts("test complete.\n");
  return 0;
}
