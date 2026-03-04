// g++ -I.. -D__ENABLE_COMPILE_ASSERT__ -O2 -Wall -o main17_a.bin main17_a.cpp

#include <iostream>
#include <cstdlib>  // std::stoi

#include "compile_assert.h"

/* $ ./main17_a.bin 10 0
 */

// force calling code to check for 0
static int divide(int num, int div)
{
    compile_assert(div != 0, "div by zero");
    return num / div;
}


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage " << argv[0] << " <num1> <num2>\n";
        return 1;
    }

    int a = std::stoi(argv[1]);
    int b = std::stoi(argv[2]);

    std::cout << "a: " << a << "\n";
    std::cout << "b: " << b << "\n";

    std::cout << divide(a, b) << " divided\n";

    return 0;
}
