/*==- json/Array.h ---------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#ifndef ENI_JSON_ARRAY
#define ENI_JSON_ARRAY

#include <json/Notation.h>
#include <adt/Vector.h>
#include <iostream>

namespace json {

class Value;

class Array : public eni::Vector<Value>, public Notation
{
public:
  Array();

  ~Array() { }

  Array(const Array& pArray);

  Array& operator=(const Array& pArray);

  const Value& operator[](int pIdx) const { return this->at(pIdx); }

  void print(std::ostream &os) const;
};

} // namespace json

#endif
