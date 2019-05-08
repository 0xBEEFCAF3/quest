#include <raspi/framebuffer.h>
#include <gpu/gpu.h>
#include <mem/mem.h>
#include <raspi/mailbox.h>
#include <util/kerio.h>
#include <drivers/uart/uart.h>

int framebuffer_init(void) {

    uart_puts("In framebuffer_init\r\n");

    property_message_tag_t tags[5];

    tags[0].proptag = FB_SET_PHYSICAL_DIMENSIONS;
    tags[0].value_buffer.fb_screen_size.width = 640;
    tags[0].value_buffer.fb_screen_size.height = 480;
    tags[1].proptag = FB_SET_VIRTUAL_DIMENSIONS;
    tags[1].value_buffer.fb_screen_size.width = 640;
    tags[1].value_buffer.fb_screen_size.height = 480;
    tags[2].proptag = FB_SET_BITS_PER_PIXEL;
    tags[2].value_buffer.fb_bits_per_pixel = COLORDEPTH;
    tags[3].proptag = NULL_TAG;

    // Send over the initialization
    if (send_messages(tags) != 0) {
        uart_puts("In framebuffer_init send_messages failed\r\n");
        return -1;
    }

    uart_puts("DBG\r\n");

    fbinfo.width = tags[0].value_buffer.fb_screen_size.width;
    fbinfo.height = tags[0].value_buffer.fb_screen_size.height;
    fbinfo.chars_width = fbinfo.width / CHAR_WIDTH;
    fbinfo.chars_height = fbinfo.height / CHAR_HEIGHT;
    fbinfo.chars_x = 0;
    fbinfo.chars_y = 0;
    fbinfo.pitch = fbinfo.width*BYTES_PER_PIXEL;

    // request a framebuffer
    tags[0].proptag = FB_ALLOCATE_BUFFER;
    tags[0].value_buffer.fb_screen_size.width = 0;
    tags[0].value_buffer.fb_screen_size.height = 0;
    tags[0].value_buffer.fb_allocate_align = 16;
    tags[1].proptag = NULL_TAG;


    if (send_messages(tags) != 0) {
        uart_puts("framebuffer_init: requesting a buffer failed.\r\n");
        return -1;
    }

    fbinfo.buf = tags[0].value_buffer.fb_allocate_res.fb_addr;
    fbinfo.buf_size = tags[0].value_buffer.fb_allocate_res.fb_size;
    uart_puts("framebuffer_init succeeded.\r\n");
    return 0;
}