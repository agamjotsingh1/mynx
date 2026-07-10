#include "types.h"

#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "buf.h"
#include "defs.h"
#include "blkdev.h"

// #define __SIM__

struct {
  struct spinlock blkdev_lock;
  struct buf *b; // Active buffer
  int block_addressing;
} disk;

#ifdef __SIM__
void blkdev_init(void) {
  initlock(&disk.blkdev_lock, "blkdev");
}

void blkdev_rw(struct buf *b, int write) {
  acquire(&disk.blkdev_lock);
  disk.b = b;
  b->disk = 1;

  // wait for blkdev to be IDLE
  while(*(uint64*)BLKDEV_STATUS != 0)
    ;

  *(uint64*)BLKDEV_SECTOR = b->blockno;
  *(uint64*)BLKDEV_MEM_ADDR = (uint64)b->data;
  *(uint64*)BLKDEV_CMD = write ? BLKDEV_CMD_WRITE : BLKDEV_CMD_READ; 

  // sleep the process until the blkdev IRQ raises
  while(b->disk == 1) {
    sleep(b, &disk.blkdev_lock);
  }

  disk.b = 0;
  release(&disk.blkdev_lock);
}

void blkdev_intr(void) {
  acquire(&disk.blkdev_lock);
  
  // must read STATUS to clear the hardware IRQ flag
  volatile uint64 status __attribute__((unused)) = *(uint64*)BLKDEV_STATUS;
  
  if(disk.b && disk.b->disk == 1) {
    disk.b->disk = 0;   // mark complete
    wakeup(disk.b);     // wake the sleeping process
  }
  
  release(&disk.blkdev_lock);
}
#else
// sd card interface
#define SD_CFG   (*(volatile uint64*) (BLKDEV + 0x00))
#define SD_ADDR  (*(volatile uint64*) (BLKDEV + 0x08))
#define SD_DATA  (*(volatile uint64*) (BLKDEV + 0x10))
#define SD_REPLY (*(volatile uint64*) (BLKDEV + 0x18))
#define SD_DONE  (*(volatile uint64*) (BLKDEV + 0x20))

#define SPICR  0x60
#define SPISR  0x64
#define SPIDTR 0x68
#define SPIDRR 0x6C
#define SPISSR 0x70
#define SPISRR 0x40

void sd_write(uint64 addr, uint64 data) {
  SD_DATA = data;
  SD_ADDR = addr;
  SD_CFG  = 0b1001;

  while(SD_DONE != 1)
    ;
}

uint64 sd_read(uint64 addr) {
  SD_ADDR = addr;
  SD_CFG  = 0b0101;

  while(SD_DONE != 1)
    ;
    
  return SD_REPLY; 
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
uint8 spi_xfer(uint8 byte) {
  spi_inhibit();
  sd_write(SPIDTR, byte);
  spi_release();
  spi_tx_wait();
  spi_rx_wait();
  return (uint8) sd_read(SPIDRR);
}

// clock the bus with dummy 0xFF (CS stays wherever it is)
uint8 spi_dummy() {
  return spi_xfer(0xFF);
}

// send 6-byte SD command and return the R1 response
// keep CS asserted (low) throughout
uint8 sd_cmd(uint8 cmd, uint64 arg, uint8 crc) {
  spi_xfer(0x40 | cmd);
  spi_xfer((arg >> 24) & 0xFF);
  spi_xfer((arg >> 16) & 0xFF);
  spi_xfer((arg >>  8) & 0xFF);
  spi_xfer((arg >>  0) & 0xFF);
  spi_xfer(crc);

  uint8 r;
  for (int i = 0; i < 255; i++) {
    // keep clock alive and poll for MSB 0 (R1) response
    r = spi_dummy();
    if ((r & 0x80) == 0) return r;
  }
  return r;
}

int sd_init() {
  // SPI core reset + setup
  // softreset the AXI Quad SPI IP (clears FIFOs + cfg)
  sd_write(SPISRR, 0x0000000A);

  spi_inhibit();
  spi_cs_high();

  // put alteast 74 dummy clocks
  for (int i = 0; i < 10; i++) {
    spi_dummy();
  }

  /* printf("dummy clocks done\n"); */

  // CMD0: go idle state
  spi_cs_low();
  // 0x95 is the CRC checksum
  uint8 r1 = sd_cmd(0, 0x00000000, 0x95);
  spi_cs_high();
  spi_dummy();

  if (r1 != 0x01) {
    printf("CMD0 failed, R1=");
    printf("%x", r1);
    printf("\n");
    return 1;
  }
  /* printf("CMD0 ok (idle)\n"); */

  // CMD8 - send if condition (voltage check)
  spi_cs_low();
  // 0x87 is CRC checksum
  // 0xAA is random ping
  // 0x100 is voltage check (2.7V to 3.6V compatible)
  r1 = sd_cmd(8, 0x000001AA, 0x87);
  uint64 cmd8_resp = 0;
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
    printf("CMD8 rejected (old card?), R1=");
    printf("%x", r1);
    printf("\n");
  } else {
    /* printf("CMD8 ok, R7="); */
    /* printf("%x", cmd8_resp); */
    /* printf("\n"); */
    if ((cmd8_resp & 0x1FF) != 0x1AA) {
      printf("voltage/pattern mismatch!\n");
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
      printf("CMD55 err, R1=");
      printf("%x", r1);
      printf("\n");
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
    printf("ACMD41 timed out\n");
    return 1;
  }
  /* printf("ACMD41 ok (card ready, out of idle state)\n"); */

  // CMD58 - read ocr
  // returns R3 response (5 bytes long)
  // R1 (byte) + OCR
  spi_cs_low();
  r1 = sd_cmd(58, 0x00000000, 0x01);
  uint64 ocr = 0;
  for (int i = 0; i < 4; i++)
    ocr = (ocr << 8) | spi_xfer(0xFF);
  spi_cs_high();
  spi_dummy();

  /* printf("CMD58 OCR="); */
  /* printf("%x", ocr); */
  /* printf("\n"); */

  // CCS bit (bit 30 of OCR) - if set, card uses block addressing (SDHC/SDXC)
  disk.block_addressing = (ocr >> 30) & 1;
  if (disk.block_addressing)
    printf("SDHC/SDXC (block addressing)\n");
  else
    printf("SDSC (byte addressing)\n");

  // CMD16 - set blocklen (512) for SDSC cards
  if (!(disk.block_addressing)) {
    spi_cs_low();
    r1 = sd_cmd(16, 512, 0x01);
    spi_cs_high();
    spi_dummy();

    if (r1 != 0x00) {
      printf("CMD16 failed, R1=");
      printf("%x", r1);
      printf("\n");
      return 1;
    }
    /* printf("CMD16 ok (block len = 512)\n"); */
  }

  return 0;
}

int sd_write_blk(uint64 block, uint8* data) {
  uint64 write_addr = disk.block_addressing ? block : (block * 512);

  spi_cs_low();
  uint8 r1 = sd_cmd(24, write_addr, 0x01);
  if (r1 != 0x00) {
    printf("CMD24 rejected, R1=");
    printf("%x", r1);
    printf("\n");
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
  uint8 dr = spi_xfer(0xFF) & 0x1F;
  if (dr != 0x05) {
    printf("write rejected, DR=");
    printf("%x", dr);
    printf("\n");
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
    printf("write busy timeout\n");
    return 1;
  }

  return 0;
}

int sd_read_blk(uint64 block, uint8 * data) {
  uint64 read_addr = disk.block_addressing ? block : (block * 512);
  spi_cs_low();
  uint8 r1 = sd_cmd(17, read_addr, 0x01);

  if (r1 != 0x00) {
    printf("CMD17 rejected, R1=");
    printf("%x", r1);
    printf("\n");
    spi_cs_high();
    spi_dummy();
    return 1;
  }

  // wait for data start token (0xFE)
  int timeout = 100000;
  uint8 token;
  while (timeout > 0) {
    token = spi_xfer(0xFF);
    if (token == 0xFE) break;
    if (token != 0xFF) {
      printf("read error token=");
      printf("%x", token);
      printf("\n");
      spi_cs_high();
      spi_dummy();
      return 1;
    }
    timeout--;
  }

  if (timeout == 0) {
    printf("read start token timeout\n");
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

void blkdev_init(void) {
  initlock(&disk.blkdev_lock, "blkdev");

  if (sd_init() != 0)
    panic("blkdev: sd init failed");

  printf("blkdev: sd card initialized\n");
}

void blkdev_rw(struct buf *b, int write) {
  acquire(&disk.blkdev_lock);
  disk.b = b;
  b->disk = 1;

  // BSIZE (1024) = 2 × SD sectors (512)
  // xv6 blockno N maps to SD sectors N*2 and N*2+1
  uint64 sector = (uint64)b->blockno * 2;

  if (write) {
    if (sd_write_blk(sector, b->data) != 0)
      panic("blkdev: sd write sector 0 failed");
    if (sd_write_blk(sector + 1, b->data + 512) != 0)
      panic("blkdev: sd write sector 1 failed");
  } else {
    if (sd_read_blk(sector, b->data) != 0)
      panic("blkdev: sd read sector 0 failed");
    if (sd_read_blk(sector + 1, b->data + 512) != 0)
      panic("blkdev: sd read sector 1 failed");
  }

  b->disk = 0;
  disk.b = 0;
  release(&disk.blkdev_lock);
}

void blkdev_intr(void) {
  // just dummy read done (ack), we are not using interrupts as of now
  volatile uint64 dummy __attribute__((unused)) = SD_DONE;
}

#endif
