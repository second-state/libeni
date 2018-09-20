======================
Testing ENI Operations
======================

Setup Environment
-----------------

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
