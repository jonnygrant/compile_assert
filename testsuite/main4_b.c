// gcc -O2 -o main4 main4_b.c
// gcc 13  has a handy -Warray-bounds that catches too
// demonstrate compile_assert checking all indices into an array are within bounds

#include "compile_assert.h"

int main()
{
    const int buf_size = 4;
    char buf[buf_size];

    for(int i = 0; i != 5; ++i)
    {
        // Avoid memory overrun bug and return error rather than continue
        if(i >= buf_size)
        {
            return -1;
        }

        // will fire, as out of bounds
        compile_assert(i < buf_size, "check buf index within buffer bounds");
        buf[i] = 3;
    }
}
