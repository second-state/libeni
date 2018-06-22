/*==- examples/eni/scrypt/eni_scrypt.cpp ---------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <eni.h>
#include <cstring>
#include <cctype>
#include "eni_scrypt.h"
#include "scrypt.h"

bool Scrypt::parse(const json::Array& pArgs)
{
  m_Str = pArgs[0].toString();
  return true;
}

eni::Gas Scrypt::gas() const
{
  return m_Str.length();
}

bool Scrypt::run(json::Array& pRetVal)
{
  // scrypt in dogecoin only accept 80 bytes input
  // and generate 32 bytes output
  char hash[32];
  char input[80];
  memset(input, 0, 80);

  // unhex input
  if (m_Str.length() % 2 != 0) {
      return false;
  }
  int len = m_Str.length() / 2 < 80 ? m_Str.length() / 2 : 80;
  for (int i = 0; i < len; i++) {
      char c1 = tolower(m_Str[2 * i]), c2 = tolower(m_Str[2 * i + 1]);
      input[i] += c1 < 'a' ? c1 - '0' : c1 - 'a' + 10;
      input[i] <<= 4;
      input[i] += c2 < 'a' ? c2 - '0' : c2 - 'a' + 10;
  }

  scrypt_1024_1_1_256(input, hash);

  // hex output hash
  std::ostringstream oss;
  for (int i = 0; i < 32; i++) {
    oss << std::hex << std::setw(2) << std::setfill('0') << (hash[i] & 0xff);
  }

  pRetVal.emplace_back(oss.str());
  return true;
}

ENI_C_INTERFACE(scrypt, Scrypt)
