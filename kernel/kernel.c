#include "i386.h"
#include "kernel.h"
#include "spinlock.h"

extern unsigned _kernelstart;


/* Declare space for a stack */
unsigned ul_stack[NR_MODS][1024] __attribute__ ((aligned (4096))); 

/* Declare space for a task state segment */
unsigned ul_tss[NR_MODS][1024] __attribute__ ((aligned (4096))); 

/* Declare space for a page directory */
unsigned pg_dir[NR_MODS][1024] __attribute__ ((aligned (4096)));

/* Declare space for a page table */
unsigned pg_table[NR_MODS][1024] __attribute__ ((aligned (4096)));

/* Declare space for per process kernel stack */
unsigned kl_stack[NR_MODS][1024] __attribute__ ((aligned (4096)));

/* Declare space for a page table mappings for kernel stacks */
unsigned kls_pg_table[NR_MODS][1024] __attribute__ ((aligned (4096)));

/* Declare space for a dummy TSS -- used for kernel switch_to/jmp_gate
   semantics */
tss dummyTSS;

/* This is a global index into the GDT for a dummyTSS */
unsigned short dummyTSS_selector;

/* Declare space for bitmap (physical) memory usage table.
 * PHYS_INDEX_MAX entries of 32-bit integers each for a 4K page => 
 * 4GB memory limit when PHYS_INDEX_MAX=32768
 */
unsigned mm_table[PHYS_INDEX_MAX] __attribute__ ((aligned (4096)));
unsigned mm_limit;       /* Actual physical page limit */

char *pchVideo = (char *) KERN_SCR;

/* NB: If limit is not a multiple of the system word size then all bits in
   table beyond limit must be set to zero */
int bitmap_find_first_set( unsigned int *table, unsigned int limit ) {
  
  int i;

  for( i = 0; i < ( limit >> 5 ); i++ )
    if( table[i] )
      return ffs( table[i] ) + ( i << 5 );

  return -1;
}


struct spinlock screen_lock = {0};


int _putchar( int ch ) {

    static int x, y;
    
    if( ch == '\n' ) {
	x = 0;
	y++;

	if( y > 24 )
	    y = 0;
	
	return (int) (unsigned char) ch;
    }

    pchVideo[ y * 160 + x * 2 ] = ch;
    pchVideo[ y * 160 + x * 2 + 1 ] = 7;
    x++;

    return (int) (unsigned char) ch;
}

int putchar( int ch ) {
  int x;
  spinlock_lock(&screen_lock);
  x = _putchar (ch);
  spinlock_unlock(&screen_lock);
  return x;
}

int print( char *pch ) {
    spinlock_lock(&screen_lock);
    while( *pch )
	_putchar( *pch++ );
    spinlock_unlock(&screen_lock);
    return 0;
}


void putx( unsigned long l ) {

    int i, li;

    spinlock_lock(&screen_lock);
    for( i = 7; i >= 0; i-- )
	if( ( li = ( l >> ( i << 2 ) ) & 0x0F ) > 9 )
	    _putchar( 'A' + li - 0x0A );
	else
	    _putchar( '0' + li );
    spinlock_unlock(&screen_lock);
}

/* Find free page in mm_table 
 *
 * Returns physical address rather than virtual, since we
 * we don't want user-level pages mapped into kernel page tables in all cases
 */
unsigned AllocatePhysicalPage( void ) {

  int i;
  
  for( i = 0; i < mm_limit; i++ )
    if( BITMAP_TST( mm_table, i) ) { /* Free page */
      BITMAP_CLR( mm_table, i );
      return ( i << 12 );	/* physical byte address of free page/frame */
    }

  return -1;			/* Error -- no free page? */
}


/* Find free virtual page and map it to a corresponding physical frame 
 *
 * Returns virtual address
 *
 */
void *MapVirtualPage( unsigned phys_frame ) {

  unsigned *page_table = (unsigned *) KERN_PGT;
  int i;
  void *va;

  for( i = 0; i < 0x400; i++ )
    if( !page_table[ i ] ) {	/* Free page */
      page_table[ i ] = phys_frame;

      va = (char *)&_kernelstart + (i << 12);

      /* Invalidate page in case it was cached in the TLB */
      invalidate_page( va ); 

      return va;
    }

  return NULL;			/* Invalid address */
}


/* 
 * Release previously mapped virtual page 
 */
void UnmapVirtualPage( void *virt_addr ) {

    unsigned *page_table = (unsigned *) KERN_PGT;

    page_table[ ((unsigned)virt_addr >> 12) & 0x3FF ] = 0;

    /* Invalidate page in case it was cached in the TLB */
    invalidate_page( virt_addr ); 
}

void *get_phys_addr( void *virt_addr ) {

  void *pa;
  unsigned phys_frame;
  unsigned va = (unsigned)virt_addr;

  unsigned *kernel_pdbr = (unsigned *)get_pdbr(); /* --WARN-- Assumes
						   * virtual and phys addrs
						   * are the same. Okay to
						   * use at boot time up
						   * until we activate the
						   * first dynamically
						   * created address space
						   */
  unsigned *kernel_ptbr;

  kernel_ptbr = (unsigned *)( kernel_pdbr[va >> 22] & 0xFFFFF000 );

  phys_frame = kernel_ptbr[(va >> 12) & 0x3FF] & 0xFFFFF000;
  
  pa = (void *)( phys_frame + ( va & 0x00000FFF ));

  return pa;
}


__attribute__((noreturn)) void panic( char *sz ) {

    print( "kernel panic: " );
    print( sz );

    cli();
    hlt();
}



extern quest_tss *LookupTSS( unsigned short selector ) {

    descriptor *ad = (descriptor *) KERN_GDT;
    
    return (quest_tss *) ( ad[ selector >> 3 ].pBase0 |
			   ( ad[ selector >> 3 ].pBase1 << 16 ) |
			   ( ad[ selector >> 3 ].pBase2 << 24 ));    
}