/*==- examples/eni/reverse/eni_reverse.cpp ---------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <eni.h>

class Reverse : public eni::EniBase
{
public:
  Reverse(const std::string& pArgStr) : eni::EniBase(pArgStr) { }

  ~Reverse() { }

private:
  bool parse(const json::Array& pArgs) override {
    m_Str = pArgs[0].toString();
    return true;
  }

  eni::Gas gas() const override {
    return m_Str.length();
  }

  bool run(json::Array& pRetVal) override {
    std::string ret(m_Str.rbegin(), m_Str.rend());
    pRetVal.emplace_back(ret);
    return true;
  }

private:
  std::string m_Str;
};

ENI_C_INTERFACE(reverse, Reverse)
