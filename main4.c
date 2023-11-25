// gcc -O2 -Wall -o main4 main4.c

// demonstrate compile_assert checking all indices into an array are within bounds

#include "compile_assert.h"
#include <stdio.h>

int main()
{
    const size_t buf_size = 4;
    char buf[buf_size];

    for(size_t i = 0; i != 5; ++i)
    {
        compile_assert(i < buf_size, "check buf index");  // will fire, as out of bounds
        buf[i] = 3;
    }
}
