ENTRY(_start)
OUTPUT_ARCH(arm)
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
 
    __bss_start = .;
    .bss :
    {
        bss = .;
        *(.bss)
    }
    . = ALIGN(4096); /* align to page size */
    __bss_end = .;
    __end = .;
}
