// gcc -D__ENABLE_COMPILE_ASSERT__ -O2 -Wall -o main10 main10.c

// demonstrate compile_assert checking array ranges, based on values computed at runtime

#include "compile_assert.h"
#include <stddef.h>
#include <stdlib.h>

#define buf_capacity 10
#define buf_count_capacity 99  // TODO change this to 100 to FIX

int main()
{
    int buf[buf_capacity];
    int buf_count[buf_count_capacity] = {0};

    // fill with random values between 0 and 99 (100 different values)
    for(size_t i = 0; i != buf_capacity; ++i)
    {
        const int r = rand();
        buf[i] = (r%100);

        compile_assert(buf[i] < buf_count_capacity, "check array bounds");
        // increment the count of each
        buf_count[buf[i]]++;
    }

    return 0;
}
