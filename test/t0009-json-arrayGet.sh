#!/usr/bin/env bash
#==- t0009-json-arratGet.sh ----------------------------------------------==#
#
# This file is part of the Lity project distributed under GPL-3.0.
# See LICENSE for details.
#
#==-----------------------------------------------------------------------==#
PATH=$T_BINDIR/tools/eni_cli:$PATH
LD_LIBRARY_PATH=$T_BINDIR:$LD_LIBRARY_PATH
source ./testlib.sh

# ["Hello", "World!"]
# 01234567890123456789

libpath=$T_BINDIR/examples/eni/eni_json.so
params='["arrayGet", "[\"Hello\", \"World!\"]", 0, 19, 0]'
o_expect '["\u0000\u0000\u0000\u0001\u0000\u0000\u0000\u0008"]' eni_run "$libpath" json "$params"

params='["arrayGet", "[\"Hello\", \"World!\"]", 0, 19, 1]'
o_expect '["\u0000\u0000\u0000\u000A\u0000\u0000\u0000\u0012"]' eni_run "$libpath" json "$params"
