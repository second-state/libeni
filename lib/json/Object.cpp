/*==- json/Object.cpp ------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <json/Object.h>

using namespace json;

Object::Object()
  : std::map<std::string, Value>(), Notation(OBJECT) {
}

Object::Object(const Object& pCopy)
 : std::map<std::string, Value>(pCopy), Notation(OBJECT) {
}

Object& Object::operator=(const Object& pCopy)
{
  std::map<std::string, Value>::operator=(pCopy);
  Notation::operator=(pCopy);
  return *this;
}

void Object::print(std::ostream& pOs) const {
  pOs << '{';
  unsigned int i = 0;
  pOs << '\n';
  for (std::pair<std::string, Value> v: *this) {
    if(i++)
      pOs << ',';
    pOs << v.first << ':';
    v.second.print(pOs);
  }
  pOs << '\n';
  pOs << '}';
}
