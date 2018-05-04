#include <eni_crypto.h>
#include <cassert> // replace with a testing framework such as SkyPat
#include <fstream>
#include <iostream>
#include <streambuf>

using namespace eni_crypto;

static inline bool readfile(const std::string& pName, std::string& pStr)
{
  std::ifstream ifs(pName);
  if (!ifs.is_open())
    return false;

  pStr.assign((std::istreambuf_iterator<char>(ifs)),
               std::istreambuf_iterator<char>());
  return true;
}

int main(int argc, char* argv[])
{
  if (argc < 2)
    return -1;

  std::string pemstr;
  if (!readfile("priv.pem", pemstr))
    return -2;
  RSA* privkey = rsa::create_privkey(pemstr);
  if (NULL == privkey)
    return -3;

  if (!readfile("pub.pem", pemstr))
    return -4;
  RSA* pubkey = rsa::create_pubkey(pemstr);
  if (NULL == pubkey)
    return -5;

  // Case 1: RSA_public_encrypt + RSA_private_decrypt
  const std::string msg(argv[1]);
  std::string encrypted, decrypted;
  if (!rsa::pub_encrypt(*pubkey, msg, encrypted))
    return 2;
  if (!rsa::priv_decrypt(*privkey, encrypted, decrypted))
    return 3;
  std::cout << decrypted << std::endl;
  assert((msg == decrypted));

  // Case 2: RSA_private_encrypt + RSA_public_decrypt
  if (!rsa::priv_encrypt(*privkey, msg, encrypted))
    return 4;
  if (!rsa::pub_decrypt(*pubkey, encrypted, decrypted))
    return 5;
  std::cout << decrypted << std::endl;
  assert((msg == decrypted));

  rsa::destroy(pubkey);
  rsa::destroy(privkey);
  return 0;
}
