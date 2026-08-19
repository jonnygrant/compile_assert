#ifndef SOURCE_ASSERT_H
#define SOURCE_ASSERT_H

#include <stdbool.h>

#define STRINGIFY_IMP(x) #x
#define STRINGIFY(x) STRINGIFY_IMP(x)

#define SOURCE_LOCATION __FILE__ ":" STRINGIFY(__LINE__)


#define source_assert_imp(expression, message) \
    do { \
        void _source_assert_fail() __attribute__ ((error(message))); \
        if (!(expression)) { \
            _source_assert_fail(); \
        } \
    } while (0)

#define source_assert(expr) source_assert_imp(expr, "inline_assert: constraint proof failure at: " SOURCE_LOCATION);

#endif
