#ifndef DSTDIO_H
#define DSTDIO_H

extern char getc(void);
extern void putc(char c);

extern void puts(const char * s);

// This version of gets copies until newline, replacing newline with null char, or until buflen.
// whichever comes first
extern void gets(char * buf, int buflen);

extern void printf(const char * fmt, ...);

#endif