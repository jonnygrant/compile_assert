#ifndef TEST_33_STRCPY_H
#define TEST_33_STRCPY_H

#include <string.h>

#define compile_assert(expression, message) \
    do { \
        [[noreturn]] void _compile_assert_fail() __attribute__ ((error(message))); \
        if (!(expression)) { \
            _compile_assert_fail(); \
        } \
    } while (0)


#if 0
#define safe_strcpy(dest, src) \
    do { \
        compile_assert((dest) != NULL, "strcpy: destination is NULL"); \
        compile_assert((src) != NULL, "strcpy: source is NULL"); \
        strcpy((dest), (src)); \
    } while (0)
#endif

// implement with attribute error

#define safe_strcpy(dest, src) \
    do { \
        [[noreturn]] void _safe_strcpy_1() __attribute__ ((error("dest is invalid : " #dest))); \
        if (!(dest != NULL)) { \
            _safe_strcpy_1(); \
        } \
        [[noreturn]] void _safe_strcpy_2() __attribute__ ((error("src is invalid : " #src))); \
        if (!(src != NULL)) { \
            _safe_strcpy_2(); \
        } \
    } while (0)




#endif
