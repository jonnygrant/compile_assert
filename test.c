// gcc -O2 -Wall -D__ENABLE_COMPILE_ASSERT__ -ftrack-macro-expansion=0 -o test test.c

#include "compile_assert.h"

static float quotient(float num, float den)
{
    compile_assert(den != 0);

    return num / den;
}


int main()
{
    float result = quotient(0.0f, 0.0f);

    __builtin_printf("%2.2f\n", result);

    return 0;
}
