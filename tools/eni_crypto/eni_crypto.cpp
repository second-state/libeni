#include "eni_crypto.h"
#include <json/Array.h>
#include <sstream>

extern "C" {
#include <openssl/pem.h>
#include <openssl/rsa.h>
}

using namespace eni_crypto;

//===----------------------------------------------------------------------===//
// Helper functions
//===----------------------------------------------------------------------===//
static inline unsigned char hex2digit(char h1, char h0)
{
  auto h2d = [](char h) { return (h < 'a') ? (h - '0') : (h - 'a' + 10); };
  return h2d(h1) * 16 + h2d(h0);
}

bool eni_crypto::str2hex(const std::string& pStr, std::string& pHex)
{
  std::ostringstream oss;
  std::string::const_iterator ic, end = pStr.end();
  for (ic = pStr.begin(); ic != end; ++ic)
    oss << std::hex << std::setw(2) << std::setfill('0')
        << (int)(unsigned char)(*ic);
  pHex = oss.str();
  return true;
}

bool eni_crypto::hex2str(const std::string& pHex, std::string& pStr)
{
  if (0 != (pHex.length() % 2))
    return false;
  pStr.clear();
  std::string::const_iterator ic, end = pHex.end();
  for (ic = pHex.begin(); ic != end; ic += 2)
    pStr.push_back((char)hex2digit(*ic, *(ic + 1)));
  return true;
}

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
  if (nullptr == m_Key)
    return false;
  m_Msg = pArgs[1].toString();
  return true;
}

eni::Gas RSAEncrypt::gas() const
{
  return m_Msg.length();
}

bool RSAEncrypt::run(json::Value& pRetVal)
{
  std::string result, hexs;
  if (!rsa::pub_encrypt(*m_Key, m_Msg, result))
    return false;
  if (!str2hex(result, hexs))
    return false;
  pRetVal.delegate(*(new json::Array()));
  pRetVal.asArray().push_back(*(new json::Value(hexs)));
  return true;
}

//===----------------------------------------------------------------------===//
// RSADecrypt
//===----------------------------------------------------------------------===//
bool RSADecrypt::parse(const json::Value& pArgs)
{
  m_Key = rsa::create_privkey(pArgs[0].toString());
  if (nullptr == m_Key)
    return false;
  if (!hex2str(pArgs[1].toString(), m_Msg))
    return false;
  return true;
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
// C interface for RSAEncrypt and RSADecrypt
//===----------------------------------------------------------------------===//
ENI_C_INTERFACE(rsa_encrypt, RSAEncrypt)
ENI_C_INTERFACE(rsa_decrypt, RSADecrypt)
