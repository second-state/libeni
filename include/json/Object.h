#ifndef ENI_JSON_OBJECT
#define ENI_JSON_OBJECT

#include <json/Value.h>
#include <string>
#include <map>

namespace json {

class Object : public std::map<std::string, Value>, public Notation
{
public:
  Object();

  Object(const Object& pCopy);

  Object& operator=(const Object& pCopy);

  ~Object() { }

  void print(std::ostream &os) const;
};

} // namespace of json

#endif
