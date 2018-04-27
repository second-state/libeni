#include <eni.h>

class Reverse : public eni::EniBase
{
public:
  Reverse(const std::string& pArgStr) : eni::EniBase(pArgStr) { }

  ~Reverse() { }

private:
  eni::Gas gas(const json::Value& pArgs) const override {
    return pArgs.length();
  }

  bool run(const json::Value& pArgs, json::Value& pRetVal) override {
    pRetVal.assign(pArgs.rbegin(), pArgs.rend());
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
