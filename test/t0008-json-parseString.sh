#!/usr/bin/env bash
#==- t0008-json-parseString.sh -------------------------------------------==#
#
# This file is part of the Lity project distributed under GPL-3.0.
# See LICENSE for details.
#
#==-----------------------------------------------------------------------==#
PATH=$T_BINDIR/tools/eni_cli:$PATH
LD_LIBRARY_PATH=$T_BINDIR:$LD_LIBRARY_PATH
source ./testlib.sh

libpath=$T_BINDIR/examples/eni/eni_json.so
params='["parseString", "\"Hello World!\"", 0, 14]'
o_expect '["Hello World!"]' eni_run "$libpath" json "$params"
