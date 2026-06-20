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

volatile int done = 0;
volatile char input_char = 0;

void putc(char c) {
  while ((UART_LSR & LSR_THR_EMPTY) == 0);
  UART_THR = c;
}

void puts(const char* str) {
  while (*str) {
    putc(*str++);
  }
}

void print_num(int n) {
  if (n == 0) { 
    putc('0'); 
    return; 
  }
  if (n < 0) { 
    putc('-'); 
    n = -n; 
  }
  
  char buf[12];
  int i = 0;
  
  while (n > 0) { 
    int temp = n;
    int quotient = 0;
    
    while (temp >= 10) {
        temp -= 10;
        quotient++;
    }
    
    buf[i++] = temp + '0'; 
    n = quotient; 
  }
  
  while (i > 0) { 
    putc(buf[--i]); 
  }
}

void trap_handler() {
  uint64_t mcause;
  csrr(mcause, mcause);

  if (mcause == 0x8000000000000009ULL) { 
    if (UART_LSR & LSR_DATA_READY) {
      char c = UART_RHR; 
      putc(c); 
      
      if (c == '3') {
        done = 1;
      } else {
        input_char = c;
      }
    }
  }
}

void print_menu(int energy, int gold) {
  puts("\r\n\r\n=== LIFE SIMULATOR ===\r\n");
  puts("Energy: "); print_num(energy); puts("\r\n");
  puts("Gold:   "); print_num(gold); puts("\r\n");
  puts("1. Work (-2 Energy, +10 Gold)\r\n");
  puts("2. Rest (+5 Energy)\r\n");
  puts("3. Quit\r\n");
  puts("> ");
}

int main(){
  UART_FCR = FCR_FIFO_EN;
  UART_IER = IER_RX_ENABLE;
  csrw(mtvec, trapvec);
  csrs(mie, 1 << 9);     
  csrs(mstatus, 1 << 3); 

  int energy = 10;
  int gold = 0;

  print_menu(energy, gold);

  while(!done) {
    if (input_char != 0) {
      char action = input_char;
      input_char = 0; 
      
      if (action == '1') {
        if (energy >= 2) {
          energy -= 2;
          gold += 10;
          puts("\r\nWorked hard! Earned 10 gold.");
        } else {
          puts("\r\nToo tired to work! Rest first.");
        }
      } else if (action == '2') {
        energy += 5;
        puts("\r\nSlept well. Recovered 5 energy.");
      } else if (action == '3') {
        done = 1;
        break;
      } else if (action == '\r' || action == '\n') {
        continue;
      } else {
        puts("\r\nInvalid action.");
      }
      
      print_menu(energy, gold);
    }
    
    __asm__ volatile("nop");
  }

  puts("\r\nGame Over. Final Gold: ");
  print_num(gold);
  puts("\r\n");
  
  return 1;
}