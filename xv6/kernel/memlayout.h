// Physical memory layout

// 10000000 -- uart0 
// 20000000 -- blkdev (disk)
// 30000000 -- PLIC
// 40000000 -- CLINT
// 80000000 -- kernel is loaded here
// unused RAM after 80000000.

// the kernel uses physical memory thus:
// 80000000 -- entry.S, then kernel text and data
// end -- start of kernel page allocation area
// PHYSTOP -- end RAM used by the kernel

// qemu puts UART registers here in physical memory.
#define UART0 0x10000000L
#define UART0_IRQ 1

// blkdev mmio interface
#define BLKDEV 0x20000000L
#define BLKDEV_IRQ 2

// local interrupt controller, which contains the timer.
#define CLINT          0x40000000L
#define CLINT_MTIME    (CLINT + 0x00)
#define CLINT_MTIMECMP (CLINT + 0x08)

// qemu puts programmable interrupt controller here.
#define PLIC_IRQ 0x30000000L
#define PLIC_IRQ_NONE   0x0L
#define PLIC_IRQ_UART   0x1L
#define PLIC_IRQ_BLKDEV 0x2L

// the kernel expects there to be RAM
// for use by the kernel and user pages
// from physical address 0x80000000 to PHYSTOP.
#define KERNBASE 0x80000000L
#define PHYSTOP (KERNBASE + 8*1024*1024)

// map the trampoline page to the highest address,
// in both user and kernel space.
#define TRAMPOLINE (MAXVA - PGSIZE)

// map kernel stacks beneath the trampoline,
// each surrounded by invalid guard pages.
#define KSTACK(p) (TRAMPOLINE - ((p)+1)* 2*PGSIZE)

// User memory layout.
// Address zero first:
//   text
//   original data and bss
//   fixed-size stack
//   expandable heap
//   ...
//   TRAPFRAME (p->trapframe, used by the trampoline)
//   TRAMPOLINE (the same page as in the kernel)
#define TRAPFRAME (TRAMPOLINE - PGSIZE)
