/*==- diagnostic/Exception.cpp ---------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <diagnostic/Exception.h>

namespace eni {
namespace internal {

/*==------------------------------------------------------------------------==
  ExceptionBase (full template specialization goes here)
==------------------------------------------------------------------------==*/
#define DIAG(ID, MSG) \
  const std::string ExceptionBase<ID>::ErrStr = MSG;
#include <diagnostic/DiagList.inc>
#undef DIAG

} // namespace of internal
} // namespace of eni
