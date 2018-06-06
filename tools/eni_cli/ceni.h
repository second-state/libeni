/*==- ceni.h ---------------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#ifndef ENI_CLI_CENI
#define ENI_CLI_CENI

#include <cstdint>

namespace ceni {

typedef void* eni_op_t(char* pArgStr);

enum ExitStatus : uint8_t {
  ExitSuccess = 0,
  ExitFailure = 1,
  ExitParseError,
  ExitLoadError,
  ExitSymError,
  ExitRunError,
  ExitCloseError,
};

} // namespace of ceni

#endif
