#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "buf.h"
#include "defs.h"

#define BLKDEV_STATUS   (VIRTIO0 + 0x00)
#define BLKDEV_SECTOR   (VIRTIO0 + 0x08)
#define BLKDEV_MEM_ADDR (VIRTIO0 + 0x10)
#define BLKDEV_CMD      (VIRTIO0 + 0x18)

struct {
  struct spinlock vdisk_lock;
  struct buf *b; // Active buffer
} disk;

void virtio_disk_init(void) {
  initlock(&disk.vdisk_lock, "virtio_disk");
}

void virtio_disk_rw(struct buf *b, int write) {
  acquire(&disk.vdisk_lock);
  disk.b = b;
  b->disk = 1;

  // wait for blkdev to be IDLE
  while(*(uint64*)BLKDEV_STATUS != 0)
    ;

  *(uint64*)BLKDEV_SECTOR = b->blockno;
  *(uint64*)BLKDEV_MEM_ADDR = (uint64)b->data;
  *(uint64*)BLKDEV_CMD = write ? 2 : 1; 

  // sleep the process until the blkdev IRQ raises
  while(b->disk == 1) {
    sleep(b, &disk.vdisk_lock);
  }

  disk.b = 0;
  release(&disk.vdisk_lock);
}

void virtio_disk_intr(void) {
  acquire(&disk.vdisk_lock);
  
  // must read STATUS to clear the hardware IRQ flag
  volatile uint64 status __attribute__((unused)) = *(uint64*)BLKDEV_STATUS;
  
  if(disk.b && disk.b->disk == 1) {
    disk.b->disk = 0;   // Mark complete
    wakeup(disk.b);     // Wake the sleeping process
  }
  
  release(&disk.vdisk_lock);
}
