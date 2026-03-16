// g++ -I.. -D__ENABLE_COMPILE_ASSERT__ -Wall -O3 -o throw_vec_at.bin throw_vec_at.cpp

// demonstrate that the compiler cannot fathom exceptions even with catch(...)

#include "compile_assert.h"

#include <stdexcept>
#include <iostream>
#include "compile_assert.h"

#include <vector>

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
        std::vector<int> vec;
        std::cout << vec.at(0);
    }
    catch (const std::out_of_range & e)
    {
        std::cout << "received out_of_range exception: " << e.what() << "\n";
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
