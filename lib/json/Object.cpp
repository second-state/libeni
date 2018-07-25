/*==- json/Object.cpp ------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <json/Object.h>

using namespace json;

Object::Object()
  : eni::StringMap<Value>(), Notation(OBJECT) {
}

Object::Object(const Object& pCopy)
 : eni::StringMap<Value>(pCopy), Notation(OBJECT) {
}

Object& Object::operator=(const Object& pCopy)
{
  eni::StringMap<Value>::operator=(pCopy);
  Notation::operator=(pCopy);
  return *this;
}

void Object::print(std::ostream& pOs) const {
  pOs << '{';
  pOs << '\n';
  bool first = true;
  eni::StringMap<Value>::const_iterator it, itEnd = end();
  for (it = begin(); it != itEnd; ++it) {
    if (!first)
      pOs << ',';
    else
      first = false;
    pOs << it->key() << ':';
    it->value().print(pOs);
  }
  pOs << '\n';
  pOs << '}';
}
