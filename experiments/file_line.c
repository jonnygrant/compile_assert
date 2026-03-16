// gcc -I.. -D__ENABLE_COMPILE_ASSERT__ -Wall -O3 -o file_line.bin file_line.c

#include "compile_assert.h"

/*
 * // actual output

*/

#define STRING2(x) #x
#define STRING(x) STRING2(x)
#define FILE_AND_LINE __FILE__ ":" STRING(__LINE__)

int main()
{
    compile_assert(0, "file test: " FILE_AND_LINE);
}
