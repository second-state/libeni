===============
Getting Started
===============

Download the Prebuilt `libeni`
------------------------------

.. TODO: add link to binaries for pre-released version

Prerequisites
`````````````
- Boost >= 1.58

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
  cmake .
  make

Run Tests
`````````

In your `${LIBENI_PATH}` directory, run ``ctest``.
The result looks like the below.

.. code:: bash

  Test project /builds/cybermiles/libeni/build
      Start 1: crypto_tests
  1/4 Test #1: crypto_tests .....................   Passed    0.00 sec
      Start 2: crypto_so_tests
  2/4 Test #2: crypto_so_tests ..................   Passed    0.00 sec
      Start 3: json_tests
  3/4 Test #3: json_tests .......................   Passed    0.00 sec
      Start 4: example_tests
  4/4 Test #4: example_tests ....................   Passed    0.00 sec
  
  100% tests passed, 0 tests failed out of 4
  
  Label Time Summary:
  json          =   0.00 sec (1 test)
  regression    =   0.00 sec (2 tests)
  sharedlib     =   0.00 sec (2 tests)
  unittest      =   0.01 sec (2 tests)
  
  Total Test time (real) =   0.01 sec

See `Testing/Temporary/LastTest.log` for the detailed output of all tests.
