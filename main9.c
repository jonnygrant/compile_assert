// gcc -O2 -Wall -o main9 main9.c

// Just an example, this isn't production code

// demonstrate compile_assert checking with multiple conditions

#include "compile_assert.h"
#include <stddef.h>
#include <stdlib.h>

static void my_test(const char * p, const int value)
{
    compile_assert(p != NULL && value >= 0, "check not null and value");
    __builtin_printf("%s %d\n", p, value);
}

int main()
{
    const char * ptr = "hello";
    if(rand() != 10) ptr = NULL;

    const int value = -1;

    //if(NULL != ptr) // TODO put this check in
    {
        //if(value == 1) // TODO put this check in
        {
            my_test(ptr, value);
        }
    }

    return 0;
}
