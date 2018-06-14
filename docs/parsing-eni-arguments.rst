=====================
Parsing ENI Arguments
=====================

How Parameter is Converted
--------------------------

If your ENI operation takes several arguments, such as
``eni("magic_encrypt", "Messages", 1024, true)``, all arguments will be listed
in the ``json::Array`` in the original order, keeping their original type.

.. code:: JSON

  ["Messages", 1024, true]

Access the arguments in ``json::Array`` with ``operator[]`` and convert them
to the original type with its member function ``toTYPE()``.

.. code:: C++

  std::string msg   = pArgs[0].toString();
  eni::Int    seed  = pArgs[1].toInteger();
  eni::Bool   magic = pArgs[2].toBoolean();

Here is a list of `TYPE` supported by our json API.

* `Array`
* `Boolean`
* `Integer`
* `Object`
* `String`

See `libENI API <#>`_ for more information about json APIs in libENI.
