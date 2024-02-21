#include "lifo_buffer.h"
#include "stdlib.h"
#include "stdio.h"

//create buffer
void create_lifo_buffer(lifo_buffer_t* buffer, uint32_t length)
{
    if(buffer != NULL)
    {
        buffer->size = length;
        buffer->flag = LIFO_FLAGS_NULL;
        buffer->base = NULL;
        if(length > 0)
        {
            buffer->base = (uint8_t*)malloc(sizeof(uint8_t)*length);
            buffer->flag = (buffer->base) ? LIFO_FLAGS_EMPTY : LIFO_FLAGS_NULL;          
        }
        buffer->head = buffer->base;
    }  
}

//add element to buffer
void add_to_lifo_buffer(lifo_buffer_t* buffer, uint8_t element)
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
uint8_t remove_from_lifo_buffer(lifo_buffer_t* buffer)
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
void print_lifo_buffer(lifo_buffer_t* buffer)
{
    if(buffer != NULL && buffer->base != NULL)
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
    else
    {
        printf("Buffer does not exist!\n");
    }
}

lifo_flags_e check_lifo_status(lifo_buffer_t* buffer)
{
    lifo_flags_e flag = LIFO_FLAGS_NONE;
    if(buffer != NULL )
    {
        flag = buffer->flag;
    }
    return flag;
}

void destroy_lifo_buffer(lifo_buffer_t* buffer)
{
    free(buffer->base);
    buffer->base = NULL;
    buffer->head = NULL;
    buffer->flag = LIFO_FLAGS_NULL;
    buffer->size = 0u;
}


