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

void put_dec(uint64_t v) {
  char buf[21];
  int i = 0;

  if (v == 0) {
    putc('0');
    return;
  }

  while (v) {
    buf[i++] = '0' + (char)(v % 10);
    v /= 10;
  }

  while (i) putc(buf[--i]);
}

// print num/den with 3 decimal places.
// no fp here, so the fraction comes from the remainder.
void put_ratio(uint64_t num, uint64_t den) {
  uint64_t whole, frac;
  int i;

  if (den == 0) {
    puts("n/a");
    return;
  }

  whole = num / den;
  frac  = ((num % den) * 1000) / den;

  put_dec(whole);
  putc('.');
  // pad fraction out to 3 digits
  for (i = 100; i > 1; i /= 10) {
    if (frac < (uint64_t)i) putc('0');
  }
  put_dec(frac);
}

void trap_handler() {
  uint64_t mcause;
  csrr(mcause, mcause);
}

int main(){
  uint64_t cycle0, instret0, cycle1, instret1;
  uint64_t cycles, instrs;

  UART_FCR = FCR_FIFO_EN;
  UART_IER = IER_RX_ENABLE;
  csrw(mtvec, trapvec);
  csrs(mie, 1 << 9);     // enable SEIP
  csrs(mstatus, 1 << 3); // enable global M-Mode interrupts

  puts("\n> ");

  csrr(mcycle, cycle0);
  csrr(minstret, instret0);

  csrr(mcycle, cycle1);
  csrr(minstret, instret1);

  cycles = cycle1 - cycle0;
  instrs = instret1 - instret0;

  puts("\ncycles   : "); put_dec(cycles);
  puts("\ninstret  : "); put_dec(instrs);
  puts("\nCPI      : "); put_ratio(cycles, instrs);
  puts("\nIPC      : "); put_ratio(instrs, cycles);
  putc('\n');

  puts("program done\n");
  return 1;
}
