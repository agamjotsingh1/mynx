/* AI GENERATED TESTBENCH */

// Typedefs to replace stdint.h
typedef unsigned long long uint64_t;
typedef unsigned int       uint32_t;
typedef unsigned char      uint8_t;

// SV39 Constants
#define SATP_MODE_SV39 (8ULL << 60)
#define PTE_V (1ULL << 0)
#define PTE_R (1ULL << 1)
#define PTE_W (1ULL << 2)
#define PTE_X (1ULL << 3)
#define PTE_U (1ULL << 4)
#define PTE_A (1ULL << 6)
#define PTE_D (1ULL << 7)

#define PA2PTE(pa) ((((uint64_t)(pa) >> 12) << 10))

void __attribute__((naked)) trap_handler() {
    __asm__ volatile (
        "csrr t0, mcause \n"
        "li t1, 15 \n"         // 15 = Store/AMO Page Fault
        "bne t0, t1, test_fail \n"

        "test_pass: \n"
        "li x31, 0xBABE \n"
        "1: j 1b \n"

        "test_fail: \n"
        "li x31, 0xDEAD \n"
        "2: j 2b \n"
    );
}

void __attribute__((naked)) user_payload() {
    __asm__ volatile (
        ".global payload_start \n payload_start: \n"
        "li t0, 0x2000 \n"     // VA 0x2000
        "ld t1, 0(t0) \n"      // Should succeed
        "li t2, 0xCAFE \n"
        "sd t2, 0(t0) \n"      // Should fault
        ".global payload_end \n payload_end: \n"
    );
}

extern char payload_start[];
extern char payload_end[];

void main() {
    __asm__ volatile ("csrw mtvec, %0" : : "r"(trap_handler));

    // Page Tables in physical memory
    uint64_t *root = (uint64_t *)0x80010000;
    uint64_t *l1   = (uint64_t *)0x80020000;
    uint64_t *l0   = (uint64_t *)0x80030000;

    // Build tree
    root[0] = PA2PTE(l1) | PTE_V;
    l1[0]   = PA2PTE(l0) | PTE_V;
    
    // Map VA 0x1000 and 0x2000
    l0[1] = PA2PTE(0x80040000) | PTE_V | PTE_R | PTE_W | PTE_X | PTE_U | PTE_A | PTE_D;
    l0[2] = PA2PTE(0x80050000) | PTE_V | PTE_R | PTE_U | PTE_A | PTE_D;

    // Load data/code
    *(uint64_t*)0x80050000 = 0xDEADBEEFCAFEBABE;
    char *dest = (char *)0x80040000;
    for(int i=0; i < (payload_end - payload_start); i++) dest[i] = payload_start[i];

    // Enable MMU and MRET
    uint64_t satp = SATP_MODE_SV39 | ((uint64_t)root >> 12);
    __asm__ volatile (
        "csrw satp, %0 \n"
        // "sfence.vma \n"
        "li t0, 0x1800 \n"
        "csrc mstatus, t0 \n"
        "li t0, 0x1000 \n"
        "csrw mepc, t0 \n"
        "mret \n"
        : : "r"(satp) : "t0"
    );
}