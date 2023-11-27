
// demonstrate compile_assert checking two files, that are compiled separately
// then linked
//
// This is the api file
#include <stddef.h>

int _internal_log_api(const char * const str, const size_t length)
{
    __builtin_printf("log [%s] %zu\n", str, length);
    return (int)length;
}
