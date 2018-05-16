#include <json/Object.h>

using namespace json;
typedef unsigned uint;

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

void Object::print(std::ostream &os) const {
    os<<'{';
    uint i = 0;
        os<<'\n';
    for(std::pair<std::string, Value> v: *this){
        if(i++)os<<",\n";
        os<<v.first<<':';
        v.second.print(os);
    }
    os<<'\n';
    os<<'}';
}
