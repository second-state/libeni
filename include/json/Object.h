/*==- json/Object.h --------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#ifndef ENI_JSON_OBJECT
#define ENI_JSON_OBJECT

#include <json/Value.h>
#include <string>
#include <map>

namespace json {

class Object : private std::map<std::string, Value>, public Notation
{
public:
  using std::map<std::string, Value>::operator[];

public:
  Object();

  Object(const Object& pCopy);

  Object& operator=(const Object& pCopy);

  ~Object() { }

  void print(std::ostream &os) const;
};

} // namespace of json

#endif
