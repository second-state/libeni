#include "eni_crypto.h"
#include <json/Array.h>

extern "C" {
#include <openssl/pem.h>
#include <openssl/rsa.h>
}

using namespace eni_crypto;

//===----------------------------------------------------------------------===//
// Helper functions
//===----------------------------------------------------------------------===//
RSA* rsa::create_pubkey(const std::string& pPemStr)
{
  BIO* bio = BIO_new_mem_buf(pPemStr.c_str(), -1);
  if (NULL == bio)
    return NULL;
  RSA* key = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);
  return key;
}

RSA* rsa::create_privkey(const std::string& pPemStr)
{
  BIO* bio = BIO_new_mem_buf(pPemStr.c_str(), -1);
  if (NULL == bio)
    return NULL;
  RSA* key = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);
  return key;
}

void rsa::destroy(RSA*& pKey)
{
  RSA_free(pKey);
  pKey = NULL;
}

bool rsa::pub_encrypt(RSA& pKey, const std::string& pMsg, std::string& pResult)
{
  unsigned char* encrypted = new unsigned char[::RSA_size(&pKey)];
  int len = ::RSA_public_encrypt(pMsg.length(),
    reinterpret_cast<const unsigned char*>(pMsg.c_str()), encrypted, &pKey,
    RSA_PKCS1_PADDING);
  if (-1 == len)
    return false;
  pResult.assign(reinterpret_cast<char*>(encrypted), len);
  return true;
}

bool rsa::pub_decrypt(RSA& pKey, const std::string& pMsg, std::string& pResult)
{
  unsigned char* decrypted = new unsigned char[::RSA_size(&pKey)];
  int len = ::RSA_public_decrypt(pMsg.length(),
    reinterpret_cast<const unsigned char*>(pMsg.c_str()), decrypted, &pKey,
    RSA_PKCS1_PADDING);
  if (-1 == len)
    return false;
  pResult.assign(reinterpret_cast<char*>(decrypted), len);
  return true;
}

bool rsa::priv_encrypt(RSA& pKey, const std::string& pMsg, std::string& pResult)
{
  unsigned char* encrypted = new unsigned char[::RSA_size(&pKey)];
  int len = ::RSA_private_encrypt(pMsg.length(),
    reinterpret_cast<const unsigned char*>(pMsg.c_str()), encrypted, &pKey,
    RSA_PKCS1_PADDING);
  if (-1 == len)
    return false;
  pResult.assign(reinterpret_cast<char*>(encrypted), len);
  return true;
}

bool rsa::priv_decrypt(RSA& pKey, const std::string& pMsg, std::string& pResult)
{
  unsigned char* decrypted = new unsigned char[::RSA_size(&pKey)];
  int len = ::RSA_private_decrypt(pMsg.length(),
    reinterpret_cast<const unsigned char*>(pMsg.c_str()), decrypted, &pKey,
    RSA_PKCS1_PADDING);
  if (-1 == len)
    return false;
  pResult.assign(reinterpret_cast<char*>(decrypted), len);
  return true;
}

//===----------------------------------------------------------------------===//
// RSAEncrypt
//===----------------------------------------------------------------------===//
bool RSAEncrypt::parse(const json::Value& pArgs)
{
  m_Key = rsa::create_pubkey(pArgs[0].toString());
  m_Msg = pArgs[1].toString();
  return (nullptr != m_Key);
}

eni::Gas RSAEncrypt::gas() const
{
  return m_Msg.length();
}

bool RSAEncrypt::run(json::Value& pRetVal)
{
  std::string result;
  if (!rsa::pub_encrypt(*m_Key, m_Msg, result))
    return false;
  pRetVal.delegate(*(new json::Array()));
  pRetVal.asArray().push_back(*(new json::Value(result)));
  return true;
}

//===----------------------------------------------------------------------===//
// RSADecrypt
//===----------------------------------------------------------------------===//
bool RSADecrypt::parse(const json::Value& pArgs)
{
  m_Key = rsa::create_privkey(pArgs[0].toString());
  m_Msg = pArgs[1].toString();
  return (nullptr != m_Key);
}

eni::Gas RSADecrypt::gas() const
{
  return m_Msg.length();
}

bool RSADecrypt::run(json::Value& pRetVal)
{
  std::string result;
  if (!rsa::priv_decrypt(*m_Key, m_Msg, result))
    return false;
  pRetVal.delegate(*(new json::Array()));
  pRetVal.asArray().push_back(*(new json::Value(result)));
  return true;
}

//===----------------------------------------------------------------------===//
// C interface for RSAEncrypt
//===----------------------------------------------------------------------===//
extern "C" void* rsa_encrypt_create(char* pArgStr)
{
  return (void*)new RSAEncrypt(pArgStr);
}

extern "C" void rsa_encrypt_destroy(void* pFunctor)
{
  return delete (eni::EniBase*)pFunctor;
}

//===----------------------------------------------------------------------===//
// C interface for RSADecrypt
//===----------------------------------------------------------------------===//
extern "C" void* rsa_decrypt_create(char* pArgStr)
{
  return (void*)new RSADecrypt(pArgStr);
}

extern "C" void rsa_decrypt_destroy(void* pFunctor)
{
  return delete (eni::EniBase*)pFunctor;
}
