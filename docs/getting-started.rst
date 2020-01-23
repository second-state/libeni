===============
Getting Started
===============

Download the Pre-built libENI
----------------------------

See `libENI releases <https://github.com/second-state/libeni/releases>`_
for the latest release.

- `libeni-dev`: for ENI operation developers
- `libeni`: for general ENI users.

Releases
````````
+---------+----------------------------+----------------------------+
| Version | libeni-dev                 | libeni                     |
+=========+============================+============================+
| v1.3.6_ | `Ubuntu 16.04 <ud136_>`__, | `Ubuntu 16.04 <uu136_>`__, |
|         | `CentOS 7 <cd136_>`__      | `CentOS 7 <cu136_>`__      |
+---------+----------------------------+----------------------------+
| v1.2.x_ | `Ubuntu 16.04 <ud12x_>`__, | `Ubuntu 16.04 <uu12x_>`__, |
|         | `CentOS 7 <cd12x_>`__      | `CentOS 7 <cu12x_>`__      |
+---------+----------------------------+----------------------------+
| v1.2.0_ | `Ubuntu 16.04 <ud120_>`__, | `Ubuntu 16.04 <uu120_>`__, |
|         | `CentOS 7 <cd120_>`__      | `CentOS 7 <cu120_>`__      |
+---------+----------------------------+----------------------------+

.. _v1.3.6: https://github.com/second-state/libeni/releases/tag/v1.3.6
.. _ud136: https://github.com/second-state/libeni/releases/download/v1.3.6/libeni-1.3.6-dev_ubuntu-16.04.tgz
.. _uu136: https://github.com/second-state/libeni/releases/download/v1.3.6/libeni-1.3.6_ubuntu-16.04.tgz
.. _cd136: https://github.com/second-state/libeni/releases/download/v1.3.6/libeni-1.3.6-dev_centos-7.tgz
.. _cu136: https://github.com/second-state/libeni/releases/download/v1.3.6/libeni-1.3.6_centos-7.tgz

.. _v1.2.x: https://github.com/second-state/libeni/releases/tag/v1.2.x
.. _ud12x: https://github.com/second-state/libeni/releases/download/v1.2.x/libeni-1.2.x-dev_ubuntu-16.04.tgz
.. _uu12x: https://github.com/second-state/libeni/releases/download/v1.2.x/libeni-1.2.x_ubuntu-16.04.tgz
.. _cd12x: https://github.com/second-state/libeni/releases/download/v1.2.x/libeni-1.2.x-dev_centos-7.tgz
.. _cu12x: https://github.com/second-state/libeni/releases/download/v1.2.x/libeni-1.2.x_centos-7.tgz

.. _v1.2.0: https://github.com/second-state/libeni/releases/tag/v1.2.0
.. _ud120: https://github.com/second-state/libeni/releases/download/v1.2.0/libeni-1.2.0-dev_ubuntu-16.04.tgz
.. _uu120: https://github.com/second-state/libeni/releases/download/v1.2.0/libeni-1.2.0_ubuntu-16.04.tgz
.. _cd120: https://github.com/second-state/libeni/releases/download/v1.2.0/libeni-1.2.0-dev_centos-7.tgz
.. _cu120: https://github.com/second-state/libeni/releases/download/v1.2.0/libeni-1.2.0_centos-7.tgz

Prerequisites
`````````````
+----------------------------+----------------------------+
| libeni-dev                 | libeni                     |
+============================+============================+
| - Boost >= 1.58            | - OpenSSL >= 1.0.2         |
| - OpenSSL >= 1.0.2         |                            |
+----------------------------+----------------------------+

See :doc:`Prerequisites <prerequisites>` for platform specific prerequisites guide.

Install
```````

.. code:: bash

  tar zxvf libeni.tgz --strip-components 1 -C ${LIBENI_PATH}

Validate the Shared Libraries
`````````````````````````````

.. code:: bash

  cd ${LIBENI_PATH}/lib
  sha512sum -c *.so.sha512

You should get a list of OKs if all libraries are good.

.. code:: bash

  eni_crypto.so: OK
  eni_reverse.so: OK
  eni_scrypt.so: OK

Test Manually
`````````````

See :doc:`Testing Prebuilt ENI Operations <testing-prebuilt-eni-operations>`
for how to test the prebuilt shared libraries of ENI operations.

Build From Source
-----------------

Prerequisites
`````````````

- Boost >= 1.58
- CMake >= 3.1
- OpenSSL >= 1.0.2
- SkyPat >= 3.1.1 (see `SkyPat releases <https://github.com/skymizer/SkyPat/releases/>`_)

Download Source Code
````````````````````

.. code:: bash

  git clone https://github.com/second-state/libeni.git ${LIBENI_PATH}
  git submodule update --init --recursive

Build with CMake
````````````````

.. code:: bash

  cd ${LIBENI_PATH}
  mkdir build
  cd build
  cmake ..
  make

Run Tests
`````````

In your build directory, run ``ctest``.
The result looks like the below.

.. code:: bash

  Test project ${LIBENI_PATH}/build
        Start  1: eni_reverse_checksum_test
   1/13 Test  #1: eni_reverse_checksum_test ........   Passed    0.00 sec
        Start  2: eni_crypto_checksum_test
   2/13 Test  #2: eni_crypto_checksum_test .........   Passed    0.00 sec
        Start  3: crypto_unittests
   3/13 Test  #3: crypto_unittests .................   Passed    0.01 sec
        Start  4: eni_scrypt_checksum_test
   4/13 Test  #4: eni_scrypt_checksum_test .........   Passed    0.00 sec
        Start  5: scrypt_unittests
   5/13 Test  #5: scrypt_unittests .................   Passed    0.01 sec
        Start  6: t0000-smoke
   6/13 Test  #6: t0000-smoke ......................   Passed    0.00 sec
        Start  7: t0005-tools-eni-scrypt
   7/13 Test  #7: t0005-tools-eni-scrypt ...........   Passed    0.01 sec
        Start  8: t0004-tools-eni-crypto
   8/13 Test  #8: t0004-tools-eni-crypto ...........   Passed    0.02 sec
        Start  9: t0001-testlib
   9/13 Test  #9: t0001-testlib ....................   Passed    0.01 sec
        Start 10: t0002-examples-eni-reverse
  10/13 Test #10: t0002-examples-eni-reverse .......   Passed    0.01 sec
        Start 11: consensus_tests
  11/13 Test #11: consensus_tests ..................   Passed    0.07 sec
        Start 12: malformed_consensus_tests
  12/13 Test #12: malformed_consensus_tests ........   Passed    0.03 sec
        Start 13: unittests
  13/13 Test #13: unittests ........................   Passed    1.37 sec

  100% tests passed, 0 tests failed out of 13

  Label Time Summary:
  auto          =   0.06 sec (8 tests)
  checksum      =   0.00 sec (3 tests)
  regression    =   0.13 sec (6 tests)
  unittest      =   1.40 sec (3 tests)

  Total Test time (real) =   1.57 sec

See `Testing/Temporary/LastTest.log` for the detailed output of all tests.
