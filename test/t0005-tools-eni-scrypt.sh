#!/usr/bin/env bash
#==- t0005-tools-eni-scrypt.sh -------------------------------------------==#
#
# This file is part of the Lity project distributed under GPL-3.0.
# See LICENSE for details.
#
#==-----------------------------------------------------------------------==#
PATH=$T_BINDIR/tools/eni_cli:$PATH
LD_LIBRARY_PATH=$T_BINDIR:$LD_LIBRARY_PATH
source ./testlib.sh

libpath=$T_BINDIR/tools/eni_scrypt/eni_scrypt.so
params='["00"]'
o_expect '2' eni_gas "$libpath" scrypt "$params"
o_expect '["161d0876f3b93b1048cda1bdeaa7332ee210f7131b42013cb43913a6553a4b69"]' eni_run "$libpath" scrypt "$params"
