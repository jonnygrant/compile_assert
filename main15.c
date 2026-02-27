// gcc -D__ENABLE_COMPILE_ASSERT__ -O2 -Wall -o main15 main15.c

#include <string.h>
#include <stdint.h>

// demonstrate compile_assert checking for NULL, even late, causes the compiler to stop
// Based on https://www.redhat.com/en/blog/security-flaws-caused-compiler-optimizations
//
#include "compile_assert.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>




struct data
{
    uint32_t id;
    const char * p;
};


static void check_data(const struct data * ptr)
{
    if(NULL == ptr)
    {
        return;
    }

    const char * d = ptr->p;

    //if(p == NULL) return;

    // BUG identified, the NULL check may be optimized out,
    // this draws attention to the issues in this function
    compile_assert((d != NULL), "check_data: d was NULL");

    __builtin_printf("d %p\n", ptr);
}


int main()
{
    struct data d = {100, NULL};

    check_data(&d);

    return 0;
}
