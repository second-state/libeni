#!/usr/bin/env bash
#==- t0004-tools-eni-crypto.sh -------------------------------------------==#
#
# This file is part of the Lity project distributed under GPL-3.0.
# See LICENSE for details.
#
#==-----------------------------------------------------------------------==#
PATH=$T_BINDIR/tools/eni_cli:$PATH
LD_LIBRARY_PATH=$T_BINDIR:$LD_LIBRARY_PATH
source ./testlib.sh

libpath=$T_BINDIR/tools/eni_crypto/eni_crypto.so
params=$(cat "$T_ID/pub_encrypt.json")
o_expect '2560'             eni_gas "$libpath" rsa_encrypt "$params"
t_run                       eni_run "$libpath" rsa_encrypt "$params"
o_expect '516'              echo ${#output}
params=$(cat "$T_ID/priv_decrypt.json")
o_expect '2560'             eni_gas "$libpath" rsa_decrypt "$params"
o_expect '["Hello World!"]' eni_run "$libpath" rsa_decrypt "$params"
