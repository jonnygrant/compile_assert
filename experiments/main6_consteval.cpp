// g++ -std=c++23 -O2 -Wall -o main6_consteval main6_consteval.cpp

#include <cstdio>
#include <cstdint>
#include <cstddef>

// 18+16 bytes expected
constexpr uint8_t tga_file[] =
{
    0x00,
    0x00,
    0x02,
    0x00, 0x00,
    0x00, 0x00,
    0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x02, 0x00,
    0x02, 0x00,
    0x20,
    0x00,
    0x00, 0xFF, 0xFF, 0x00,
    0x00, 0xFF, 0xFF, 0x00,
    0x00, 0xFF, 0xFF, 0x00,
    0x00, 0xFF, 0xFF, 0x00,
    0x11 // deliberate bug
};

#if 0
consteval void validate_tga()
{
    if (tga_file[2] != 0x02)
        throw "Must be truecolor";

    if (sizeof(tga_file) != (16 + 18))
        throw "Must be the right size";
}

// Force compile-time execution
constexpr auto force_validation = (validate_tga(), 0);
#endif

constexpr void consteval_throw()
{
    throw "consteval_throw";
}

#define compile_assert(expression, message) \
    do { \
        if (!(expression)) { \
            consteval_throw(); \
        } \
    } while (0)





#if 0
consteval void compile_assert()
{
    char * buf = nullptr;

    if(buf == nullptr) throw "null";

    if(tga_file[2] != 0x02)
        throw "err";
}
#endif

consteval void compile_assert2(bool expr)
{
   // if(expr) throw "error";
}

void f(const char * buf)
{
    if(buf == nullptr) compile_assert(buf != nullptr, "");
    std::printf("%s\n", buf);
}

int main()
{
    constexpr char * buf = nullptr;

    f(buf);

    //compile_assert(buf == nullptr, "");

    std::printf("%d\n", tga_file[0]);
    return 0;
}
