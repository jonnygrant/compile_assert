// g++ -O2 -Wall -o main7 main7.cpp

// Try std::string

#include "compile_assert.h"
#include <stdio.h>

#include <string>

int main()
{
    const std::string str("hello");

    // there is some strange interoperation, the 2nd always fails, unless the 1st is commented out
    //compile_assert(str[0] == 'a', "Must be 'h'"); // change to 'h' to pass
    compile_assert(str.size() == 6, "Must be 5");
    printf("%zu\n", str.size());
}
