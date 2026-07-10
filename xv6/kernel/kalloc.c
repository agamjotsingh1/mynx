// Physical memory allocator, for user processes,
// kernel stacks, page-table pages,
// and pipe buffers. Allocates whole 4096-byte pages.

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "riscv.h"
#include "defs.h"

void freerange(void *pa_start, void *pa_end);

extern char end[]; // first address after kernel.
                   // defined by kernel.ld.

struct run {
  struct run *next;
};

struct {
  struct spinlock lock;
  struct run *freelist;
} kmem;

void
kinit()
{
  /* printf("inside kinit\n"); */
  initlock(&kmem.lock, "kmem");
  /* printf("locked kmem lock\n"); */
  freerange(end, (void*)PHYSTOP);
}

void
freerange(void *pa_start, void *pa_end)
{
  char *p;
  p = (char*)PGROUNDUP((uint64)pa_start);
  /* printf("inside freerange"); */
  for(; p + PGSIZE <= (char*)pa_end; p += PGSIZE) {
    /* if((uint64)p%(128*PGSIZE)==0) printf("freeing %p\n", p); */
    /* printf("freeing %p\n", (uint64) p); */
    kfree(p);
  }
}

// Free the page of physical memory pointed at by v,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
void
kfree(void *pa)
{
  struct run *r;

  if(((uint64)pa % PGSIZE) != 0 || (char*)pa < end || (uint64)pa >= PHYSTOP)
    panic("kfree");

  // Fill with junk to catch dangling refs.
  // too slow for fpga work
  // memset(pa, 1, PGSIZE);

  r = (struct run*)pa;

  acquire(&kmem.lock);
  r->next = kmem.freelist;
  kmem.freelist = r;
  release(&kmem.lock);
}

// DEBUG: count reachable freelist pages (bounded so a cyclic/corrupt
// chain can't hang). also returns head via *head.
int
kmem_count(uint64 *head)
{
  int n = 0;
  struct run *r;
  acquire(&kmem.lock);
  if(head) *head = (uint64)kmem.freelist;
  for(r = kmem.freelist; r && n < 200000; r = r->next) n++;
  release(&kmem.lock);
  return n;
}

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
void *
kalloc(void)
{
  struct run *r;

  acquire(&kmem.lock);
  r = kmem.freelist;
  if(r)
    kmem.freelist = r->next;
  release(&kmem.lock);

  // too slow for fpga work
  /* if(r) */
  /*   memset((char*)r, 5, PGSIZE); // fill with junk */
  return (void*)r;
}
