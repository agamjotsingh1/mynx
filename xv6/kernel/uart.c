//
// low-level driver routines for 16550a UART.
//

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"

#define UART_RHR (*((volatile unsigned char *)(UART0 + 0x00)))
#define UART_THR (*((volatile unsigned char *)(UART0 + 0x00)))
#define UART_IER (*((volatile unsigned char *)(UART0 + 0x01)))
#define UART_FCR (*((volatile unsigned char *)(UART0 + 0x02)))
#define UART_LSR (*((volatile unsigned char *)(UART0 + 0x05)))

#define LSR_DATA_READY 0x01
#define LSR_THR_EMPTY  0x20
#define IER_RX_ENABLE  0x01
#define FCR_FIFO_EN    0x01

extern volatile int panicked; // from printf.c

void
uartinit(void)
{
  UART_IER = 0x00;
  UART_FCR = FCR_FIFO_EN;
  UART_IER = IER_RX_ENABLE;
}

// puts character instantly
void
uartputc(int c)
{
// while ((UART_LSR & LSR_THR_EMPTY) == 0);
  UART_THR = c;
}

void
uartputc_sync(int c)
{
  uartputc(c);
}

// read one input character from the UART.
// return -1 if none is waiting.
int
uartgetc(void)
{
  if(LSR_DATA_READY & UART_LSR){
    return UART_RHR;
  } else {
    return -1;
  }
}

// handle a uart interrupt, raised because input has
// arrived, or the uart is ready for more output, or
// both. called from trap.c.
void
uartintr(void)
{
  // read and process incoming characters.
  while(1){
    int c = uartgetc();
    if(c == -1)
      break;
    consoleintr(c);
  }
}
