/*==- adt/StringMap.h ------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#ifndef ENI_ADT_STRING_MAP
#define ENI_ADT_STRING_MAP

#include <adt/StringHashTable.h>
#include <diagnostic/Exception.h>

namespace eni {

namespace {

typedef internal::StringHasher<internal::SDBM> HasherType;

} // annonymous namespace

template<class ValueType>
class StringMap : private StringHashTable<ValueType, HasherType>
{
public:
  typedef StringHashTable<ValueType, HasherType> super;

  using typename super::entry_type;
  using typename super::key_type;
  using typename super::value_type;
  using typename super::size_type;

  using typename super::iterator;
  using typename super::const_iterator;

  using typename super::empty;
  using typename super::erase;
  using typename super::find;
  using typename super::begin;
  using typename super::end;

public:
  explicit StringMap(size_type pSize = 8) : super(pSize) { }

  StringMap(const StringMap& pCopy) : super(pCopy) { }

  StringMap(StringMap&& pOther) : super(pOther) { }

  ~StringMap() { }

  StringMap& operator=(const StringMap& pCopy) {
    super::operator=(pCopy);
  }

  StringMap& operator=(StringMap&& pOther) {
    super::operator=(pOther);
  }

  value_type& at(const key_type& pKey) {
    iterator it = super::find(pKey);
    if (it == this->end())
      throw OutOfRange<InvalidStringMapKey>();
    return it->value();
  }

  const value_type& at(const key_type& pKey) const {
    const_iterator it = super::find(pKey);
    if (it == this->end())
      throw OutOfRange<InvalidStringMapKey>();
    return it->value();
  }

  value_type& operator[](const key_type& pKey) {
    bool exist = false;
    entry_type* entry = super::insert(pKey, exist);
    return entry->value();
  }

  const value_type& operator[](const key_type& pKey) const {
    return at(pKey);
  }

  size_type size() const { return super::numOfEntries(); }
};

} // namespace of eni

#endif
