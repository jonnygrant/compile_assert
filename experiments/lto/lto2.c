
#include "compile_assert.h"

void f_lto(int a)
{
  //if(a == 2) return;

  compile_assert(a != 2, "");

  if(a == 0) __builtin_printf("0\n");
}
