#!/usr/bin/env bash
#==- t0006-json-parse-error.sh -------------------------------------------==#
#
# This file is part of the Lity project distributed under GPL-3.0.
# See LICENSE for details.
#
#==-----------------------------------------------------------------------==#
PATH=$T_BINDIR/test/$T_ID:$PATH
source ./testlib.sh

t_run t0006
o_expect '87' echo $status
