/*==- examples/eni/scrypt/eni_scypt.cpp ---------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#ifndef ENI_SCRYPT_ENI_SCRYPT
#define ENI_SCRYPT_ENI_SCRYPT

#include <eni.h>

class Scrypt : public eni::EniBase
{
public:
  Scrypt(const std::string& pArgStr) : eni::EniBase(pArgStr) { }

  ~Scrypt() { }

private:
  bool parse(const json::Array& pArgs) override;

  eni::Gas gas() const override;

  bool run(json::Array& pRetVal) override;

private:
  std::string m_Str;
};

#endif
