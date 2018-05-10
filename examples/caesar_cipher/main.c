#include <dlfcn.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef void* eni_create_t(char* pArgStr);
typedef void  eni_destroy_t(void* pFunctor);

extern uint64_t eni_gas(void* pFunctor);
extern char*    eni_run(void *pFunctor);

int main(int argc, char* argv[])
{
  if (argc < 3)
    return -1;

  void* handle = dlopen("./eni_caesar_cipher.so", RTLD_LAZY);
  if (NULL == handle)
    return 1;

  /* Loading symbols from shared library. */
  eni_create_t*  caesar_encrypt_create  = dlsym(handle, "caesar_encrypt_create");
  eni_destroy_t* caesar_encrypt_destroy = dlsym(handle, "caesar_encrypt_destroy");
  eni_create_t*  caesar_decrypt_create  = dlsym(handle, "caesar_decrypt_create");
  eni_destroy_t* caesar_decrypt_destroy = dlsym(handle, "caesar_decrypt_destroy");

  /* Construct JSON parameters. */
  size_t data_len = strlen(argv[1]);
  size_t seed_len = strlen(argv[2]);
  char* params = (char*)malloc(data_len + seed_len + 10);
  sprintf(params, "[\"%s\",\"%s\"]", argv[1], argv[2]);
  printf("params: %s\n", params);

  /* Simulate calling an ENI function. */
  /* Encrypt data with seed */
  void* functor = caesar_encrypt_create(params);
  uint64_t gas = eni_gas(functor);
  char *retval = eni_run(functor);
  printf("gas: %llu\n", (unsigned long long)gas);
  printf("ret: %s\n", retval);
  caesar_encrypt_destroy(functor);
  free(params);

  /* Decrypt retval with seed */
  char *strtmp = (char*)malloc(strlen(retval));
  strcpy(strtmp, retval+3);
  strtmp[strlen(strtmp)-2] = '\0';
  data_len = strlen(strtmp);
  params = (char*)malloc(data_len + seed_len + 10);
  sprintf(params, "[\"%s\",\"%s\"]", strtmp, argv[2]);
  printf("params: %s\n", params);
  functor = caesar_decrypt_create(params);
  gas = eni_gas(functor);
  free(retval);
  retval = eni_run(functor);
  printf("gas: %llu\n", (unsigned long long)gas);
  printf("ret: %s\n", retval);
  caesar_encrypt_destroy(functor);

  free(strtmp);
  free(retval);
  free(params);

  dlclose(handle);
  return 0;
}
