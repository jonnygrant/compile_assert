#ifndef COMPILE_ASSERT_H
#define COMPILE_ASSERT_H

// Utilize GCC attribute error as part of an optimized build to stop when conditions are not met
// This is at build time, by the compiler, when it does redundant code removal, aka dead code removal.

// Implemented in C, it can be used in C++ projects as well.

// Few other ideas, to check float range etc

#define compile_assert(condition, description) {if(condition) { _stop_compile();}}

void _stop_compile() __attribute ((error("build stopped")));

void * _stop_compile2(void * p) __attribute ((error("build stopped")));


#define compile_never_null(ptr) ptr?ptr:_stop_compile2((void*)ptr)

#endif
