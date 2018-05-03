#include <eni_crypto.h>
#include <cassert> // replace with a testing framework such as SkyPat
#include <iostream>

extern "C" {
#include <openssl/rsa.h>
}

using namespace eni_crypto;

int main(int argc, char* argv[])
{
  if (argc < 2)
    return -1;

  RSA* key = RSA_generate_key(1024, 3, 0, 0);
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

  RSA_free(key);
  return 0;
}
