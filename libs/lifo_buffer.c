#include "lifo_buffer.h"
#include "stdlib.h"
#include "stdio.h"

void create_buffer(lifo_buffer_t* buffer, uint32_t length);
void add_to_buffer(lifo_buffer_t* buffer, uint8_t element);
uint8_t remove_from_buffer(lifo_buffer_t* buffer);
void print_buffer(lifo_buffer_t* buffer);
lifo_flags_e check_status(lifo_buffer_t* buffer);

//create buffer
void create_buffer(lifo_buffer_t* buffer, uint32_t length)
{
    buffer->size = length;
    buffer->flag = LIFO_FLAGS_NULL;
    if(length > 0 && buffer != NULL)
    {
        buffer->base = (uint8_t*)malloc(sizeof(uint8_t)*length);
        buffer->flag = (buffer->base) ? LIFO_FLAGS_EMPTY : LIFO_FLAGS_NULL;
    }
    buffer->head = buffer->base;
}

//add element to buffer
void add_to_buffer(lifo_buffer_t* buffer, uint8_t element)
{
    if( buffer != NULL && (buffer->base == NULL || buffer->head == NULL))
    {
        buffer->flag = LIFO_FLAGS_NULL;
    }
    else if(buffer != NULL)
    {
        if(buffer->flag == LIFO_FLAGS_EMPTY)
        {
            *buffer->head = element;
            buffer->flag = LIFO_FLAGS_NOT_EMPTY;
        }
        else
        {
            buffer->head += (buffer->flag == LIFO_FLAGS_FULL) ? 0u : 1u;            
            *buffer->head = element;
            if(buffer->head == (buffer->base + buffer->size - 1))
            {
                buffer->flag = LIFO_FLAGS_FULL;
            }
        }
    }
}

//remove/read from buffer
uint8_t remove_from_buffer(lifo_buffer_t* buffer)
{
    uint8_t out = 0;
    if(buffer != NULL && ( buffer->flag == LIFO_FLAGS_NOT_EMPTY || buffer->flag == LIFO_FLAGS_FULL ))
    {
        out = *buffer->head;
        if(buffer->head == buffer->base)
        {
            buffer->flag = LIFO_FLAGS_EMPTY;
        }
        else
        {
            buffer->head--;
        }       
    }
    return out;
}

//print buffer
void print_buffer(lifo_buffer_t* buffer)
{
    uint8_t* copyPointer = buffer->base;
    printf(" Buffer content: ");
    while(copyPointer < buffer->head)
    {
        printf("%c, ", *copyPointer);
        copyPointer++;
    }
    printf("%c\n", *copyPointer);
}

//check status
lifo_flags_e check_status(lifo_buffer_t* buffer)
{
    return buffer->flag;
}

void destroy_buffer(lifo_buffer_t* buffer)
{
    return free(buffer->base);
}


