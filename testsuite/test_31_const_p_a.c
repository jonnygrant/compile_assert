// gcc -I.. -D__ENABLE_COMPILE_ASSERT__ -O2 -o test_31_const_p_a.bin test_31_const_p_a.c

// Demonstrates the variadic compile_assert_const_p(). The trailing arguments name the
// compile-time-constant operands that gate the check: the assert only fires when every
// listed operand is __builtin_constant_p. Here the message (12 bytes) does not fit the
// buffer (8 bytes) and both operands are constants, so the check fires.
//
// This is the un-fixed version, so it must *not* compile.

#include "compile_assert.h"

#define BUF_SIZE 8
#define MSG_LEN  12

int main(void)
{
    compile_assert_const_p(MSG_LEN <= BUF_SIZE,
                           "message does not fit in buffer",
                           MSG_LEN, BUF_SIZE);
    return 0;
}
