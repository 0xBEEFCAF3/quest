#include <atag/atag.h>
#include <util/kerio.h>
#include <raspi/mailbox.h>
#include <drivers/uart/uart.h>

uint32_t get_mem_size(atag_t *tag) {
    uart_puts("In get_mem_size\r\n");
    // atag_t *ttag = memcpy(&ttag, &tag, tag->tag_size);
    while (tag->tag != NONE) {
    	uart_puts("in while\r\n");
    	if (tag->tag == MEM) {
    		uart_puts("Return tag->mem.size\r\n");
    		return tag->mem.size;
    	}
       // Won't work on a VM. 
       tag = (atag_t *)(((uint32_t *)tag) + tag->tag_size);
       //ttag = ((uint32_t *)ttag) + ttag->tag_size;
   }
   uart_puts("Return DBG_MEM_SIZE\r\n");
   return 0;
}

