#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"

volatile static int started = 0;

// DEBUG: deterministic DRAM/cache stress test. runs BEFORE kinit (paging
// off, freelist not built) so it is layout-independent and cannot corrupt
// kernel state. region = 4MB, 32x the 128KB direct-mapped cache, so every
// pass forces heavy eviction + writeback + reload through the AMC.
// pattern is address-derived so a wrong-line/wrong-address return is caught
// too, not just wrong-data.
#define MT_LO 0x80400000UL
#define MT_HI 0x80800000UL
#define MT_KEY 0x5a5a5a5a5a5a5a5aUL

// write pattern then read back over [lo,hi). returns error count and
// characterizes failures: how many landed at line-offset 0, how many read
// back as exactly 0, and the offset-in-line of the first errors.
static uint64
mt_pass(uint64 lo, uint64 hi, const char *tag)
{
  volatile uint64 *base = (uint64*)lo;
  uint64 n = (hi - lo) / 8;
  uint64 i, errs, zeros, off0, shown;

  for(i = 0; i < n; i++)
    base[i] = (lo + i*8) ^ MT_KEY;

  errs = zeros = off0 = shown = 0;
  for(i = 0; i < n; i++){
    uint64 a = lo + i*8;
    uint64 want = a ^ MT_KEY;
    uint64 got = base[i];
    if(got != want){
      errs++;
      if(got == 0) zeros++;
      if((a & 0x3f) == 0) off0++;      // 64B line offset == 0 (first beat)
      if(shown < 8){
        printf("  FAIL @%p off=%d want=%p got=%p\n",
               (void*)a, (int)(a & 0x3f), (void*)want, (void*)got);
        shown++;
      }
    }
  }
  printf("MEMTEST[%s] range=%p..%p errs=%d zeros=%d off0=%d (of %d)\n",
         tag, (void*)lo, (void*)hi, (int)errs, (int)zeros, (int)off0, (int)n);
  return errs;
}

static void
memtest(void)
{
  // small: 32KB, fits inside the 128KB cache -> no eviction/writeback.
  // if this is clean but big fails, the bug is in eviction (AMC burst).
  mt_pass(MT_LO, MT_LO + 0x8000UL, "small-fits-cache");
  // big: 4MB, 32x the cache -> forces constant eviction + writeback + reload.
  mt_pass(MT_LO, MT_HI, "big-evict");
}

// start() jumps here in supervisor mode on all CPUs.
void
main()
{
  if(cpuid() == 0){
    consoleinit();
    printfinit();
    printf("\n");
    printf("xv6 kernel is booting\n");
    printf("\n");
    memtest();       // DEBUG: cache/AMC integrity before anything else
    kinit();         // physical page allocator
    printf("kinit done\n");
    kvminit();       // create kernel page table
    printf("kvminit done\n");
    kvminithart();   // turn on paging
    printf("kvminithart done\n");
    procinit();      // process table
    printf("procinit done\n");
    trapinit();      // trap vectors
    printf("trapinit done\n");
    trapinithart();  // install kernel trap vector
    printf("trapinithart done\n");
    plicinit();      // set up interrupt controller
    printf("plicinit done\n");
    plicinithart();  // ask PLIC for device interrupts
    printf("plicinithart done\n");
    binit();         // buffer cache
    printf("binit done\n");
    iinit();         // inode cache
    printf("iinit done\n");
    fileinit();      // file table
    printf("fileinit done\n");
    blkdev_init(); // emulated hard disk
    printf("blkdev_init done\n");
    userinit();      // first user process
    printf("userinit done\n");
    // __sync_synchronize();
    started = 1;
  } else {
    while(started == 0)
      ;
    // __sync_synchronize();
    printf("hart %d starting\n", cpuid());
    kvminithart();    // turn on paging
    trapinithart();   // install kernel trap vector
    plicinithart();   // ask PLIC for device interrupts
  }

  scheduler();        
}
