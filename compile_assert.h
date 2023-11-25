#ifndef COMPILE_ASSERT_H
#define COMPILE_ASSERT_H

/**
 * Copyright 2023 Jonny Grant <jg@jguk.org>

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 * Neither the name of the copyright holder nor the names of its contributors may be
 * used to endorse or promote products derived from this software without specific
 * prior written permission.
*/

/**
 * @file compile_assert.h
 * @brief Header file providing a macro for compile-time assertions in optimized builds.
 */

// Utilize GCC attribute error as part of an optimized build to stop when conditions
// are not met. This is at build time, by the compiler, when it does redundant code
// removal, aka dead code removal.
//
// Implemented in C, it can be used in C++ projects as well.
//
// compile_assert() is kept as a macro so GCC shows the line it's invoked as in
// any asserts that fire. (If changed to inline, GCC shows the inline function code instead)
//
// Note this relies upon an optimized compiler build, in -O0 builds, it "compiles out"


/**
 * @brief Utilize GCC attribute error as part of an optimized build to stop when conditions
 * are not met. This is at build time, by the compiler, when it does redundant code
 * removal, aka dead code removal.
 *
 * Implemented in C, it can be used in C++ projects as well.
 *
 * @note compile_assert() is kept as a macro so GCC shows the line it's invoked as in
 * any asserts that fire. (If changed to inline, GCC shows the inline function code instead)
 *
 * @note This only works in an Optimized build; in -O0 builds, it "compiles out".
 *
 * @note Future work: The description isn't logged yet - never will be, just note
 * to the programmer to refer to when they look up the file and line number of the compiler
 * output.
 */

#ifdef __OPTIMIZE__

/**
 * @brief Function to stop compilation with an error message if a compile_assert condition is not satisfied.
 * There is no implementation as it is only used to stop the compiler.
 * @see compile_assert
 */
void _stop_compile() __attribute ((error("'compile_assert condition not satisfied'")));


/**
 * @def compile_assert
 * @brief Macro for compile-time assertion in optimized builds.
 * @param condition The compile-time condition to be checked.
 * @param description A description of the assertion (unused).
 */
#define compile_assert(condition, description) \
    do { \
        if (!(condition)) { \
            _stop_compile(); \
        } \
    } while (0)

#else
#define compile_assert(condition, description)
#endif


#ifdef __OPTIMIZE__
/**
 * @def compile_never_null
 * @brief Macro to ensure a pointer is never NULL in optimized builds.
 * @param ptr The pointer to be checked for NULL.
 * @return The pointer ptr if not NULL.
 */
#define compile_never_null(ptr) ((ptr) ? (ptr) : _stop_compile())

#else
#define compile_never_null(ptr) ptr
#endif

#endif
