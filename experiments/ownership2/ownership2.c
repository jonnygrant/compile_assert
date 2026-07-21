
// Demonstrate assigning ownership of an object, upon which it can no longer be used by
// the original object

#include "ownership2.h"

void ownership2(float_container * value2)
{
    //compile_assert(nullptr != value2, "err");

    __builtin_printf("ownership2 %6.2f\n", float_container_get(value2));
}

