// gcc -I.. -D__ENABLE_COMPILE_ASSERT__ -Wall -O3 -o file_line.bin file_line.c

#include "compile_assert.h"

/*
 * // actual output
 *
./compile_assert.h:79:13: error: call to ‘_compile_assert_fail’ declared with attribute error: file test: file_line.c:16
   79 |             _compile_assert_fail(); \
      |             ^~~~~~~~~~~~~~~~~~~~~~
file_line.c:16:5: note: in expansion of macro ‘compile_assert’
   16 |     compile_assert(0, "file test: " FILE_AND_LINE);

*/

#define STRING2(x) #x
#define STRING(x) STRING2(x)
#define FILE_AND_LINE __FILE__ ":" STRING(__LINE__)

int main()
{
    compile_assert(0, "file test: " FILE_AND_LINE);
}
