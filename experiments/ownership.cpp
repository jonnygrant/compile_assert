//g++ -I.. -D__ENABLE_COMPILE_ASSERT__ -std=c++23 -Wall -O2 -o ownership.bin ownership.cpp


// Demonstrate assigning ownership of an object, upon which it can no longer be used by
// the original object

#include "float_container.hpp"

int main()
{
    float_container value;

    // Allocate internally.
    value.set(3.14f);
    __builtin_printf("%6.2f\n", *value.get());

    // Take ownership of an existing allocation.
    float_container value2;
    value2 = value;

    // fail to compile
    // comment out, and see warning disapears
    __builtin_printf("%6.2f\n", *value.get());
}
