#ifndef ETHEREUM_NATIVE_INTERFACE
#define ETHEREUM_NATIVE_INTERFACE

#include <json/Value.h>
#include <cstdint>
#include <cstring>
#include <string>
#include <sstream>

namespace eni {

using Gas = uint64_t;

class EniBase
{
public:
  EniBase(const std::string& pArgStr);

  virtual ~EniBase() = 0;

  Gas getGas() const {
    return gas(m_Args);
  }

  char* start() {
    if (!run(m_Args, m_RetVals))
      return nullptr;

    std::ostringstream os;
    m_RetVals.print(os);
    return ::strdup(os.str().c_str());
  }

private:
  virtual Gas gas(const json::Value& pArgs) const = 0;

  virtual bool run(const json::Value& pArgs, json::Value& pRetVal) = 0;

private:
  json::Value m_Args;
  json::Value m_RetVals;
};

} // namespace of eni

#endif
