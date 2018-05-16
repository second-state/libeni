#include <eni.h>
#include <json/Array.h>

class Reverse : public eni::EniBase
{
public:
  Reverse(const std::string& pArgStr) : eni::EniBase(pArgStr) { }

  ~Reverse() { }

private:
  bool parse(const json::Value& pArgs) override {
    m_Str = pArgs[0].toString();
    return true;
  }

  eni::Gas gas() const override {
    return m_Str.length();
  }

  bool run(json::Array& pRetVal) override {
    std::string ret(m_Str.rbegin(), m_Str.rend());
    pRetVal.push_back(*(new json::Value(ret)));
    return true;
  }

private:
  std::string m_Str;
};

ENI_C_INTERFACE(reverse, Reverse)
