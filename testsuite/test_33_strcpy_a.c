// gcc -I.. -D__ENABLE_COMPILE_ASSERT__ -O2 -Wno-nonnull -o test_33_strcpy_a.bom test_33_strcpy_a.c

// demonstates implementing safe_strcpy() as a macro, so the checks are in the library
// and the warning is in the user C code

#include "test_33_strcpy.h"

int main(void)
{
    char dest[6];
    char src[] = "hello";

    safe_strcpy(dest, NULL);

    return 0;
}
