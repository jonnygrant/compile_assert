// gcc -I.. -D__ENABLE_COMPILE_ASSERT__ -O2 -Wno-nonnull -o test_33_strcpy_a.bom test_33_strcpy_a.c

// demonstates implementing safe_strcpy() as a macro, so the checks are in the library
// and the warning is in the user C code

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "test_33_strcpy.h"

int main(void)
{
    char * dest = malloc(6);

    if(NULL == dest)
    {
        perror("malloc");
        return EXIT_FAILURE;
    }

    const char * src = "hello";

    safe_strcpy(dest, src);

    free(dest);

    return 0;
}
