#ifndef CSR_H
#define CSR_H

#define csrr(csr) ({ \
    unsigned long __v; \
    __asm__ __volatile__ ("csrr %0, " #csr : "=r" (__v)); \
    __v; \
})

#define csrw(csr, val) ({ \
    __asm__ __volatile__ ("csrw " #csr ", %0" :: "rK" (val)); \
})

#define csrs(csr, val) ({ \
    __asm__ __volatile__ ("csrs " #csr ", %0" :: "rK" (val)); \
})

#define csrc(csr, val) ({ \
    __asm__ __volatile__ ("csrc " #csr ", %0" :: "rK" (val)); \
})

#endif