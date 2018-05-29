/*==- ceni.h ---------------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#ifndef ENI_CLI_CENI
#define ENI_CLI_CENI

#include <cstdint>

namespace ceni {

typedef void* eni_create_t(char* pArgStr);
typedef void  eni_destroy_t(void* pFunctor);

extern "C" uint64_t eni_gas(void* pFunctor);
extern "C" char*    eni_run(void *pFunctor);

} // namespace of ceni

#endif
