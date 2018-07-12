/*==- adt/StringMap.h ------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#ifndef LITY_ADT_STRING_MAP_H
#define LITY_ADT_STRING_MAP_H

#include <adt/StringHashTable.h>

namespace eni {

template<class ValueType>
using StringMap = StringHashTable<ValueType,
                                  internal::StringHasher<internal::SDBM> >;

} // namespace of eni

#endif
