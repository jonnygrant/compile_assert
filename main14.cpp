// g++ -Wall -O3 -o main14 main14.cpp
// g++ -g -pipe -pthread -O3 -march=native --std=c++23 -fno-delete-null-pointer-checks -D_FORTIFY_SOURCE=2 -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fexceptions -Wall -Wextra -Werror -Werror=format-security -Wpointer-arith -pedantic -Wpedantic -Wformat=2 -Wshadow -Wvla -Wformat-nonliteral -Wnonnull -Winit-self -Wuninitialized -Wconversion -Wconversion-null -Wdiv-by-zero -Wsign-conversion -Wnull-dereference -Wunused-parameter -Wformat-security -Wundef -Wunused-macros -Wpointer-compare -Wcast-align -Wswitch-unreachable -Wmaybe-uninitialized -Wno-nonnull-compare -Wformat-truncation=1 -Wstringop-truncation -Wformat-overflow=2 -Wformat-signedness -Wformat-security -pedantic-errors -Wdangling-else -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast -Wdouble-promotion -Wbool-compare -fmax-errors=2 -Wno-restrict -Wanalyzer-use-of-uninitialized-value -Wanalyzer-null-argument -Wanalyzer-possible-null-argument -Wanalyzer-possible-null-dereference -Wanalyzer-null-dereference -Wanalyzer-malloc-leak  -o main14 main14.cpp

#include "compile_assert.h"

static int main2(char * const argv[])
{
    compile_assert(argv != nullptr, "check main2() argv not nullptr");

    __builtin_printf("%s\n", argv[0]);

    return 0;
}

int main(int argc, char * const argv[])
{
    if(nullptr == argv) return 1;
    if(0 == argc) return 1;

    compile_assert(argv != nullptr, "check main() argv not nullptr");

    main2(argv);

    return 0;
}
