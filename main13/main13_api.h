#ifndef MAIN13_API_H
#define MAIN13_API_H

#include <stddef.h>

#include "./../compile_assert.h"

// Example public API, programmers should call the checked version log_api()
int _internal_log_api(const char * const str, const size_t length);

#define log_api(str, length) _internal_log_api(compile_assert_never_null(str), compile_assert_scalar((length != 0), length))

#endif
