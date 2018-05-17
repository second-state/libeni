Library for ENI (Ethereum Native Interface)
===========================================

The C++ implementation for libeni.

## Directory Structure

| Path          | Description                                     |
| ------------- | ----------------------------------------------- |
| include/      | Header files for this library.                  |
| lib/          | Implementations for this library.               |
| examples/     | Examples of how to use this library.            |
| test/         | Unit-tests for this library and its examples.   |
| tools/        | Tools and modules for this library.             |
| docs/         | Documentations.                                 |
| CMakeList.txt | The top-directory Makefile.                     |
| CHANGELOG.md  | Change logs for each released versions.         |
| LICENSE       | License file for the whole project.             |
| README.md     | This file.                                      |

## Prerequisites

- CMake >= 3.1
- OpenSSL >= 1.0
- SkyPat >= 3.1.1

## Build

Build libeni and all packages.

```
mkdir build
cd build
cmake ..
make
```

## Run Tests

In your build directory, run `ctest`.
The result looks like the below.

```
Test project /builds/cybermiles/libeni/build
    Start 1: crypto_tests
1/4 Test #1: crypto_tests .....................   Passed    0.00 sec
    Start 2: crypto_so_tests
2/4 Test #2: crypto_so_tests ..................   Passed    0.00 sec
    Start 3: json_tests
3/4 Test #3: json_tests .......................   Passed    0.00 sec
    Start 4: example_tests
4/4 Test #4: example_tests ....................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 4

Label Time Summary:
json          =   0.00 sec (1 test)
regression    =   0.00 sec (2 tests)
sharedlib     =   0.00 sec (2 tests)
unittest      =   0.01 sec (2 tests)

Total Test time (real) =   0.01 sec
```

See `Testing/Temporary/LastTest.log` for the detailed output of all tests.

## Attribution
- [Icon](https://commons.wikimedia.org/wiki/File:Creative-Tail-pulse.svg)
