/*==- TypeTag.h ---------------------------------------------------------===

	This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==----------------------------------------------------------------------===*/
#ifndef LITY_ADT_TYPE_TAG_H
#define LITY_ADT_TYPE_TAG_H

#include <cstdlib>

namespace lity {

typedef void* TypeTag;

template<typename ValueType> TypeTag type_tag() { return NULL; }

template<> TypeTag type_tag<bool>();
template<> TypeTag type_tag<int>();
template<> TypeTag type_tag<long>();
template<> TypeTag type_tag<unsigned int>();
template<> TypeTag type_tag<unsigned long>();
template<> TypeTag type_tag<float>();
template<> TypeTag type_tag<double>();
template<> TypeTag type_tag<const char*>();

} // namespace of lity

#endif
