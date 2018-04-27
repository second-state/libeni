#ifndef ENI_JSON_CALLBACKS
#define ENI_JSON_CALLBACKS

#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <json/Type.h>
#include <json/Object.h>
#include <json/Array.h>
#include <eni_types.h>

namespace json {

using std::string;
using std::pair;
using std::make_pair;
using std::vector;

class Callbacks {
public:
  Callbacks() { }

  void on_boolean(bool b) {
    Value v(b);
    set_parent(v);
  }

  void on_number(const vector<char> &pStr) {
    Value v;
    string s(pStr.cbegin(),pStr.cend());
    eni::s256 i(s);
    v.delegate(i);
    set_parent(v);
  }

  void on_string(const vector<char> &pStr, bool pIsKey) {
    if(pIsKey) {
      m_Stack.back().second = string(pStr.begin(), pStr.end());
    }
    else {
      string s(pStr.begin(), pStr.end());
      Value v(s);
      set_parent(v);
    }
  }

  void begin_array() {
    Array a;
    Value v(a);
    m_Stack.push_back(make_pair(v, ""));
  }

  void end_array() {
    Value v = m_Stack.back().first;
    m_Stack.pop_back();
    set_parent(v);
  }

  void begin_object() {
    Object o;
    Value v(o);
    m_Stack.push_back(make_pair(v,""));
  }

  void end_object() {
    Value v = m_Stack.back().first;
    m_Stack.pop_back();
    set_parent(v);
  }

  // set v's parent as the top element in m_Stack
  void set_parent(Value pV) {
    if (m_Stack.empty()) {
      m_Root = pV;
      return;
    }
    Value &par = m_Stack.back().first;
    string key = m_Stack.back().second;
    if (par.isObject()) {
      par.asObject()[key] = pV;
    }
    else if (par.isArray()) {
      par.asArray().push_back(pV);
    }
  }

  void print(std::ostream &os) {
    m_Root.print(os);
  }

  const Value &getRoot() {
    return m_Root;
  }

private:
  vector<pair<Value, string>> m_Stack;
  Value m_Root;
};

} // namespace of json

#endif
