# compile_assert
Demonstrate how compiler asserts can be implemented, these are evaluated at build time in an optimized build, not at runtime! It is implemented in compile_assert.h and works well in C/C++.

There are limitations, like where the compile_assert is within a function, it must be static so the compiler can verify all paths (means can't put checks within a public interface API) as the compiler needs to verify all paths to the a function, so the public API is obliged to check parameters, before passing them to the private static API. example 13 shows how to provide a checked public API, that helps by putting the API checks, all on the caller's side of the code, rather than the callee (the implemented API function).

I'll write a few examples, which demonstrate how it can work. NB, these examples aren't production code.

I'm also interested to hear any other approaches that work at compile time (not simply using a static analyzer), and which don't add runtime assert() and such things.

These compiler asserts draw attention to code paths that are able to pass invalid parameters by stopping the build. It's a way for an programmer to specify the constraints, the prerequisites of the function or class. When they're not 100% met the build error gives an opportunity for a programmer to address the issue.  Remedial action can be taken, to make the that code safer and more secure.

# description of each example

These are example issues that compile_assert() detects, giving the programmer opportunity to take remedial action(s).

main.c - showcases a compile_assert within a static function, compelling the calling code to verify the validity of arguments before calling.

main2.c - demonstrates compile_never_null, enabling the calling code to validate pointer arguments prior to passing, resulting in a compile error pinpointing the issue at main2.c:22, providing clearer location for programmers to identify and mitigate the cause.

main3.c - illustrates the use of compile_assert to validate that a given percentage falls within the acceptable range of 0 to 100%.

main4.c - demonstrates compile_assert ensuring all indices accessing an array remain within the specified bounds of the array.

main5.c - demonstrate compile_assert checking array access via another array of offset indices into that array are within bounds.

main6.c - demonstrate compile_assert checking a TGA image data file header is valid.

main7.cpp - demonstrates using compile_assert to validate the size of an std::string object.

main8.c - demonstrate static_assert to checking all indices into an array are within bounds. Note this does not work, as data needs to be constexpr (that is the fix).

main9.c - demonstrate compile_assert checking with multiple conditions.

main10.c - demonstrate compile_assert checking array ranges, based on values computed at runtime.

main11.c - demonstrate compile_assert checking array ranges, based on values read from a file.

main12. c - demonstrate compile_assert checking an offset resolved to a pointer is within the range bounds of a buffer (avoids buffer overruns) at runtime.

main13.c - demonstrates how compile_assert can be used with multi file projects. The two files are compiled to objects, and then linked.

# avoiding buffer overflows
main11.c illustrates the potential for a buffer overrun when loading data from a file if the input range is not adequately validated. Buffer overruns constitute frequent triggers for cybersecurity incidents, as observed in various third-party libraries like WebP and others.

# notes

compile_assert is best at converting runtime checks, and assert() into compile time checks. Of course it can only do this where it can satisfy the conditions. It's no use trying to compile_assert the size of a file downloaded from the internet at runtime. Where used, compile_assert is very good at drawing attention to logic errors not covered by code. Now, some code covers intractable problems, so while the compiler can't compute, if the programmer has some offline proof that say an array will never be overrun by a bad index, checking the bounds of the array index check could be skipped. However, in practice these index range checks if called infrequently per second, will not be perceivable to users, and the benefits avoiding overruns will outweigh the risks of not having the checks (security vulnerabilities, like in WebP where a variable amount of compressed data was not meant to exceed the bounds of a fixed sized array when decoded).

It's important to consider candidates for compile_assert(), assess if it's reasonable to make changes to satisify the issue identified. assert() is usually a good candidate to replace. Not all candiates are suitable for compile_assert().

The use of compile_assert doesn't preclude the use of runtime checks, runtime input validation - after-all, software that loads a PNG image file, can't validate the header and file is appropriately sized at compile time (yet). In the future, perhaps compilers will be able to validate buffers in linker sections at compile time, or simpler might be #include "myimage_buf.h" and use compile_assert to check it at build time (there is the #embed proposal). Of course, can specify some constraints, like max image size, on the static function, and force the calling code to check those requirements.

I believe a project with many C/C++ files may need to compile all the files on the same GCC command line to give it full program visibility. That could reach some memory limit.  An alternative, might be to build each module as a separate ELF executable. Then a main program could invoke it with data in a file to process, and collect the results of in another file.  For instance, a compression tool could be in a binary, separate from the UI binary.

I've only found a way to put the compile_assert within static functions in optimized builds, otherwise the compiler can't validate that all calling locations are truly validating their inputs passed to the checked static function at compile time.

compile_assert(condition, description) where description is not logged, it is an easy way for a programmer to include a note explaining why there is this compile time check, they can write "" if they really don't need to explain.  It's implemented as a macro, rather than inline. If it was an inline function, the compiler error would display the file and line number as the inline function from the header.

# sample output main13 library API example
```C
$ make
gcc -Wall -Wextra -O3 -std=c11 -c -o main13.o main13.c
In file included from main13.c:8:
main13.c: In function ‘main’:
<snip>
main13_api.h:14:5: note: in expansion of macro ‘compile_assert’
   14 |     compile_assert((str != NULL), "cannot be NULL"); \
      |     ^~~~~~~~~~~~~~
main13.c:16:5: note: in expansion of macro ‘log_api’
   16 |     log_api(str);
      |     ^~~~~~~
make: *** [makefile:17: main13.o] Error 1
```

# compile_assert compared to UBSAN

gcc has -fsanitize=undefined

```
UBSAN: array-index-out-of-bounds in ~/app/src/app.c:4000
index 4 is out of range of type 'SUP [1]'
```

main10 checks index before accessing the array, and reports as follows:

```
main10.c:23:9: note: in expansion of macro ‘compile_assert’
   23 |         compile_assert(buf[i] < buf_count_capacity, "check array bounds");
```
compile_assert can only detect those conditions the programmer asserts at compile time.


# uses
compile_assert is useful for infosec, cyber security, cyber-resilience, safety critical software validation and functional safety.

There are plenty of standards:

ISO 26262 Automotive Functional Safety.
ISO 27001 Information security, cybersecurity and privacy protection.
ISO 29147 Information technology Security techniques.
ISO 30111 Information technology Security techniques Vulnerability handling processes.

compile_assert is about increasing security and stability to an acceptable level.


# future
Add more examples.

Try out on more large projects and codebases.

There are cases where a compiler's optimizer has "compiled out" some needed code, compile_assert could be put in, to validate that the check was retained eg a NULL pointer check.
