// Martin Uecker's __builtin_trap() approach.
// Relies upon UBSan "null" instrumentation that calls __builtin_trap()
//
// Attributes require C23, which was c2x until finalised
//
// gcc -std=c2x -Wall -fsanitize=null -fsanitize-trap=null -Wno-error=maybe-uninitialized -o trap main.c

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
