#!/usr/bin/env bash
#==- t0001-testlib.sh ----------------------------------------------------==#
#
# This file is part of the Lity project distributed under GPL-3.0.
# See LICENSE for details.
#
#==-----------------------------------------------------------------------==#
source ./testlib.sh

o_expect 't0001' echo $T_ID
o_expect 't0001-testlib' echo $T_NAME

o_expect '' t_run                   echo 'Hello World!'
o_expect '' o_expect 'Hello World!' echo 'Hello World!'
