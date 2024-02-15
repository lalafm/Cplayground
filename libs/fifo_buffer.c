#include "fifo_buffer.h"
#include "stdlib.h"
#include "stdio.h"

bool create_fifo_buffer(fifo_buffer_t* buffer, uint32_t length)
{
    bool success = false;
    if(buffer != NULL)
    {
        buffer->size = length;
        buffer->flag = FIFO_FLAGS_NULL;
        buffer->base = NULL;
        if(length > 0)
        {
            buffer->base = (uint8_t*)malloc(sizeof(uint8_t)*length);
            if(buffer->base != NULL)
            {
                buffer->flag = FIFO_FLAGS_EMPTY;
                success = true;               
            }      
        }
        buffer->head = buffer->base;
        buffer->tail = buffer->head;     
    }
    return success;
}

void destroy_fifo_buffer(fifo_buffer_t* buffer)
{
    free(buffer->base);
    buffer->base = NULL;
    buffer->head = NULL;
    buffer->tail = NULL;
    buffer->flag = FIFO_FLAGS_NULL;
    buffer->size = 0u;
}

void add_to_fifo_buffer(fifo_buffer_t* buffer, uint8_t element)
{
    if(buffer != NULL && buffer->base != NULL)
    {
        // if buffer is full and no element was removed to move the tail, data will be overwritten and tail will point to next oldest byte
        if((buffer->flag == FIFO_FLAGS_FULL) && (buffer->head == buffer->tail))
        {
            buffer->tail++;     
        }
        buffer->flag = FIFO_FLAGS_NOT_EMPTY;
        *buffer->head = element;
        // head should point to next location checking end of buffer (return to base when buffer ends)
        buffer->head = (buffer->head == (buffer->base + buffer->size - 1)) ? buffer->base : (buffer->head + 1);
        // when, after incrementing the head, it reaches the tail, it means buffer is full and next add will be an overwrite
        if(buffer->head == buffer->tail)
        {
            buffer->flag = FIFO_FLAGS_FULL;     
        }
    }
}

uint8_t remove_from_fifo_buffer(fifo_buffer_t* buffer)
{
    // return 0 when buffer is invalid or empty
    uint8_t out = 0;
    if(buffer != NULL && buffer->flag != FIFO_FLAGS_NULL && buffer->flag != FIFO_FLAGS_EMPTY)
    {              
        // otherwise return oldest element from buffer
        out = *buffer->tail;
        // increment the tail, if end of buffer is reached return to base
        buffer->tail = (buffer->tail == (buffer->base + buffer->size - 1)) ? buffer->base : (buffer->tail + 1);
        buffer->flag = FIFO_FLAGS_NOT_EMPTY;
        // if head=tail it means the buffer is now empty
        if(buffer->head == buffer->tail)
        {
            buffer->flag = FIFO_FLAGS_EMPTY;
        }         
    }
    return out;
}

void print_fifo_buffer(fifo_buffer_t* buffer)
{
    if(buffer != NULL && buffer->base != NULL)
    {
        uint8_t* copyPointer = buffer->base;
        printf(" Buffer content: ");
        while(copyPointer < (buffer->base + buffer->size - 1))
        {
            printf("%c, ", *copyPointer);
            copyPointer++;
        }
        printf("%c\n", *copyPointer);        
    }
    else
    {
        printf("Buffer does not exist!\n");
    }
}

fifo_flags_e check_fifo_status(fifo_buffer_t* buffer)
{
    fifo_flags_e flag = FIFO_FLAGS_NONE;
    if(buffer != NULL )
    {
        flag = buffer->flag;
    }
    return flag;
}