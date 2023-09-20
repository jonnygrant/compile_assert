// gcc -O2 -Wall -Wno-nonnull -o main main.c

// demonstrate compile_assert

#include "compile_assert.h"
#include <stdio.h>
#include <stdlib.h>

static void my_test(const char * p)
{
    compile_assert(p, "check not null");
    printf("%s\n", p);
}

int main()
{
    const char * ptr = "hello";
    if(rand() != 10) ptr = NULL;

    // The following line, is the pogrammer fix in this little example, of course in a real application a diagnosis should be done to see how this could occur.
    //if(NULL != ptr)
    {
        my_test(ptr);
    }
}
