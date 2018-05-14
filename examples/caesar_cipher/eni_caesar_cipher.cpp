#include <eni.h>
#include <json/Array.h>
#include <cstring>
#include "eni_caesar_cipher.h"

using namespace CaesarCipher;

//===----------------------------------------------------------------------===//
// Helper functions
//===----------------------------------------------------------------------===//
int CaesarCipher::char2int(char ch) {
  if (isupper(ch)) {
    return ch-'A';
  } else if (islower(ch)) {
    return ch-'a';
  } else {
    return 0;
  }
}

//===----------------------------------------------------------------------===//
// Encrypt functions
//===----------------------------------------------------------------------===//
bool Encrypt::parse(const json::Value& pArgs) {
  m_Data = pArgs[0].toString();
  m_Seed = pArgs[1].toString();
  return true;
};

eni::Gas Encrypt::gas() const {
  return m_Data.length();
}

bool Encrypt::run(json::Array& pRetVal) {
  const int cseed = char2int(m_Seed[0]);
  std::string ret("");
  for (auto ch : m_Data) {
    char tmp = char2int(ch);
    if (isupper(ch)) {
      ret.push_back((tmp+cseed)%26+'A');
    } else if (islower(ch)) {
      ret.push_back((tmp+cseed)%26+'a');
    } else {
      ret.push_back(ch);
    }
  }
  pRetVal.push_back(*(new json::Value(ret)));
  return true;
}

//===----------------------------------------------------------------------===//
// Decrypt functions
//===----------------------------------------------------------------------===//
eni::Gas Decrypt::gas() const {
  return m_Data.length();
}

bool Decrypt::parse(const json::Value& pArgs) {
  m_Data = pArgs[0].toString();
  m_Seed = pArgs[1].toString();
  return true;
};

bool Decrypt::run(json::Array& pRetVal) {
  const int cseed = char2int(m_Seed[0]);
  std::string ret("");
  for (auto ch : m_Data) {
    char tmp = char2int(ch);
    if (isupper(ch)) {
      ret.push_back((26+tmp-cseed)%26+'A');
    } else if (islower(ch)) {
      ret.push_back((26+tmp-cseed)%26+'a');
    } else {
      ret.push_back(ch);
    }
  }
  pRetVal.push_back(*(new json::Value(ret)));
  return true;
}

//===----------------------------------------------------------------------===//
// C interface
//===----------------------------------------------------------------------===//
ENI_C_INTERFACE(caesar_encrypt, Encrypt)
ENI_C_INTERFACE(caesar_decrypt, Decrypt)
