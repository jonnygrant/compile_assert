// gcc -g -O2 -Wall -Wno-nonnull -o main20 main20.c

// Demonstrate an alternative compile_assert
// Does not work as C++ yet. Probably never will, because the compiler
// checks static_assert() as soon as it sees it, not after the Optimizer
// has pruned redundant code

#include <stddef.h>

// Based on Alejandro Colomar's suggestion must_be()

#define compile_assert(expression, message) \
    do { \
        if (!(expression)) { \
            typedef struct \
            { static_assert(expression); \
            int  _no_empty_struct; } \
            __comp_struct; __comp_struct _unused; (void)_unused;\
        } \
    } while (0)

int main()
{
    const char * const buf = NULL;

    // change to == to let it pass
    compile_assert(buf != NULL, "");

    return 0;
}
