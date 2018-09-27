==========================================
Build ENI Operations Into a Shared Library
==========================================

Please add these flags ``-std=c++11 -fPIC`` when compiling your ENI operation
into a shared library.
See `GCC Option Summary <https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html>`_
for explanation to these flags.

Specify the path to libENI headers with ``-I${LIBENI_PATH}/include``.

You might also want to link to libENI by specifying the path
``-L${LIBENI_PATH}/lib``, and the library name ``-leni``.

Here is an example Makefile for `examples/eni/reverse`. Please be aware that
the flags and commands might differ if you're using different compilers.

.. code:: Makefile

  CPPFLAGS=-I${LIBENI_PATH}/include
  CXXFLAGS=-std=c++11 -fPIC
  LDFLAGS=-L${LIBENI_PATH}/lib
  LDADD=-leni

  all:
  	g++ ${CPPFLAGS} ${CXXFLAGS} ${LDFLAGS} -shared -oeni_reverse.so eni_reverse.cpp ${LDADD}

Related Guides
--------------

Next: :doc:<guides/test-eni-operations>.
Previous: :doc:<guides/implementing-eni-operations>.
