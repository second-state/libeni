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

  bool run(json::Value& pRetVal) override {
    std::string ret(m_Str.rbegin(), m_Str.rend());
    pRetVal.delegate(*(new json::Array()));
    pRetVal.asArray().push_back(*(new json::Value(ret)));
    return true;
  }

private:
  std::string m_Str;
};

extern "C" void* reverse_create(char* pArgStr)
{
  return (void*)new Reverse(pArgStr);
}

extern "C" void reverse_destroy(void* pFunctor)
{
  return delete (eni::EniBase*)pFunctor;
}
