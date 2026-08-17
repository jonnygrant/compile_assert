
#include <stddef.h>
#include <stdbool.h>

#include "compile_assert.h"


#define OPTIONAL(T, Name)         \
    typedef struct                \
    {                             \
        T *_dont_access_ptr;      \
        bool _checked;            \
    } Name;                       \
                                \
    static inline T *Name##_get(Name optional) \
    {                           \
        compile_assert(optional._checked, \
            "Optional: Pointer is dereferenced without a preceding check for null"); \
                                                          \
        compile_assert(optional._dont_access_ptr != NULL, \
            "Optional: Cannot access an empty Optional"); \
                                                          \
        return optional._dont_access_ptr;                 \
    }                                                     \
                                                          \
    static inline bool Name##_has_value(Name * optional)  \
    {                                                     \
        optional->_checked = true;                        \
                                                          \
        return optional->_dont_access_ptr != NULL;        \
    }

// TODO add the copy API
