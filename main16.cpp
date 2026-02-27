// g++ -D__ENABLE_COMPILE_ASSERT__ -Wall -O3 -o main16 main16.cpp


#include "compile_assert.h"
#include <cstddef>

// demonstates a class that prevents construction with nullptr

template <typename T>
class never_null_ptr
{
public:
explicit never_null_ptr(T* ptr)
    {
        compile_assert(ptr != nullptr, "never_null_ptr: null pointer");
        m_ptr = ptr;
    }

    // Never reaches here in this example
    never_null_ptr(std::nullptr_t) = delete;

    T* operator()() const noexcept { return m_ptr; }

private:
    T* m_ptr;
};


void f(never_null_ptr<const char> ptr)
{
    __builtin_printf("argv[0]: [%s]\n", ptr());
}


int main(int argc, char * const argv[])
{
    if(nullptr == argv) return 1;
    if(0 == argc) return 1;

    compile_assert(argv != nullptr, "check main() argv not nullptr");

/*
    // This approach doesn't work, because the constructor is checked before the optimizer
    // realizes that a few lines above the argv pointer was already checked.
    if(argv != nullptr)
    {
        never_null_ptr<const char> abc("hello");
    }
    else
    {
        never_null_ptr<const char> abc(nullptr);
    }
*/

    const char * str = argv[0];

    //  This line is the fix
    if(str == nullptr) return 1;

    // This line forces a check on the pointer by the calling code
    never_null_ptr<const char> abc(str);


    f(abc);

    return 0;
}
