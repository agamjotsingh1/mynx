typedef unsigned long uint64_t;
typedef signed long int64_t;

// 64-bit Software Multiplication
uint64_t __muldi3(uint64_t a, uint64_t b) {
    uint64_t res = 0;
    while (b > 0) {
        if (b & 1) res += a;
        a <<= 1;
        b >>= 1;
    }
    return res;
}

// 64-bit Unsigned Division
uint64_t __udivdi3(uint64_t n, uint64_t d) {
    if (d == 0) return -1ULL; // Divide by zero trap could go here
    uint64_t q = 0, r = 0;
    for (int i = 63; i >= 0; i--) {
        r <<= 1;
        r |= (n >> i) & 1;
        if (r >= d) {
            r -= d;
            q |= (1ULL << i);
        }
    }
    return q;
}

// 64-bit Unsigned Modulo
uint64_t __umoddi3(uint64_t n, uint64_t d) {
    if (d == 0) return n;
    uint64_t r = 0;
    for (int i = 63; i >= 0; i--) {
        r <<= 1;
        r |= (n >> i) & 1;
        if (r >= d) {
            r -= d;
        }
    }
    return r;
}

// 64-bit Signed Division
int64_t __divdi3(int64_t n, int64_t d) {
    int sign = 1;
    if (n < 0) { n = -n; sign = -sign; }
    if (d < 0) { d = -d; sign = -sign; }
    int64_t q = __udivdi3(n, d);
    return sign > 0 ? q : -q;
}

// 64-bit Signed Modulo
int64_t __moddi3(int64_t n, int64_t d) {
    int sign = 1;
    if (n < 0) { n = -n; sign = -sign; }
    if (d < 0) { d = -d; }
    int64_t r = __umoddi3(n, d);
    return sign > 0 ? r : -r;
}