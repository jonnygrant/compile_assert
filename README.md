# compile_assert
Demonstrate how compiler asserts can be implemented, these are evaluated at build time in an optimized build, not at runtime. This saves runtime performance.

There are limitations, like the need for the compiler to verify all paths to the static function, so the public API is obliged to check parameters, before passing them to the private static API

I'll write a few examples, which demonstrate how it works.

I'm also interested to hear any other approaches that work at compile time (not simply using a static analyzer), and which don't add runtime assert() and such things.

