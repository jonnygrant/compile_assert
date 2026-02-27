// g++ -g --std=c++23 -O2 -Wall -Wno-nonnull -o missing_function missing_function.cpp


// This works with GCC, MSVC

/*
 * output is like:
 *
/usr/bin/ld: /tmp/ccIMlrPG.o: in function `main':
missing_function.cpp:20:(.text.startup+0xd): undefined reference to `_compile_assert_failure()'
missing_function.cpp:22:(.text.startup+0x12): undefined reference to `_compile_assert_failure()'
collect2: error: ld returned 1 exit status
*/

#include <iostream>

#define compile_assert(expression, message) \
    do { \
        if (!(expression)) { \
            _compile_assert_failure(); \
        } \
    } while (0)

extern void _compile_assert_failure();

int main()
{
    const char * str = nullptr; // "hello\n";

    const char * second = "";

    compile_assert(nullptr != str, "error constraint failure str is nullptr");

    compile_assert(nullptr != second && second[0] != '\0', "error constraint failure second is invalid");

    std::cout << str << second;

    return 1;
}

