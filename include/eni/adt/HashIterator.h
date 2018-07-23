/*==- adt/HashIterator.h ---------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#ifndef ENI_ADT_HASH_ITERATOR
#define ENI_ADT_HASH_ITERATOR

#include <diagnostic/Exception.h>
#include <cstddef>

namespace eni {

/** \class ChainIterBase
 *  \brief ChainIterBase follows the HashEntry with the same hash value.
 */
template<typename HashTable>
class ChainIterBase
{
public:
  typedef HashTable hash_table;
  typedef typename HashTable::key_type key_type;
  typedef typename HashTable::entry_type entry_type;
  typedef typename HashTable::bucket_type bucket_type;

private:
  typedef ChainIterBase<hash_table>       self;
  typedef ChainIterBase<const hash_table> const_self;

public:
  ChainIterBase();
  ChainIterBase(HashTable* pTable, const key_type& pKey);
  ChainIterBase(HashTable* pTable, unsigned int pIndex,
                unsigned int pHashValue, unsigned pEndIndex);
  ChainIterBase(const self& pCopy);

  self& assign(const self& pCopy);

  const bucket_type* getBucket() const;
  bucket_type*       getBucket();

  const entry_type* getEntry() const;
  entry_type*       getEntry();

  void reset();

  void advance();

  bool equals(const self& pCopy) const;

  /// const conversion
  operator const_self() const {
    return const_self(m_pHashTable, m_Index, m_HashValue, m_EndIndex);
  }

private:
  HashTable* m_pHashTable;
  unsigned int m_Index;
  unsigned int m_HashValue;
  unsigned int m_EndIndex;
};

/** \class EntryIterBase
 *  \brief EntryIterBase walks over hash table by the natural layout of the
 *  buckets
 */
template<typename HashTable>
class EntryIterBase
{
public:
  typedef HashTable hash_table;
  typedef typename HashTable::key_type key_type;
  typedef typename HashTable::entry_type entry_type;
  typedef typename HashTable::bucket_type bucket_type;

private:
  typedef EntryIterBase<hash_table>       self;
  typedef EntryIterBase<const hash_table> const_self;

public:
  EntryIterBase();
  EntryIterBase(HashTable* pTable, unsigned int pIndex);
  EntryIterBase(const self& pCopy);

  self& assign(const self& pCopy);

  const bucket_type* getBucket() const;
  bucket_type*       getBucket();

  const entry_type* getEntry() const;
  entry_type* getEntry();

  void reset();

  void advance();

  bool equals(const self& pCopy) const;

  /// const conversion
  operator const_self() const {
    return const_self(m_pHashTable, m_Index);
  }

private:
  HashTable* m_pHashTable;
  unsigned int m_Index;
};

/** \class HashIterator
 *  \brief HashIterator provides a policy-based iterator.
 *
 *  HashTable has two kinds of iterators. One is used to traverse buckets
 *  with the same hash value; the other is used to traverse all entries of the
 *  hash table.
 *
 *  HashIterator is a template policy-based iterator, which can change its
 *  behavior by change the template argument IteratorImpl. HashTable defines
 *  above two iterators by defining HashIterators with different IteratorImpl.
 */
template<template<class> class IteratorImpl, class TableType>
class HashIterator : public std::iterator<std::forward_iterator_tag,
                                          typename TableType::entry_type>
{
public:
  typedef size_t    size_type;
  typedef ptrdiff_t difference_type;

  typedef IteratorImpl<TableType>         impl_type;
  typedef typename impl_type::key_type    key_type;
  typedef typename impl_type::entry_type  entry_type;
  typedef typename impl_type::bucket_type bucket_type;

  typedef const entry_type* const_pointer;
  typedef       entry_type* pointer;
  typedef const entry_type& const_reference;
  typedef       entry_type& reference;

private:
  typedef IteratorImpl<const TableType>               const_impl_type;
  typedef HashIterator<IteratorImpl, TableType>       self;
  typedef HashIterator<IteratorImpl, const TableType> const_self;

public:
  HashIterator() : m_Impl() { }

  /// HashIterator - constructor for EntryIterator
  HashIterator(TableType* pTable, unsigned int pIndex)
    : m_Impl(pTable, pIndex) {
  }

  /// HashIterator - constructor for ChainIterator
  HashIterator(TableType* pTable, const key_type& pKey, int)
    : m_Impl(pTable, pKey) {
  }

  HashIterator(const self& pCopy) : m_Impl(pCopy.m_Impl) { }

  ~HashIterator() { }

  HashIterator& operator=(const self& pCopy) {
    m_Impl.assign(pCopy.m_Impl);
    return *this;
  }

  bool operator==(const self& pCopy) const {
    return m_Impl.equals(pCopy.m_Impl);
  }

  bool operator!=(const self& pCopy) const {
    return !(this->operator==(pCopy));
  }

  const_pointer   operator->() const { return m_Impl.getEntry(); }
  pointer         operator->()       { return m_Impl.getEntry(); }

  /// @name C++ Iterator (dereferenceable)
  /// @{
  const_reference operator*() const { return *m_Impl.operator->(); }
  reference       operator*()       { return *m_Impl.operator->(); }
  /// @}

  /// @name C++ Iterator (incrementable)
  /// @{
  self& operator++() {
    m_Impl.advance();
    return *this;
  }
  /// @}

  /// @name C++ Forward Iterator
  /// @{
  self operator++(int) {
    self tmp = *this;
    m_Impl.advance();
    return tmp;
  }
  /// @}

  /// @name const conversion
  /// @{
  operator const_self() const {
    return const_self(m_Impl);
  }

  HashIterator(const const_impl_type& pImpl) : m_Impl(pImpl) { }
  /// @}

private:
  impl_type m_Impl;
};

#include "bits/HashIterator.tcc"

} // namespace of eni

#endif
