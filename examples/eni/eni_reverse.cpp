#include <eni.h>
#include <json/Array.h>

class Reverse : public eni::EniBase
{
public:
  Reverse(const std::string& pArgStr) : eni::EniBase(pArgStr) { }

  ~Reverse() { }

private:
  eni::Gas gas(const json::Value& pArgs) const override {
    return pArgs[0].toString().length();
  }

  bool run(const json::Value& pArgs, json::Value& pRetVal) override {
    const std::string& str = pArgs[0].toString();
    std::string ret(str.rbegin(), str.rend());
    pRetVal.delegate(*(new json::Array()));
    pRetVal.asArray().push_back(*(new json::Value(ret)));
    return true;
  }
};

extern "C" void* reverse_create(char* pArgStr)
{
  return (void*)new Reverse(pArgStr);
}

extern "C" void reverse_destroy(void* pFunctor)
{
  return delete (eni::EniBase*)pFunctor;
}
