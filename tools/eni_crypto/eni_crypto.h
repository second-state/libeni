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
bool str2hex(const std::string& pStr, std::string& pHex);
bool hex2str(const std::string& pHex, std::string& pStr);

namespace rsa {

RSA* create_privkey(const std::string& pPemStr);
RSA* create_pubkey(const std::string& pPemStr);

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
  RSAEncrypt(const std::string& pArgStr)
    : EniBase(pArgStr), m_Key(nullptr), m_Msg() { }

  ~RSAEncrypt() { rsa::destroy(m_Key); }

private:
  bool parse(const json::Value& pArgs) override;

  eni::Gas gas() const override;

  bool run(json::Array& pRetVal) override;

private:
  RSA* m_Key;
  std::string m_Msg;
};

//===----------------------------------------------------------------------===//
// RSADecrypt
//===----------------------------------------------------------------------===//
class RSADecrypt : public eni::EniBase
{
public:
  RSADecrypt(const std::string& pArgStr)
    : EniBase(pArgStr), m_Key(nullptr), m_Msg() { }

  ~RSADecrypt() { rsa::destroy(m_Key); }

private:
  bool parse(const json::Value& pArgs) override;

  eni::Gas gas() const override;

  bool run(json::Array& pRetVal) override;

private:
  RSA* m_Key;
  std::string m_Msg;
};

} // namespace of eni_rsa

#endif
