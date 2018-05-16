#include <skypat/skypat.h>
#include <json/Parser.h>
#include <dlfcn.h>
#include <cstdlib>
#include <cstring>

namespace {

typedef void* eni_create_t(char* pArgStr);
typedef void  eni_destroy_t(void* pFunctor);

extern "C" uint64_t eni_gas(void* pFunctor);
extern "C" char*    eni_run(void *pFunctor);

} // annonymous namespace

SKYPAT_F(EniCryptoTest, rsa_encrypt)
{
  // Initialize.
  void* handle = ::dlopen("./eni_crypto.so", RTLD_LAZY);
  ASSERT_NE(handle, NULL);

  // Loading symbols from shared library.
  eni_create_t*  eni_create  = (eni_create_t*)::dlsym(handle, "rsa_encrypt_create");
  eni_destroy_t* eni_destroy = (eni_destroy_t*)::dlsym(handle, "rsa_encrypt_destroy");

  // Simulate calling an ENI function.
  char params[] = "[\"-----BEGIN PUBLIC KEY-----\n"
    "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEApr/atzUuBArbsWHkn8tU\n"
    "mq00tCV4CcLfVUVg+zr41sixYIb54rd5EFWoQ1xecYMZIbnoTl2vu9awHBZF18Dk\n"
    "NlG8pjw1Vw5EjaWrCDn734lcKGhsYe20H7138XgznwhJNuAeNy2OOwbEIkSl4jf8\n"
    "Ro+7nOuMK5yeHXAPZEMCnEipd/7gGk0aWP/E1XoqkZJnBUYN5N6mOgtV3jv62w+X\n"
    "lNlozUySI0mBmjgyymAhPm4qx5Zcf/Wmg42vbIFRrBl5PgWKGsY0L7xcPRDPAPRt\n"
    "ndUPr+CLLk5KjyHI8a2WiYrJvjUGTQNyqPM5MmLLfHMkjkbE6DshWbMZona+/5ji\n"
    "3wIDAQAB\n-----END PUBLIC KEY-----\",\"Hello World!\"]";

  void* functor = eni_create(params);
  uint64_t gas = eni_gas(functor);
  char *encrypted = eni_run(functor);
  EXPECT_EQ(gas, 12);

  // Parse return value.
  json::Parser ps(encrypted);
  json::Value val = ps.getRoot();
  ASSERT_TRUE(val.isArray());
  EXPECT_TRUE(val[0].isString());
  EXPECT_EQ(val[0].toString().length(), 512);

  // Finalize.
  eni_destroy(functor);
  delete encrypted;
  ::dlclose(handle);
}

SKYPAT_F(EniCryptoTest, rsa_decrypt)
{
  // Initialize.
  void* handle = ::dlopen("./eni_crypto.so", RTLD_LAZY);
  ASSERT_NE(handle, NULL);

  // Loading symbols from shared library.
  eni_create_t*  eni_create  = (eni_create_t*)::dlsym(handle, "rsa_decrypt_create");
  eni_destroy_t* eni_destroy = (eni_destroy_t*)::dlsym(handle, "rsa_decrypt_destroy");

  // Simulate calling an ENI function.
  char params[] = "[\"-----BEGIN RSA PRIVATE KEY-----\n"
    "MIIEowIBAAKCAQEApr/atzUuBArbsWHkn8tUmq00tCV4CcLfVUVg+zr41sixYIb5\n"
    "4rd5EFWoQ1xecYMZIbnoTl2vu9awHBZF18DkNlG8pjw1Vw5EjaWrCDn734lcKGhs\n"
    "Ye20H7138XgznwhJNuAeNy2OOwbEIkSl4jf8Ro+7nOuMK5yeHXAPZEMCnEipd/7g\n"
    "Gk0aWP/E1XoqkZJnBUYN5N6mOgtV3jv62w+XlNlozUySI0mBmjgyymAhPm4qx5Zc\n"
    "f/Wmg42vbIFRrBl5PgWKGsY0L7xcPRDPAPRtndUPr+CLLk5KjyHI8a2WiYrJvjUG\n"
    "TQNyqPM5MmLLfHMkjkbE6DshWbMZona+/5ji3wIDAQABAoIBAAjwNdAmSJ4s2tPq\n"
    "VHAAXTuhVzbk30deq8wNWQJ+icIxpdhvw8tUXGf0v31E4UciaOF27q3stbPS8UPA\n"
    "KeRD0bfbr8oVZiKRgDk7jSx2tzqnSUpdNpoVPNeKt3g5IkM/FXWck+IPThV56l+P\n"
    "4Hh82cgKglsKAUyBK7SWQiz0rpoj8MWlkG0TblsMVLnOTAO0N3p3NiHxv1eUJrHK\n"
    "wyI42Mkb+nUm1jKSUAg9JuOQJUWcKzlgs8Z4+gvvOukO1tTs4EBMZdn2wYC0+BSE\n"
    "qB0Sx496fuIZ0YPExwF21h2bansEuG2kN5OnW80vnUT724bGvGv3yffyK3fZhE2M\n"
    "WdwDJtkCgYEA3Vw/O8cRxSv6gU4bWH6YE24XQz/pRvOsLLcQeXrxbxvm1ZsD65ou\n"
    "tpvA0/eF3c5KRAhoqgRGPDV7eHvRdo9v6Ih4mwp6wR9bEGU3beHCIjZPb5nCCGtk\n"
    "TCNiVt+MIXKBHXt9lKBjTnmbCvRt+chRz8yFwRpdu49GawOX6NY8YasCgYEAwNfh\n"
    "TbTRawCqC1WY1weFIn9y9NN1reFVvYZhb6stdfBUVAG6vjB0dGG0bZCJUH/+h65/\n"
    "AuvahIugw5AA+H8iTTeB2KpgCc2FmiUviohug39GMz6oabkzZH9KAZjCf5/zMhm3\n"
    "IvtVDMDXBJah7SFYsxM1sBfklPAHFlAe7zP/950CgYBM60IZzonRPv/0MKT18j97\n"
    "+PRibPHtsrywaQhzfhIpLsPek9gf5Vq4H5U40rkUoxtRWq6r7YJOZ7M44aWekicr\n"
    "4Ugvb8vKEdA9+T3yk9E2vDKMMBypek/G2UDRuSpjcPuGuCOiIr1/RmhmvRr+AerT\n"
    "z1jnCfdqNlYc14nQ4ajnswKBgDtlAj6lt25mePketwFbjpTOfkCLtI4Gfhrufaog\n"
    "JdNSXxa0paiYUfXadfDc+H3zvhhaFUJ4FAiI3M3+112yAoWX2AU8jHHYfBK660aW\n"
    "uLsFg0CbRtGxOfP1BH0zaIxYXlYK943trQdNiawfHOZlQ+V7wChpY3y/5N7pdG2m\n"
    "LWs9AoGBAMEgKXwA2ubWrxe622PHXwgUx9oja3LwmuT3oQZDtwxfs4lw3xzIgGps\n"
    "WVvgNL2aceE/qkI032ysKTIbM3JvKa7AzrGKDi8XbyE98QSKM9qyFmdrTG7UIbSo\n"
    "DNen8V4qgCV/z34+6uxWMR7AozgQmzrKogmxhZpIYdyqO4F35cMb\n"
    "-----END RSA PRIVATE KEY-----\",\"395c82afd767e9f94fe050647cc24b83"
    "d53147d495aad8d1fde2a1254bc198bcc98df05c52316bbd9abf3ee897c6e2e44c"
    "0cb2568d5fd57a17fbd466f01d8489ae5b81940c42b83fec69e56b74a02d3ce07a"
    "1e986e42313e2dd15359cef29539a7165549be57c7307b8725fcaa879108599d34"
    "3400f12d518c60317931ab097a1e5b369afb02308b6ff946b08445d5cee78dbd40"
    "c506cea60c7801b5994a7649684f4b97ca38ac4d57c5f4a69f0a0552920bccd0a8"
    "97c642deb2208c74472fe0ba09a0b0c124cfe104b99505e4af90602f62ec6a76f8"
    "dd077ff27cea7d3a5905ccdbcf1cd38bdfc28c55a52bfa30f4d99aa7c62272721c"
    "71adac5b7716262460\"]";

  void* functor = eni_create(params);
  uint64_t gas = eni_gas(functor);
  char *decrypted = eni_run(functor);
  EXPECT_EQ(gas, 256);

  // Parse return value.
  json::Parser ps(decrypted);
  json::Value val = ps.getRoot();
  ASSERT_TRUE(val.isArray());
  EXPECT_TRUE(val[0].isString());
  EXPECT_EQ(val[0].toString(), "Hello World!");

  // Finalize.
  eni_destroy(functor);
  delete decrypted;
  ::dlclose(handle);
}
