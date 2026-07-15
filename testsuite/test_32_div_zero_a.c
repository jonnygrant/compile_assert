// gcc -I.. -D__ENABLE_COMPILE_ASSERT__ -O2 -Wno-div-by-zero -o test_32_div_zero_a.bin test_32_div_zero_a.c

// Demonstrates catching a division by a compile-time-constant zero *at build time* with
// compile_assert_const_p(), before it becomes runtime undefined behaviour. Naming DIVISOR as
// the guarded operand makes the check fire when the divisor is a known-constant zero.
//
// Note: a constant "/0" is only a warning to the compiler (silenced here with
// -Wno-div-by-zero), so absent the guard this would still build and then crash at runtime.
// It is compile_assert_const_p that turns it into a hard build error.
//
// This is the un-fixed version (DIVISOR == 0), so it must *not* compile.

#include "compile_assert.h"

#define NUMERATOR 100
#define DIVISOR   0

static int checked_divide(void)
{
    compile_assert_const_p(DIVISOR != 0, "division by zero", DIVISOR);
    return NUMERATOR / DIVISOR;
}

int main(void)
{
    return checked_divide();
}
