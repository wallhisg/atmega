#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <c_def.h>

#define LF      0x0A    //  '\n'
#define CR      0x0D    //  '\r'


typedef enum {
    RING_STATUS_EMPTY = 0,
    RING_STATUS_DATA_PRESENT = 1,
    RING_STATUS_FULL = 2
} ring_buffer_status_e;

typedef struct {
    uint8_t* head;
    uint8_t* tail;
    uint8_t* buffer;
    uint8_t  size;
    ring_buffer_status_e status;
} ring_buffer_t;

typedef ring_buffer_t* buffer_ptr;


buffer_ptr ringbuf_create(void);
void ringbuf_reset(buffer_ptr buff);

void ringbuf_write_one_byte(buffer_ptr buff, const uint8_t byte);
uint16_t ringbuf_write_bytes(buffer_ptr buff, uint8_t* bytes);
const uint8_t ringbuf_read_one_byte (buffer_ptr buff);
uint8_t ringbuf_read_bytes(uint8_t* result,  buffer_ptr buff);

const uint8_t ringbuf_bytes_used (const buffer_ptr buff);
const ring_buffer_status_e ringbuf_status();

#endif  //  _RING_BUFFER_H_
