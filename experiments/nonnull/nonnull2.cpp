#include <iostream>

void output(const char * p) [[gnu::nonnull(1)]];

void add_to_log(const char * p)
{
    output(p);
}
