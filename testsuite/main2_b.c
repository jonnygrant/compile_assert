// gcc -O2 -Wall -Wno-nonnull -o main2_b.bin main2.c

// demonstrate compile_assert_never_null

#include "compile_assert.h"
#include <stdio.h>
#include <stdlib.h>

static void my_test(const char * p)
{
    printf("%s\n", p);
}

int main()
{
    const char * ptr = "hello";
    if(rand() != 10) ptr = NULL;

    // The following line, is the pogrammer fix in this little example, of course in a real application a diagnosis should be done to see how this could occur.
    if(NULL != ptr)
    {
        my_test(compile_assert_never_null(ptr));
    }
}
