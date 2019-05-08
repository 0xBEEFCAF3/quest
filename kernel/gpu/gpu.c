#include <raspi/framebuffer.h>
#include <gpu/gpu.h>
#include <mem/mem.h>
#include <util/kerio.h>
#include <raspi/mailbox.h>
#include <raspi/chars_pixels.h>
#include <common/dstdlib.h>
#include <drivers/uart/uart.h>



void write_pixel(uint32_t x, uint32_t y, const pixel_t * pix) {
    uint8_t * location = fbinfo.buf + y*fbinfo.pitch + x*BYTES_PER_PIXEL;
    memcpy(location, pix, BYTES_PER_PIXEL);
}

void gpu_putc(char c) {
    static const pixel_t WHITE = {0xff, 0xff, 0xff};
    static const pixel_t BLACK = {0x00, 0x00, 0x00};
    uint8_t w,h;
    uint8_t mask;
    const uint8_t * bmp = font(c);
    uint32_t i, num_rows = fbinfo.height/CHAR_HEIGHT;

    // Shift everything up one row
    if (fbinfo.chars_y >= num_rows) {
        // Copy a whole character row into the one above it
        for (i = 0; i < num_rows-1; i++)
            memcpy(fbinfo.buf + fbinfo.pitch*i*CHAR_HEIGHT, fbinfo.buf + fbinfo.pitch*(i+1)*CHAR_HEIGHT, fbinfo.pitch * CHAR_HEIGHT);
        // Zero out the last row
        bzero(fbinfo.buf + fbinfo.pitch*i*CHAR_HEIGHT,fbinfo.pitch * CHAR_HEIGHT);
        fbinfo.chars_y--;
    }

    if (c == '\n') {
        fbinfo.chars_x = 0;
        fbinfo.chars_y++;
        return;
    }

    for(w = 0; w < CHAR_WIDTH; w++) {
        for(h = 0; h < CHAR_HEIGHT; h++) {
            mask = 1 << (w);
            if (bmp[h] & mask)
                write_pixel(fbinfo.chars_x*CHAR_WIDTH + w, fbinfo.chars_y*CHAR_HEIGHT + h, &WHITE);
            else
                write_pixel(fbinfo.chars_x*CHAR_WIDTH + w, fbinfo.chars_y*CHAR_HEIGHT + h, &BLACK);
        }
    }

    fbinfo.chars_x++;
    if (fbinfo.chars_x > fbinfo.chars_width) {
        fbinfo.chars_x = 0;
        fbinfo.chars_y++;
    }
}

void gpu_init(void) {
    static const pixel_t BLACK = {0x00, 0x00, 0x00};
    // Apparently, this sometimes does not work, so try in a loop.
    while(framebuffer_init() != 0);
    uart_puts("In gpu init\n");
    // Clear screen
    uint32_t j = 0;
    for (j = 0; j < fbinfo.height; j++) {
        uint32_t i = 0;
        for (i = 0; i < fbinfo.width; i++) {
            write_pixel(i,j,&BLACK);
        }
    }
    uart_puts("Exit gpu_init\r\n");
}