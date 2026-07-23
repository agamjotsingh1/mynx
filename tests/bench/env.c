#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#define UART_THR (*((volatile uint8_t *)(0x10000000 + 0x00)))
#define UART_LSR (*((volatile uint8_t *)(0x10000000 + 0x05)))
#define LSR_THR_EMPTY 0x20

#define rdcsr(name) ({ uint64_t __v; asm volatile ("csrr %0, " #name : "=r"(__v)); __v; })

static void uart_putc(char c) {
  while ((UART_LSR & LSR_THR_EMPTY) == 0);
  UART_THR = c;
}

int putchar(int c) { uart_putc((char)c); return c; }

static void out_str(const char *s) { while (*s) uart_putc(*s++); }

static void out_udec(uint64_t v) {
  char buf[21];
  int i = 0;
  if (v == 0) { uart_putc('0'); return; }
  while (v) { buf[i++] = '0' + (v % 10); v /= 10; }
  while (i) uart_putc(buf[--i]);
}

static void out_dec(int64_t v) {
  if (v < 0) { uart_putc('-'); out_udec((uint64_t)(-v)); }
  else out_udec((uint64_t)v);
}

static void out_hex(uint64_t v) {
  const char *d = "0123456789abcdef";
  char buf[16];
  int i = 0;
  if (v == 0) { uart_putc('0'); return; }
  while (v) { buf[i++] = d[v & 0xf]; v >>= 4; }
  while (i) uart_putc(buf[--i]);
}

// minimal printf: %d %u %x %c %s %l{d,u,x} %ll{d,u} %%
int printf(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  for (; *fmt; fmt++) {
    if (*fmt != '%') { uart_putc(*fmt); continue; }
    fmt++;
    int lng = 0;
    while (*fmt == 'l') { lng++; fmt++; }
    switch (*fmt) {
      case 'd': out_dec(lng ? va_arg(ap, int64_t) : (int64_t)va_arg(ap, int)); break;
      case 'u': out_udec(lng ? va_arg(ap, uint64_t) : (uint64_t)va_arg(ap, unsigned)); break;
      case 'x': out_hex(lng ? va_arg(ap, uint64_t) : (uint64_t)va_arg(ap, unsigned)); break;
      case 'c': uart_putc((char)va_arg(ap, int)); break;
      case 's': out_str(va_arg(ap, const char *)); break;
      case '%': uart_putc('%'); break;
      default:  uart_putc('%'); uart_putc(*fmt); break;
    }
  }
  va_end(ap);
  return 0;
}

void *memcpy(void *dst, const void *src, size_t n) {
  uint8_t *d = dst; const uint8_t *s = src;
  while (n--) *d++ = *s++;
  return dst;
}

void *memset(void *dst, int c, size_t n) {
  uint8_t *d = dst;
  while (n--) *d++ = (uint8_t)c;
  return dst;
}

char *strcpy(char *dst, const char *src) {
  char *r = dst;
  while ((*dst++ = *src++));
  return r;
}

int strcmp(const char *a, const char *b) {
  while (*a && *a == *b) { a++; b++; }
  return (uint8_t)*a - (uint8_t)*b;
}

extern void setStats(int enable); // referenced by benchmark

static void print_ratio(uint64_t num, uint64_t den) {
  if (den == 0) { out_str("n/a"); return; }
  out_udec(num / den);
  uart_putc('.');
  uint64_t frac = ((num % den) * 1000) / den;
  if (frac < 100) uart_putc('0');
  if (frac < 10)  uart_putc('0');
  out_udec(frac);
}

static uint64_t s_cyc, s_ins, s_ihit, s_iacc, s_dhit, s_dacc;

void setStats(int enable) {
  uint64_t cyc  = rdcsr(mcycle);
  uint64_t ins  = rdcsr(minstret);
  uint64_t ihit = rdcsr(mhpmcounter3);
  uint64_t iacc = rdcsr(mhpmcounter4);
  uint64_t dhit = rdcsr(mhpmcounter5);
  uint64_t dacc = rdcsr(mhpmcounter6);

  if (enable) {
    s_cyc = cyc; s_ins = ins;
    s_ihit = ihit; s_iacc = iacc;
    s_dhit = dhit; s_dacc = dacc;
    return;
  }

  uint64_t d_cyc  = cyc  - s_cyc;
  uint64_t d_ins  = ins  - s_ins;
  uint64_t d_ihit = ihit - s_ihit;
  uint64_t d_iacc = iacc - s_iacc;
  uint64_t d_dhit = dhit - s_dhit;
  uint64_t d_dacc = dacc - s_dacc;

  out_str("\nperf (measured region)\n");
  out_str("\tcycles          : "); out_udec(d_cyc); uart_putc('\n');
  out_str("\tinstructions    : "); out_udec(d_ins); uart_putc('\n');
  out_str("\tCPI             : "); print_ratio(d_cyc, d_ins); uart_putc('\n');
  out_str("\tIPC             : "); print_ratio(d_ins, d_cyc); uart_putc('\n');
  out_str("\tI-cache hits    : "); out_udec(d_ihit); uart_putc('\n');
  out_str("\tI-cache accesses: "); out_udec(d_iacc); uart_putc('\n');
  out_str("\tI-cache hit rate: "); print_ratio(d_ihit, d_iacc); uart_putc('\n');
  out_str("\tD-cache hits    : "); out_udec(d_dhit); uart_putc('\n');
  out_str("\tD-cache accesses: "); out_udec(d_dacc); uart_putc('\n');
  out_str("\tD-cache hit rate: "); print_ratio(d_dhit, d_dacc); uart_putc('\n');
  out_str("\n");
}
