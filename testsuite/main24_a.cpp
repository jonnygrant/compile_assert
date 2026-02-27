// g++ -I.. -D__ENABLE_COMPILE_ASSERT__ -Wall -O3 -o main24 main24_b.cpp

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "compile_assert.h"

int main()
{
    //double number = 5;

    double number = std::numeric_limits<double>::max();
    // if set to this compiler cannot figure out

    // Does not make any difference, maybe compiler understands rand() implementation
    if(rand() != 10) number = 4.0;

    double sq = number*number;
    std::cout << number << " squared is " << sq << std::endl;
    double result = std::sqrt(sq);
    compile_assert(result == number, "Cannot determine sqrt");
    std::cout << "sqrt: " << result << std::endl;

    return 0;
}
