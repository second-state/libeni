Library for ENI (Ethereum Native Interface)
===========================================

The C++ implementation for libeni.

## Directory Structure

| Path          | Description                                     |
| ------------- | ----------------------------------------------- |
| include/      | Header files for this library.                  |
| lib/          | Implementations for this library.               |
| examples/     | Demonstrate how to use this library.            |
| CMakeList.txt | Makefile for this library.                      |
| CHANGELOG.md  | Change logs for each released versions.         |
| README.md     | This file.                                      |

## Prerequisites

- CMake >= 3.1
- OpenSSL >= 1.0

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
The output looks like the below.

```
Test project libeni/build
    Start 1: examples_json
1/5 Test #1: examples_json ....................   Passed    0.00 sec
    Start 2: examples_eni
2/5 Test #2: examples_eni .....................   Passed    0.00 sec
    Start 3: examples_crypto
3/5 Test #3: examples_crypto ..................   Passed    0.00 sec
    Start 4: test_eni_crypto_hex
4/5 Test #4: test_eni_crypto_hex ..............   Passed    0.00 sec
    Start 5: test_eni_crypto_rsa
5/5 Test #5: test_eni_crypto_rsa ..............   Passed    0.00 sec

100% tests passed, 0 tests failed out of 5
```

## Attribution
- [Icon](https://commons.wikimedia.org/wiki/File:Creative-Tail-pulse.svg)
