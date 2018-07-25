/*==- adt/bits/PointerIterator.tcc -----------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/

template<typename ItemType>
PointerIterator<ItemType>::PointerIterator(pointer pPtr)
  : m_Ptr(pPtr) {
}

template<typename ItemType>
PointerIterator<ItemType>::PointerIterator(const_reference pRef)
  : m_Ptr(&pRef) {
}

template<typename ItemType>
PointerIterator<ItemType>::PointerIterator(const_iterator& pOther)
  : m_Ptr(pOther.m_Ptr) {
}

template<typename ItemType> typename PointerIterator<ItemType>::iterator&
PointerIterator<ItemType>::operator=(const_iterator& pOther)
{
  m_Ptr = pOther.m_Ptr;
}

template<typename ItemType> typename PointerIterator<ItemType>::reference
PointerIterator<ItemType>::operator*()
{
  return *(this->operator->());
}

template<typename ItemType> typename PointerIterator<ItemType>::const_reference
PointerIterator<ItemType>::operator*() const
{
  return *(this->operator->());
}

template<typename ItemType> typename PointerIterator<ItemType>::pointer
PointerIterator<ItemType>::operator->()
{
  return m_Ptr;
}

template<typename ItemType> typename PointerIterator<ItemType>::const_pointer
PointerIterator<ItemType>::operator->() const
{
  return m_Ptr;
}

template<typename ItemType> typename PointerIterator<ItemType>::iterator&
PointerIterator<ItemType>::operator++()
{
  ++m_Ptr;
  return *this;
}

template<typename ItemType> typename PointerIterator<ItemType>::iterator
PointerIterator<ItemType>::operator++(int)
{
  iterator it = *this;
  ++m_Ptr;
  return it;
}

template<typename ItemType> typename PointerIterator<ItemType>::iterator&
PointerIterator<ItemType>::operator--()
{
  --m_Ptr;
  return *this;
}

template<typename ItemType> typename PointerIterator<ItemType>::iterator
PointerIterator<ItemType>::operator--(int)
{
  iterator it = *this;
  --m_Ptr;
  return it;
}

template<typename ItemType> typename PointerIterator<ItemType>::iterator&
PointerIterator<ItemType>::operator+=(size_type pOffset)
{
  m_Ptr += pOffset;
  return *this;
}

template<typename ItemType> typename PointerIterator<ItemType>::iterator
PointerIterator<ItemType>::operator+(size_type pOffset)
{
  return iterator(m_Ptr + pOffset);
}

template<typename ItemType> typename PointerIterator<ItemType>::iterator&
PointerIterator<ItemType>::operator-=(size_type pOffset)
{
  m_Ptr -= pOffset;
  return *this;
}

template<typename ItemType> typename PointerIterator<ItemType>::iterator
PointerIterator<ItemType>::operator-(size_type pOffset)
{
  return iterator(m_Ptr - pOffset);
}

template<typename ItemType> typename PointerIterator<ItemType>::difference_type
PointerIterator<ItemType>::operator-(iterator pOther)
{
  return m_Ptr - pOther.m_Ptr;
}

template<typename ItemType> typename PointerIterator<ItemType>::reference
PointerIterator<ItemType>::operator[](size_type pOffset)
{
  return *(this->operator+(pOffset));
}

template<typename ItemType> bool
PointerIterator<ItemType>::operator<(const_iterator& pOther) const
{
  return ((pOther.m_Ptr - m_Ptr) > 0);
}

template<typename ItemType> bool
PointerIterator<ItemType>::operator>(const_iterator& pOther) const
{
  return m_Ptr > pOther.m_Ptr;
}

template<typename ItemType> bool
PointerIterator<ItemType>::operator<=(const_iterator& pOther) const
{
  return !(this->operator>(pOther));
}

template<typename ItemType> bool
PointerIterator<ItemType>::operator>=(const_iterator& pOther) const
{
  return !(this->operator<(pOther));
}

template<typename ItemType> bool
PointerIterator<ItemType>::operator==(const_iterator& pOther) const
{
  return m_Ptr == pOther.m_Ptr;
}

template<typename ItemType> bool
PointerIterator<ItemType>::operator!=(const_iterator& pOther) const
{
  return !(this->operator==(pOther));
}
