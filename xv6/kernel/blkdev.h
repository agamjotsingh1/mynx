// custom blkdev driver header
#define BLKDEV_STATUS   (BLKDEV + 0x00)
#define BLKDEV_SECTOR   (BLKDEV + 0x08)
#define BLKDEV_MEM_ADDR (BLKDEV + 0x10)
#define BLKDEV_CMD      (BLKDEV + 0x18)

#define BLKDEV_CMD_WRITE 2
#define BLKDEV_CMD_READ  1

