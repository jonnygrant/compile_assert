
// Demonstrate assigning ownership of an object, upon which it can no longer be used by
// the original object

// See below COMMENT, these are the fixes needed to address the issues detected at compile time

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

    // COMMENT comment this in, and then ownership is transfered so call to ownership2() will not fail
    //float_container_ownership(&value2, &value);

    // check the ownership was transfered
    compile_assert(value.ptr == nullptr, "error nullptr");

    // Takes ownership of the allocation
    ownership2(&value2);

    // fail to compile as the ownership is already handed-over
    // COMMENT out, and see warning disapears
    __builtin_printf("after ownership %6.2f\n", float_container_get(&value));
}
