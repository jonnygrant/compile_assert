# compile_assert
Demonstrate how compiler asserts can be implemented, these are evaluated at build time in an optimized build, not at runtime. This saves runtime performance.

There are limitations, like the need for the compiler to verify all paths to the static function, so the public API is obliged to check parameters, before passing them to the private static API.

I'll write a few examples, which demonstrate how it works.

I'm also interested to hear any other approaches that work at compile time (not simply using a static analyzer), and which don't add runtime assert() and such things.

# notes
The use of compile_assert doesn't preclude the use of runtime checks, runtime input validation - after-all, software that loads a PNG image file, can't validate the header and file is appropriately sized at compile time (yet). In the future, perhaps compilers will be able to validate buffers in linker sections at compile time, or simpler might be #include "myimage_buf.h" and use compile_assert to check it at build time. Of course, can specify some constraints, like max image size, on the static function, and force the calling code to check those requirements.

I believe a project with many C/C++ files will need to compile them all on the same GCC command line to give it full program visibility. That could reach some memory limit.  An alternative, might be to build each module as a separate ELF executable. Then a main program could invoke it with data in a file to process, and collect the results of in another file.  For instance, a compression tool could be in a binary, separate from the UI binary.

I've only found a way to put the compile_assert within static functions in optimized builds, otherwise the compiler can't validate that all calling locations are truly validating their inputs passed to the checked static function at compile time.


# future
Add support for multiple conditions in the same compile_assert
