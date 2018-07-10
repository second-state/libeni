/*===- lity/adt/bits/Vector.tcc ------------------------------------------===

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==----------------------------------------------------------------------===*/

using namespace lity;

template<class ElementType>
Vector<ElementType>::Vector()
  : elementSize(0), allocatedSize(0), dataArr(nullptr) {
}

template<class ElementType>
Vector<ElementType>::Vector(size_t n)
  : elementSize(n), allocatedSize(n) {
  dataArr = (ElementType*)calloc(n, sizeof(ElementType));
}

template<class ElementType>
Vector<ElementType>::Vector(size_t n, const ElementType& value)
  : elementSize(n), allocatedSize(n) {
  dataArr = (ElementType*)calloc(n, sizeof(ElementType));
  for (Vector<ElementType>::iterator it = begin(); it != end(); ++it) {
    *it = value;
  }
}

template<class ElementType>
Vector<ElementType>::Vector(std::vector<ElementType>& stdVector)
  : elementSize(stdVector.size()), allocatedSize(stdVector.size()) {
  dataArr = (ElementType*)calloc(stdVector.size(), sizeof(ElementType));
  Vector<ElementType>::iterator myIt = begin();
  for (typename std::vector<ElementType>::iterator it = stdVector.begin(); it != stdVector.end(); ++it, ++myIt) {
    *myIt = *it;
  }
}

template<class ElementType>
Vector<ElementType>::Vector(Vector& x)
  : elementSize(x.elementSize), allocatedSize(x.elementSize) {
  dataArr = (ElementType*)calloc(x.elementSize, sizeof(ElementType));
  for (Vector<ElementType>::iterator myIt = begin(), xIt = x.begin(); myIt != end(); ++myIt, ++xIt) {
    *myIt = *xIt;
  }
}

template<class ElementType>
Vector<ElementType>::Vector(std::initializer_list<ElementType> ilist)
  : elementSize(ilist.size()), allocatedSize(ilist.size()) {
  dataArr = (ElementType*)calloc(ilist.size(), sizeof(ElementType));
  Vector<ElementType>::iterator myIt = begin();
  for (typename std::initializer_list<ElementType>::iterator iIt = ilist.begin(); iIt != ilist.end(); ++myIt, ++iIt) {
    *myIt = *iIt;
  }
}

template<class ElementType>
Vector<ElementType>::~Vector()
{
  if (dataArr) {
    free(dataArr);
    dataArr = nullptr;
  }
}

template<class ElementType>
Vector<ElementType>& Vector<ElementType>::operator=(const Vector<ElementType>& x)
{
  resize(x.elementSize);
  for (Vector<ElementType>::iterator myIt = begin(), xIt = x.begin(); myIt != end(); ++myIt, ++xIt) {
    *myIt = *xIt;
  }
  return *this;
}

template<class ElementType>
Vector<ElementType>& Vector<ElementType>::operator=(std::initializer_list<ElementType> ilist)
{
  resize(ilist.size());
  Vector<ElementType>::iterator myIt = begin();
  for (typename std::initializer_list<ElementType>::iterator iIt = ilist.begin(); iIt != ilist.end(); ++myIt, ++iIt) {
    *myIt = *iIt;
  }
  return *this;
}

template<class ElementType>
typename Vector<ElementType>::iterator Vector<ElementType>::begin()
{
  return Vector<ElementType>::iterator(dataArr);
}

template<class ElementType>
typename Vector<ElementType>::iterator Vector<ElementType>::end()
{
  return Vector<ElementType>::iterator(dataArr + elementSize);
}

template<class ElementType>
size_t Vector<ElementType>::size()
{
  return elementSize;
}

template<class ElementType>
size_t Vector<ElementType>::max_size()
{
  return ((size_t) 0 - 1) / sizeof(ElementType);
}

template<class ElementType>
void Vector<ElementType>::resize(size_t n)
{
  if (n > max_size()) {
    throw Vector<ElementType>::bad_alloc(ENOMEM);
  }
  else {
    if (n > allocatedSize && allocatedSize != max_size()) {
      dataArr = (ElementType*)realloc(dataArr, n);
      if (errno) {
        int err = errno;
        throw Vector<ElementType>::bad_alloc(err);
      }
      allocatedSize = n;
    }
    elementSize = n;
  }
}

template<class ElementType>
void Vector<ElementType>::resize(size_t n, const ElementType& value)
{
  if (n > max_size()) {
    throw Vector<ElementType>::bad_alloc(ENOMEM);
  }
  else {
    if (n > allocatedSize && allocatedSize != max_size()) {
      dataArr = (ElementType*)realloc(dataArr, n);
      if (errno) {
        int err = errno;
        throw Vector<ElementType>::bad_alloc(err);
      }
      for (size_t i = allocatedSize; i < n; ++i) {
        dataArr[i] = value;
      }
      allocatedSize = n;
    }
    elementSize = n;
  }
}

template<class ElementType>
bool Vector<ElementType>::empty()
{
  return elementSize == 0;
}

template<class ElementType>
size_t Vector<ElementType>::capacity()
{
  return allocatedSize;
}

template<class ElementType>
void Vector<ElementType>::reserve(size_t n)
{
  if (n > allocatedSize) {
    if (n > max_size()) {
      throw std::length_error("Vector: reserve size exceed max size");
    }
    resize(n);
  }
}

template<class ElementType>
void Vector<ElementType>::shrink_to_fit()
{
  if (allocatedSize > elementSize) {
    dataArr = (ElementType*)realloc(dataArr, elementSize);
    if (errno) {
      int err = errno;
      throw Vector<ElementType>::bad_alloc(err);
    }
    allocatedSize = elementSize;
  }
}

template<class ElementType>
ElementType& Vector<ElementType>::operator[](size_t index)
{
  return dataArr[index];
}

template<class ElementType>
ElementType& Vector<ElementType>::at(size_t index)
{
  if (index >= elementSize || index < 0) {
    throw std::out_of_range("Vector: index out of range");
  }
  return dataArr[index];
}

template<class ElementType>
ElementType& Vector<ElementType>::front()
{
  return dataArr[0];
}

template<class ElementType>
ElementType& Vector<ElementType>::back()
{
  return dataArr[elementSize - 1];
}

template<class ElementType>
ElementType* Vector<ElementType>::data()
{
  return dataArr;
}

template<class ElementType>
void Vector<ElementType>::assign(Vector<ElementType>::iterator first, Vector<ElementType>::iterator last)
{
  resize(last - first);
  for (Vector<ElementType>::iterator myIt = begin(), xIt = first; xIt != last; ++myIt, ++xIt) {
    *myIt = *xIt;
  }
}

template<class ElementType>
void Vector<ElementType>::assign(std::vector<ElementType>& stdVector)
{
  resize(stdVector.size());
  Vector<ElementType>::iterator myIt = begin();
  for (typename std::vector<ElementType>::iterator it = stdVector.begin(); it != stdVector.end(); ++it, ++myIt) {
    *myIt = *it;
  }
}

template<class ElementType>
void Vector<ElementType>::assign(size_t n, const ElementType& value)
{
  resize(n);
  for (Vector<ElementType>::iterator myIt = begin(); myIt != end(); ++myIt) {
    *myIt = value;
  }
}

template<class ElementType>
void Vector<ElementType>::assign(std::initializer_list<ElementType> ilist)
{
  resize(ilist.size());
  Vector<ElementType>::iterator myIt = begin();
  for (typename std::initializer_list<ElementType>::iterator it = ilist.begin(); it != ilist.end(); ++it, ++myIt) {
    *myIt = *it;
  }
}

template<class ElementType>
void Vector<ElementType>::push_back(const ElementType& value)
{
  if (elementSize == allocatedSize) {
    grow_memory();
  }
  dataArr[elementSize++] = value;
}

template<class ElementType>
ElementType Vector<ElementType>::pop_back()
{
  return dataArr[--elementSize];
}

template<class ElementType>
typename Vector<ElementType>::iterator Vector<ElementType>::insert(Vector<ElementType>::iterator position, const ElementType& value)
{
  size_t index = position - begin();
  insert(index, value);
  return Vector<ElementType>::iterator(dataArr + index);
}

template<class ElementType>
typename Vector<ElementType>::iterator Vector<ElementType>::insert(Vector<ElementType>::iterator position, size_t n, const ElementType& value)
{
  size_t index = position - begin();
  insert(index, n, value);
  return Vector<ElementType>::iterator(dataArr + index);
}

template<class ElementType>
typename Vector<ElementType>::iterator Vector<ElementType>::insert(Vector<ElementType>::iterator position, std::initializer_list<ElementType> ilist)
{
  size_t index = position - begin();
  insert(index, ilist);
  return Vector<ElementType>::iterator(dataArr + index);
}

template<class ElementType>
typename Vector<ElementType>::iterator Vector<ElementType>::insert(Vector<ElementType>::iterator position, std::vector<ElementType>& stdVector)
{
  size_t index = position - begin();
  insert(index, stdVector);
  return Vector<ElementType>::iterator(dataArr + index);
}

template<class ElementType>
void Vector<ElementType>::insert(size_t index, std::vector<ElementType>& stdVector)
{
  size_t n = stdVector.size();
  if (index > elementSize) {
    throw std::out_of_range("Vector: index out of range");
  }
  resize(elementSize + n);
  for (size_t i = elementSize - 1; i >= index + n; --i) {
    dataArr[i] = dataArr[i - n];
  }
  for (size_t i = index, j = 0; i < index + n; ++i, ++j) {
    dataArr[i] = stdVector[j];
  }
}

template<class ElementType>
void Vector<ElementType>::insert(size_t index, const ElementType& value)
{
  if (index > elementSize) {
    throw std::out_of_range("Vector: index out of range");
  }
  resize(elementSize + 1);
  for (size_t i = elementSize - 1; i > index; --i) {
    dataArr[i] = dataArr[i - 1];
  }
  dataArr[index] = value;
}

template<class ElementType>
void Vector<ElementType>::insert(size_t index, size_t n, const ElementType& value)
{
  if (index > elementSize) {
    throw std::out_of_range("Vector: index out of range");
  }
  resize(elementSize + n);
  for (size_t i = elementSize - 1; i >= index + n; --i) {
    dataArr[i] = dataArr[i - n];
  }
  for (size_t i = index; i < index + n; ++i) {
    dataArr[i] = value;
  }
}

template<class ElementType>
void Vector<ElementType>::insert(size_t index, std::initializer_list<ElementType> ilist)
{
  size_t n = ilist.size();
  if (index > elementSize) {
    throw std::out_of_range("Vector: index out of range");
  }
  resize(elementSize + n);
  for (size_t i = elementSize - 1; i >= index + n; --i) {
    dataArr[i] = dataArr[i - n];
  }
  typename std::initializer_list<ElementType>::iterator it = ilist.begin();
  for (size_t i = index; i < index + n; ++i, ++it) {
    dataArr[i] = *it;
  }
}

template<class ElementType>
typename Vector<ElementType>::iterator Vector<ElementType>::erase(Vector<ElementType>::iterator position)
{
  Vector<ElementType>::iterator ret = position;
  for (Vector<ElementType>::iterator it = position + 1; it != end(); ++it, ++position) {
    *position = *it;
  }
  pop_back();
  return ret;
}

template<class ElementType>
typename Vector<ElementType>::iterator Vector<ElementType>::erase(Vector<ElementType>::iterator first, Vector<ElementType>::iterator last)
{
  Vector<ElementType>::iterator ret = first;
  size_t reducedSize = last - first;
  for (Vector<ElementType>::iterator it = last + 1; it != end(); ++it, ++first) {
    *first = *it;
  }
  resize(elementSize - reducedSize - 1);
  return ret;
}

template<class ElementType>
void Vector<ElementType>::erase(size_t position)
{
  for (; position < elementSize - 1; ++position) {
    dataArr[position] = dataArr[position + 1];
  }
  pop_back();
}

template<class ElementType>
void Vector<ElementType>::erase(size_t first, size_t last) {
  size_t reducedSize = last - first;
  for (size_t i = last + 1; i < elementSize; ++i, ++first) {
    dataArr[first] = dataArr[i];
  }
  resize(elementSize - reducedSize - 1);
}

template<class ElementType>
void Vector<ElementType>::swap(Vector<ElementType>& x)
{
  // Compare
  Vector<ElementType>* largePtr;
  Vector<ElementType>* smallPtr;
  if (elementSize >= x.elementSize) {
    largePtr = this;
    smallPtr = &x;
  }
  else {
    largePtr = &x;
    smallPtr = this;
  }
  // Swap small one
  for (Vector<ElementType>::iterator lIt = largePtr->begin(), sIt = smallPtr->begin(); sIt != smallPtr->end(); ++lIt, ++sIt) {
    *lIt ^= *sIt;
    *sIt = *lIt ^ *sIt;
    *lIt ^= *sIt;
  }
  // Save origin size
  size_t lSize = largePtr->elementSize, sSize = smallPtr->elementSize;
  // Remainer
  smallPtr->resize(lSize);
  for (Vector<ElementType>::iterator lIt = largePtr->begin() + sSize, sIt = smallPtr->begin() + sSize; sIt != smallPtr->end(); ++lIt, ++sIt) {
    *sIt = *lIt;
  }
  largePtr->resize(sSize);
}

template<class ElementType>
void Vector<ElementType>::clear()
{
  free(dataArr);
  dataArr = nullptr;
  elementSize = 0;
  allocatedSize = 0;
}

template<class ElementType>
void Vector<ElementType>::grow_memory()
{
  if (allocatedSize != max_size()) {
    size_t suggested = (allocatedSize != 0) ? allocatedSize * 2 : 1;
    if (suggested > max_size()) {
      suggested = max_size();
    }
    dataArr = (ElementType*)realloc(dataArr, sizeof(ElementType) * suggested);
    allocatedSize = suggested;
  }
}
