#ifndef MACROS_H
#define MACROS_H

typedef unsigned long long uint64_t;
typedef unsigned int       uint32_t;
typedef unsigned char      uint8_t;

#define csrw(csr, val) asm volatile ("csrw " #csr ", %0" : : "r"(val))
#define csrr(csr, val) asm volatile ("csrr %0, " #csr : "=r"(val))
#define csrs(csr, val) asm volatile ("csrs " #csr ", %0" : : "r"(val))
#define csrc(csr, val) asm volatile ("csrc " #csr ", %0" : : "r"(val))

#define UARTBASE 0x10000000
#define MEMBASE  0x80000000

#endif