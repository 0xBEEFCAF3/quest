/**
 * Property Channel Messages:
 * Messages have a fairly complex and poorly documented structure.
 * A message must be a 16 byte aligned buffer of 4 byte words.
 * NB: The response overwrites the original message.
 * A Message starts with a 4 byte size of the message, including the 4 bytes for the size itself.
 * The size is followed by 4 byte a request/response code. 
 * When sending a message, this value must be 0.
 * When receiving a message, this part will either be 0x80000000 for success and 0x80000001 for an error.
 *
 * Following the request/response code comes a concatenated list of tags. 
 * Tags are simultaneously commands and buffers for responses to those commands. 
 * There are many tags, but we will only talk about those directly relevent to us.
 * The very last tag must be an end tag, which is just 4 bytes of 0.
 * Finally, the message must be padded so that the size of the whole buffer is 16 byte aligned.
Below is a map of the message buffer:
 */
/*
       0       4       8      12      16      20      24      28      32
       +---------------------------------------------------------------+
0x00   |                         Buffer Size                           |
       +---------------------------------------------------------------+
0x04   |                   Request/Response Code                       |
       +---------------------------------------------------------------+
0x08   |                             Tags                              |
...    \\                                                             \\
0xXX   |                             Tags                              |
       +---------------------------------------------------------------+
0xXX+4 |                           End Tag (0)                         |
       +---------------------------------------------------------------+
0xXX+8 |                           Padding                             |
...    \\                                                             \\
0xXX+16|                           Padding                             |
       +---------------------------------------------------------------+
*/

#include <stdint.h>
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#define COLORDEPTH 24
#define BYTES_PER_PIXEL COLORDEPTH/8

typedef struct framebuffer_info {
    uint32_t width;
    uint32_t height;
    uint32_t pitch;
    void * buf;
    uint32_t buf_size;
    uint32_t chars_width;
    uint32_t chars_height;
    uint32_t chars_x;
    uint32_t chars_y;
} framebuffer_info_t;

framebuffer_info_t fbinfo;

int framebuffer_init(void);

#endif