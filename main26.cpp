// g++ -D__ENABLE_COMPILE_ASSERT__ -Wall -O3 -o main26 main26.cpp

// demonstrate compile_assert works well with std::vector and std::array
// constraint checks at compile time

#include <vector>
#include <array>
#include <iostream>

#include "compile_assert.h"

int main()
{
    //std::array<size_t,6> container = {1,2,3,4,5,6};
    std::vector<size_t> container = {1,2,3,4,5,6};

    const size_t index = 9;

    // This is the fix
/*
    if(index >= container.size())
    {
         std::cout << "oops index out of bounds [" << index << "] container size [" << container.size() << "]\n";

         return -1;
    }
*/

    compile_assert(index < container.size(), "error index for container is not within bounds");

    try
    {
        // std::out_of_range thrown
        container.at(index);
    }
    catch (const std::exception & e)
    {
        std::cout << "oops exception [" << e.what() << "]\n";
    }

    return 0;
}
