// gcc -I.. -D__ENABLE_COMPILE_ASSERT__ -O2 -Wall -c -o example1.o example1.c

#include <stddef.h>

#include "compile_assert.h"

// External API
void add_to_log(const char * p);

static void my_log(const char * p)
{
  compile_assert(p != NULL, "may be null");
  add_to_log(p);
}


void app_api(const char * ptr)
{
  my_log(ptr);
}
