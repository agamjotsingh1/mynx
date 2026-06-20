#define UART_BASE 0x10000000 
#define UART_THR  ((volatile unsigned char *)(UART_BASE + 0x00))

void trap_handler() {}

void print_uart(const char *str) {
  while (*str != '\0') {
    *UART_THR = *str;
    str++;
  }
}

int main(void) {
  print_uart("Hello, World from RISC-V!\n");
  return 0;
}