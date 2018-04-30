#include "eni_crypto.h"
#include <json/Array.h>

extern "C" {
#include <openssl/bio.h>
#include <openssl/rsa.h>
}

using namespace eni_crypto;

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

eni::Gas RSAEncrypt::gas(const json::Value& pArgs) const
{
  // TODO
}

bool RSAEncrypt::run(const json::Value& pArgs, json::Value& pRetVal)
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

eni::Gas RSADecrypt::gas(const json::Value& pArgs) const
{
  // TODO
}

bool RSADecrypt::run(const json::Value& pArgs, json::Value& pRetVal)
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
