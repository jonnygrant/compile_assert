// This example demonstrates compile-time Optional in C, like how std::optional manages an optional contained pointer value.

#include "safe_optional.h"

OPTIONAL(int, OptionalInt);

int main()
{
    int x = 42;

    OptionalInt a = {&x, false};
    OptionalInt b = {nullptr, false};

    // COMMENT Will fail unless check has_value
    __builtin_printf("Optional a %d\n", *OptionalInt_get(a));

    if(OptionalInt_has_value(&a))
    {
        __builtin_printf("has_value %d\n", a._checked);

        __builtin_printf("Optional a check2 %d\n", *OptionalInt_get(a));
    }

    if(OptionalInt_has_value(&b))
    {
        __builtin_printf("Optional b is valid\n");
        __builtin_printf("b = %d\n", *OptionalInt_get(b));
    }
    else
    {
        // COMMENT this will fail
        __builtin_printf("Optional b is %d\n", *OptionalInt_get(b));
    }

    return 0;
}
