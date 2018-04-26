#ifndef C_ETHEREUM_NATIVE_INTERFACE
#define C_ETHEREUM_NATIVE_INTERFACE

#include <stdint.h>

typedef void*    eni_create_t(char* pArgStr);
typedef uint64_t eni_gas_t(void* pFunctor);
typedef char*    eni_run_t(void* pFunctor);
typedef void     eni_destroy_t(void* pFunctor);

#endif
