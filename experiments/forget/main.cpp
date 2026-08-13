// This example demonstrates compile-time Forget

#include "compile_assert.h"

#include "forget.hpp"

int main()
{
    Forget<int> a(42);

    int x = a;
    __builtin_printf("a %d\n", x);

    // remove access to 'a'
    Forget<int> b(a);

    int try_to_access = a;
    __builtin_printf("a again %d\n", try_to_access);

    return 0;
}
