#include <stdio.h>
#include "lifo_buffer.h"

int main(void)
{
    lifo_buffer_t bufferTest;
    create_buffer(&bufferTest, 5u);
    printf("Buffer size: %d\n", bufferTest.size);
    add_to_buffer(&bufferTest, 'c');
    add_to_buffer(&bufferTest, 'a');
    add_to_buffer(&bufferTest, 's');
    add_to_buffer(&bufferTest, 'a');
    add_to_buffer(&bufferTest, 'l');
    add_to_buffer(&bufferTest, 'm');
    add_to_buffer(&bufferTest, 'e');
    print_buffer(&bufferTest);
    printf("%c\n", remove_from_buffer(&bufferTest));
    printf("%c\n", remove_from_buffer(&bufferTest));
    printf("%c\n", remove_from_buffer(&bufferTest));
    print_buffer(&bufferTest);
    destroy_buffer(&bufferTest);
    return 0;
}