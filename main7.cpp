// g++ -D__ENABLE_COMPILE_ASSERT__ -O2 -Wall -o main7 main7.cpp

// Try compile_assert with a C++ STL container std::string
// Note: C++ and STL faces issues, this example has some strange interoperation, the 2nd always fails, unless the 1st is commented out

#include "compile_assert.h"

#include <string>
#include <iostream>


int main()
{
    // Create an object with a 5 character word
    const std::string str("hello");
    const size_t str_len = 6; // FIXME change to 6 to pass

    //compile_assert(str[0] == 'a', "Must be 'h'"); // change to 'h' to pass
    compile_assert(str.size() == str_len, "Must be 5");
    std::cout << "str.size: " << str.size() << std::endl;
}
