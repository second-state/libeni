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
