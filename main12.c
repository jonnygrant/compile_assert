// gcc -D__ENABLE_COMPILE_ASSERT__ -O2 -Wall -o main12 main12.c

#include <string.h>
#include <stdint.h>

// demonstrate compile_assert checking an offset resovled to a
// pointer is within the range bounds of a buffer.
// this use case is common when loading data files from a file
// Any access beyond the buffer size is a read-overflow, could be segv
// in this example, it just tries to print out some decimal values.

#include "compile_assert.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct data
{
    char id[4];
    uint32_t offset;
    char data[0];
} data_t;


void load_data(const data_t * ptr, const size_t buf_size)
{
    const char * data = (char*)ptr + ptr->offset;
    const char * end = (char*)ptr + buf_size;

    __builtin_printf("data %p\n", data);
    __builtin_printf("end  %p\n", end);
    __builtin_printf("assert %d\n", data < end);  // Check space for 1 byte

#if 0
    if(data >= end)
    {
        return;
    }
#endif

    // FIXME unfortunately the this example doesn't appear to be satisfied, compiler
    // can't see that the address is within bounds

    // Check space for 1 byte read
    compile_assert((data < end), "load_data: data offset is beyond the end of the buffer");

    printf("%d\n", data[0]);

    // FIXME do another one, that tests there is space for 12 bytes
}

int main()
{
    const size_t byte_buffer_size = 512;
    data_t * test = malloc(byte_buffer_size);
    test->id[0] = 'A';
    test->id[1] = 'B';
    test->id[2] = 'C';
    test->id[3] = 'D';
    test->offset = 100;  // NOTE test with offset beyond the 512 bytes allocated for this test

    load_data(test, byte_buffer_size);

    return 0;
}
