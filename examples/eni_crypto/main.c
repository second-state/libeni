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
  if (argc < 2)
    return -1;

  void* handle = dlopen("./eni_crypto.so", RTLD_LAZY);
  if (NULL == handle)
    return 1;

  /* TODO: Loading symbols from shared library. */

  /* TODO: Construct JSON parameters. */

  /* TODO: Simulate calling an ENI function. */

  dlclose(handle);
  return 0;
}
