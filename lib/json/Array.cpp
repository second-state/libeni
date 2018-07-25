/*==- json/Array.cpp -------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <json/Array.h>
#include <json/Value.h>

using namespace json;

Array::Array()
  : eni::Vector<Value>(), Notation(ARRAY) {
}

Array::Array(const Array& pArray)
  : eni::Vector<Value>(pArray), Notation(ARRAY) {
}

Array& Array::operator=(const Array& pArray)
{
  eni::Vector<Value>::operator=(pArray);
  Notation::operator=(pArray);
  return *this;
}

void Array::print(std::ostream& os) const
{
  os << '[';
  int i=0;
  for(const Value &e: *this){
    if(i++) os << ',';
    e.print(os);
  }
  os << ']';
}
