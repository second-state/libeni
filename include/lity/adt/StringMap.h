/*===- lity/adt/StringMap.h ----------------------------------------------===

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==----------------------------------------------------------------------===*/
#ifndef LITY_ADT_STRING_MAP_H
#define LITY_ADT_STRING_MAP_H
#include <lity/adt/StringHashTable.h>

namespace lity {

template<class ValueType>
using StringMap = StringHashTable<ValueType,
                                  internal::StringHasher<internal::SDBM> >;

} // namespace of lity

#endif
