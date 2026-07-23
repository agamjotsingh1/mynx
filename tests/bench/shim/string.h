#ifndef _BENCH_STRING_H
#define _BENCH_STRING_H
#include <stddef.h>
void *memcpy(void *dst, const void *src, size_t n);
void *memset(void *dst, int c, size_t n);
char *strcpy(char *dst, const char *src);
int strcmp(const char *a, const char *b);
#endif
