#ifndef MAIN13_API_H
#define MAIN13_API_H

#include <stddef.h>

#include "./../compile_assert.h"

// Example public API, programmers should call the checked version log_api()
void _internal_log_api(const char * const str);

#define log_api(str) \
    do \
    { \
    compile_assert((str != NULL), "cannot be NULL"); \
    _internal_log_api(str); \
    } while (0)

#endif
