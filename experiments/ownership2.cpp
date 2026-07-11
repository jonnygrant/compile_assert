//g++ -I.. -D__ENABLE_COMPILE_ASSERT__ -std=c++23 -Wall -O2 -o ownership1 ownership1.cpp ownership2.cpp


// Demonstrate assigning ownership of an object, upon which it can no longer be used by
// the original object

#include "float_container.hpp"

void ownership2(float_container value2)
{
    // fail to compile
    // comment out, and see warning disapears
    __builtin_printf("%6.2f\n", *value2.get());
}
