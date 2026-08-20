// https://godbolt.org/z/5TfKa1j6q

// gcc -Wall -o gas_assert gas_assert.c

#define STR2(x) #x
#define STR(x) STR2(x)

#define GNU_AS_ERROR(msg) \
    __asm__ volatile (".error \"" __FILE__ ":" STR(__LINE__) " *** gas_assert: " msg " "   "***\"" )

int main()
{
    int a = 1;

    if(a != 2) GNU_AS_ERROR("a was not 2");
}
