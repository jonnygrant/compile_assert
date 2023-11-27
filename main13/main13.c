
// This example demonstrates how compile_assert can be used with multi file projects
// The two files are compiled to objects, and then linked.
//
// The main benefit of this example is that main13_api.h shows how each public API can be
// turned into a safe API, that is implemented as a substitution macro (to retain line numbers)

#include "./../compile_assert.h"
#include "main13_api.h"
#include <stddef.h>

int main()
{
    //FIXME, change to a valid string to stop the build error
    const char * str = NULL; // "A rose by any other name";

    // FIXME 0 is too small, so increase this
    int result = log_api(str, 0);

    return result;
}
