# compile_assert
Demonstrate how compiler asserts can be implemented, these are evaluated at build time in an optimized build, not at runtime. This saves runtime performance. It is implemented in compile_assert.h and works well in C/C++.

There are limitations, like the need for the compiler to verify all paths to the static function, so the public API is obliged to check parameters, before passing them to the private static API.

I'll write a few examples, which demonstrate how it works. NB, these examples aren't production code.

I'm also interested to hear any other approaches that work at compile time (not simply using a static analyzer), and which don't add runtime assert() and such things.

These compiler asserts draw attention to code paths that are able to pass invalid parameters by stopping the build. It's a way for an programmer to specify the constraints, the prerequisites of the function or class. When they're not 100% met the build error gives an opportunity for a programmer to address the issue.

# description of each example

These are example issues that compile_assert() detects, giving the programmer opportunity to take remedial action(s).

main.c - showcases a compile_assert within a static function, compelling the calling code to verify the validity of arguments before calling.

main2.c - demonstrates compile_never_null, enabling the calling code to validate pointer arguments prior to passing, resulting in a compile error pinpointing the issue at main2.c:22, providing clearer location for programmers to identify and mitigate the cause.

main3.c - illustrates the use of compile_assert to validate that a given percentage falls within the acceptable range of 0 to 100%.

main4.c - demonstrates compile_assert ensuring all indices accessing an array remain within the specified bounds of the array.

main5.c - demonstrate compile_assert checking array access via annother array of offset indices into that array are within bounds.

main6.c - demonstrate compile_assert checking a TGA image data file header is valid.

main7.cpp - demonstrates using compile_assert to validate the size of an std::string object.

main8.c - demonstrate static_assert to checking all indices into an array are within bounds. Note this does not work, as data needs to be constexpr (that is the fix).

main9.c - demonstrate compile_assert checking with multiple conditions.

main10.c - demonstrate compile_assert checking array ranges, based on values computed at runtime.

main11.c - demonstrate compile_assert checking array ranges, based on values read from a file.

main12. c - demonstrate compile_assert checking an offset resovled to a pointer is within the range bounds of a buffer (avoids buffer overruns) at runtime.

main13.c - demonstrates how compile_assert can be used with multi file projects. The two files are compiled to objects, and then linked.


# avoiding buffer overflows
main11.c illustrates the potential for a buffer overrun when loading data from a file if the input range is not adequately validated. Buffer overruns constitute frequent triggers for cybersecurity incidents, as observed in various third-party libraries like WebP and others.

# notes
The use of compile_assert doesn't preclude the use of runtime checks, runtime input validation - after-all, software that loads a PNG image file, can't validate the header and file is appropriately sized at compile time (yet). In the future, perhaps compilers will be able to validate buffers in linker sections at compile time, or simpler might be #include "myimage_buf.h" and use compile_assert to check it at build time (there is the #embed proposal). Of course, can specify some constraints, like max image size, on the static function, and force the calling code to check those requirements.

I believe a project with many C/C++ files may need to compile all the files on the same GCC command line to give it full program visibility. That could reach some memory limit.  An alternative, might be to build each module as a separate ELF executable. Then a main program could invoke it with data in a file to process, and collect the results of in another file.  For instance, a compression tool could be in a binary, separate from the UI binary.

I've only found a way to put the compile_assert within static functions in optimized builds, otherwise the compiler can't validate that all calling locations are truly validating their inputs passed to the checked static function at compile time.

compile_assert(condition, description) where description is not logged, it is an easy way for a programmer to include a note explaining why there is this compile time check, they can write "" if they really don't need to explain.  It's implemented as a macro, rather than inline. If it was an inline function, the compiler error would display the file and line number as the inline function from the header.


# future
Add support for multiple conditions in the same compile_assert
