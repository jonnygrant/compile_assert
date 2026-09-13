// gcc -I.. -D__ENABLE_COMPILE_ASSERT__ -O2 -Wno-nonnull -o test_33_strcpy_a.bin test_33_strcpy_a.c

// demonstates implementing safe_strcpy() as a macro, so the checks are in the library
// and the warning is in the user C code

#include "compile_assert.h"

/*
In file included from test_33_strcpy_a.c:19:
test_33_strcpy_a.c: In function ‘main’:
test_33_strcpy.h:34:13: error: call to ‘_safe_strcpy_err_2’ declared with attribute error: src is invalid
   34 |             _safe_strcpy_err_2(); \
      |             ^~~~~~~~~~~~~~~~~~~~
test_33_strcpy_a.c:26:5: note: in expansion of macro ‘safe_strcpy’
   26 |     safe_strcpy(dest, NULL);
      |     ^~~~~~~~~~~
*/

#include "test_33_strcpy.h"

int main(void)
{
    char dest[6];
    char * src = NULL; // "hello";

    safe_strcpy(dest, src);

    compile_assert(src != NULL, "err");

    return 0;
}
