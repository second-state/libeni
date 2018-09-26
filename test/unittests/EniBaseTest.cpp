/*==- test/unittests/EniBaseTest.cpp ---------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <skypat/skypat.h>
#include <eni.h>

using namespace eni;

namespace {

class EniEcho : public EniBase
{
public:
  EniEcho(const std::string& pArgStr)
    : EniBase(pArgStr), m_Str("error") { }

private:
  bool parse(const json::Array& pArgs) override {
    if (pArgs.size() <= 0 || !pArgs[0].isString())
      return false;
    m_Str = pArgs[0].toString();
    return true;
  }

  Gas gas() const override {
    return m_Str.length();
  }

  bool run(json::Array& pRetVal) override {
    pRetVal.emplace_back(m_Str);
    return true;
  }

private:
  std::string m_Str;
};

} // anonymous namespace

SKYPAT_F(EniBaseTest, get_gas_twice)
{
  EniEcho echo("[]");

  Gas gas = echo.getGas();
  EXPECT_EQ(gas, 1500);
  gas = echo.getGas();
  EXPECT_EQ(gas, 1500);
}
