#include <dlfcn.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef void*    eni_create_t(char* pArgStr);
typedef uint64_t eni_gas_t(void* pFunctor);
typedef char*    eni_run_t(void* pFunctor);
typedef void     eni_destroy_t(void* pFunctor);

int main(int argc, char* argv[])
{
  if (argc < 2)
    return -1;

  void* handle = dlopen("./eni_reverse.so", RTLD_LAZY);
  if (NULL == handle)
    return 1;

  eni_create_t*  eni_create  = dlsym(handle, "eni_create");
  eni_gas_t*     eni_gas     = dlsym(handle, "eni_gas");
  eni_run_t*     eni_run     = dlsym(handle, "eni_run");
  eni_destroy_t* eni_destroy = dlsym(handle, "eni_destroy");

  void* functor = eni_create(argv[1]);
  printf("gas: %llu\n", (unsigned long long)eni_gas(functor));
  printf("ret: %s\n", eni_run(functor));
  eni_destroy(functor);

  dlclose(handle);
  return 0;
}
