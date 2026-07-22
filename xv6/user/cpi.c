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
  csrr(cycle, cycles);
  csrr(instret, instructions);

  printf("CPI:");
  printf_ratio(cycles, instructions);
  printf("\n");

  exit(0);
}

