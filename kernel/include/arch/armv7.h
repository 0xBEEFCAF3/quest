#ifndef ARMV7_H
#define ARMV7_H

#define F_1 0x02
#define F_IOPL0 0x1000
#define F_IF 0x200              /* interrupt enable */
#define F_IOPL 0x3000           /* I/O privilege level */
#define PIC1_BASE_IRQ 0x20
#define PIC2_BASE_IRQ 0x28
extern uint16 serial_port1;
#include "types.h"
typedef struct _tss
{
  /* 80386 hardware data */
  uint16 usPrevious;            /* previous task selector */
  uint16 usReserved0;
  uint32 ulESP0;                /* ring 0 stack pointer */
  uint16 usSS0;                 /* ring 0 stack selector */
  uint16 usReserved1;
  uint32 ulESP1;                /* ring 1 stack pointer */
  uint16 usSS1;                 /* ring 1 stack selector */
  uint16 usReserved2;
  uint32 ulESP2;                /* ring 2 stack pointer */
  uint16 usSS2;                 /* ring 2 stack selector */
  uint16 usReserved3;
  void *pCR3;                   /* page directory */
  uint32 ulEIP;                 /* instruction pointer */
  uint32 ulEFlags;
  uint32 ulEAX, ulECX, ulEDX, ulEBX, ulESP, ulEBP, ulESI, ulEDI;
  uint16 usES, usReserved4, usCS, usReserved5, usSS, usReserved6,
    usDS, usReserved7, usFS, usReserved8, usGS, usReserved9;
  uint16 usLDT, usReserved10;
  uint32 fTrap:1;
  uint32 uReserved11:15;
  uint16 usIOMap;
} tss;

/* Bit-field definitions for a segment descriptor */
typedef struct _descriptor
{
  uint32 uLimit0:16;      /* limit (bits 0-15) */
  uint32 pBase0:16;       /* base (bits 0-15) */
  uint32 pBase1:8;        /* base (bits 16-23) */
  uint32 uType:5;         /* type */
  uint32 uDPL:2;          /* privilege level */
  uint32 fPresent:1;      /* present */
  uint32 uLimit1:4;       /* limit (bits 16-19) */
  uint32 f:1;             /* available */
  uint32 f0:1;            /* reserved */
  uint32 fX:1;            /* varies (32-bit) */
  uint32 fGranularity:1;  /* granularity */
  uint32 pBase2:8;        /* base (bits 24-31) */
} descriptor;

static inline void *
get_pdbr (void)
{
  int k = 8;
  int *i = &k;
  void *f = (void *)i;
  return f;
}

static inline void
hw_ltr (uint16 us)
{

  return;

}

static inline void
flush_tlb_all ()
{
  return;
  // uint32 tmpreg;

  // asm volatile ("movl %%cr3, %0\n" "movl %0, %%cr3":"=&r" (tmpreg):);

}

// static inline void *
// memcpy (void *pDest, const void *pSrc, uint32 cb)
// {
//   // asm volatile ("cld; rep movsb"
//   //               :"=c" (cb), "=D" (pDest), "=S" (pSrc)
//   //               :"0" (cb), "1" (pDest), "2" (pSrc)
//   //               :"memory","flags");
//   return pDest;
// }
#endif