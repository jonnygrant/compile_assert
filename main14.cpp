// g++ -D__ENABLE_COMPILE_ASSERT__ -Wall -O3 -o main14 main14.cpp

#include "compile_assert.h"

static int main2(char * const argv[])
{
    compile_assert(argv != nullptr, "check main2() argv not nullptr");

    __builtin_printf("%s\n", argv[0]);

    return 0;
}

int main(int argc, char * const argv[])
{
    //if(nullptr == argv) return 1;
    //if(0 == argc) return 1;

    compile_assert(argv != nullptr, "check main() argv not nullptr");

    main2(argv);

    return 0;
}
