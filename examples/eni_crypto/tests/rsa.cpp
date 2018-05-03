#include <eni_crypto.h>
#include <cassert> // replace with a testing framework such as SkyPat
#include <cstdio>
#include <cstring>

extern "C" {
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
}

using namespace eni_crypto;

int main(int argc, char* argv[])
{
  if (argc < 2)
    return -1;
  fprintf(stderr, "strlen = %zu\n", ::strlen(argv[1]));

  RSA* key = RSA_generate_key(1024, 3, 0, 0);
  if (NULL == key)
    return 1;
  fprintf(stderr, "RSA_size = %d\n", ::RSA_size(key));

  unsigned char* orig = new unsigned char[::strlen(argv[1])];
  ::memcpy(orig, argv[1], ::strlen(argv[1]));

  unsigned char* encrypted = new unsigned char[::RSA_size(key)];
  int ret = RSA_public_encrypt(::strlen(argv[1]), orig, encrypted, key,
    RSA_PKCS1_PADDING);
  if (-1 == ret)
    return 2;
  delete[] orig;

  unsigned char* decrypted = new unsigned char[ret];
  ret = RSA_private_decrypt(ret, encrypted, decrypted, key,
    RSA_PKCS1_PADDING);
  if (-1 == ret)
    return 3;
  delete[] encrypted;
  RSA_free(key);

  char* result = new char[ret + 1];
  ::memcpy(result, decrypted, ret);
  result[ret] = '\0';
  delete[] decrypted;

  fprintf(stderr, "Original: %s, Result: %s\n", argv[1], result);
  assert((0 == ::strcmp(result, argv[1])));
  delete[] result;
  return 0;
}
