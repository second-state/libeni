===============
Getting Started
===============

Download the Prebuilt libENI
----------------------------

See `libENI releases <https://github.com/CyberMiles/libeni/releases>`_
for the latest release.

- `libeni-dev`: for ENI operation developers
- `libeni`: for general ENI users.

Releases
````````
+---------+----------------------------+----------------------------+
| Version | libeni-dev                 | libeni                     |
+=========+============================+============================+
| v1.3.1_ | `Ubuntu 16.04 <ud131_>`__, | `Ubuntu 16.04 <uu131_>`__, |
|         | `CentOS 7 <cd131_>`__      | `CentOS 7 <cu131_>`__      |
+---------+----------------------------+----------------------------+
| v1.3.0_ | `Ubuntu 16.04 <ud130_>`__, | `Ubuntu 16.04 <uu130_>`__, |
|         | `CentOS 7 <cd130_>`__      | `CentOS 7 <cu130_>`__      |
+---------+----------------------------+----------------------------+
| v1.2.x_ | `Ubuntu 16.04 <ud12x_>`__, | `Ubuntu 16.04 <uu12x_>`__, |
|         | `CentOS 7 <cd12x_>`__      | `CentOS 7 <cu12x_>`__      |
+---------+----------------------------+----------------------------+
| v1.2.0_ | `Ubuntu 16.04 <ud120_>`__, | `Ubuntu 16.04 <uu120_>`__, |
|         | `CentOS 7 <cd120_>`__      | `CentOS 7 <cu120_>`__      |
+---------+----------------------------+----------------------------+

.. _v1.3.1: https://github.com/CyberMiles/libeni/releases/tag/v1.3.1
.. _ud131: https://github.com/CyberMiles/libeni/releases/download/v1.3.1/libeni-1.3.1-dev_ubuntu-16.04.tgz
.. _uu131: https://github.com/CyberMiles/libeni/releases/download/v1.3.1/libeni-1.3.1_ubuntu-16.04.tgz
.. _cd131: https://github.com/CyberMiles/libeni/releases/download/v1.3.1/libeni-1.3.1-dev_centos-7.tgz
.. _cu131: https://github.com/CyberMiles/libeni/releases/download/v1.3.1/libeni-1.3.1_centos-7.tgz

.. _v1.3.0: https://github.com/CyberMiles/libeni/releases/tag/v1.3.0
.. _ud130: https://github.com/CyberMiles/libeni/releases/download/v1.3.0/libeni-1.3.0-dev_ubuntu-16.04.tgz
.. _uu130: https://github.com/CyberMiles/libeni/releases/download/v1.3.0/libeni-1.3.0_ubuntu-16.04.tgz
.. _cd130: https://github.com/CyberMiles/libeni/releases/download/v1.3.0/libeni-1.3.0-dev_centos-7.tgz
.. _cu130: https://github.com/CyberMiles/libeni/releases/download/v1.3.0/libeni-1.3.0_centos-7.tgz

.. _v1.2.x: https://github.com/CyberMiles/libeni/releases/tag/v1.2.x
.. _ud12x: https://github.com/CyberMiles/libeni/releases/download/v1.2.x/libeni-1.2.x-dev_ubuntu-16.04.tgz
.. _uu12x: https://github.com/CyberMiles/libeni/releases/download/v1.2.x/libeni-1.2.x_ubuntu-16.04.tgz
.. _cd12x: https://github.com/CyberMiles/libeni/releases/download/v1.2.x/libeni-1.2.x-dev_centos-7.tgz
.. _cu12x: https://github.com/CyberMiles/libeni/releases/download/v1.2.x/libeni-1.2.x_centos-7.tgz

.. _v1.2.0: https://github.com/CyberMiles/libeni/releases/tag/v1.2.0
.. _ud120: https://github.com/CyberMiles/libeni/releases/download/v1.2.0/libeni-1.2.0-dev_ubuntu-16.04.tgz
.. _uu120: https://github.com/CyberMiles/libeni/releases/download/v1.2.0/libeni-1.2.0_ubuntu-16.04.tgz
.. _cd120: https://github.com/CyberMiles/libeni/releases/download/v1.2.0/libeni-1.2.0-dev_centos-7.tgz
.. _cu120: https://github.com/CyberMiles/libeni/releases/download/v1.2.0/libeni-1.2.0_centos-7.tgz

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

  eni_caesar_cipher.so: OK
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

  git clone https://github.com/CyberMiles/libeni.git ${LIBENI_PATH}

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
      Start 1: crypto_unittests
  1/7 Test #1: crypto_unittests .................   Passed    0.02 sec
      Start 2: t0000-smoke
  2/7 Test #2: t0000-smoke ......................   Passed    0.01 sec
      Start 3: t0001-testlib
  3/7 Test #3: t0001-testlib ....................   Passed    0.03 sec
      Start 4: t0002-examples-eni-reverse
  4/7 Test #4: t0002-examples-eni-reverse .......   Passed    0.02 sec
      Start 5: t0003-examples-eni-caesar
  5/7 Test #5: t0003-examples-eni-caesar ........   Passed    0.02 sec
      Start 6: t0004-tools-eni-crypto
  6/7 Test #6: t0004-tools-eni-crypto ...........   Passed    0.07 sec
      Start 7: unittests
  7/7 Test #7: unittests ........................   Passed    0.01 sec
  
  100% tests passed, 0 tests failed out of 7
  
  Label Time Summary:
  auto          =   0.15 sec*proc (5 tests)
  regression    =   0.15 sec*proc (5 tests)
  unittest      =   0.03 sec*proc (2 tests)
  
  Total Test time (real) =   0.19 sec

See `Testing/Temporary/LastTest.log` for the detailed output of all tests.
