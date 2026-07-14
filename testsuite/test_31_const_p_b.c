// gcc -I.. -D__ENABLE_COMPILE_ASSERT__ -O2 -o test_31_const_p_b.bin test_31_const_p_b.c

// The fix: the message now fits within the buffer, so the variadic
// compile_assert_const_p() check is satisfied and the program compiles cleanly.

#include "compile_assert.h"

#define BUF_SIZE 8
#define MSG_LEN  6

int main(void)
{
    compile_assert_const_p(MSG_LEN <= BUF_SIZE,
                           "message does not fit in buffer",
                           MSG_LEN, BUF_SIZE);
    return 0;
}
