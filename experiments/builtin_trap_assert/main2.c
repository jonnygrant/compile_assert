// Martin Uecker's __builtin_trap() approach.
// Relies upon UBSan "null" instrumentation that calls __builtin_trap()
//
// Attributes require C23, which was c2x until finalised
//
// gcc -O2 -g -std=c2x -Wall -fsanitize=null -fsanitize-trap=null -Wno-error=maybe-uninitialized -o trap2.bin main2.c


// With optimization:

/*
$ gcc -O2 -g -std=c2x -Wall -fsanitize=null -fsanitize-trap=null -Wno-error=maybe-uninitialized -o trap2.bin main2.c
main2.c: In function ‘main’:
main2.c:27:12: warning: call to ‘__builtin_trap’ declared with attribute warning: WARN potential null pointer dereference [-Wattribute-warning]
   27 |     buf[0] = 'a';
      |     ~~~~~~~^~~~~
*/

// without optimization, both locations are reachable
/*
$ gcc -g -std=c2x -Wall -fsanitize=null -fsanitize-trap=null -Wno-error=maybe-uninitialized -o trap2.bin main2.c
main2.c: In function ‘main’:
main2.c:24:14: warning: call to ‘__builtin_trap’ declared with attribute warning: WARN potential null pointer dereference [-Wattribute-warning]
   24 |         *buf = 'b';
      |         ~~~~~^~~~~
main2.c:27:12: warning: call to ‘__builtin_trap’ declared with attribute warning: WARN potential null pointer dereference [-Wattribute-warning]
   27 |     buf[0] = 'a';
      |     ~~~~~~~^~~~~
*/


[[gnu::warning("WARN potential null pointer dereference")]] void __builtin_trap();

int main()
{
    char * buf = nullptr;

    if(buf != nullptr)
    {
        *buf = 'b';
    }

    buf[0] = 'a';

    return 0;
}
