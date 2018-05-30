#!/usr/bin/env bash
#==- t0002-examples-eni-reverse.sh ---------------------------------------==#
#
# This file is part of the Lity project distributed under GPL-3.0.
# See LICENSE for details.
#
#==-----------------------------------------------------------------------==#
PATH=$T_BINDIR/tools/eni_cli:$PATH
LD_LIBRARY_PATH=$T_BINDIR:$LD_LIBRARY_PATH
source ./testlib.sh

libpath=$T_BINDIR/examples/eni/eni_reverse.so
params='["Hello World!"]'
o_expect '12'               eni_gas "$libpath" reverse "$params"
o_expect '["!dlroW olleH"]' eni_run "$libpath" reverse "$params"
