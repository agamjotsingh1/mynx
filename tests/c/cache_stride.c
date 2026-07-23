// Capacity misses: walk a large array touching one element per 64B line.
// Working set (16384 lines) >> 2048-line cache, so nothing survives to the
// next pass => cold + capacity misses dominate, ~0% intra-line reuse.
#include "cacheperf.h"
#pragma GCC optimize("O2")   // keep loop vars in registers; arr volatile => loads emit

#define N       (131072)          // 1 MiB
#define STRIDE  (8)               // one uint64 per 64B line
#define PASSES  (4)
static volatile uint64_t arr[N];

int main() {
  perf_init();
  puts("cache_stride: 1 line-stride over 1 MiB, 4 passes\n");

  for (int i = 0; i < N; i++) arr[i] = i;   // warm/populate

  perf_t a, b;
  uint64_t sink = 0;
  perf_read(&a);
  for (int p = 0; p < PASSES; p++)
    for (int i = 0; i < N; i += STRIDE) sink += arr[i];
  perf_read(&b);

  perf_report("cache_stride (capacity misses)", &a, &b);
  (void)sink;
  puts("program done\n");
  return 1;
}
