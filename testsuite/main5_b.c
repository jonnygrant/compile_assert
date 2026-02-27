// gcc -O2 -Wall -o main5 main5.c

// demonstrate compile_assert checking array indirection indices into an array are within bounds

#include "compile_assert.h"
#include <stdio.h>

int main()
{
    const size_t buf_size = 5;
    size_t index[buf_size];
    index[0] = 20; // fires because these should be under '5';
    index[1] = 20;
    index[2] = 20;
    index[3] = 20;
    index[4] = 20;

    char second[buf_size];

    second[0] = 'a';

    for(size_t i = 0; i != buf_size; ++i)
    {
        if(index[i] >= buf_size) return -2;

        // this will fire because '2' and '2' are out of bounds
        compile_assert(index[i] < buf_size, "check buffer index");

        second[index[i]] = 100;
    }

    printf("%d\n", second[0]);
}
