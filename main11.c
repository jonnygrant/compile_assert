// gcc -O2 -Wall -o main11 main11.c

// demonstrate compile_assert checking array ranges, based on values read from a file

#include "compile_assert.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define buf_capacity 10
#define buf_count_capacity 100

int main()
{
    int buf[buf_capacity];
    int buf_count[buf_count_capacity] = {0};

    // read the raw file
    const char * file_name = "main11.bin";
    FILE * file = fopen(file_name, "r");
    if (!file)
    {
        perror(file_name);
        return 1;
    }

    size_t fread_result = fread(buf, sizeof(int), buf_capacity, file);
    if(buf_capacity != fread_result)
    {
        printf("err: %d expected but got %zu\n", buf_capacity, fread_result);
        fclose(file);
        return 1;
    }

    fclose(file);

    // count the occurance of each
    for(size_t i = 0; i != buf_capacity; ++i)
    {
        // TODO put this bounds check in to FIX the range uncertainty
#if 0
        if(buf[i] >= buf_count_capacity)
        {
            printf("value %d out of bounds\n", buf[i]);
            continue;
        }
#endif
        compile_assert(buf[i] < buf_count_capacity, "check array bounds");
        // increment the count of each
        buf_count[buf[i]]++;
    }

    return 0;
}
