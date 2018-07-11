/*==- lity/diagnostic/DiagList.inc -----------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

  This file is included in both "include/lity/diagnostic/Exception.h"
  and "lib/diagnostic/Exception.cpp".

==------------------------------------------------------------------------==*/
DIAG(Unknown,                 "unknown")
DIAG(Unimplemented,           "not implemented")
DIAG(NoMemory,                "no memory")
DIAG(InvalidDelegateAssigned, "invalid delegation: value has been assigned")
DIAG(InvalidIteratorEmpty,    "invalid iterator: iterator points to nowhere")
DIAG(InvalidVectorIndex,      "invalid access: index out of bound")
DIAG(InvalidVectorSize,       "invalid reserve: exceed maximum size")
