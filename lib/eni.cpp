#include <eni.h>
#include <json/Parser.h>

using namespace eni;

EniBase::EniBase(const std::string& pArgStr)
  : m_Parsed(false), m_Args(), m_RetVals() {
  json::Parser parser(pArgStr);
  m_Args = parser.getRoot();
}

EniBase::~EniBase()
{
  // implementation of pure virtual destructor
}

extern "C" uint64_t eni_gas(void* pFunctor) {
  return ((eni::EniBase*)pFunctor)->getGas();
}

extern "C" char* eni_run(void* pFunctor) {
  return ((eni::EniBase*)pFunctor)->start();
}
