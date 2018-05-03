#ifndef ENI_EXAMPLE_CRYPTO
#define ENI_EXAMPLE_CRYPTO

#include <eni.h>

//===----------------------------------------------------------------------===//
// Forward declaration of OpenSSL types
//===----------------------------------------------------------------------===//
extern "C" struct rsa_st;
extern "C" typedef struct rsa_st RSA;

namespace eni_crypto {

//===----------------------------------------------------------------------===//
// Helper functions
//===----------------------------------------------------------------------===//
namespace rsa {

RSA* create(const std::string& pPemStr);
void destroy(RSA*& pKey);

bool pub_encrypt(RSA& pKey, const std::string& pMsg, std::string& pResult);
bool pub_decrypt(RSA& pKey, const std::string& pMsg, std::string& pResult);

bool priv_encrypt(RSA& pKey, const std::string& pMsg, std::string& pResult);
bool priv_decrypt(RSA& pKey, const std::string& pMsg, std::string& pResult);

} // namespace of rsa

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
