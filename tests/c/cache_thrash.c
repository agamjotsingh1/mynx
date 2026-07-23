// Conflict thrash: touch a handful of addresses that all alias to the SAME
// cache set (spaced exactly CACHE_BYTES apart). Direct-mapped => the set holds
// only one line, so every access evicts the previous one => ~0% D$ hits even
// though only 16 distinct lines are ever touched.
#include "cacheperf.h"
// -O2 so loop counters stay in registers; without it -O0 stack traffic (all
// hot hits) would drown the array misses. arr is volatile so the loads are
// actually emitted (the array is never written, so the optimizer would
// otherwise fold the zero-init reads away).
#pragma GCC optimize("O2")

#define STEP  (CACHE_BYTES / 8)   // doublewords between aliasing addresses
#define POINTS 16
#define N     (STEP * POINTS)     // 2 MiB span
#define ITERS (4096)
static volatile uint64_t arr[N];

int main() {
  perf_init();
  puts("cache_thrash: 16 aliasing lines, 4096 passes\n");

  perf_t a, b;
  uint64_t sink = 0;   // register accumulator (arr is volatile => loads emit)
  perf_read(&a);
  for (int it = 0; it < ITERS; it++)
    for (int k = 0; k < POINTS; k++)
      sink += arr[(uint64_t)k * STEP];
  perf_read(&b);

  perf_report("cache_thrash (conflict misses)", &a, &b);
  (void)sink;
  puts("program done\n");
  return 1;
}
