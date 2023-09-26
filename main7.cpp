// g++ -O2 -Wall -o main7 main7.cpp

// Try compile_assert with a C++ STL container std::string
// Note: There is some strange interoperation, the 2nd always fails, unless the 1st is commented out

#include "compile_assert.h"
#include <stdio.h>

#include <string>

int main()
{
    const std::string str("hello");

    //compile_assert(str[0] == 'a', "Must be 'h'"); // change to 'h' to pass
    compile_assert(str.size() == 6, "Must be 5");
    printf("%zu\n", str.size());
}
