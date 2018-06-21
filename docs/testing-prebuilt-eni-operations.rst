===============================
Testing Prebuilt ENI Operations
===============================

See :doc:`Testing ENI Operations <testing-eni-operations>` for more details.

Test Prebuilt Shared Libraries
------------------------------

Here we demonstrate how to test the ENI operation built from our examples
and tools with the CLI tools `eni_gas` and `eni_run`.

Test "eni_reverse.so" (`examples/eni/reverse`)
``````````````````````````````````````````````

.. code:: bash

  eni_gas ${LIBENI_PATH}/lib/eni_reverse.so reverse '["Hello World!"]'
  eni_run ${LIBENI_PATH}/lib/eni_reverse.so reverse '["Hello World!"]'

The first call `eni_gas` will output `12`, and
the second one `eni_run` will output `["!dlroW olleH"]`.

Test "eni_caesar_cipher.so" (`examples/eni/caesar_cipher`)
``````````````````````````````````````````````````````````

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

Test "eni_crypto.so" (`tools/eni_crypto`)
`````````````````````````````````````````

Get the JSON files for testing from the directory `test/t0004 <test/t0004>`_.

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
