# compile_assert() testsuite — portable across GCC, Clang and MSVC.
#
# Each example ships as a pair:
#   *_a  the un-fixed version   -> the build MUST fail  (compile error on GCC/Clang,
#                                   unresolved-symbol link error on MSVC)
#   *_b  the fixed version      -> the build MUST succeed
#
# compile_assert() only fires in an *optimized* build (it relies on dead-code
# elimination), so every test target is compiled with -O2 / /O2 regardless of the
# CMake configuration.
#
# The "must fail" tests are registered with the CTest WILL_FAIL property: CTest
# drives the per-target build itself, so a failing compile/link is reported as a
# passing test. Run with:
#
#   cmake -S . -B build
#   ctest --test-dir build --output-on-failure -C Release
#
cmake_minimum_required(VERSION 3.21)
project(compile_assert_testsuite C CXX)

enable_testing()

# compile_assert relies on optimization; a Debug build injects /Od /Ob0 (no inlining)
# which defeats the constant propagation it needs. Default single-config generators
# to Release. (We also force -O2/-O2 per target below as a belt-and-braces guard.)
get_property(_ca_multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(NOT _ca_multi_config AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CA_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")

# Default the language levels; individual tests override where they need newer.
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 20)

# Force an optimized build per target so results don't depend on the chosen config.
if(MSVC)
  set(CA_OPT_FLAGS /O2)
  # Debug configs inject /RTC1, which is incompatible with /O2; strip it so the
  # suite behaves identically in every configuration.
  string(REGEX REPLACE "/RTC[1csu]+" "" CMAKE_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS_DEBUG}")
  string(REGEX REPLACE "/RTC[1csu]+" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
else()
  set(CA_OPT_FLAGS -O2)
endif()

# ca_test(NAME <name> EXPECT compile|nocompile
#         SOURCES <files...>
#         [CXX_STANDARD <n>] [C_STANDARD <n>]
#         [DEFINES <d>...]
#         [GNU_OPTIONS <o>...] [MSVC_OPTIONS <o>...]
#         [LTO]
#         [COMPILERS GNU Clang MSVC])   # restrict to a subset; default = all
function(ca_test)
  cmake_parse_arguments(T
    "LTO"
    "NAME;EXPECT"
    "SOURCES;DEFINES;GNU_OPTIONS;MSVC_OPTIONS;COMPILERS;CXX_STANDARD;C_STANDARD"
    ${ARGN})

  # Skip tests that exercise features a given compiler does not implement
  # (e.g. compile_assert_const_p / _never_null and GNU builtins are GCC/Clang only).
  if(T_COMPILERS)
    set(_id "${CMAKE_CXX_COMPILER_ID}")
    if(NOT _id IN_LIST T_COMPILERS)
      message(STATUS "compile_assert: skipping ${T_NAME} (not applicable to ${_id})")
      return()
    endif()
  endif()

  add_executable(${T_NAME} EXCLUDE_FROM_ALL ${T_SOURCES})
  target_include_directories(${T_NAME} PRIVATE ${CA_INCLUDE_DIR})
  target_compile_definitions(${T_NAME} PRIVATE __ENABLE_COMPILE_ASSERT__ ${T_DEFINES})
  target_compile_options(${T_NAME} PRIVATE ${CA_OPT_FLAGS})

  if(T_CXX_STANDARD)
    set_target_properties(${T_NAME} PROPERTIES CXX_STANDARD ${T_CXX_STANDARD} CXX_STANDARD_REQUIRED ON)
  endif()
  if(T_C_STANDARD)
    set_target_properties(${T_NAME} PROPERTIES C_STANDARD ${T_C_STANDARD} C_STANDARD_REQUIRED ON)
  endif()

  if(MSVC)
    # The MSVC path builds the failure symbol name from a per-file token.
    target_compile_definitions(${T_NAME} PRIVATE COMPILE_FILE=__FILE_${T_NAME}_)
    target_compile_options(${T_NAME} PRIVATE ${T_MSVC_OPTIONS})
    # CMake 3.27 does not map C_STANDARD 23 to an MSVC flag (it falls back to c17), so
    # request the latest C mode explicitly for C sources. (Note: this MSVC still rejects
    # the C23 nullptr keyword even here, so tests that use it stay GCC/Clang only.)
    target_compile_options(${T_NAME} PRIVATE $<$<COMPILE_LANGUAGE:C>:/std:clatest>)
  else()
    target_compile_options(${T_NAME} PRIVATE ${T_GNU_OPTIONS})
  endif()

  if(T_LTO)
    set_target_properties(${T_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
  endif()

  # CTest builds the target on demand; a failing build == a nonzero exit code.
  add_test(NAME ${T_NAME}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --config $<CONFIG> --target ${T_NAME})

  if(T_EXPECT STREQUAL "nocompile")
    set_tests_properties(${T_NAME} PROPERTIES WILL_FAIL TRUE)
  endif()
endfunction()

# --- C tests, base compile_assert() (portable) -------------------------------
# GENUINE MSVC FAILURE: main1_a uses the C23 nullptr keyword, which this MSVC C mode rejects
# even under /std:clatest (error C2065). main1_b is valid code, but MSVC /O2 will not fold
# "Hello"[0]=='H' through the pointer (even after inlining), leaving the failure symbol
# unresolved (LNK2019); GCC/Clang propagate the constant and drop it. Both GCC/Clang only.
ca_test(NAME main1_a EXPECT nocompile SOURCES main1_a.c GNU_OPTIONS -Wno-nonnull COMPILERS GNU Clang)
ca_test(NAME main1_b EXPECT compile   SOURCES main1_b.c GNU_OPTIONS -Wno-nonnull COMPILERS GNU Clang)
ca_test(NAME main3_a EXPECT nocompile SOURCES main3_a.c)
ca_test(NAME main3_b EXPECT compile   SOURCES main3_b.c)
# GENUINE MSVC FAILURE: both versions use a variable-length array (char buf[const int]),
# which MSVC does not support (error C2466) regardless of compile_assert. GCC/Clang only.
ca_test(NAME main4_a EXPECT nocompile SOURCES main4_a.c COMPILERS GNU Clang)
ca_test(NAME main4_b EXPECT compile   SOURCES main4_b.c COMPILERS GNU Clang)
# GENUINE MSVC FAILURE: both versions use VLAs (size_t buf[const size_t]); MSVC has no
# VLA support (error C2466) regardless of compile_assert. GCC/Clang only.
ca_test(NAME main5_a EXPECT nocompile SOURCES main5_a.c COMPILERS GNU Clang)
ca_test(NAME main5_b EXPECT compile   SOURCES main5_b.c COMPILERS GNU Clang)
ca_test(NAME main6_a EXPECT nocompile SOURCES main6_a.c)
ca_test(NAME main6_b EXPECT compile   SOURCES main6_b.c)

# --- C++ tests, base compile_assert() (portable) -----------------------------
# GENUINE MSVC FAILURE: both versions need #include <string> for std::stoi (MSVC does not pull
# it in transitively -> error C2039/C3861), and even fixed, MSVC /O2 will not prove div != 0
# after the caller's guard, so the failure symbol stays unresolved. GCC/Clang only.
ca_test(NAME main17_a EXPECT nocompile SOURCES main17_a.cpp COMPILERS GNU Clang)
ca_test(NAME main17_b EXPECT compile   SOURCES main17_b.cpp COMPILERS GNU Clang)
# GENUINE MSVC FAILURE: broken code accepted. MSVC eliminates the failure call and links the
# program, so the assertion never fires (should NOT compile, but MSVC builds it). GCC/Clang only.
ca_test(NAME main24_a EXPECT nocompile SOURCES main24_a.cpp COMPILERS GNU Clang)
ca_test(NAME main24_b EXPECT compile   SOURCES main24_b.cpp)
# GENUINE MSVC FAILURE: broken code accepted (assertion eliminated by MSVC). GCC/Clang only.
ca_test(NAME main25_a EXPECT nocompile SOURCES main25_a.cpp COMPILERS GNU Clang)
ca_test(NAME main25_b EXPECT compile   SOURCES main25_b.cpp)
# GENUINE MSVC FAILURE: broken code accepted (assertion eliminated by MSVC). GCC/Clang only.
ca_test(NAME main28_a EXPECT nocompile SOURCES main28_a.cpp CXX_STANDARD 23 COMPILERS GNU Clang)
ca_test(NAME main28_b EXPECT compile   SOURCES main28_b.cpp CXX_STANDARD 23)
# GENUINE MSVC FAILURE: broken code accepted (assertion eliminated by MSVC). GCC/Clang only.
ca_test(NAME test_30_web_a EXPECT nocompile SOURCES test_30_web_a.cpp CXX_STANDARD 23 COMPILERS GNU Clang)
ca_test(NAME test_30_web_b EXPECT compile   SOURCES test_30_web_b.cpp CXX_STANDARD 23)

# --- GCC/Clang-only tests ----------------------------------------------------
# compile_assert_never_null()
ca_test(NAME main2_a EXPECT nocompile SOURCES main2_a.c GNU_OPTIONS -Wno-nonnull COMPILERS GNU Clang)
ca_test(NAME main2_b EXPECT compile   SOURCES main2_b.c GNU_OPTIONS -Wno-nonnull COMPILERS GNU Clang)

# [[gnu::noinline]] constant-propagation demo
ca_test(NAME test_20_inline_a EXPECT nocompile SOURCES test_20_inline_a.cpp COMPILERS GNU Clang)

# Link-time (LTO) cross-TU assertion, uses __builtin_printf
ca_test(NAME main29_a EXPECT nocompile LTO SOURCES test_29_lto1_a.c test_29_lto2_a.c
        DEFINES LINKMSG COMPILERS GNU Clang)
ca_test(NAME main29_b EXPECT compile   LTO SOURCES test_29_lto1_b.c test_29_lto2_b.c
        DEFINES LINKMSG COMPILERS GNU Clang)

# compile_assert_const_p()
ca_test(NAME test_31_const_p_a EXPECT nocompile SOURCES test_31_const_p_a.c COMPILERS GNU Clang)
ca_test(NAME test_31_const_p_b EXPECT compile   SOURCES test_31_const_p_b.c COMPILERS GNU Clang)
ca_test(NAME test_32_div_zero_a EXPECT nocompile SOURCES test_32_div_zero_a.c
        GNU_OPTIONS -Wno-div-by-zero COMPILERS GNU Clang)
ca_test(NAME test_32_div_zero_b EXPECT compile   SOURCES test_32_div_zero_b.c
        GNU_OPTIONS -Wno-div-by-zero COMPILERS GNU Clang)
