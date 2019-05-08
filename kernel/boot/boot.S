// AArch32 mode
 
// To keep this in the first portion of the binary.
/*
 * These are notes to the linker. The first is about where this code belongs in the compiled binary.
 * In a little bit, we are going to specify where that is. 
 * The second specifies that _start is a name that should be visible from outside of the assembly file.
 */
.section ".text.boot"
 
// Make _start global.
.globl _start
 
        .org 0x8000
// Entry point for the kernel.
// r15 -> should begin execution at 0x8000.
// r0 -> 0x00000000
// r1 -> 0x00000C42
// r2 -> 0x00000100 - start of ATAGS `
// preserve these registers as argument for kernel_main
_start:
    // Shut off extra cores
    mrc p15, 0, r5, c0, c0, 5
    and r5, r5, #3
    cmp r5, #0
    bne halt

    // ACT LED On
    /*ldr r0,=0x3f200000
    mov r1,#1
    lsl r1,#21
    str r1,[r0,#16]
    mov r1,#1
    lsl r1,#15
    str r1,[r0,#32]*/
    // LED stuff ends here

 
    // Setup the stack.
    ldr r5, =_start
    mov sp, r5
 
    // Clear out bss.
    /* 
     * This loads the addresses of the start and end of the BSS section into registers.
     * BSS is where C global variables that are not initialized at compile time are stored.
     * The C runtime requires that uninitialized global variables are zero, so we must zero out
     * this entire section ourselves. The symbols __bss_start and __bss_end are going to be defined
     * later in when we work with the linker, so don’t worry about where they come from for now.
     */
    ldr r4, =__bss_start
    ldr r9, =__bss_end
    mov r5, #0
    mov r6, #0
    mov r7, #0
    mov r8, #0
    b       2f
    /*
     * This code is what zeros out the BSS section. 
     * First it loads 0 into four consecutive registers.
     * Then it checks whether the address stored in r4 is less than the one in r9.
     * If it is, then it executes stmia r4!, {r5-r8}. The stm instruction stores
     * the second operand into the address contained in the first.
     * The ia suffix on the instruction means increment after, or increment the
     * address in r4 to the address after the last address written by the instruction.
     * The ! means store that address back in r4, as opposed to throwing it out.
     * The {r5-r8} operand means that stm should store the values in the consecutive
     * registers r5,r6,r7,r8 (so 16 bytes) into r4. So overall, the instruction stores
     * 16 bytes of zeros into the address in r4, then increments that address by 16 bytes.
     * This loops until r4 is greater than or equal to r9, and the whole BSS section is zeroed out.
     */
 
1:
    // store multiple at r4.
    stmia r4!, {r5-r8}
 
    // If we are still below bss_end, loop.
2:
    cmp r4, r9
    blo 1b
    /*
     * This loads the address of the C function called kernel_main into a register
     * and jumps to that location. When the C function returns,
     * it enters the halt procedure where it loops forever doing nothing.
     */
    // Call kernel_main
    ldr r3, =init
    //blx r3
 
    // halt
halt:
    //wfe
    b halt
