#!/usr/bin/env bash
#==- t0007-bug-493629.sh -------------------------------------------------==#
#
# This file is part of the Lity project distributed under GPL-3.0.
# See LICENSE for details.
#
#==-----------------------------------------------------------------------==#
PATH=$T_BINDIR/test/$T_ID:$PATH
source ./testlib.sh

t_run t0007
[ 'invalid code number' = "$output" ] && [ '87' -eq "$status" ]
