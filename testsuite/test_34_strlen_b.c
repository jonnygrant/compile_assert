// gcc -I.. -D__ENABLE_COMPILE_ASSERT__ -O2 -o

/* Demonstrates checking argc argv
 * Example written by Mailhol Vincent
 *
 * This is expected to *not* compile, its a test of
 * -fno-delete-null-pointer-checks
 */

#include <stdio.h>
#include <string.h>

#include "compile_assert.h"

int main(int argc, char **argv)
{
    /* These checks also identify constraints not proven. Left out as not needed. */
    //compile_assert(argc > 1, "argc");
    //compile_assert(NULL != argv, "argv");

    /* strlen(NULL) is undefined behaviour */

	(void)strlen(argv[1]);
	/* So the compiler may assume argv[1] is not NULL... */

	/* ... thus fooling the compile_assert */
	compile_assert(argv[1] != NULL, "argv[1] could be NULL");
	printf("argv[1]: %p\n", argv[1]);

    return 0;
}
