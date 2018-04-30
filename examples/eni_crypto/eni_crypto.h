#ifndef ENI_EXAMPLE_CRYPTO
#define ENI_EXAMPLE_CRYPTO

#include <eni.h>

namespace eni_crypto {

//===----------------------------------------------------------------------===//
// RSAEncrypt
//===----------------------------------------------------------------------===//
class RSAEncrypt : public eni::EniBase
{
public:
  RSAEncrypt(const std::string& pArgStr);

  ~RSAEncrypt();

private:
  eni::Gas gas(const json::Value& pArgs) const override;

  bool run(const json::Value& pArgs, json::Value& pRetVal) override;
};

//===----------------------------------------------------------------------===//
// RSADecrypt
//===----------------------------------------------------------------------===//
class RSADecrypt : public eni::EniBase
{
public:
  RSADecrypt(const std::string& pArgStr);

  ~RSADecrypt();

private:
  eni::Gas gas(const json::Value& pArgs) const override;

  bool run(const json::Value& pArgs, json::Value& pRetVal) override;
};

} // namespace of eni_rsa

#endif
