#ifndef ETHEREUM_NATIVE_INTERFACE
#define ETHEREUM_NATIVE_INTERFACE

#include <json/Value.h>
#include <cstdint>
#include <cstring>
#include <string>
#include <sstream>

#define ENI_CREATE(OP, CLZ) \
  extern "C" void* OP ## _create(char* pArgStr) { \
    return (void*)new CLZ(pArgStr); \
  }

#define ENI_DESTROY(OP, CLZ) \
  extern "C" void OP ## _destroy(void* pFunctor) { \
    return delete (eni::EniBase*)pFunctor; \
  }

#define ENI_C_INTERFACE(OP, CLZ) \
  ENI_CREATE(OP, CLZ) \
  ENI_DESTROY(OP, CLZ)

namespace eni {

using Gas = uint64_t;

class EniBase
{
public:
  explicit EniBase(const std::string& pArgStr);

  virtual ~EniBase() = 0;

  Gas getGas() {
    if ((!m_Parsed) && (!parse(m_Args)))
      return 0;
    return gas();
  }

  char* start() {
    if ((!m_Parsed) && (!parse(m_Args)))
      return nullptr;

    if (!run(m_RetVals.asArray()))
      return nullptr;

    std::ostringstream os;
    m_RetVals.print(os);
    return ::strdup(os.str().c_str());
  }

private:
  virtual bool parse(const json::Value& pArgs) = 0;

  virtual Gas gas() const = 0;

  virtual bool run(json::Array& pRetVal) = 0;

private:
  bool m_Parsed;
  json::Value m_Args;
  json::Value m_RetVals;
};

} // namespace of eni

#endif
