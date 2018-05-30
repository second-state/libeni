#!/usr/bin/env bash
#==- t0003-examples-eni-caesar.sh ----------------------------------------==#
#
# This file is part of the Lity project distributed under GPL-3.0.
# See LICENSE for details.
#
#==-----------------------------------------------------------------------==#
PATH=$T_BINDIR/tools/eni_cli:$PATH
LD_LIBRARY_PATH=$T_BINDIR:$LD_LIBRARY_PATH
source ./testlib.sh

libpath=$T_BINDIR/examples/eni/eni_caesar_cipher.so
params='["Hello World!","HELLOGCC"]'
o_expect '12'               eni_gas "$libpath" caesar_encrypt "$params"
o_expect '["Olssv Dvysk!"]' eni_run "$libpath" caesar_encrypt "$params"
params='["Olssv Dvysk!","HELLOGCC"]'
o_expect '12'               eni_gas "$libpath" caesar_decrypt "$params"
o_expect '["Hello World!"]' eni_run "$libpath" caesar_decrypt "$params"
