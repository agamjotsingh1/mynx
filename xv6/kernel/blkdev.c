#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "buf.h"
#include "defs.h"
#include "blkdev.h"

struct {
  struct spinlock blkdev_lock;
  struct buf *b; // Active buffer
} disk;

void blkdev_init(void) {
  initlock(&disk.blkdev_lock, "blkdev");
}

void blkdev_rw(struct buf *b, int write) {
  acquire(&disk.blkdev_lock);
  disk.b = b;
  b->disk = 1;

  // wait for blkdev to be IDLE
  while(*(uint64*)BLKDEV_STATUS != 0)
    ;

  *(uint64*)BLKDEV_SECTOR = b->blockno;
  *(uint64*)BLKDEV_MEM_ADDR = (uint64)b->data;
  *(uint64*)BLKDEV_CMD = write ? BLKDEV_CMD_WRITE : BLKDEV_CMD_READ; 

  // sleep the process until the blkdev IRQ raises
  while(b->disk == 1) {
    sleep(b, &disk.blkdev_lock);
  }

  disk.b = 0;
  release(&disk.blkdev_lock);
}

void blkdev_intr(void) {
  acquire(&disk.blkdev_lock);
  
  // must read STATUS to clear the hardware IRQ flag
  volatile uint64 status __attribute__((unused)) = *(uint64*)BLKDEV_STATUS;
  
  if(disk.b && disk.b->disk == 1) {
    disk.b->disk = 0;   // mark complete
    wakeup(disk.b);     // wake the sleeping process
  }
  
  release(&disk.blkdev_lock);
}
