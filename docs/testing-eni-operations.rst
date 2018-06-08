======================
Testing ENI Operations
======================

Setup Environment
-----------------

Make sure `libeni` can be found in your environment.
See `Getting Started <docs/getting-started.rst>`_ for how to install `libeni`.

You might want to try the following settings if `libeni` is installed
but not found in your environment.

.. code:: bash

  PATH=${PATH}:${LIBENI_PATH}/bin
  LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${LIBENI_PATH}/lib

Tools for Testing
-----------------

We provide two CLI tools `eni_gas` and `eni_run`, which simulate how the ENI
operations are called in a shared library from EVM.

Test "eni_reverse.so"
`````````````````````

Here we demonstrate how to test the ENI operation `reverse` built from
`examples/eni/reverse` with the CLI tools `eni_gas` and `eni_run`.

.. code:: bash

  eni_gas ${LIBENI_PATH}/lib/eni_reverse.so reverse '["Hello World!"]'
  eni_run ${LIBENI_PATH}/lib/eni_reverse.so reverse '["Hello World!"]'

The first call `eni_gas` will output `12`, and
the second one `eni_run` will output `["!dlroW olleH"]`.

Test "eni_caesar_cipher.so"
```````````````````````````

.. code:: bash

  eni_gas ${LIBENI_PATH}/lib/eni_caesar_cipher.so caesar_encrypt '["Hello World!","HELLOGCC"]'
  eni_run ${LIBENI_PATH}/lib/eni_caesar_cipher.so caesar_encrypt '["Hello World!","HELLOGCC"]'
  eni_gas ${LIBENI_PATH}/lib/eni_caesar_cipher.so caesar_decrypt '["Olssv Dvysk!","HELLOGCC"]'
  eni_run ${LIBENI_PATH}/lib/eni_caesar_cipher.so caesar_decrypt '["Olssv Dvysk!","HELLOGCC"]'

Output for the above lines.

.. code:: bash

  12
  ["Olssv Dvysk!"]
  12
  ["Hello World!"]

Test "eni_crypto.so"
````````````````````

Get the JSON files for testing from the directory `test/t0004` in the source repository.

.. code:: bash

  eni_gas ${LIBENI_PATH}/lib/eni_crypto.so rsa_encrypt $(cat pub_encrypt.json)
  eni_run ${LIBENI_PATH}/lib/eni_crypto.so rsa_encrypt $(cat pub_encrypt.json)
  eni_gas ${LIBENI_PATH}/lib/eni_crypto.so rsa_decrypt $(cat priv_decrypt.json)
  eni_run ${LIBENI_PATH}/lib/eni_crypto.so rsa_decrypt $(cat priv_decrypt.json)

Output for the above lines.

.. code:: bash

  12
  ["An encrypted hex-string that is 512 characters in length."]
  256
  ["Hello World!"]
