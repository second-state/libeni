#ifndef ENI_JSON_ARRAY
#define ENI_JSON_ARRAY

#include <json/Notation.h>
#include <vector>
#include <iostream>

namespace json {

class Value;

class Array : public std::vector<Value>, public Notation
{
public:
  Array();

  ~Array() { }

  Array(const Array& pArray);

  Array& operator=(const Array& pArray);

  void print(std::ostream &os) const;
};

} // namespace json

#endif
