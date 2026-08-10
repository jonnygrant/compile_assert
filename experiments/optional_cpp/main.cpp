// g++ -O2 -I../.. -D__ENABLE_COMPILE_ASSERT__ -ftrack-macro-expansion=0 -std=c++23 -Wall -O3 -o optional.bin main.cpp
#include "compile_assert.h"

#include "optional.hpp"

int main()
{
    int var = 42;

    Optional<int> a(&var);
    Optional<int> b(nullptr);

    int var1 = *a;
    __builtin_printf("%d\n", var1);

    if(b)
    {
        __builtin_printf("b is valid\n");
        __builtin_printf("%d\n", *b);
    }
    else
    {
        __builtin_printf("b is NULL\n");

        // COMMENT this out so it compiles
        __builtin_printf("%d\n", *b);
    }

    return 0;
}
