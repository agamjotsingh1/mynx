#include "env/encoding.h"

#define BLKDEV_STATUS        (*(volatile uint64_t *) (BLKDEVBASE + 0x00))
#define BLKDEV_SECTOR        (*(volatile uint64_t *) (BLKDEVBASE + 0x08))
#define BLKDEV_MEM_ADDR      (*(volatile uint64_t *) (BLKDEVBASE + 0x10))
#define BLKDEV_CMD           (*(volatile uint64_t *) (BLKDEVBASE + 0x18))
#define PLIC_IRQ             (*(volatile uint64_t *) (PLICBASE   + 0x00))

#define WSECTOR        0x80030000
#define SECTOR_DEPTH   512

#define UART_RHR (*((volatile uint8_t *)(UARTBASE + 0x00)))
#define UART_THR (*((volatile uint8_t *)(UARTBASE + 0x00)))
#define UART_IER (*((volatile uint8_t *)(UARTBASE + 0x01)))
#define UART_FCR (*((volatile uint8_t *)(UARTBASE + 0x02)))
#define UART_LSR (*((volatile uint8_t *)(UARTBASE + 0x05)))

#define LSR_DATA_READY 0x01
#define LSR_THR_EMPTY  0x20
#define IER_RX_ENABLE  0x01
#define FCR_FIFO_EN    0x01

extern void trapvec();

volatile int status = 0;
char sector[SECTOR_DEPTH];

void putc(char c) {
  while ((UART_LSR & LSR_THR_EMPTY) == 0);
  UART_THR = c;
}

void puts(const char* str) {
  while (*str) {
    putc(*str++);
  }
}

void putc_sector(char c, uint64_t off) {
  *(char *) (WSECTOR + off) = c;
}

void puts_sector(const char* str) {
  uint64_t off = 0;
  while (*str && off < SECTOR_DEPTH) {
    putc_sector(*str++, off);
    off++;
  }
  while(off < SECTOR_DEPTH) {
    putc_sector('*', off);
    off++;
  }
  BLKDEV_SECTOR = 0;
  BLKDEV_MEM_ADDR = WSECTOR;
  BLKDEV_CMD = 2;
}

void read_sector() {
  BLKDEV_SECTOR = 0;
  BLKDEV_MEM_ADDR = (uint64_t) sector;
  BLKDEV_CMD = 1;
}

void trap_handler() {
  uint64_t mcause;
  csrr(mcause, mcause);

  if (mcause == 0x8000000000000009ULL) { // MSB=1 (Interrupt), Code=9 (S-External)
    if(status == 0 && PLIC_IRQ == 2) { // done with writing
      BLKDEV_STATUS;
      status = 1;
    }
    else if(status == 1 && PLIC_IRQ == 2) { // done with reading
      BLKDEV_STATUS;
      puts(sector);
      status = 2;
    }
  }
}

int main(){
  csrw(mtvec, trapvec);
  csrs(mie, 1 << 9);     // enable SEIP
  csrs(mstatus, 1 << 3); // enable global M-Mode interrupts

  puts_sector("hello world");

  while(status != 1) {
    // avoid infinite recursion detection here
    __asm__ volatile("nop");
  }

  read_sector();

  while(status != 2) {
    // avoid infinite recursion detection here
    __asm__ volatile("nop");
  }

  return 1;
}