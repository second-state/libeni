### 1.0.x (pre-released)

Features:
  * all: Add license information to the beginning of all source code.
  * all: Setup building system with CMake.
  * eni: Refine interface.
  * eni: Add a Caesar Cipher example.
  * json: Support unicode `string`.
  * test: Integrate SkyPat as the main testing framework and support running
    tests with CTest.

Bug fixes:
  * eni: '\0' problem is resolved by JSON printer and parser.
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
