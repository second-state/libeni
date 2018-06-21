===============
Getting Started
===============

Download the Prebuilt libENI
----------------------------

See `libENI releases <https://github.com/CyberMiles/libeni/releases>`_
for the newest release.

Prerequisites
`````````````

- Boost >= 1.58

Install
```````

.. code:: bash

  tar zxvf libeni.tgz --strip-components 1 -C ${LIBENI_PATH}

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
- OpenSSL >= 1.0
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
