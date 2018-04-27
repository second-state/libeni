#ifndef ENI_JSON_TYPE
#define ENI_JSON_TYPE

namespace json {

enum Type {
  INT,    ///< JSON's int
  BOOL,   ///< JSON's boolean (true, false)
  STRING, ///< JSON's string " ... " or (not really JSON) ' ... '
  OBJECT, ///< JSON's object { ... }
  ARRAY,  ///< JSON's array [ ... ]
  UNDEF   ///< Undefined
};

} // namespace of json

#endif
