#!/usr/bin/env bash
#==- t0000-smoke.sh ------------------------------------------------------==#
#
# This file is part of the Lity project distributed under GPL-3.0.
# See LICENSE for details.
#
#==-----------------------------------------------------------------------==#
source ./testlib.sh

o_expect 'Hello World!' echo 'Hello World!'
