#ifndef ETHEREUM_NATIVE_INTERFACE
#define ETHEREUM_NATIVE_INTERFACE

#include <cstdint>
#include <string>

namespace json { // TODO: replace with something like include<json.h>

using Value = std::string;

} // namespace of json

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

  const char* start() {
    if (!run(m_Args, m_RetVals))
      return nullptr;
    return m_RetVals.c_str(); // TODO: replace with something like json-to-str
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
