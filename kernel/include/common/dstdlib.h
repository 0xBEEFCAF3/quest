#include <stdint.h>
#include "types.h"
#ifndef DSTDLIB_H
#define DSTDLIB_H

#define MIN(x,y) ((x < y ? x : y))
#define MAX(x,y) ((x < y ? y : x))

typedef struct divmod_result {
    uint32_t div;
    uint32_t mod;
} divmod_t;

divmod_t divmod(uint32_t dividend, uint32_t divisor);
uint32_t div(uint32_t dividend, uint32_t divisor);
void memcpy(void * dest, const void * src, int bytes);
size_t strlen( const char *s );
char *strncpy( char *s1, const char *s2, int length );
int strcmp(const char *s1, const char *s2);
void bzero(void * dest, int bytes);
void memset(void * dest, uint8_t c, int bytes);
char * itoa(int i, int base);
int atoi(char * num);

static inline int
strncmp (const char *a, const char *b, int n)
{
  int i = 0;
  while (*a && *b && n-- > 0) {
    i = *(a++) - *(b++);
    if (i != 0) return i;
  }
  return i;
}

#endif
