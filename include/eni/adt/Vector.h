/*==- adt/Vector.h ---------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#ifndef ENI_ADT_VECTOR
#define ENI_ADT_VECTOR

#include <adt/PointerIterator.h>
#include <diagnostic/Exception.h>
#include <algorithm>
#include <cstdlib>
#include <limits>
#include <initializer_list>
#include <vector>

namespace eni {

/** \class Vector
 *  \brief Vector is a container with continuous memory
 */
template<class ElementType>
class Vector
{
public:
  typedef ElementType value_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef value_type&       reference;
  typedef const value_type& const_reference;

  typedef PointerIterator<ElementType>        iterator;
  typedef PointerIterator<const ElementType>  const_iterator;

  typedef std::vector<ElementType>            std_vector;
  typedef std::initializer_list<ElementType>  initializer_list;

public:
  Vector();
  explicit Vector(size_type pSize);
  Vector(size_type pSize, const_reference pValue);
  Vector(const std_vector& pVector);
  Vector(const Vector& pOther);
  Vector(initializer_list pIList);

  virtual ~Vector();

  Vector& operator=(const Vector& pOther);
  Vector& operator=(initializer_list pIList);

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  size_type size() const;
  size_type max_size() const;
  void resize(size_type pSize);
  void resize(size_type pSize, const_reference value);

  bool empty() const;
  size_type capacity() const;
  void reserve(size_type pSize);
  void shrink_to_fit();

  reference operator[](size_type pIndex);
  reference at(size_type pIndex);
  reference front();
  reference back();
  pointer data();

  void assign(size_type pSize, const_reference pValue);
  void assign(const_iterator pFirst, const_iterator pLast);
  void assign(initializer_list pIList);

  void push_back(const_reference value);
  value_type pop_back();

  iterator insert(iterator pIt, const_reference pValue);
  iterator insert(iterator pIt, size_type pSize, const_reference pValue);
  iterator insert(iterator pIt, const_iterator pFirst, const_iterator pLast);
  iterator insert(iterator pIt, initializer_list pIList);
  void insert(size_type pIndex, const_reference pValue);
  void insert(size_type pIndex, size_type pSize, const_reference pValue);
  void insert(size_type pIndex, const_iterator pFirst, const_iterator pLast);
  void insert(size_type pIndex, initializer_list pIList);

  iterator erase(iterator pIt);
  iterator erase(iterator pFirst, iterator pLast);
  void erase(size_type pIndex);
  void erase(size_type pFirst, size_type pLast);

  void swap(Vector& pOther);
  void clear();

private:
  pointer m_Data;
  size_type m_DataSize;
  size_type m_AllocSize;
};

#include "bits/Vector.tcc"

} // namespace of eni

#endif
