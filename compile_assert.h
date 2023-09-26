#ifndef COMPILE_ASSERT_H
#define COMPILE_ASSERT_H

#include <stdbool.h>

// Utilize GCC attribute error as part of an optimized build to stop when conditions are not met
// This is at build time, by the compiler, when it does redundant code removal, aka dead code removal.

// Implemented in C, it can be used in C++ projects as well.

// Few other ideas, to check float range etc

// The description isn't logged yet, it is at least a note to the programmer

#ifdef __OPTIMIZE__
void _stop_compile() __attribute ((error("build stopped")));
void * _stop_compile2(void * p) __attribute ((error("build stopped")));

inline void _compile_assert(bool condition, const char * const description)
{
    (void)description;

    if(!condition) _stop_compile();
}

#define compile_assert(condition, description) _compile_assert(condition, description)
#else
#define compile_assert(condition, description)
#endif

#ifdef __OPTIMIZE__
#define compile_never_null(ptr) ptr?ptr:_stop_compile2((void*)ptr)
#else
#define compile_never_null(ptr) ptr
#endif

#endif
