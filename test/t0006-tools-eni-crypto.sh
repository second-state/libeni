#!/usr/bin/env bash
#==- t0006-tools-eni-crypto.sh -------------------------------------------==#
#
# This file is part of the Lity project distributed under GPL-3.0.
# See LICENSE for details.
#
#==-----------------------------------------------------------------------==#
PATH=$T_BINDIR/tools/eni_cli:$PATH
LD_LIBRARY_PATH=$T_BINDIR:$LD_LIBRARY_PATH
source ./testlib.sh

# Generate random string of length 32
function rands32()
{
  echo $(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 32 | head -n 1)
}

# Extract string from json array
function js1()
{
  local text=${1#'["'}
  echo ${text%'"]'}
}

text="$(rands32)"
len=${#text}
libpath=$T_BINDIR/tools/eni_crypto/eni_crypto.so
for i in {1..3}; do
  params="[$(cat "$T_ID/pubkey.json"),\"$text\"]"
  o_expect '32' eni_gas "$libpath" rsa_encrypt "$params"
  t_run         eni_run "$libpath" rsa_encrypt "$params"
  enc_text=$(js1 "$output")
  enc_len=${#enc_text}

  params="[$(cat "$T_ID/privkey.json"),\"$enc_text\"]"
  o_expect "$(( $enc_len / 2 ))" eni_gas "$libpath" rsa_decrypt "$params"
  t_run                          eni_run "$libpath" rsa_decrypt "$params"
  dec_text=$(js1 "$output")
  dec_len=${#dec_text}

  o_expect "$text" echo "$dec_text"
  o_expect "$len"  echo "$dec_len"

  if [[ $i > 1 ]]; then
    o_expect "$first_enc" echo "$enc_text"
  else
    first_enc=$enc_text
  fi
done
