// gcc -O2 -Wall -o main3 main3.c

// demonstrate compile_assert to check a percentage is valid

#include "compile_assert.h"
#include <stdio.h>

static void increase_percentage(double value, double increase_by_pc)
{
    compile_assert(increase_by_pc >= 0.0, "percentage not within 0 - 100 range");
    compile_assert(increase_by_pc <= 100.0, "percentage not within 0 - 100 range");

    double value2 = value /100.0 * (1.0 + increase_by_pc);
    printf("%f\n", value2);
}

int main()
{
    double value = 50.0;
    double increase_by_pc = 100.01;

    //compile_assert(increase_by_pc <= 100.0, "err");

    increase_percentage(value, increase_by_pc);
}
