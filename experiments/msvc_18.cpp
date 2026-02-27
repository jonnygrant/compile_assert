// Run on Godbolt
// https://godbolt.org/z/aG3G573dW

#include <iostream>

// cl /O2 /D__ENABLE_COMPILE_ASSERT__ /DCOMPILE_FILE=__FILE_msvc18_cpp_ msvc18.cpp
// MSVC, optimization level 2, and the compiled file name for the macro.

#ifndef COMPILE_FILE
#error MSVC compile_assert() requires makefile to pass COMPILE_FILE set to the filename
#endif

/*
 * MSVC file and line information
 *
 *  error LNK2019: unresolved external symbol "void __cdecl _compile_assert__FILE_msvc18_cpp_23(void)"
 */

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


int main()
{
    const char * str = "hello\n";
    const char * second = "";

    compile_assert(nullptr != str, "error constraint failure str is nullptr");

    compile_assert(nullptr != second && second[0] != '\0', "error constraint failure second is invalid");

    std::cout << str << second;

    return 1;
}
