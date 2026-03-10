// g++ -I.. -D__ENABLE_COMPILE_ASSERT__ -Wall -O3 -o test_30_web_b.bin test_30_web_b.cpp


#include <vector>
#include <array>
#include <iostream>

#include "compile_assert.h"

// pretend web API that is meant to only return 0 or 1 but actually can return -1

int web_api(const char * str)
{
    // This line causes the error, the alternative return value
    //if(str[0] == 'h') return -1;

    if(str[0] == 'H') return 0;

    std::cout << str << "\n";

    return 1;
}

int main()
{
    int result = web_api("hello");
    compile_assert(result == 0 || result == 1, "only two values");
}

