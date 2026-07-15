// g++ -I../.. -D__ENABLE_COMPILE_ASSERT__ -O2 -Wall -S -fverbose-asm -flto -fanalyzer -o lto lto1.cpp lto2.cpp

// demonstrate LTO

#include "compile_assert.h"


extern void f_lto(int a);

int main()
{
  f_lto(2);
  return 2;
}
