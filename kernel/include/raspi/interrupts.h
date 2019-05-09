/*
Address Exception Name  Exception Source    Action to take
0x00    Reset   Hardware Reset  Restart the Kernel
0x04    Undefined instruction   Attempted to execute a meaningless instruction  Kill the offending program
0x08    Software Interrupt (SWI)    Software wants to execute a privileged operation    Perform the opertation and return to the caller
0x0C    Prefetch Abort  Bad memory access of an instruction Kill the offending program
0x10    Data Abort  Bad memory access of data   Kill the offending program
0x14    Reserved    Reserved    Reserved
0x18    Interrupt Request (IRQ) Hardware wants to make the CPU aware of something   Find out which hardware triggered the interrupt and take appropriate action
0x1C    Fast Interrupt Request (FIQ)    One select hardware can do the above faster than all others Find out which hardware triggered the interrupt and take appropriate action
*/
/*
 *
 * The Raspberry Pi has 72 possible IRQs.
 * IRQs 0-63 are shared between the GPU and CPU, and 64-71 are specific to the CPU.
 * The two most important IRQs for our purposes will be the system timer (IRQ number 1) 
 * and the USB controller (IRQ number 9).

Here is the layout of the IRQ peripheral:

       0       4       8      12      16      20      24      28      32
       +---------------------------------------------------------------+
0x00   |                 ARM Specific Pending (64-71)                  |
       +---------------------------------------------------------------+
0x04   |                ARM/GPU Shared Pending 1 (0-31)                |
       +---------------------------------------------------------------+
0x08   |               ARM/GPU Shared Pending 2 (32-63)                |
       +---------------------------------------------------------------+
0x0C   |                       Fast IRQ Control                        |
       +---------------------------------------------------------------+
0x10   |                ARM/GPU Shared Enable 1 (0-31)                 |
       +---------------------------------------------------------------+
0x14   |                ARM/GPU Shared Enable 2 (32-63)                |
       +---------------------------------------------------------------+
0x18   |                 ARM Specific Enable (64-72)                   |
       +---------------------------------------------------------------+
0x1C   |                ARM/GPU Shared Disable 1 (0-31)                |
       +---------------------------------------------------------------+
0x20   |                ARM/GPU Shared Disable 2 (32-63)               |
       +---------------------------------------------------------------+
0x24   |                 ARM Specific Disable (64-72)                  |
       +---------------------------------------------------------------+

NB: (because of-fucking-course -.-)
I.   When you see an interrupt is pending, you should not clear that bit. 
     Each peripheral that can trigger an interrupt has its own mechanism for clearing the pending bit
     that should be done in the handler for that peripheral’s IRQ.

II.  Clearing a bit in an enable regiester is neither sufficient nor necessary to disable an IRQ. 
     An IRQ should only be disabled by setting the correct bit in the disable register.
     See Pete Cockrell's excellent manual on ARM assembly for more information on this.
*/
#include <raspi/peripheral.h>
#include <stdint.h>
#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#define INTERRUPTS_BASE (PERIPHERAL_BASE + INTERRUPTS_OFFSET)
#define INTERRUPTS_PENDING (INTERRUPTS_BASE + 0x200)

#define IRQ_IS_BASIC(x) ((x >= 64 ))
#define IRQ_IS_GPU2(x) ((x >= 32 && x < 64 ))
#define IRQ_IS_GPU1(x) ((x < 32 ))
#define IRQ_IS_PENDING(regs, num) ((IRQ_IS_BASIC(num) && ((1 << (num-64)) & regs->irq_basic_pending)) || (IRQ_IS_GPU2(num) && ((1 << (num-32)) & regs->irq_gpu_pending2)) || (IRQ_IS_GPU1(num) && ((1 << (num)) & regs->irq_gpu_pending1)))
#define NUM_IRQS 72

extern __inline__ int INTERRUPTS_ENABLED(void);

extern __inline__ void ENABLE_INTERRUPTS(void);

extern __inline__ void DISABLE_INTERRUPTS(void);

typedef void (*interrupt_handler_f)(void);
typedef void (*interrupt_clearer_f)(void);


typedef enum {
    SYSTEM_TIMER_1 = 1,
    USB_CONTROLER = 9,
    ARM_TIMER = 64
} irq_number_t;

typedef struct {
    uint32_t irq_basic_pending;
    uint32_t irq_gpu_pending1;
    uint32_t irq_gpu_pending2;
    uint32_t fiq_control;
    uint32_t irq_gpu_enable1;
    uint32_t irq_gpu_enable2;
    uint32_t irq_basic_enable;
    uint32_t irq_gpu_disable1;
    uint32_t irq_gpu_disable2;
    uint32_t irq_basic_disable;
} interrupt_registers_t;

void interrupts_init(void);

void register_irq_handler(irq_number_t irq_num, interrupt_handler_f handler, interrupt_clearer_f clearer);
void unregister_irq_handler(irq_number_t irq_num);


#endif