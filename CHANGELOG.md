### 1.3.0

Features:
  * adt: Refactor `StringMap` interface.
  * docs: Update SHA512 usage and add platform-specific prerequisites.
  * json: Refactor `json::Object`, inherit from `eni::StringMap` instead
    of `std::map`.
  * json: Refactor `json::Array`, inherit from `eni::Vector` instead of
    `std::vector`.

Bug fixes:
  * adt: Fix several bugs in `HashIterator`.

Known issues:
  * all: Current building system does not support Mac OSX.


### 1.2.x (pre-release)

Features:
  * all: Generate SHA512 checksum for all ENI libraries.
  * all: Add our own `Exception`.
  * all: Refactor all C-style asserts and exceptions to use `Exception`.
  * adt: Add our own abstract data types `StringMap`, `HashIterator`, `Vector`,
    and `PointerIterator`.
  * json: Exit when parsing error.

Bug fixes:
  * json: Fix implicit casting to `bool` when constructing a `json::Value` from
    `char*` or `int`.
  * test: Fix memory leak in ScryptTest.

Known issues:
  * all: Current building system does not support Mac OSX.
  * adt: Interface for `HashTable` and its descendents is very inconvenient.

### 1.2.0

Features:
  * all: Change C interface of libENI.
  * all: Update documentations and deploy to [ReadTheDocs].
  * tools: The second ENI package, `eni_scrypt`, which implements the Scrypt
    hash algorithm.

Known issues:
  * all: Current building system does not support Mac OSX.

[ReadTheDocs]: https://lity.readthedocs.io/projects/libeni/


### 1.1.0

Features:
  * tools: Add command line tools `eni_gas` and `eni_run` for testing ENI
    libraries.
  * test: Create regression tests for ENI libraries (including examples)
    using the new CLIs `eni_gas` and `eni_run`.

Bug fixes:
  * all: Fix several memory issues.
  * json: Change array and object to privately inherit from STL containers
    to prevent potential memory leak.
  * json: Use `at` instead of `operator[]` to access `std::vector` to avoid
    potential undefined behavior.

Known issues:
  * all: Current building system does not support Mac OSX.


### 1.0.x (pre-release)

Features:
  * all: Add license information to the beginning of all source code.
  * all: Setup building system with CMake.
  * eni: Refine interface.
  * eni: Add a Caesar Cipher example.
  * json: Support unicode `string`.
  * test: Integrate SkyPat as the main testing framework and support running
    tests with CTest.

Bug fixes:
  * eni: `'\0'` problem is resolved by JSON printer and parser.
  * json: Fix memory leak in destructors.

Known issues:
  * all: Current building system does not support Mac OSX.


### 1.0.0

Features:
 * eni: Define the C++ interface `EniBase`.
 * eni: Define the C interface (`${op}_create`, `eni_gas`, `eni_run`,
   `${op}_destroy` for an ENI operation `${op}`).
 * json: Support basic ENI types `boolean`, `string` (ASCII only),
   `number` (256-bit), `array`, `object`.
 * json: Extend the definition for `string` to support all ASCII characters,
   including backslash, newline, and double-quote.
 * tools: The first ENI package, `eni_crypto`, which supports RSA encryption
   and decryption using the OpenSSL library.

Known issues:
 * eni: The C interface currently takes string as NULL-terminated string.
   Passing string that contains `'\0'` to ENI will result in errors.
 * json: Converting from a `json::Value` to string (print) may contain
   redundant white-spaces.
