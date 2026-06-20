#include "env/encoding.h"

#define UART_RHR (*((volatile uint8_t *)(UARTBASE + 0x00)))
#define UART_THR (*((volatile uint8_t *)(UARTBASE + 0x00)))
#define UART_IER (*((volatile uint8_t *)(UARTBASE + 0x01)))
#define UART_FCR (*((volatile uint8_t *)(UARTBASE + 0x02)))
#define UART_LSR (*((volatile uint8_t *)(UARTBASE + 0x05)))

#define LSR_DATA_READY 0x01
#define LSR_THR_EMPTY  0x20
#define IER_RX_ENABLE  0x01
#define FCR_FIFO_EN    0x01

#define CLINT_MTIME    (*((volatile uint64_t *)(CLINTBASE + 0x00)))
#define CLINT_MTIMECMP (*((volatile uint64_t *)(CLINTBASE + 0x08)))

extern void trapvec();

int done = 0;

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

  if (mcause == 0x8000000000000007ULL) { // MSB=1 (Interrupt), Code=7 (M-Timer)
    // timer interrupt
    putc('.');
    CLINT_MTIME;
  }
}

int main(){
  csrw(mtvec, trapvec);
  csrs(mie, 1 << 7);     // enable MTIP
  csrs(mstatus, 1 << 3); // enable global M-Mode interrupts
  CLINT_MTIMECMP = 20000;

  while(!done) {
    // avoid infinite recursion detection here
    __asm__ volatile("nop");
  }

  return 1;
}