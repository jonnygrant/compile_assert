
// Demonstrate assigning ownership of an object, upon which it can no longer be used by
// the original object

#include "float_container.h"
#include "ownership2.h"

int main()
{
    float_container value;

    float_container_init(&value);

    float_container_set(&value, 3.14f);
    __builtin_printf("after set %6.2f\n", float_container_get(&value));

    float_container value2;

    float_container_init(&value2);
    float_container_ownership(&value2, &value);

    compile_assert(value.ptr == nullptr, "error nullptr");

    //value2 = value;
    // Takes ownership of the allocation
    ownership2(&value2);

    // fail to compile as the ownership is already handed-over
    // comment out, and see warning disapears
    //__builtin_printf("after ownership %6.2f\n", float_container_get(&value));
}
