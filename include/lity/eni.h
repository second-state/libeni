/*==- eni.h ----------------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#ifndef ETHEREUM_NATIVE_INTERFACE
#define ETHEREUM_NATIVE_INTERFACE

#include <json/Array.h>
#include <json/Value.h>
#include <cstdint>
#include <cstring>
#include <string>
#include <sstream>

#define ENI_GAS(OP, CLZ) \
  extern "C" uint64_t* OP ## _gas(char* pArgStr) {              \
    eni::EniBase* functor = new CLZ(pArgStr);                   \
    uint64_t gas = functor->getGas();                           \
    uint64_t* ptrGas = (uint64_t*)::malloc(sizeof(uint64_t));   \
    *ptrGas = gas;                                              \
    delete functor;                                             \
    return ptrGas;                                              \
  }

#define ENI_RUN(OP, CLZ) \
  extern "C" char* OP ## _run(char* pArgStr) {  \
    eni::EniBase* functor = new CLZ(pArgStr);   \
    char* ret = functor->start();               \
    delete functor;                             \
    return ret;                                 \
  }

#define ENI_C_INTERFACE(OP, CLZ) \
  ENI_GAS(OP, CLZ) \
  ENI_RUN(OP, CLZ)

namespace eni {

using Gas = uint64_t;

class EniBase
{
public:
  explicit EniBase(const std::string& pArgStr);

  virtual ~EniBase() = 0;

  Gas getGas() {
    if (!check(m_Args))
      return 0;
    return gas();
  }

  char* start() {
    if (!check(m_Args))
      return nullptr;

    if (!run(m_RetVals.asArray()))
      return nullptr;

    std::ostringstream os;
    m_RetVals.print(os);
    return ::strdup(os.str().c_str());
  }

private:
  bool check(const json::Value& pArgs) {
    bool ret = true;
    if (!m_Parsed) {
      ret = parse(pArgs.toArray());
      m_Parsed = true;
    }
    return ret;
  }

private:
  virtual bool parse(const json::Array& pArgs) = 0;

  virtual Gas gas() const = 0;

  virtual bool run(json::Array& pRetVal) = 0;

private:
  bool m_Parsed;
  json::Value m_Args;
  json::Value m_RetVals;
};

} // namespace of eni

#endif
