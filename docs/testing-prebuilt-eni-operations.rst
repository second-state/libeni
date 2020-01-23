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

Test "eni_crypto.so" (`tools/eni_crypto`)
`````````````````````````````````````````

Get the JSON files for testing from the directory
`test/t0004 <https://github.com/second-state/libeni/tree/master/test/t0004>`_.

.. code:: bash

  eni_gas ${LIBENI_PATH}/lib/eni_crypto.so rsa_encrypt "$(cat pub_encrypt.json)"
  eni_run ${LIBENI_PATH}/lib/eni_crypto.so rsa_encrypt "$(cat pub_encrypt.json)"
  eni_gas ${LIBENI_PATH}/lib/eni_crypto.so rsa_decrypt "$(cat priv_decrypt.json)"
  eni_run ${LIBENI_PATH}/lib/eni_crypto.so rsa_decrypt "$(cat priv_decrypt.json)"

Output for the above lines.

.. code:: bash

  12
  ["An encrypted hex-string that is 512 characters in length."]
  256
  ["Hello World!"]

Test "eni_scrypt.so" (`tools/eni_scrypt`)
`````````````````````````````````````````

.. code:: bash

  eni_gas ${LIBENI_PATH}/lib/eni_scrypt.so scrypt '["00"]'
  eni_run ${LIBENI_PATH}/lib/eni_scrypt.so scrypt '["00"]'

Output for the above lines.

.. code:: bash

  2
  ["161d0876f3b93b1048cda1bdeaa7332ee210f7131b42013cb43913a6553a4b69"]
