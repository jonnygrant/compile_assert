// g++ -I.. -D__ENABLE_COMPILE_ASSERT__ -Wall -O3 -o throw.bin throw.cpp

// demonstrate that the compiler cannot fathom exceptions even with catch(...)

#include "compile_assert.h"

#include <stdexcept>
#include <iostream>
#include "compile_assert.h"

/*
 * // actual output
throw.cpp:29:5: note: in expansion of macro ‘compile_assert’
   29 |     compile_assert(throw_caught, "throw test");
      |     ^~~~~~~~~~~~~~
*/

int main()
{
    bool throw_caught = false;

    try
    {
        throw std::runtime_error("oops");;
    }
    catch (const std::exception& e)
    {
        std::cout << "runtime exception: " << e.what() << "\n";
        throw_caught = true;
    }
    catch (...)
    {
        // compiler cannot figure out that it will never reach here.
        // so this is needed
        //throw_caught = true;
    }

    compile_assert(throw_caught, "throw test");
}
