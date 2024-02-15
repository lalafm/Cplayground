#ifndef __LIFOBUFFER_H__
#define __LIFOBUFFER_H__

#include <stdint.h>

typedef enum{
    LIFO_FLAGS_NONE = 0,
    LIFO_FLAGS_NOT_EMPTY,
    LIFO_FLAGS_FULL,
    LIFO_FLAGS_EMPTY,
    LIFO_FLAGS_NULL
}lifo_flags_e;

typedef struct{
    uint8_t* buffer;
    uint8_t* head;
    uint8_t* base;
    uint32_t size;
    lifo_flags_e flag;
}lifo_buffer_t;

// Functions
void create_buffer(lifo_buffer_t* buffer, uint32_t length);
void destroy_buffer(lifo_buffer_t* buffer);
void add_to_buffer(lifo_buffer_t* buffer, uint8_t element);
uint8_t remove_from_buffer(lifo_buffer_t* buffer);
void print_buffer(lifo_buffer_t* buffer);
lifo_flags_e check_status(lifo_buffer_t* buffer);

#endif
