// gcc -I.. -D__ENABLE_COMPILE_ASSERT__ -ftrack-macro-expansion=0 -std=c2x -Wall -O3 -c -o main.o main.c


#include "compile_assert.h"

void f(int x)
{
	static const int const_p = 10;
	compile_assert(10 != const_p, "status const_p");

	compile_assert(x> 5, "x arg");
}
