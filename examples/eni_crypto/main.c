#include <dlfcn.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef void* eni_create_t(char* pArgStr);
typedef void  eni_destroy_t(void* pFunctor);

extern uint64_t eni_gas(void* pFunctor);
extern char*    eni_run(void *pFunctor);

static const char priv_key[] = "-----BEGIN RSA PRIVATE KEY-----\n"
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
"-----END RSA PRIVATE KEY-----";

static const char pub_key[] = "-----BEGIN PUBLIC KEY-----\n"
"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEApr/atzUuBArbsWHkn8tU\n"
"mq00tCV4CcLfVUVg+zr41sixYIb54rd5EFWoQ1xecYMZIbnoTl2vu9awHBZF18Dk\n"
"NlG8pjw1Vw5EjaWrCDn734lcKGhsYe20H7138XgznwhJNuAeNy2OOwbEIkSl4jf8\n"
"Ro+7nOuMK5yeHXAPZEMCnEipd/7gGk0aWP/E1XoqkZJnBUYN5N6mOgtV3jv62w+X\n"
"lNlozUySI0mBmjgyymAhPm4qx5Zcf/Wmg42vbIFRrBl5PgWKGsY0L7xcPRDPAPRt\n"
"ndUPr+CLLk5KjyHI8a2WiYrJvjUGTQNyqPM5MmLLfHMkjkbE6DshWbMZona+/5ji\n"
"3wIDAQAB\n"
"-----END PUBLIC KEY-----";

int main(int argc, char* argv[])
{
  if (argc < 2)
    return -1;

  void* handle = dlopen("./eni_crypto.so", RTLD_LAZY);
  if (NULL == handle)
    return 1;

  /* Loading symbols from shared library. */
  eni_create_t*  encrypt_create  = dlsym(handle, "rsa_encrypt_create");
  eni_destroy_t* encrypt_destroy = dlsym(handle, "rsa_encrypt_destroy");
  eni_create_t*  decrypt_create  = dlsym(handle, "rsa_decrypt_create");
  eni_destroy_t* decrypt_destroy = dlsym(handle, "rsa_decrypt_destroy");

  /* Construct JSON parameters. ["Public Key","Message"] */
  size_t len = 2 + sizeof(pub_key) + 3 + strlen(argv[1]) + 2;
  char* params = (char*)malloc(len);
  snprintf(params, len, "[\"%s\",\"%s\"]", pub_key, argv[1]);

  fprintf(stderr, "%s\n", params);

  /* Simulate calling an ENI function. */
  void* functor = encrypt_create(params);
  uint64_t gas = eni_gas(functor);
  char *encrypted = eni_run(functor);
  printf("gas: %llu\n", (unsigned long long)gas);
  encrypt_destroy(functor);

  free(params);

  /* Construct JSON parameters. ["Private Key","Message"] */
  len = 2 + sizeof(priv_key) + 3 + strlen(encrypted) + 2;
  params = (char*)malloc(len);
  snprintf(params, len, "[\"%s\",\"%s\"]", priv_key, encrypted);

  fprintf(stderr, "%s\n", params);

  /* Simulate calling an ENI function. */
  functor = decrypt_create(params);
  gas = eni_gas(functor);
  char *decrypted = eni_run(functor);
  printf("gas: %llu\n", (unsigned long long)gas);
  printf("ret: %s\n", decrypted);
  decrypt_destroy(functor);

  free(encrypted);
  free(decrypted);
  free(params);

  dlclose(handle);
  return 0;
}
