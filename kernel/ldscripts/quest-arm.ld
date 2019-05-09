ENTRY(_start)
OUTPUT_ARCH(arm)
/*PHDRS {
  physical PT_LOAD FILEHDR PHDRS;
  virtualtext PT_LOAD;
  virtualdata PT_LOAD;
  virtualtext16 PT_LOAD;
}*/
SECTIONS
{
    /* Starts at LOADER_ADDR. */
    . = 0x8000;
    /* For AArch64, use . = 0x80000; */
    __start = .;
    __text_start = .;
    .text :
    {
        /* 
         * Stop linker from optimising the code in .text.boot
         * This isn't strictly speaking necessary.
         */
        KEEP(*(.text.boot))
        *(.text)
    }
    . = ALIGN(4096); /* align to page size */
    __text_end = .;

    /* This sets the symbols __start, and __text_start to be 0x8000. 
    It then declares the .text section to start right after that. 
    The first part of the .text section is .text.boot, where the code from boot.S resides. 
    KEEP signifies that the linker should not try to optimize out the code in .text.boot,
    even though it is not referenced anywhere. The second part of the .text section is
    all .text sections from all other objects, in any order.
    Then declare __text_end to be the next largest address divisible by 4096
    after all of the .text is put in. This rounding to the nearest 4096 is called
    page alignment, and it becomes important when we start working with memory. */
 
    __rodata_start = .;
    .rodata :
    {
        *(.rodata)
    }
    . = ALIGN(4096); /* align to page size */
    __rodata_end = .;
 
    __data_start = .;
    .data :
    {
        *(.data)
    }
    . = ALIGN(4096); /* align to page size */
    __data_end = .;

     /* Insert a read-only null-terminated array of pointers to modules */
     /*# PRAGMA Need up */
  /* Insert a read-only null-terminated array of pointers to constructors */
/*    _percpu_ctor_list = .;
   .ctors : AT ( ( LOADADDR (.rodata) + SIZEOF (.rodata) + 31 ) )
              { *(.percpu.ctor); LONG(0) } : virtualtext*/

  . = ALIGN(4096);
     _module_ptr_list = .;
/*     .moduleptrs : AT ( ( LOADADDR (.ctors) + SIZEOF (.ctors) + 31 ) )
                   { *(.module.ptrs); LONG(0) } : virtualtext*/
 
    __bss_start = .;
    .bss :
    {
        bss = .;
        *(.bss)
    }
    . = ALIGN(4096); /* align to page size */
    __bss_end = .;
    /* Marks the beginning of a region of memory just after the kernel image ends that we will reserve in mem.c
     * to store an array of page metadata.
     */
    __end = .;
}
