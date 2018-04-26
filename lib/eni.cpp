#include <eni.h>

using namespace eni;

EniBase::EniBase(const std::string& pArgStr)
  : m_Args(pArgStr) {
  // empty
}

EniBase::~EniBase()
{
  // implementation of pure virtual destructor
}

extern "C" uint64_t eni_gas(void* pFunctor) {
  return ((eni::EniBase*)pFunctor)->getGas();
}

extern "C" const char* eni_run(eni::EniBase* pFunctor) {
  return ((eni::EniBase*)pFunctor)->start();
}
