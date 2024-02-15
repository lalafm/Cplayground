#ifndef __FIFOBUFFER_H__
#define __FIFOBUFFER_H__

#include <stdint.h>
#include <stdbool.h>

typedef enum{
    FIFO_FLAGS_NONE = 0,
    FIFO_FLAGS_NOT_EMPTY,
    FIFO_FLAGS_FULL,
    FIFO_FLAGS_EMPTY,
    FIFO_FLAGS_NULL
}fifo_flags_e;

typedef struct{
    uint8_t* buffer;
    uint8_t* head;
    uint8_t* tail;
    uint8_t* base;
    uint32_t size; //in bytes
    fifo_flags_e flag;
}fifo_buffer_t;

// Functions
bool create_fifo_buffer(fifo_buffer_t* buffer, uint32_t length);
void destroy_fifo_buffer(fifo_buffer_t* buffer);
void add_to_fifo_buffer(fifo_buffer_t* buffer, uint8_t element);
uint8_t remove_from_fifo_buffer(fifo_buffer_t* buffer);
void print_fifo_buffer(fifo_buffer_t* buffer);
fifo_flags_e check_fifo_status(fifo_buffer_t* buffer);

#endif
