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
      pOs << ",\n";
    pOs << v.first << ':';
    v.second.print(pOs);
  }
  pOs << '\n';
  pOs << '}';
}
