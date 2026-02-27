// gcc -O2 -Wall -o main5 main5.c

// demonstrate compile_assert checking array indirection indices into an array are within bounds

#include "compile_assert.h"
#include <stdio.h>

int main()
{
    const size_t buf_size = 2;
    size_t buf[buf_size];
    buf[0] = 2; // fires because these should be '1';
    buf[1] = 2;

    char second[buf_size];
    second[0] = 'a';

    for(size_t i = 0; i != buf_size; ++i)
    {
        compile_assert(buf[i] < buf_size, "check buf index");  // this will fire because '2' and '2' are out of bounds
        second[buf[i]] = 100;
    }

    printf("%d\n", second[0]);
}
