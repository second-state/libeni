/*==- adt/bits/Vector.tcc --------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/

template<class ElementType>
Vector<ElementType>::Vector()
  : m_DataSize(0), m_AllocSize(0), m_Data(nullptr) {
}

template<class ElementType>
Vector<ElementType>::Vector(size_type pSize)
  : m_DataSize(pSize), m_AllocSize(pSize) {
  m_Data = (ElementType*)std::calloc(m_DataSize, sizeof(ElementType));
}

template<class ElementType>
Vector<ElementType>::Vector(size_type pSize, const_reference pValue)
  : m_DataSize(pSize), m_AllocSize(pSize) {
  m_Data = (ElementType*)std::calloc(m_DataSize, sizeof(ElementType));
  std::fill_n(m_Data, m_DataSize, pValue);
}

template<class ElementType>
Vector<ElementType>::Vector(const std_vector& pVector)
  : m_DataSize(pVector.size()), m_AllocSize(pVector.size()) {
  m_Data = (ElementType*)std::calloc(m_DataSize, sizeof(ElementType));
  std::copy(pVector.begin(), pVector.end(), m_Data);
}

template<class ElementType>
Vector<ElementType>::Vector(const Vector& pOther)
  : m_DataSize(pOther.m_DataSize), m_AllocSize(pOther.m_DataSize) {
  m_Data = (ElementType*)std::calloc(m_DataSize, sizeof(ElementType));
  std::copy(pOther.begin(), pOther.end(), m_Data);
}

template<class ElementType>
Vector<ElementType>::Vector(initializer_list pIList)
  : m_DataSize(pIList.size()), m_AllocSize(pIList.size()) {
  m_Data = (ElementType*)std::calloc(m_DataSize, sizeof(ElementType));
  std::copy(pIList.begin(), pIList.end(), m_Data);
}

template<class ElementType>
Vector<ElementType>::~Vector()
{
  clear();
}

template<class ElementType> Vector<ElementType>&
Vector<ElementType>::operator=(const Vector<ElementType>& pOther)
{
  assign(pOther.begin(), pOther.end());
  return *this;
}

template<class ElementType> Vector<ElementType>&
Vector<ElementType>::operator=(initializer_list pIList)
{
  assign(pIList);
  return *this;
}

template<class ElementType> typename Vector<ElementType>::iterator
Vector<ElementType>::begin()
{
  return iterator(m_Data);
}

template<class ElementType> typename Vector<ElementType>::const_iterator
Vector<ElementType>::begin() const
{
  return const_iterator(m_Data);
}

template<class ElementType> typename Vector<ElementType>::iterator
Vector<ElementType>::end()
{
  return iterator(m_Data + m_DataSize);
}

template<class ElementType> typename Vector<ElementType>::const_iterator
Vector<ElementType>::end() const
{
  return const_iterator(m_Data + m_DataSize);
}

template<class ElementType> typename Vector<ElementType>::size_type
Vector<ElementType>::size() const
{
  return m_DataSize;
}

template<class ElementType> typename Vector<ElementType>::size_type
Vector<ElementType>::max_size() const
{
  return std::numeric_limits<size_t>::max();
}

template<class ElementType> void
Vector<ElementType>::resize(size_type pSize)
{
  resize(pSize, value_type());
}

template<class ElementType> void
Vector<ElementType>::resize(size_t pSize, const ElementType& pValue)
{
  reserve(pSize);
  if (pSize > m_DataSize)
    std::fill_n(end(), pSize - m_DataSize, pValue);
  m_DataSize = pSize;
}

template<class ElementType> bool
Vector<ElementType>::empty() const
{
  return 0 == size();
}

template<class ElementType> typename Vector<ElementType>::size_type
Vector<ElementType>::capacity() const
{
  return m_AllocSize;
}

template<class ElementType> void
Vector<ElementType>::reserve(size_type pSize)
{
  if (pSize <= capacity()) //< no need to allocate
    return;
  if (pSize > max_size()) //< too much to be allocated
    throw LengthError<InvalidVectorSize>();
  else {
    size_type targetSize = capacity();
    while (targetSize < pSize && targetSize < max_size()) {
      targetSize = (targetSize > 0) ? targetSize * 2 : 1;
    }
    if (targetSize > max_size())
      targetSize = max_size();
    pointer ptr = (ElementType*)std::realloc(m_Data, sizeof(ElementType) * targetSize);
    if (nullptr == ptr) //< not enough memory
      throw BadAlloc<NoMemory>();
    else {
      m_Data = ptr;
      m_AllocSize = pSize;
    }
  }
}

template<class ElementType> void
Vector<ElementType>::shrink_to_fit()
{
  // Not implemented (allowed by the spec).
}

template<class ElementType> typename Vector<ElementType>::reference
Vector<ElementType>::operator[](size_type pIndex)
{
  return m_Data[pIndex];
}

template<class ElementType> typename Vector<ElementType>::const_reference
Vector<ElementType>::operator[](size_type pIndex) const
{
  return m_Data[pIndex];
}

template<class ElementType> typename Vector<ElementType>::const_reference
Vector<ElementType>::at(size_type pIndex) const
{
  if (0 > pIndex || pIndex >= size()) {
    throw OutOfRange<InvalidVectorIndex>();
  }
  return m_Data[pIndex];
}

template<class ElementType> typename Vector<ElementType>::reference
Vector<ElementType>::at(size_type pIndex)
{
  if (0 > pIndex || pIndex >= size()) {
    throw OutOfRange<InvalidVectorIndex>();
  }
  return m_Data[pIndex];
}

template<class ElementType> typename Vector<ElementType>::reference
Vector<ElementType>::front()
{
  return m_Data[0];
}

template<class ElementType> typename Vector<ElementType>::reference
Vector<ElementType>::back()
{
  return m_Data[size() - 1];
}

template<class ElementType> typename Vector<ElementType>::pointer
Vector<ElementType>::data()
{
  return m_Data;
}

template<class ElementType> void
Vector<ElementType>::assign(size_type pSize, const_reference pValue)
{
  resize(pSize);
  std::fill_n(m_Data, pSize, pValue);
}

template<class ElementType> void
Vector<ElementType>::assign(const_iterator pFirst, const_iterator pLast)
{
  resize(pLast - pFirst);
  std::copy(pFirst, pLast, m_Data);
}

template<class ElementType> void
Vector<ElementType>::assign(initializer_list pIList)
{
  assign(pIList.begin(), pIList.end());
}

template<class ElementType> void
Vector<ElementType>::push_back(const_reference pValue)
{
  reserve(size() + 1);
  m_Data[m_DataSize++] = pValue;
}

template<class ElementType> typename Vector<ElementType>::value_type
Vector<ElementType>::pop_back()
{
  return m_Data[--m_DataSize];
}

template<class ElementType>
template<class ...Args> void
Vector<ElementType>::emplace_back(Args&& ...pArgs)
{
  reserve(size() + 1);
  m_Data[m_DataSize++] = *(new ElementType(std::forward<Args>(pArgs)...));
}

template<class ElementType> typename Vector<ElementType>::iterator
Vector<ElementType>::insert(iterator pIt, const_reference pValue)
{
  size_type index = pIt - begin();
  insert(index, pValue);
  return iterator(m_Data + index);
}

template<class ElementType> typename Vector<ElementType>::iterator
Vector<ElementType>::insert(iterator pIt, size_type pSize, const_reference pValue)
{
  size_type index = pIt - begin();
  insert(index, pSize, pValue);
  return iterator(m_Data + index);
}

template<class ElementType> typename Vector<ElementType>::iterator
Vector<ElementType>::insert(iterator pIt, const_iterator pFirst, const_iterator pLast)
{
  size_type index = pIt - begin();
  insert(index, pFirst, pLast);
  return Vector<ElementType>::iterator(m_Data + index);
}

template<class ElementType> typename Vector<ElementType>::iterator
Vector<ElementType>::insert(iterator pIt, initializer_list pIList)
{
  size_type index = pIt - begin();
  insert(index, pIList);
  return iterator(m_Data + index);
}

template<class ElementType> void
Vector<ElementType>::insert(size_type pIndex, const_reference pValue)
{
  insert(pIndex, 1, pValue);
}

template<class ElementType> void
Vector<ElementType>::insert(size_type pIndex, size_type pSize, const_reference pValue)
{
  if (0 > pIndex || pIndex > size()) {
    throw OutOfRange<InvalidVectorIndex>();
  }
  resize(size() + pSize);
  pointer ptr = m_Data + pIndex;
  pointer end = m_Data + size();
  std::copy_backward(ptr, end - pSize, end);
  std::fill_n(ptr, pSize, pValue);
}

template<class ElementType> void
Vector<ElementType>::insert(size_type pIndex, const_iterator pFirst, const_iterator pLast)
{
  if (0 > pIndex || pIndex > size()) {
    throw OutOfRange<InvalidVectorIndex>();
  }
  size_type insertSize = pLast - pFirst;
  resize(size() + insertSize);
  pointer ptr = m_Data + pIndex;
  pointer end = m_Data + size();
  std::copy_backward(ptr, end - insertSize, end);
  std::copy(pFirst, pLast, ptr);
}

template<class ElementType> void
Vector<ElementType>::insert(size_type pIndex, initializer_list pIList)
{
  insert(pIndex, pIList.begin(), pIList.end());
}

template<class ElementType> typename Vector<ElementType>::iterator
Vector<ElementType>::erase(iterator pIt)
{
  size_type index = pIt - begin();
  erase(index);
  return iterator(m_Data + index);
}

template<class ElementType> typename Vector<ElementType>::iterator
Vector<ElementType>::erase(iterator pFirst, iterator pLast)
{
  size_type index = pFirst - begin();
  erase(index, pLast - begin());
  return iterator(m_Data + index);
}

template<class ElementType> void
Vector<ElementType>::erase(size_type pIndex)
{
  erase(pIndex, pIndex + 1);
}

template<class ElementType> void
Vector<ElementType>::erase(size_type pFirst, size_type pLast)
{
  if (0 > pFirst || pFirst >= pLast || pLast >= size())
    throw OutOfRange<InvalidVectorIndex>();
  size_type eraseSize = pLast - pFirst;
  std::copy(m_Data + pLast, m_Data + size(), m_Data + pFirst);
  resize(size() - eraseSize);
}

template<class ElementType> void
Vector<ElementType>::swap(Vector<ElementType>& pOther)
{
  std::swap(m_Data, pOther.m_Data);
  std::swap(m_DataSize, pOther.m_DataSize);
  std::swap(m_AllocSize, pOther.m_AllocSize);
}

template<class ElementType>
void Vector<ElementType>::clear()
{
  if (nullptr != m_Data) {
    std::free(m_Data);
    m_Data = nullptr;
  }
  m_DataSize = 0;
  m_AllocSize = 0;
}
