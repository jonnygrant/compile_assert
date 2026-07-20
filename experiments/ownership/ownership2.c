
// Demonstrate assigning ownership of an object, upon which it can no longer be used by
// the original object

#include "float_container.h"

void ownership2(float_container * value2)
{
    // fail to compile
    // comment out, and see error disapears
    __builtin_printf("ownership2 %6.2f\n", float_container_get(value2));
}
