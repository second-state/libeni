/*==- adt/StringMap.h ------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#ifndef ENI_ADT_STRING_MAP
#define ENI_ADT_STRING_MAP

#include <adt/StringHashTable.h>

namespace eni {

template<class ValueType>
using StringMap = StringHashTable<ValueType,
                                  internal::StringHasher<internal::SDBM> >;

} // namespace of eni

#endif
