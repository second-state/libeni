/*==- adt/PointerIterator.h ------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#ifndef ENI_ADT_POINTER_ITERATOR
#define ENI_ADT_POINTER_ITERATOR

#include <diagnostic/Exception.h>
#include <cstddef>
#include <iterator>

namespace eni {

/** \class PointerIterator
 *  \brief PointerIterator supports random access to continuous memory.
 */
template<typename ItemType>
class PointerIterator : public std::iterator<std::random_access_iterator_tag,
                                             ItemType>
{
public:
  typedef ItemType value_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef value_type&       reference;
  typedef const value_type& const_reference;

  typedef PointerIterator<ItemType>        iterator;
  typedef const PointerIterator<ItemType>  const_iterator;

public:
  PointerIterator(pointer pPtr);

  PointerIterator(const_reference pRef);

  PointerIterator(const_iterator& pOther);

  iterator& operator=(const_iterator& pOther);

  /// @name C++ Iterator
  /// @{
  reference operator*();

  iterator& operator++();
  /// @}

  /// @name C++ Forward Iterator
  /// @{
  iterator operator++(int);
  /// @}

  /// @name C++ Bidirectional Iterator
  /// @{
  iterator& operator--();
  iterator operator--(int);
  /// @}

  /// @name C++ Random-Access Iterator
  /// @{
  iterator& operator+=(size_type pOffset);
  iterator operator+(size_type pOffset);

  iterator& operator-=(size_type pOffset);
  iterator operator-(size_type pOffset);

  difference_type operator-(iterator pOther);

  reference operator[](size_type pOffset);

  bool operator<(const_iterator& pOther) const;
  bool operator>(const_iterator& pOther) const;
  bool operator<=(const_iterator& pOther) const;
  bool operator>=(const_iterator& pOther) const;
  /// @}

  bool operator==(const_iterator& pOther) const;
  bool operator!=(const_iterator& pOther) const;

private:
  pointer m_Ptr;
};

#include "bits/PointerIterator.tcc"

} // namespace of eni

#endif
