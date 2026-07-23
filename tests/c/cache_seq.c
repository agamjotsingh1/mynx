#include "cacheperf.h"
#pragma GCC optimize("O2")   // keep loop vars in registers; arr volatile => loads emit

#define N (65536)
static volatile uint64_t arr[N];

int main() {
  perf_init();
  puts("cache_seq: streaming read, 512 KiB\n");

  for (int i = 0; i < N; i++) {
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    arr[i] = i;
  }

  perf_t a, b;
  uint64_t sink = 0;
  perf_read(&a);
  for (int i = 0; i < N; i++) sink += arr[i];
  perf_read(&b);

  perf_report("cache_seq (streaming)", &a, &b);
  (void)sink;
  puts("program done\n");
  return 1;
}
