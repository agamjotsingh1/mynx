// Tight loop over a small array that fits entirely in cache.
// After the first pass everything is resident => D$ hit ~= 100%, and the
// small instruction loop => I$ hit very high too.
#include "cacheperf.h"
#pragma GCC optimize("O2")   // keep loop vars in registers; arr volatile => loads emit

#define N (256)           // 2 KiB working set, << 128 KiB cache
#define ITERS (256)
static volatile uint64_t arr[N];

int main() {
  perf_init();
  puts("cache_tight: hot 2 KiB array, 256 passes\n");

  for (int i = 0; i < N; i++) arr[i] = i;   // warm

  perf_t a, b;
  uint64_t sink = 0;
  perf_read(&a);
  for (int it = 0; it < ITERS; it++)
    for (int i = 0; i < N; i++) sink += arr[i];
  perf_read(&b);

  perf_report("cache_tight (hot working set)", &a, &b);
  (void)sink;
  puts("program done\n");
  return 1;
}
