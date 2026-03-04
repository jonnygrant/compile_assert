// gcc -D__ENABLE_COMPILE_ASSERT__-O2 -Wall -o main17 main17.cpp

#include "compile_assert.h"

// force calling code to check for 0
static int divide(int num, int denominator)
{
    compile_assert(denominator != 0, "divide by zero");
    return num / denominator;
}

int main(void)
{
    int num = 10;
    int div = 0;

    if(div == 0)
    {
        return 2;
    }

    int result = divide(num, div);

    return result;
}
