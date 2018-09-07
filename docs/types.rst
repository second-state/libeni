=====
Types
=====

ENI Types
---------

These types are provided to be coherent with `primitive types of Lity <lity_>`__
(`Solidity <solidity_>`__).

.. _lity: https://lity.readthedocs.io/en/latest/types.html
.. _solidity: https://solidity.readthedocs.io/en/latest/types.html

ENI Integers
````````````

All integer types in ENI is implemented using `boost::multiprecision::number <boostnumber_>`__.
Some of them are aliases for types predefined in `boost::multiprecision::cpp_int <boostcppint_>`__.

+---------------+-------------+--------+-------------------------------------------------+
| Integer Type  | Size (bits) | Signed | Note                                            |
+===============+=============+========+=================================================+
| ``eni::s256`` | 256         | ✔      | Alias for ``boost::multiprecision::int256_t``.  |
+---------------+-------------+--------+-------------------------------------------------+
| ``eni::Int``  | 256         | ✔      | Alias for ``eni::s256``.                        |
+---------------+-------------+--------+-------------------------------------------------+
| ``eni::u256`` | 256         | ✘      | Alias for ``boost::multiprecision::uint256_t``. |
+---------------+-------------+--------+-------------------------------------------------+
| ``eni::u160`` | 160         | ✘      | Size of an Ethereum address.                    |
+---------------+-------------+--------+-------------------------------------------------+
| ``eni::u128`` | 128         | ✘      | Alias for ``boost::multiprecision::uint128_t``. |
+---------------+-------------+--------+-------------------------------------------------+
| ``eni::u64``  | 64          | ✘      |                                                 |
+---------------+-------------+--------+-------------------------------------------------+
| ``eni::UInt`` | 256         | ✘      | Alias for ``eni::u256``.                        |
+---------------+-------------+--------+-------------------------------------------------+

Operations on ENI Integers
''''''''''''''''''''''''''

See `the documentation for boost::multiprecision::number <boostnumber_>`__ for
supported operations.

You may use `boost::lexical_cast <boostlexcast_>`__ to convert ENI integers to strings.

.. _boostnumber: https://www.boost.org/doc/libs/1_58_0/libs/multiprecision/doc/html/boost_multiprecision/ref/number.html
.. _boostcppint: https://www.boost.org/doc/libs/1_58_0/libs/multiprecision/doc/html/boost_multiprecision/tut/ints/cpp_int.html

.. _boostlexcast: https://www.boost.org/doc/libs/1_58_0/doc/html/boost_lexical_cast.html

Suggested Use of ENI Integers
'''''''''''''''''''''''''''''

.. include:: 404.rst

ENI Boolean
```````````

``eni::Bool`` is an alias for C++ ``bool``.

ENI Address
```````````

``eni::Address`` is an alias for ``eni::u160`` (20 bytes, size of an Ethereum address).

Abstract Data Types
-------------------

See ``eni::Vector`` and ``eni::StringMap``.

.. include:: 404.rst

JSON Types
----------

.. include:: 404.rst
