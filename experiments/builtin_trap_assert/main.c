// Martin Uecker's __builtin_trap() approach.
// Relies upon UBSan "null" instrumentation that calls __builtin_trap()
//
// Martin's original example
// https://godbolt.org/z/4K4s44h3T
//
// Attributes require C23, which was c2x until finalised
//
// gcc -g -std=c2x -Wall -fsanitize=null -fsanitize-trap=null -Wno-error=maybe-uninitialized -o trap.bin main.c

/*
main.c: In function ‘main’:
main.c:15:12: error: call to ‘__builtin_trap’ declared with attribute error: Error potential null pointer dereference
   15 |     buf[0] = 'a';
      |     ~~~~~~~^~~~~
*/



[[gnu::warning("WARN potential null pointer dereference")]] void __builtin_trap();

int main()
{
    char * buf = nullptr;
    buf[0] = 'a';

    return 0;
}
