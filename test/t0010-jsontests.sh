#!/usr/bin/env bash
#==- t0010-jsontests.sh --------------------------------------------------==#
#
# This file is part of the Lity project distributed under GPL-3.0.
# See LICENSE for details.
#
#==-----------------------------------------------------------------------==#

# TODO: jsontests should be run refactored to run independently,
#       i.e. directly from ctest(1)
PATH=$T_BINDIR/tools/eni_cli:$PATH \
    LD_LIBRARY_PATH=$T_BINDIR:$LD_LIBRARY_PATH \
    python3 -m unittest discover -s jsontests -t .
