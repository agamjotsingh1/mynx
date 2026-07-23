#include "cacheperf.h"
#pragma GCC optimize("O2")   // keep loop vars in registers; arr volatile => loads emit

#define N     (65536)
#define ITERS (65536)
static volatile uint64_t arr[N];

int main() {
  perf_init();

  for (int i = 0; i < N; i++) arr[i] = i;
  perf_t a, b;
  uint64_t sink = 0;
  uint64_t x = 0x2545F4914F6CDD1DULL;
  perf_read(&a);
  for (int i = 0; i < ITERS; i++) {
    x = x * 6364136223846793005ULL + 1442695040888963407ULL;
    sink += arr[(x >> 33) & (N - 1)];
  }
  perf_read(&b);

  perf_report("cache_random (poor locality)", &a, &b);
  (void)sink;
  puts("program done\n");
  return 1;
}
