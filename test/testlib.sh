#!/usr/bin/env bash
#==- testlib.sh ----------------------------------------------------------==#
#
# This file is part of the Lity project distributed under GPL-3.0.
# See LICENSE for details.
#
#==-----------------------------------------------------------------------==#
set -e

# SYNOPSYS
#   p_expect <EXPECTED_OUTPUT> <OUTPUT>
#
# RETURNS
#   1
function p_expect
{
  >&2 printf "%s\nExpect:\n%s\nOutput:\n%s\n" "$@"
  return 1
}

# SYNOPSYS
#   t_run <CMD> [ARG ...]
#
# VARIABLES
#   $status
#   $output
#
# RETURNS
#   (undefined)
function t_run
{
  output=$("$@")
  status=$?
}

# SYNOPSYS
#   o_expect <OUTPUT> <CMD> [ARG ...]
#
# RETURNS
#   0   if <OUTPUT> = the output of <CMD>
#   1   otherwise
function o_expect
{
  local expect=$1
  shift
  t_run "$@"
  [ "$expect" = "$output" ] && : || p_expect "$*" "$expect" "$output"
}
