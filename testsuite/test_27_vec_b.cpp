// g++ -I.. -D__ENABLE_COMPILE_ASSERT__ -Wall -O3 -o test_27_vec_a.bin test_27_vec_a.cpp

// demonstrate compile_assert works well with std::vector and std::array
// constraint checks at compile time

// demonstrate how a vec.at() container method can be called from a wrapper, that checks the index is within bounds
// This saves the need for application code to write it's own container_get_at() wrapper
// implemented as a macro, so that when it fails, the file and line is output for the application code
// where the required fix to check the index is within range is required.

// the wraper checks that exceptions are handled, and throws out_of_range, so the issue is transparently handled
// the optimizer /should/ produce the same code, as the compile_assert itself "compiles out".


#include <vector>
#include <array>
#include <iostream>

#include "compile_assert.h"



#include <array>
#include <stdexcept>
#include <iostream>
#include "compile_assert.h"

template<typename Container>
decltype(auto) safe_at(Container& c, size_t index)
{
    // Compile-time rejection if provably false
    compile_assert(index < c.size(),
        "index is provably out of bounds");

    // Runtime enforcement otherwise
    if (index >= c.size())
        throw std::out_of_range("index out of bounds");

    return c[index];
}

int main()
{
    std::array<int, 6> a = {1,2,3,4,5,6};

    const size_t i = 5; // within bounds

    try
    {
        std::cout << safe_at(a, i) << "\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "runtime exception: " << e.what() << "\n";
    }
}

