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
  RSA* key = PEM_read_bio_RSAPublicKey(bio, NULL, NULL, NULL);
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
RSAEncrypt::RSAEncrypt(const std::string& pArgStr)
  : EniBase(pArgStr) {
  // TODO
}

RSAEncrypt::~RSAEncrypt()
{
  // empty
}

bool RSAEncrypt::parse(const json::Value& pArgs)
{
  // TODO
}

eni::Gas RSAEncrypt::gas() const
{
  // TODO
}

bool RSAEncrypt::run(json::Value& pRetVal)
{
  // TODO
}

//===----------------------------------------------------------------------===//
// RSADecrypt
//===----------------------------------------------------------------------===//
RSADecrypt::RSADecrypt(const std::string& pArgStr)
  : EniBase(pArgStr) {
  // TODO
}

RSADecrypt::~RSADecrypt()
{
  // empty
}

bool RSADecrypt::parse(const json::Value& pArgs)
{
  // TODO
}

eni::Gas RSADecrypt::gas() const
{
  // TODO
}

bool RSADecrypt::run(json::Value& pRetVal)
{
  // TODO
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
