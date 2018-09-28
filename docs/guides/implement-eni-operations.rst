==========================
Implement an ENI Operation
==========================

Here, we use `examples/eni/reverse` as an example.
In this example, we will create an ENI operation called `reverse`
that takes a string, and returns the reversed string.

The below code piece shows how developers use this ENI operation when writing
a contract in Solidity.

.. code:: C++

  string memory reversed;
  reversed = eni("reverse", "The string to be reversed.");

Subclass ``EniBase``
--------------------

In order to implement an ENI operation, you need to ``#include <eni.h>``,
create a subclass of ``eni::EniBase``, and implement the following functions.

0. A constructor that takes a string as its parameter.
   Remember to pass the string to the constructor of the superclass,
   ``eni::EniBase``, which will convert the raw string into a ``json::Array``
   containing the arguments for your ENI operation.
1. A destructor.
2. Three pure virtual functions, which should be implement privately.

   * ``parse`` to parse the arguments.
   * ``gas`` to calculate gas consumption from the arguments.
   * ``run`` to execute your ENI operation with the arguments.

.. code:: C++

  #include <eni.h>
  class Reverse : public eni::EniBase {
  public:
    Reverse(const std::string& pArgStr)
      : eni::EniBase(pArgStr) { ... }

    ~Reverse() { ... }

  private:
    bool parse(const json::Array& pArgs) override { ... }

    eni::Gas gas() const override { ... }

    bool run(json::Array& pRetVal) override { ... }
  };

Parse Arguments
```````````````

The ``parse`` function takes a ``json::Array`` containing the arguments given
to your ENI operation. To ensure the other two functions ``gas`` and ``run``
process the arguments in the same way, please validate, preprocess, and store
the arguments into member variables in the ``parse`` function.

The ``parse`` function should return ``true`` when all arguments are good, and
return ``false`` otherwise. (i.e. when the given arguments are not correct,
e.g., lacking arguments, or wrong type).

In this example, the ``json::Array`` constructed by ``eni::EniBase`` contains
only the argument string for ENI operation `reverse`.

.. code:: JSON

  ["The string to be reversed."]

Here we just take the first argument and convert it to a string.

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

Check :doc:`the documentation <parsing-eni-arguments>` to see more detail
about how arguments are converted into a ``json::Array``.

Estimate Gas Consumption
````````````````````````

Before your ENI operation is run, you need to estimate how much gas it will cost.
Override the pure virtual function ``gas``, and return your estimated gas cost.

In this example, we use the string length as its gas consumption.

.. code:: C++

  class Reverse : public eni::EniBase {
    ...
  private:
    eni::Gas gas() const override {
      return m_Str.length();
    }
  };

Return ``0`` when error occurs (e.g., gas is incalculable).

Execute the Operation
`````````````````````

Override the pure virtual function ``run``, and push the result of your ENI
operation back into the ``json::Array``.

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

Return ``true`` only when your ENI operation is successfully executed.

Export the ENI Operation with C Interface
-----------------------------------------

Your ENI operation will be called via its C interface, so be sure to export
the C interface with ``ENI_C_INTERFACE(OP, CLASS)``, where `OP` is your ENI
operation name (i.e., `reverse` in this example), and `CLASS` is the name of
implemented class (i.e., ``Reverse`` in this example).

.. code:: C++

  ENI_C_INTERFACE(reverse, Reverse)

Related Guides
--------------

Next: :doc:`build-eni-operations`.
