#include <json/Array.h>
#include <json/Value.h>

using namespace json;

Array::Array()
  : std::vector<Value>(), Notation(ARRAY) {
}

Array::Array(const Array& pArray)
  : std::vector<Value>(pArray), Notation(ARRAY) {
}

Array& Array::operator=(const Array& pArray)
{
  std::vector<Value>::operator=(pArray);
  Notation::operator=(pArray);
  return *this;
}

void Array::print(std::ostream& os) const
{
  os << "[ ";
  for(const Value &e: *this){
    e.print(os);
    os << ",";
    os << ' ';
  }
  os << ']';
}
