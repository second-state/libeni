/*==- examples/eni/caesar_cipher/eni_caesar_cipher.h -----------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#ifndef ENI_CAESAR_CIPHER_H
#define ENI_CAESAR_CIPHER_H
#include <eni.h>

namespace CaesarCipher {

int char2int(char ch);

class Encrypt : public eni::EniBase
{
public:
  Encrypt(const std::string& pArgStr)
    : eni::EniBase(pArgStr), m_Data( ), m_Seed( ) { }

  ~Encrypt() { }

private:
  bool parse(const json::Array& pArgs) override;

  eni::Gas gas() const override;

  bool run(json::Array& pRetVal) override;

private:
  std::string m_Data;
  std::string m_Seed;
};

class Decrypt : public eni::EniBase
{
public:
  Decrypt(const std::string& pArgStr)
    : eni::EniBase(pArgStr), m_Data( ), m_Seed( ) { }

  ~Decrypt() { }

private:
  bool parse(const json::Array& pArgs) override;

  eni::Gas gas() const override;

  bool run(json::Array& pRetVal) override;

private:
  std::string m_Data;
  std::string m_Seed;
};

}; // end of namespace

#endif
