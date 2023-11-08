// gcc -std=c2x -O2 -Wall -o main8 main8.c

// demonstrate static_assert to checking all indices into an array are within bounds
// Note, this does not work, as expression in static assertion is not constant (enough)
// The data would need to be in a constexpr

#include <stdio.h>
#include <assert.h>

int main()
{
    const size_t buf_size = 2;
    size_t buf[buf_size];  // NOTE, it can't be constexpr as the array is filled on next lines
    buf[0] = 2; // fires because these should be '1';
    buf[1] = 2;

    char second[buf_size];
    second[0] = 'a';

    for(size_t i = 0; i != buf_size; ++i)
    {
        static_assert(buf[i] < buf_size);  // this will fire because '2' and '2' are out of bounds
        second[buf[i]] = 100;
    }

    printf("%d\n", second[0]);
}
