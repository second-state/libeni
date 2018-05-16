#ifndef ENI_JSON_NOTATION
#define ENI_JSON_NOTATION

#include <json/Type.h>

namespace json {

class Notation
{
public:
  Notation();

  Notation(Type pType);

  Notation(const Notation& pCopy);

  Notation(Notation&& pOther);

  virtual ~Notation() { }

  Notation& operator=(const Notation& pCopy);

  Notation& operator=(Notation&& pCopy);

  Type type() const { return m_Type; }

  bool isInteger()  const { return (INT == m_Type); }
  bool isBoolean()   const { return (BOOL == m_Type); }
  bool isString()    const { return (STRING == m_Type); }
  bool isObject()    const { return (OBJECT == m_Type); }
  bool isArray()     const { return (ARRAY == m_Type); }
  bool isUndefined() const { return (UNDEF == m_Type); }

protected:
  void setType(Type pType) { m_Type = pType; }

protected:
  Type m_Type;
};

} // namespace of json

#endif
