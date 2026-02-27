#ifndef COMPILE_ASSERT_H
#define COMPILE_ASSERT_H

/**
 * Copyright 2023, 2024, 2025, 2026 Jonny Grant <jg@jguk.org>

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

#ifdef __GNUC__
#if defined(__OPTIMIZE__) && defined(__ENABLE_COMPILE_ASSERT__)
#define GCC_COMPILE_ASSERT
#define COMPILE_ASSERT_ACTIVE
#endif // defined(__OPTIMIZE__) && defined(__ENABLE_COMPILE_ASSERT__)
#endif // __GNU__

#ifdef GCC_COMPILE_ASSERT

/**
 * @brief Function to stop compilation with an error message if a compile_assert condition is not satisfied.
 * There is no implementation as it is only used to stop the compiler.
 * @see compile_assert
 */

/**
 * @def compile_assert
 * @brief Macro for compile-time assertion in optimized builds.
 * @param expression The compile-time condition to be checked.
 * @param message A description of the assertion (unused).
 */
#define compile_assert(expression, message) \
    do { \
        void _compile_assert_fail() __attribute__ ((error(message))); \
        if (!(expression)) { \
            _compile_assert_fail(); \
        } \
    } while (0)

#define compile_assert0(expression) compile_assert(expression, NULL)

#else
#define compile_assert(condition, description)
#define compile_assert0(expression)
#endif


#ifdef GCC_COMPILE_ASSERT
void * _stop_compile2() __attribute__ ((error("'compile_assert pointer error detected'")));
/**
 * @def compile_assert_never_null
 * @brief Macro to ensure a pointer is never NULL in optimized builds.
 * @param ptr The pointer to be checked for NULL.
 * @return The pointer ptr if not NULL.
 */
#define compile_assert_never_null(ptr) ((ptr) ? (ptr) : _stop_compile2())

#else
#define compile_assert_never_null(ptr) ptr
#endif


#ifdef GCC_COMPILE_ASSERT
/**
 * @def compile_assert_ptr
 * @brief Macro to check a condition and show the pointer, or stop the
 * compiler by calling the error function in optimized builds.
 * @param condition
 * @param ptr The pointer.
 * @return The pointer.
 */
#define compile_assert_ptr(condition, ptr) ((condition) ? (ptr) : _stop_compile2())

#else
#define compile_assert_ptr(condition, ptr)
#endif


#ifdef GCC_COMPILE_ASSERT
int _stop_compile3() __attribute__ ((error("'compile_assert_scalar error detected'")));
/**
 * @def compile_assert_scalar
 * @brief Macro to check a condition and substitute with the scalar in an optimized build.
 * @param condition
 * @param scalar The value.
 * @return The scalar value.
 */
#define compile_assert_scalar(condition, scalar) ((condition) ? (scalar) : _stop_compile3())

#else
#define compile_assert_scalar(condition, scalar) scalar
#endif

#if defined(_MSC_VER)
#ifndef COMPILE_FILE
#error MSVC compile_assert requires COMPILE_FILE to be passed from makefile
#endif // COMPILE_FILE

#endif // _MSC_VER


#if defined(_MSC_VER)
#if defined(__ENABLE_COMPILE_ASSERT__)
#define COMPILE_ASSERT_ACTIVE
#define MSVC_COMPILE_ASSERT
/* Requires makefile to pass the filename as a macro: cl /DCOMPILE_FILE=__FILE_msvc18_cpp_
 * The preprocessor merges the three macros as a missing function call.
 * the failure shows as eg _compile_assert__FILE_msvc18_cpp_23(void)
 */
#define COMPILE_ASSERT_ACTIVE
#define MERGE2(a,b) a##b
#define MERGE1(a,b) MERGE2(a,b)
#define MERGE3(a,b,c) MERGE1(a, MERGE1(b,c))

#define compile_assert(expr, message) \
do { \
    if (!(expr)) { \
      extern void MERGE3(_compile_assert, COMPILE_FILE, __LINE__)(); \
      MERGE3(_compile_assert, COMPILE_FILE, __LINE__)(); \
    } \
} while (0)

#define compile_assert0(expression) compile_assert(expression, NULL)
#else

#define compile_assert(condition, description)
#define compile_assert0(expression)
#define COMPILE_ASSERT_ACTIVE

#endif // defined(__ENABLE_COMPILE_ASSERT__)
#endif // defined(_MSC_VER)

// Compile out the other variants for the moment
#if defined(_MSC_VER)
#define compile_assert_ptr(condition, ptr) ptr
#define compile_assert_never_null(ptr) ptr
#define compile_assert_scalar(condition, scalar) scalar
#endif

#ifndef compile_assert
#error compile_assert not defined
#endif

#ifndef compile_assert0
#error compile_assert0 not defined
#endif

#endif // COMPILE_ASSERT_H
