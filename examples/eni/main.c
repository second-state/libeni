#include <dlfcn.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef void* eni_create_t(char* pArgStr);
typedef void  eni_destroy_t(void* pFunctor);

extern uint64_t    eni_gas(void* pFunctor);
extern const char* eni_run(void *pFunctor);

int main(int argc, char* argv[])
{
  if (argc < 2)
    return -1;

  void* handle = dlopen("./eni_reverse.so", RTLD_LAZY);
  if (NULL == handle)
    return 1;

  /* Loading symbols from shared library. */
  eni_create_t*  eni_create  = dlsym(handle, "reverse_create");
  eni_destroy_t* eni_destroy = dlsym(handle, "reverse_destroy");

  /* Construct JSON parameters. */
  size_t len = strlen(argv[1]);
  char* params = (char*)malloc(len + 5);
  params[0] = '[';
  params[1] = '\"';
  strcpy(params + 2, argv[1]);
  params[len + 2] = '\"';
  params[len + 3] = ']';
  params[len + 4] = '\0';

  printf("params: %s\n", params);

  /* Simulate calling an ENI function. */
  void* functor = eni_create(params);
  uint64_t gas = eni_gas(functor);
  const char *retval = eni_run(functor);
  printf("gas: %llu\n", (unsigned long long)gas);
  printf("ret: %s\n", retval);
  eni_destroy(functor);

  free(retval);
  free(params);

  dlclose(handle);
  return 0;
}
