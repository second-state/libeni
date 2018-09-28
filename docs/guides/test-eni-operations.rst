========================
Test Your ENI Operations
========================

Test From ``EniBase`` Interface
-------------------------------

Your ENI operations will only be accessed from the two public member functions
of ``eni::EniBase``.

* ``Gas getGas()`` should return the gas cost of your ENI operation.
* ``char* start()`` should run your ENI operation and return the results in
  JSON format.

You may test your subclass through these two public functions.

.. code:: C++

  eni::EniBase* functor = new Reverse("[\"Hello World\"]");
  ASSERT_NE(functor, nullptr);
  EXPECT_EQ(functor->getGas(), 12);
  char* ret = functor->start();
  EXPECT_EQ(::strcmp(ret, "[\"!dlroW olleH\"]"), 0);
  free(ret);
  delete functor;

Test From Shared Library Interface
----------------------------------

Setup Environment
`````````````````

Make sure libENI can be found in your environment.
See :doc:`Getting Started <getting-started>` for how to install libENI.

You might want to try the following settings if libENI is installed
but not found in your environment.

.. code:: bash

  PATH=${PATH}:${LIBENI_PATH}/bin
  LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${LIBENI_PATH}/lib

Tools for Testing
-----------------

.. toctree::
   :maxdepth: 1

   tools/eni_cli
   tools/consensus

Related Guides
--------------

Previous: :doc:`build-eni-operations`.
