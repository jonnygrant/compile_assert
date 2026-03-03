// gcc -I.. -D__ENABLE_COMPILE_ASSERT__ -O2 -Wall -o main19_a.bin main18_a.cpp

#include <string.h>
#include <stdint.h>

// demonstrate compile_assert checking for NULL, even late, causes the compiler to stop
// Based on https://www.redhat.com/en/blog/security-flaws-caused-compiler-optimizations
//
#include "compile_assert.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

static void add_to_log(const char * p)
{
    __builtin_printf(p);
}

static void my_log(const char * p)
{
    add_to_log(p);
}


int main()
{
    //FIXME, change to a valid string to stop the build error
    const char * str = NULL; // "A rose by any other name";

    // FIXME 0 is too small, so increase this
    int result = my_log(str, 0);

    return result;
}
