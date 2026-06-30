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

// Designated memory locations for status and cache eviction
#define STATUS_ADDR  0x80060000
#define EVICT_ADDR   0x80080000 // STATUS_ADDR + (1 << 17)

void __attribute__((naked)) trap_handler() {
    __asm__ volatile (
        "csrr t0, mcause \n"
        "li t1, 15 \n"               // 15 = Store/AMO Page Fault
        
        // Load target memory addresses
        "li t2, %0 \n"               // t2 = STATUS_ADDR
        "li t3, %1 \n"               // t3 = EVICT_ADDR
        
        "bne t0, t1, test_fail \n"

        "test_pass: \n"
        "li t4, 0xBABE \n"
        "sd t4, 0(t2) \n"            // Store 0xBABE to known memory location
        "sd zero, 0(t3) \n"          // Evict by writing garbage (zero) to different tag
        "1: j 1b \n"

        "test_fail: \n"
        "li t4, 0xDEAD \n"
        "sd t4, 0(t2) \n"            // Store 0xDEAD to known memory location
        "sd zero, 0(t3) \n"          // Evict by writing garbage (zero) to different tag
        "2: j 2b \n"
        : 
        : "i"(STATUS_ADDR), "i"(EVICT_ADDR)
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

    volatile uint64_t *dummy = (volatile uint64_t *)0x81000000;
    for (int i = 0; i < (128 * 1024) / 8; i++) {
        (void)dummy[i];
    }

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
