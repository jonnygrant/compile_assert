//  gcc --std=c++23 -O2 -Wall -Wno-nonnull -o concepts_assert concepts_assert.cpp

#include <iostream>
#include <concepts>
#include <type_traits>
#include <utility>

// Concept: function must return exactly bool
template<typename F, typename... Args>
concept ReturnsBool =
    std::same_as<std::invoke_result_t<F, Args...>, bool>;

// Constrained function
template<typename F, typename... Args>
requires ReturnsBool<F, Args...>
void call(F f, Args&&... args)
{
    bool result = f(std::forward<Args>(args)...);
    std::cout << "Function returned: " << std::boolalpha << result << '\n';
}

// Test functions
bool good()
{
    return true;
}

int bad()
{
    return 42;
}

#define compile_assert(expression, message) \
    do { \
        if (!(expression)) { \
            call(bad); \
        } \
    } while (0)

int main()
{
    const char * buf = "hello";

    if(buf)
    {
        call(good);
    }
    else
    {
        call(bad);
    }

    //compile_assert(buf == nullptr, "");

    return 0;
}
