#ifndef OWNERSHIP2_H
#define OWNERSHIP2_H

#include "float_container.h"

inline void ownership2(float_container * value2)
{
    // fail to compile
    // comment out, and see error disapears
    __builtin_printf("ownership2 %6.2f\n", float_container_get(value2));
}

#endif
