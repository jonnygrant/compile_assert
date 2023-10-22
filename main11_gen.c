// gcc -O2 -Wall -o main11_gen main11_gen.c

// generate data file that the main part of this example utilises

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define buf_capacity 10

int main()
{
    int buf[buf_capacity];

    // fill with random values between 0 and 99 (100 different values)
    for(size_t i = 0; i != buf_capacity; ++i)
    {
        const int r = rand();
        buf[i] = (r%100);
    }

    // Save the buffer
    const char * file_name = "main11.bin";
    FILE * file = fopen(file_name, "w");
    if (!file)
    {
        perror(file_name);
        return 1;
    }

    fwrite(buf, sizeof(int), buf_capacity, file);
    fclose(file);

    return 0;
}
