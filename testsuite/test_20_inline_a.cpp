// g++ -I.. -D__ENABLE_COMPILE_ASSERT__ -O2 -Wall -o test_20_inline_a.bin test_20_inline_a.cpp

// demonstate that with [[gnu::noinline]] the constant propagation stops, and the compiler cannot prove

#include <iostream>

#include "compile_assert.h"

[[gnu::noinline]]
int get_index() { return 10; }

int main()
{
    int buf[5];
    int i = get_index();

    if(i > 5) return 1;

    compile_assert(i < 5, "index out of bounds");
    buf[i] = 1;

    std::cout << buf[i];

    return 0;
}
