// gcc -I.. -D__ENABLE_COMPILE_ASSERT__ -O2 -Wall -Wno-nonnull -o main1_b.bin main.c

#include "compile_assert.h"
#include <stdio.h>
#include <stdlib.h>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

static void my_test(const char * p)
{
    compile_assert(p, "main1_a check not null in: " __FILE__ ":" TOSTRING(__LINE__));

    compile_assert(p[0] == 'H', "");

    printf("%s\n", p);
}


int main()
{
    const char * ptr = "Hello";
    if(rand() != 10) ptr = NULL;

    // The following line, is the programmer fix in this little example,
    // of course in a real application a diagnosis should be done to
    // see why this bug is here!
    if(NULL != ptr)
    {
        my_test(ptr);
    }
}
