#ifndef COMPILE_ASSERT_H
#define COMPILE_ASSERT_H

/**
 * Copyright 2023 - 2026 Jonathan Grant <jgrantonline AT gmail com>
 *
 * Distributed under the LICENSE.txt included in the release.
 *
 * Distributed under the Boost Software License, Version 1.0.
 * https://www.boost.org/LICENSE_1_0.txt
*/

/**
 * @file compile_assert.h
 * @brief Header file providing a macro for compile-time assertions builds.
 */

/**
 * @brief Utilize GCC attribute warning to stop when conditions
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

// This library relies on the GCC/Clang function 'warning' attribute.
// GCC has always supported it, but Clang only supports it from version 14.
#if defined(__ENABLE_COMPILE_ASSERT__) && !(defined(__has_attribute) && __has_attribute(warning))
#error "__ENABLE_COMPILE_ASSERT__ requires the 'warning' function attribute, available on GCC and on Clang 14 or later."
#endif

#if defined(__OPTIMIZE__) && defined(__ENABLE_COMPILE_ASSERT__)
#define GCC_COMPILE_ASSERT
#define COMPILE_ASSERT_ACTIVE
#endif // defined(__OPTIMIZE__) && defined(__ENABLE_COMPILE_ASSERT__)
#endif // __GNUC__

#ifdef GCC_COMPILE_ASSERT

/**
 * @brief Statement to issue a diagnostic for a compilation with a message if a compile_assert condition is not satisfied.
 * There is no implementation as it is only used to stop the compiler.
 * @see compile_assert
 */

// The failure function carries the warning message via the warning attribute.
// Its name is made unique per expansion with __COUNTER__
#define compile_assert_cat_(a, b) a##b
#define compile_assert_cat(a, b)  compile_assert_cat_(a, b)

/* __builtin_constant_p returns 1 if known to a compile-time invariant
   It returns 0 if it is not known

   Truth table
   compile-time true, and expression true - No diagnostic
   */

/* If functions are [[noreturn]] only the first diagnostic is shown */
#define compile_assert_impl(expression, message, n) \
    do { \
        /* if known at compile time */ \
        if (__builtin_constant_p(expression)) { \
            void compile_assert_cat(_compile_assert_diag_, n)(void) \
                __attribute__((warning("Invariant expr constraint not satisfied: " message))); \
            if (!(expression)) { \
                compile_assert_cat(_compile_assert_diag_, n)(); \
            } \
        } else { \
            void compile_assert_cat(_compile_assert_notproven_, n)(void) \
                __attribute__((warning("Not proven expr: " message))); \
            if (!(expression)) { \
                compile_assert_cat(_compile_assert_notproven_, n)(); \
            } \
        } \
    } while (0)


#define FILE_LINE __FILE__ ":" CA_STRINGIFY(__LINE__)

#define CA_STRINGIFY_(x) #x
#define CA_STRINGIFY(x) CA_STRINGIFY_(x)

/**
 * @def compile_assert
 * @brief Macro for compile-time assertions.
 * @param expression The compile-time condition to be checked.
 * @param message A description of the assertion.
 */
#define compile_assert(expression, message) \
    compile_assert_impl(expression, "compile_assert " FILE_LINE ": " message, __COUNTER__)

#else
#define compile_assert(condition, description)
#endif


#ifdef GCC_COMPILE_ASSERT
[[noreturn]] void * _stop_compile2() __attribute__ ((warning("'compile_assert pointer issue detected'")));
/**
 * @def compile_assert_never_null
 * @brief Macro to ensure a pointer is never NULL.
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
 * @brief Macro to check a condition and show the pointer.
 * @param condition
 * @param ptr The pointer.
 * @return The pointer.
 */
#define compile_assert_ptr(condition, ptr) ((condition) ? (ptr) : _stop_compile2())

#else
#define compile_assert_ptr(condition, ptr) ptr
#endif


#ifdef GCC_COMPILE_ASSERT
[[noreturn]] int _stop_compile3() __attribute__ ((warning("'compile_assert_scalar issue detected'")));
/**
 * @def compile_assert_scalar
 * @brief Macro to check a condition and substitute with the scalar.
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
#define COMPILE_FILE MSVC_requires_COMPILE_FILE
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

#else

#define compile_assert(condition, description)
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


#endif // COMPILE_ASSERT_H
