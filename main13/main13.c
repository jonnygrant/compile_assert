
// This example demonstrates how compile_assert can be used with multi file projects
// The two files re compiled to objects, and then linked.
//
// The main benefit of this example is that main13_api.h shows how each public API can be
// turned into _checked() API, that is implemented as a macro (to retain line numbers)

#include "./../compile_assert.h"
#include "main13_api.h"
#include <stddef.h>

int main()
{
    //FIXME, change to a valid string to stop the build error
    const char * str = NULL; // "A rose by any other name";
    log_api_checked(str);

    return 0;
}
