#ifndef COMPILE_ASSERT_H
#define COMPILE_ASSERT_H

/**
 * Copyright 2023 - 2026 Jonathan Grant <jg@jguk.org>

 * Distributed under the Boost Software License, Version 1.0.
 * https://www.boost.org/LICENSE_1_0.txt
*/

/**
 * @file compile_assert.h
 * @brief Header file providing a macro for compile-time assertions builds.
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
 * @brief Utilize GCC attribute error to stop when conditions
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

// This library relies on the GCC/Clang function 'error' attribute.
// GCC has always supported it, but Clang only supports it from version 14.
#if defined(__ENABLE_COMPILE_ASSERT__) && !(defined(__has_attribute) && __has_attribute(error))
#error "__ENABLE_COMPILE_ASSERT__ requires the 'error' function attribute, available on GCC and on Clang 14 or later."
#endif

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

// The failure function carries the error message via the error attribute.
// Its name is made unique per expansion with __COUNTER__
#define CA_CAT2(a, b) a##b
#define CA_CAT(a, b) CA_CAT2(a, b)

/**
 * @def compile_assert
 * @brief Macro for compile-time assertions.
 * @param expression The compile-time condition to be checked.
 * @param message A description of the assertion.
 */
#define CA_ASSERT_IMPL(expression, message, fn) \
    do { \
        void fn() __attribute__ ((error(message))); \
        if (!(expression)) { \
            fn(); \
        } \
    } while (0)
#define compile_assert(expression, message) \
    CA_ASSERT_IMPL(expression, message, CA_CAT(_compile_assert_fail_, __COUNTER__))


// compile_assert_const_p turns a provably-constant precondition violation into a build error.
// The optional trailing arguments name the operands that must be compile-time constants for the
// check to fire; with none given, the condition itself is the guarded operand:
//
//   compile_assert_const_p(condition, message)             guard on the condition
//   compile_assert_const_p(condition, message, a)          guard on operand a
//   compile_assert_const_p(condition, message, a, b, ...)  guard on every listed operand (ANDed)
//
// GCC before 13 does not fold __builtin_constant_p when it is applied to a value derived from
// an overflow builtin, or even to a comparison in a deep constexpr call chain, so a guard on
// the condition is missed and the assertion never fires. Naming the raw operands (plain
// integers, which fold on every supported GCC) makes the check fire on GCC 11 and 12 as well
//
// __builtin_constant_p of every listed operand, ANDed together.
// Up to 8 arguments are currently supported
#define CA_G1(a, ...) __builtin_constant_p(a) __VA_OPT__(&& CA_G2(__VA_ARGS__))
#define CA_G2(a, ...) __builtin_constant_p(a) __VA_OPT__(&& CA_G3(__VA_ARGS__))
#define CA_G3(a, ...) __builtin_constant_p(a) __VA_OPT__(&& CA_G4(__VA_ARGS__))
#define CA_G4(a, ...) __builtin_constant_p(a) __VA_OPT__(&& CA_G5(__VA_ARGS__))
#define CA_G5(a, ...) __builtin_constant_p(a) __VA_OPT__(&& CA_G6(__VA_ARGS__))
#define CA_G6(a, ...) __builtin_constant_p(a) __VA_OPT__(&& CA_G7(__VA_ARGS__))
#define CA_G7(a, ...) __builtin_constant_p(a) __VA_OPT__(&& CA_G8(__VA_ARGS__))
#define CA_G8(a) __builtin_constant_p(a)
#define CA_GUARD(...) CA_G1(__VA_ARGS__)

// Pick the guard expression
#define CA_CONST_P_GUARD_(condition, ...)  __builtin_constant_p(condition)
#define CA_CONST_P_GUARD_1(condition, ...) CA_GUARD(__VA_ARGS__)
#define CA_CONST_P_GUARD(condition, ...) \
    CA_CAT(CA_CONST_P_GUARD_, __VA_OPT__(1))(condition, __VA_ARGS__)

#define CA_CONST_P_IMPL(condition, message, guard, fn) \
    do { \
        if (guard) { \
            if (!(condition)) { \
                void fn() __attribute__ ((error(message))); \
                fn(); \
            } \
        } \
    } while (0)
#define compile_assert_const_p(condition, message, ...) \
    CA_CONST_P_IMPL( \
        condition, message, \
        CA_CONST_P_GUARD(condition, __VA_ARGS__), \
        CA_CAT(_compile_assert_fail_, __COUNTER__))


#define compile_assert0(expression) compile_assert(expression, NULL)

#else
#define compile_assert(condition, description)
#define compile_assert0(expression)
#define compile_assert_const_p(condition, message, ...)
#endif


#ifdef GCC_COMPILE_ASSERT
void * _stop_compile2() __attribute__ ((error("'compile_assert pointer error detected'")));
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
 * @brief Macro to check a condition and show the pointer, or stop the
 * compiler by calling the error function in optimized builds.
 * @param condition
 * @param ptr The pointer.
 * @return The pointer.
 */
#define compile_assert_ptr(condition, ptr) ((condition) ? (ptr) : _stop_compile2())

#else
#define compile_assert_ptr(condition, ptr) ptr
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

// make lack of COMPILE_FILE a hard error
//#if defined(_MSC_VER)
//#ifndef COMPILE_FILE
//#error MSVC compile_assert requires COMPILE_FILE to be passed from makefile
//#endif // COMPILE_FILE
//#endif // _MSC_VER

#if defined(_MSC_VER)
#ifndef COMPILE_FILE
#define COMPILE_FILE filename_not_set
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

// Generic compiler support, via a missing symbol
#if defined(__ENABLE_COMPILE_ASSERT__)
#if !defined(compile_assert)
#define COMPILE_ASSERT_ACTIVE

#define compile_assert(expression, message) \
    do { \
        void _compile_assert_fail(); \
        if (!(expression)) { \
            _compile_assert_fail(); \
        } \
    } while (0)

#define compile_assert0(expression) compile_assert(expression, NULL)
#endif // !defined(compile_assert)
#endif // defined(__ENABLE_COMPILE_ASSERT__)


#ifndef compile_assert
#error compile_assert not defined
#endif

#ifndef compile_assert0
#error compile_assert0 not defined
#endif

#ifndef compile_assert_const_p
#error compile_assert_const_p not defined
#endif

#endif // COMPILE_ASSERT_H
