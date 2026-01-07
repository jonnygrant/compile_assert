// g++ -Wall -O3 -o main16 main16.cpp
// g++ -g -pipe -pthread -O3 -march=native --std=c++23 -fno-delete-null-pointer-checks -D_FORTIFY_SOURCE=2 -D_GLIBCXX_ASSERTIONS -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fexceptions -Wall -Wextra -Werror -Werror=format-security -Wpointer-arith -pedantic -Wpedantic -Wformat=2 -Wshadow -Wvla -Wformat-nonliteral -Wnonnull -Winit-self -Wuninitialized -Wconversion -Wconversion-null -Wdiv-by-zero -Wsign-conversion -Wnull-dereference -Wunused-parameter -Wformat-security -Wundef -Wunused-macros -Wpointer-compare -Wcast-align -Wswitch-unreachable -Wmaybe-uninitialized -Wno-nonnull-compare -Wformat-truncation=1 -Wstringop-truncation -Wformat-overflow=2 -Wformat-signedness -Wformat-security -pedantic-errors -Wdangling-else -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast -Wdouble-promotion -Wbool-compare -fmax-errors=2 -Wno-restrict -Wanalyzer-use-of-uninitialized-value -Wanalyzer-null-argument -Wanalyzer-possible-null-argument -Wanalyzer-possible-null-dereference -Wanalyzer-null-dereference -Wanalyzer-malloc-leak  -o main16 main16.cpp

#include "compile_assert.h"

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

    const char * str = argv[0];

    //  This line is the fix
    //if(str == nullptr) return 1;

    // This line forces a check on the pointer by the calling code
    never_null_ptr<const char> abc(str);

    f(abc);

    return 0;
}
