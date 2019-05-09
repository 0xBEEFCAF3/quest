#include <stddef.h>
#include <stdint.h>
#include <drivers/uart/uart.h>
#include <mem/mem.h>
#include <atag/atag.h>
#include <util/kerio.h>
#include <gpu/gpu.h>
#include <raspi/interrupts.h>
#include <raspi/timer.h>
#include <raspi/process.h>
#include <common/dstdlib.h>
#include <raspi/mailbox.h>
#include "types.h"
#include "kernel.h"


// void test(void) {
//     int i = 0;
//     while (i < 10) {
//         printf("test %d\n", i++);
//         udelay(1000000);
//     }
// }

void kernel_main(uint32_t r0, uint32_t r1, uint32_t r2)
{
    int i = 0;
    char buf[256];
    // Declare as unused
    (void) r0;
    (void) r1;
    (void) r2;

    uart_init();
    uart_puts("Initializing Memory Module\n");
    mem_init((atag_t *)r2);
    uint32_t mem_size = get_mem_size((atag_t *)r2);
    uart_puts("Now initializing GPU module\r\n");
    gpu_init();
    uart_puts("Now initializing interrupts.\r\n");
    interrupts_init();
    uart_puts("Now initializing timer.\r\n");
    timer_init();
    serial_printf("\nQuestOS: Welcome *** System Memory is: %dMB\r\n", mem_size/(1024*1024));


    property_message_tag_t mtag[1];
    mtag[0].proptag = MB_GET_VC_MEM;
    mtag[0].value_buffer.mb_vc_mem = 6432;

    if(send_messages(mtag) != 0) {
        uart_puts("In kernel send_messages failed for mtag\r\n");
    } else {
        serial_printf("\r\nVideoCore Memory: %dMB\r\n", (mtag[0].value_buffer.mb_vc_mem) / (1000*1000));
    }

    property_message_tag_t tag[1];

    tag[0].proptag = MB_GET_BOARD_REV;
    // Init with some garbage value we know to be false as a litmus test.
    tag[0].value_buffer.mb_board_rev = 6140;
    // Send over the initialization
    if (send_messages(tag) != 0) {
        uart_puts("Failed get_revision_id\r\n");
    } 
    uint32_t bid = 6140;
    bid = tag[0].value_buffer.mb_board_rev;
    printf("\r\nBoard Revision ID: %x\r\n", bid);

    uart_puts("Now setting timer.\r\n");
    uart_puts("INITIALIZING SCHEDULER...");
    //process_init();
    uart_puts("DONE\n");

    uart_puts("Hello, kernel World!\n");

    //create_kernel_thread(test, "TEST", 4);

    while (1) {
        // gets(buf,256);
        // puts(buf);
        // putc('\n');
        serial_printf("main %d\r\n", i++);
        udelay(10000000);
    }
}