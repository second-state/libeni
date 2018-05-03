#include <eni_crypto.h>
#include <cassert> // replace with a testing framework such as SkyPat
#include <fstream>
#include <iostream>
#include <streambuf>

using namespace eni_crypto;

int main(int argc, char* argv[])
{
  if (argc < 2)
    return -1;

  std::ifstream ifs("priv.pem");
  if (!ifs.is_open())
    return -2;

  std::string pemstr((std::istreambuf_iterator<char>(ifs)),
                      std::istreambuf_iterator<char>());
  RSA* key = rsa::create(pemstr);
  if (NULL == key)
    return 1;

  // Case 1: RSA_public_encrypt + RSA_private_decrypt
  const std::string msg(argv[1]);
  std::string encrypted, decrypted;
  if (!rsa::pub_encrypt(*key, msg, encrypted))
    return 2;
  if (!rsa::priv_decrypt(*key, encrypted, decrypted))
    return 3;
  std::cout << decrypted << std::endl;
  assert((msg == decrypted));

  // Case 2: RSA_private_encrypt + RSA_public_decrypt
  if (!rsa::priv_encrypt(*key, msg, encrypted))
    return 4;
  if (!rsa::pub_decrypt(*key, encrypted, decrypted))
    return 5;
  std::cout << decrypted << std::endl;
  assert((msg == decrypted));

  rsa::destroy(key);
  return 0;
}
