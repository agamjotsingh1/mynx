// displays CPI of the core till this point in time

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define csrr(csr, val) asm volatile ("csrr %0, " #csr : "=r"(val))

// upto 3 decimal places
void printf_ratio(uint64 num, uint64 den) {
  uint64 whole, frac;
  int i;

  if (den == 0) {
    printf("n/a");
    return;
  }

  whole = num / den;
  frac  = ((num % den) * 1000) / den;

  printf("%d.", whole);
  // pad fraction out to 3 digits
  for (i = 100; i > 1; i /= 10) {
    if (frac < (uint64)i) printf("0");
  }
  printf("%d", frac);
}

int
main(void)
{
  uint64 cycles, instructions;
  uint64 cache_hits_instr, mem_acc_instr;
  uint64 cache_hits_data, mem_acc_data;

  csrr(cycle, cycles);
  csrr(instret, instructions);
  csrr(hpmcounter3, cache_hits_instr);
  csrr(hpmcounter4, mem_acc_instr);
  csrr(hpmcounter5, cache_hits_data);
  csrr(hpmcounter6, mem_acc_data);

  printf("CPI:");
  printf_ratio(cycles, instructions);
  printf("\n");

  printf("IPC:");
  printf_ratio(instructions, cycles);
  printf("\n");

  printf("I-Cache hit rate:");
  printf_ratio(cache_hits_instr, mem_acc_instr);
  printf("\n");

  printf("D-Cache hit rate:");
  printf_ratio(cache_hits_data, mem_acc_data);
  printf("\n");

  printf("instructions: %d, mem_acc_instr: %d\n", instructions, mem_acc_instr);
  exit(0);
}

