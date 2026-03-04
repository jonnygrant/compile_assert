// g++ -I../.. -D__ENABLE_COMPILE_ASSERT__ -O2 -Wall -fanalyzer  -o nonnull.o nonnull1.cpp nonnull2.cpp nonnull3.cpp

// demonstrate that [[gnu::nonnull]] only

#include "compile_assert.h"

// External API
void add_to_log(const char * p);

static void my_log(const char * p)
{
  //compile_assert(p != nullptr, "may be null");
  add_to_log(p);
}


void app_api(const char * ptr)
{
  my_log(ptr);
}


int main()
{
  app_api(nullptr);
}
