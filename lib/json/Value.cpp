#include <json/Value.h>
#include <json/Object.h>
#include <json/Array.h>
#include <eni_types.h>
#include <string>
using namespace json;

static Value g_NullValue(UNDEF); // XXX

Value::Value(const Value& pCopy)
  : Notation(pCopy) {
  switch (this->type()) {
    case INT:
      m_Value.int_p = new eni::s256(*pCopy.m_Value.int_p);
      break;
    case BOOL:
      m_Value.bool_p = pCopy.m_Value.bool_p;
      break;
    case STRING:
      m_Value.string_p = new string(*pCopy.m_Value.string_p);
      break;
    case OBJECT:
      m_Value.object_p = new Object(*pCopy.m_Value.object_p);
      break;
    case ARRAY:
      m_Value.array_p = new Array(*pCopy.m_Value.array_p);
      break;
    case UNDEF:
      break;
  }
}

Value::Value(const string& pString)
  : Notation(STRING) {
  m_Value.string_p = new string(pString);
}

Value::Value(const eni::s256& pSint)
  : Notation(INT) {
  m_Value.int_p = new eni::s256(pSint);
}

Value::Value(const Object& pObject)
  : Notation(OBJECT) {
  m_Value.object_p = new Object(pObject);
}

Value::Value(const Array& pArray)
  : Notation(ARRAY) {
  m_Value.array_p = new Array(pArray);
}

Value::~Value()
{
  switch (this->type()) {
    case STRING:
      delete m_Value.string_p;
      break;
    case OBJECT:
      delete m_Value.object_p;
      break;
    case ARRAY:
      delete m_Value.array_p;
      break;
    default:
      break;
  }
  m_Value.reset();
  setType(UNDEF);
}


Value& Value::delegate(eni::s256& pSint)
{
  assert(this->isUndefined() && "Value has been assigned");
  m_Type = INT;
  m_Value.int_p = &pSint;
  return *this;
}

Value& Value::delegate(Object& pObject)
{
  assert(this->isUndefined() && "Value has been assigned");
  m_Type = OBJECT;
  m_Value.object_p = &pObject;
  return *this;
}

Value& Value::delegate(Array& pArray)
{
  assert(this->isUndefined() && "Value has been assigned");
  m_Type = ARRAY;
  m_Value.array_p = &pArray;
  return *this;
}

void Value::print(std::ostream &os) const
{
  switch (this->type()) {
    case INT:
      os << *m_Value.int_p;
      break;
    case BOOL:
      os << (m_Value.bool_p? "true": "false");
      break;
    case STRING: {
      os << '"';
      string::const_iterator c, end = m_Value.string_p->end();
      for (c = m_Value.string_p->begin(); c != end; ++c) {
        if ((*c == '"') || (*c == '\\')){
          os << '\\' << *c;
        } else if (0<=*c && *c<0x20){
          char str[11];
          sprintf(str, "%04X", *c);
          os << "\\u" << str;
        } else {
          os << *c;
        }
      }
      os << '"';
      break;
    }
    case OBJECT:
      m_Value.object_p->print(os);
      break;
    case ARRAY:
      m_Value.array_p->print(os);
      break;
    case UNDEF:
      break;
  }
}

void Value::printValue(std::ostream &os) const
{
  os << "(" << m_Type << "," << m_Value.pointer << ")\n";
}


Value& Value::operator=(const Value& pCopy)
{
  Notation::operator=(pCopy);
  switch (this->type()) {
    case INT:
      m_Value.int_p = new eni::s256(*pCopy.m_Value.int_p);
      break;
    case BOOL:
      m_Value.bool_p = pCopy.m_Value.bool_p;
      break;
    case STRING:
      m_Value.string_p = new string(*pCopy.m_Value.string_p);
      break;
    case OBJECT:
      m_Value.object_p = new Object(*pCopy.m_Value.object_p);
      break;
    case ARRAY:
      m_Value.array_p = new Array(*pCopy.m_Value.array_p);
      break;
    case UNDEF:
      break;
  }
  return *this;
}


// beware that parameter key might be assigned from an integer
// because (string <= char <= int) is available
// by the HOLLY string& operator= (char c)
// compiler WONT warn you
Value& Value::operator[](const std::string &key)
{
  if(m_Type == OBJECT) {
    return asObject()[key];
  }
  return g_NullValue;
}

const Value& Value::operator[](const std::string &key) const
{
  if (m_Type == OBJECT) {
    return (*m_Value.object_p)[key];
  }
  return g_NullValue;
}

Value& Value::operator[](int i)
{
  if (m_Type == ARRAY) {
    return asArray()[i];
  }
  return g_NullValue;
}

const Value& Value::operator[](int i) const
{
  if (m_Type == ARRAY) {
    return (*m_Value.array_p)[i];
  }
  return g_NullValue;
}
