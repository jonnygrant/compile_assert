// https://godbolt.org/z/v7dbff3qY

// cl /O2 /D__ENABLE_COMPILE_ASSERT__ /DCOMPILE_FILE=__FILE_msvc_cpp_

[[deprecated("msvc")]] void _compile_assert_fail();

#define compile_assert2(expr, msg) \
    do { \
        if (!(expr)) { \
            __assume(0); \
        } \
    } while(0)

#define compile_assert(expression, message) \
    do { \
            if (!(expression)) { \
            _compile_assert_fail(); \
        } \
    } while (0)

// Before C++14 MSVC used
// __declspec(deprecated("message"))
int main()
{
    int a = 1;


// using compile_assert2 gives a return code of 2147483651
// from the compiler, but no useful diagnostics
    compile_assert2(a == 2, "error");
}

