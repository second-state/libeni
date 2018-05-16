#ifndef ENI_JSON_VALUE
#define ENI_JSON_VALUE

#include <string>
#include <cstring>
#include <iostream>

#include <json/Notation.h>
#include <eni_types.h>

namespace json {

using std::string;
class Object;
class Array;

class Value : public Notation
{
public:
  Value() { }

  explicit Value(bool pB) : Notation(BOOL) { m_Value.bool_p = pB; }
  explicit Value(const string& pString);

  Value(const eni::s256& pValue);
  Value(const Object& pObject);
  Value(const Array& pArray);

  Value(const Value& pCopy);

  Value& delegate(eni::s256& pValue);
  Value& delegate(json::Object& pObject);
  Value& delegate(json::Array& pArray);

  eni::s256& asInteger() { return *m_Value.int_p; }
  string& asString() { return *m_Value.string_p; }
  Object& asObject() { return *m_Value.object_p; }
  Array& asArray() { return *m_Value.array_p; }

  bool toBoolean() const { return m_Value.bool_p; }
  const eni::s256& toInteger() const { return *m_Value.int_p; }
  const string& toString() const { return *m_Value.string_p; }
  const Object& toObject() const { return *m_Value.object_p; }
  const Array& toArray() const { return *m_Value.array_p; }

  void print(std::ostream &os) const;
  void printValue(std::ostream &os) const;

  Value& operator[](const std::string &key);
  const Value& operator[](const std::string &key) const;

  Value& operator[](int i);
  const Value& operator[](int i) const;

private:
  union Holder
  {
  public:
    eni::s256*    int_p;
    bool          bool_p;
    string*       string_p;
    Object*       object_p;
    Array*        array_p;
    void*         pointer;
  public:
    Holder() { reset(); }

    ~Holder() { }

    void reset() { ::memset(this, 0, sizeof(Holder)); }
  };

private:
  Holder m_Value;
};

} // namespace of json

#endif
