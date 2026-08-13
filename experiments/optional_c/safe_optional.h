
#include <stddef.h>

#include "compile_assert.h"


#define OPTIONAL(T, Name)         \
    typedef struct                \
    {                             \
        T *_dont_access_ptr;      \
    } Name;                        \
                                \
    static inline T *Name##_get(Name optional) \
    {                           \
        compile_assert(optional._dont_access_ptr != NULL, \
            "Optional: cannot access an empty Optional"); \
        return optional._dont_access_ptr; \
    }                                      \
    static inline bool Name##_has_value(Name optional) \
    {                                           \
        return optional._dont_access_ptr != NULL; \
    }
