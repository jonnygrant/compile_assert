// gcc -I.. -D__ENABLE_COMPILE_ASSERT__ -O2 -Wno-div-by-zero -o test_32_div_zero_b.bin test_32_div_zero_b.c

// The fix: DIVISOR is now non-zero, so the compile_assert_const_p() guard is satisfied and the
// division is safe. The program compiles cleanly.

#include "compile_assert.h"

#define NUMERATOR 100
#define DIVISOR   5

static int checked_divide(void)
{
    compile_assert_const_p(DIVISOR != 0, "division by zero", DIVISOR);
    return NUMERATOR / DIVISOR;
}

int main(void)
{
    return checked_divide();
}
