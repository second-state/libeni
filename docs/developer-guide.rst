===============
Developer Guide
===============

In this tutorial, we will guide you through how to create new ENI operations with `libeni` in C++.

See `Getting Started <docs/getting-started.rst>`_ for how to install `libeni`.

Implement an ENI Operations
---------------------------

Here, we use `examples/eni/reverse` as an example. In this example, we will create an ENI operation called `reverse` that takes a string, and returns the reversed string.

The below code piece shows how developers use this ENI operation when writing a contract in Solidity.

.. code:: C++

  string memory reversed;
  reversed = eni("reverse", "The string to be reversed.");

Subclass ``EniBase``
````````````````````

In order to implement one ENI operation, you need to ``#include <eni.h>`` and create a subclass
of ``eni::EniBase``. The constructor of your subclass must take a string as parameter, and pass it to its superclass ``eni::EniBase``.

.. code:: C++

  #include <eni.h>
  class Reverse : public eni::EniBase {
  public:
    Reverse(const std::string& pArgStr)
      : eni::EniBase(pArgStr) { ... }

    ~Reverse() { ... }
  };

The constructor of ``eni::EniBase`` will preprocess the parameter from a raw string into a ``json::Array`` for you, so be sure to pass the parameter to it.

Parse Arguments
```````````````

After the parameter is converted into ``json::Array``, `libeni` will call the pure virtual function `parse` that allows your ENI operation to get the arguments.

Store the arguments into member variables for further use. Return ``false`` when the given arguments are not correct (e.g., lacking arguments).

.. code:: C++

  class Reverse : public eni::EniBase {
    ...
  private:
    bool parse(const json::Array& pArgs) override {
      m_Str = pArgs[0].toString();
      return true;
    }

    std::string m_Str;
  };

How Parameter is Converted
''''''''''''''''''''''''''

In the above example, the ``json::Array`` will contain only the argument string for ENI operation `reverse`.

.. code:: JSON

  ["The string to be reversed."]

If your ENI operation takes several arguments, such as ``eni("magic_encrypt", "Messages", 1024, true)``, the ``json::Array`` will list all arguments in the original order, and keep the original type.

.. code:: JSON

  ["Messages", 1024, true]

Access the arguments in ``json::Array`` with ``operator[]`` and convert to the original type with its member function ``toTYPE()`` (`TYPE` may be `Boolean`, `Integer`, `String`, `Array`, `Object`).

.. code:: C++

  std::string msg   = pArgs[0].toString();
  eni::Int    seed  = pArgs[1].toInteger();
  eni::Bool   magic = pArgs[2].toBoolean();

See `libeni API <docs/api/index.rst>`_ for more information about the `json` in `libeni`.

Estimate Gas Consumption
````````````````````````

Before your ENI operation is run, you need to estimate how much gas it will cost. Override the pure virtual function `gas` to return your estimated gas cost.

In the ENI `reverse` example, we use the string length as its gas consumption.

.. code:: C++

  class Reverse : public eni::EniBase {
    ...
  private:
    eni::Gas gas() const override {
      return m_Str.length();
    }
  };

Implement the Operation
```````````````````````

Override the pure virtual function `run` and push the result back into the ``json::Array``.

.. code:: C++

  class Reverse : public eni::EniBase {
    ...
  private:
    bool run(json::Array& pRetVal) override {
      std::string ret(m_Str.rbegin(), m_Str.rend());
      pRetVal.emplace_back(ret);
      return true;
    }
  };

Export the ENI Operation with C Interface
`````````````````````````````````````````

Your ENI operation will be called via its C interface, so be sure to export the C interface with ``ENI_C_INTERFACE(OP, CLASS)``, where `OP` is the operation name (i.e., `reverse` in the above example), and `CLASS` is the class name for the operation implementation (i.e., ``Reverse``, the subclass of ``eni::EniBase``, in the above example).

.. code:: C++

  ENI_C_INTERFACE(reverse, Reverse)

Build the ENI Operations Into a Shared Library
----------------------------------------------

Please add these flags ``-std=c++11 -fPIC`` when compiling into a shared library. You might want to check `GCC Option Summary <https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html>`_ to see the explanation for these flags.

Specify the path to `libeni` headers, such as `eni.h``, with ``-I${LIBENI_PATH}/include``.

You might also want to link to `libeni` by specifying the path ``-L${LIBENI_PATH}/lib``, and the library name ``-leni``.

Here is an example Makefile for `examples/eni/reverse`. Please be aware that the flags and commands might differ if you're using different compilers or building systems.

.. code:: Makefile

  CPPFLAGS=-I${LIBENI_PATH}/include
  CXXFLAGS=-std=c++11 -fPIC
  LDFLAGS=-L${LIBENI_PATH}/lib
  LDADD=-leni

  all:
  	g++ ${CPPFLAGS} ${CXXFLAGS} ${LDFLAGS} -shared -oeni_reverse.so eni_reverse.cpp ${LDADD}


Test Your ENI Operations
------------------------

See `the documentation <docs/testing-eni-operations.rst>`_ for how to
test your ENI operations.
