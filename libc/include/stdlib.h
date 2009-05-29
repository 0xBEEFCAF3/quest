
#ifndef _SIZE_T
typedef int size_t;
#define _SIZE_T 1
#endif

extern void *calloc( size_t nmemb, size_t size );
extern void *malloc( size_t size );
extern void free( void *ptr );
extern void *realloc( void *ptr, size_t size );

extern int atoi(const char *nptr);

extern int rand( void );
extern __attribute__((noreturn)) void exit( int status );