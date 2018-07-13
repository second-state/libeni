/*==- adt/Vector.h ---------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#ifndef ENI_ADT_VECTOR
#define ENI_ADT_VECTOR

#include <adt/PointerIterator.h>
#include <diagnostic/Exception.h>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <string>
#include <stdexcept>
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
  typedef PointerIterator<ElementType>        iterator;
  typedef PointerIterator<const ElementType>  const_iterator;

public:
  Vector();
  explicit Vector(size_t n);
  Vector(size_t n, const ElementType& value);
  Vector(const std::vector<ElementType>& stdVector);
  Vector(const Vector& x);
  Vector(std::initializer_list<ElementType> ilist);

  ~Vector();

  Vector& operator=(const Vector& x);
  Vector& operator=(std::initializer_list<ElementType> ilist);

  iterator begin();
  iterator end();

  size_t size() const;
  size_t max_size() const;
  void resize(size_t n);
  void resize(size_t n, const ElementType& value);

  bool empty() const;
  size_t capacity() const;
  void reserve(size_t n);
  void shrink_to_fit();

  ElementType& operator[](size_t index);
  ElementType& at(size_t index);
  ElementType& front();
  ElementType& back();
  ElementType* data();

  void assign(iterator first, iterator last);
  void assign(const std::vector<ElementType>& stdVector);
  void assign(size_t n, const ElementType& value);
  void assign(std::initializer_list<ElementType> ilist);

  void push_back(const ElementType& value);
  ElementType pop_back();

  iterator insert(iterator position, const ElementType& value);
  iterator insert(iterator position, size_t n, const ElementType& value);
  iterator insert(iterator position, const std::vector<ElementType>& stdVector);
  iterator insert(iterator position, std::initializer_list<ElementType> ilist);
  void insert(size_t index, const ElementType& value);
  void insert(size_t index, size_t n, const ElementType& value);
  void insert(size_t index, const std::vector<ElementType>& stdVector);
  void insert(size_t index, std::initializer_list<ElementType> ilist);

  iterator erase(iterator position);
  iterator erase(iterator first, iterator last);
  void erase(size_t position);
  void erase(size_t first, size_t last);

  void swap(Vector& x);
  void clear();

protected:
  virtual void grow_memory();

private:
  ElementType* dataArr;
  size_t elementSize;
  size_t allocatedSize;
};

#include "bits/Vector.tcc"

} // namespace of eni

#endif
