#ifndef ENI_JSON_PARSER
#define ENI_JSON_PARSER

// dywu(Skymizer)
// this is modified from Boost library(property tree)
// But this is for Solidity ENI
// Only the following types are allowed, otherwisre an error would occur.

// bool
// int
// string
// array
// object
// Note that fraction and null is NOT supported.
// And text are encoded as UTF-8

// TODO:
// - parse escape
// - UTF-8 encoding
// - int

#include <json/Value.h>
#include <json/Callbacks.h>
#include <string>
#include <vector>

namespace json {
// the JSON parser for only JSON text in memory
// read/write files is not supported yet
using std::vector;

class Parser {
public:
  Parser(const std::string &pStr) {
    m_It = m_Start = &pStr[0];
    m_End = &pStr[0] + pStr.length();
    parse_value();
  }

  void parse_value() {
    if (parse_object()) return;
    if (parse_array()) return;
    if (parse_string(false)) return;
    if (parse_boolean()) return;
    if (parse_number()) return;
    parse_error("expected value");
  }

  bool parse_boolean() {
    skip_ws();
    if (have('t')) {
      expect("rue", "expected 'true'");
      m_CBacks.on_boolean(true);
      return true;
    }
    if (have('f')) {
      expect("alse", "expected 'false'");
      m_CBacks.on_boolean(false);
      return true;
    }
    return false;
  }

  bool parse_number() {
    skip_ws();

    vector<char> str;
    bool started = false;
    if (have('-', str))
      started = true;
    if (!have('0', str) && !parse_int_part(str)) {
      if (started) {
        parse_error("expected digits after -");
      }
      return false;
    }
    m_CBacks.on_number(str);
    return true;
  }

  bool parse_string(bool isKey) {
    skip_ws();

    if (!have('\"')) return false;

    vector<char> str;
    while (1) {
      if (have('\"')) break;
      if (m_It == m_End) parse_error("unterminated string");
      if (have('\\')) {
        str.push_back(parse_escape());
      } else {
        // TODO: UTF-8 decoding
        // Current: ASCII (temp)
        // parse_utf8();
        str.push_back(*m_It);
        m_It++;
      }
    }
    // XXX: ?
    // adapter.finish_run();
    m_CBacks.on_string(str, isKey);
    return true;
  }

  bool parse_array() {
    skip_ws();

    if (!have('[')) return false;

    m_CBacks.begin_array();
    skip_ws();
    if (have(']')) { //< empty array
      m_CBacks.end_array();
      return true;
    }
    do {
      parse_value();
      skip_ws();
    } while (have(','));
    expect(']', "expected ']' or ','");
    m_CBacks.end_array();
    return true;
  }

  bool parse_object() {
    skip_ws();
    if (!have('{')) return false;
    // fprintf(stderr, "parsing object\n");

    m_CBacks.begin_object();
    skip_ws();
    if (have('}')) {// empty
      m_CBacks.end_object();
      return true;
    }
    do {
      if (!parse_string(true))
        parse_error("expected key string");
      skip_ws();
      expect(':', "expected ':'");
      parse_value();
      skip_ws();
    } while (have(','));
    expect('}', "expected '}' or ','");
    m_CBacks.end_object();
    return true;
  }
  const Value &getRoot(){
    return m_CBacks.getRoot();
  }
private:
  void skip_ws() {
    while (have(' ') || have('\t') || have('\n') || have('\r'));
  }

  //
  bool parse_int_part(vector<char> &pStr) {
    if (!have(is_pos_digit, pStr)) {
      return false;
    }
    parse_digits(pStr);
    return true;
  }

  // [0-9]+
  void parse_digits(vector<char> &pStr) {
    while (have(is_digit, pStr));
  }

  char parse_escape() {
    if (have('"')){
      return '"';
    } else if (have('\\')) {
      return '\\';
    } else if (have('/')) {
      return '/';
    } else if (have('b')) {
      return '\b'; // backspace
    } else if (have('f')) {
      return '\f'; // formfeed
    } else if (have('n')) {
      return '\n'; // line feed
    } else if (have('r')) {
      return '\r'; // carriage return
    } else if (have('t')) {
      return '\t'; // horizontal tab
    } else if (have('u')) {
      return parse_codepoint();
    } else {
      parse_error("invalid escape sequence");
    }
  }
  char parse_codepoint() {
    std::string str(m_It, m_It+4);
    m_It += 4;
    int code;
    sscanf(str.c_str(), "%X", &code);
    return code;
  }
  vector<char> parse_utf8(){

  }

  bool have(char pCh) {
    if(*m_It == pCh) {
      m_It++;
      return 1;
    }
    return 0;
  }

  bool have(bool (*pF)(char), vector<char> &pStr){
    if(pF(*m_It)){
      pStr.push_back(*m_It);
      m_It++;
      return 1;
    }
    return 0;
  }

  bool have(char pCh, vector<char> &pBuf) {
    if(*m_It == pCh){
      m_It++;
      pBuf.push_back(pCh);
      return 1;
    }
    return 0;
  }

  // this would move the scanner iterator if the pattern is found
  // otherwise the iterator remains the same
  bool have(const char *pPat) {
    int i = 0;
    for(; pPat[i] != '\0'; ++i){
      if((m_End <= pPat+i) || (pPat[i] != m_It[i])) return 0;
    }
    m_It += i;
    return 1;
  }

  void expect(const char pCh, const char* pErrMsg) {
    if (!have(pCh)) {
      parse_error(pErrMsg);
    }
  }

  // check the pattern and output error message if not found
  void expect(const char *pPat, const char* pErrMsg) {
    if (!have(pPat)) {
      parse_error(pErrMsg);
    }
  }

  void parse_error(const char* pErrMsg) {
    // TODO
    std::cerr << pErrMsg;
  }

  template<char C>
  bool is(char pCh) {
    return (pCh == C);
  }

  static bool is_digit(char pCh) {
    return ('0' <= pCh) && (pCh <='9');
  }
  static bool is_pos_digit(char pCh) {
    return ('1' <= pCh) && (pCh <='9');
  }

private:
  const char *m_Start;
  const char *m_End;
  const char *m_It;// scanner iterator, this points to ASCII char instead of UTF-8 char

  Callbacks m_CBacks;
};

}

#endif
