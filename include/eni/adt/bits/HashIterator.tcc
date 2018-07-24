/*==- adt/bits/HashIterator.tcc --------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/

/*==------------------------------------------------------------------------==
  ChainIterBase
==------------------------------------------------------------------------==*/
template<typename HT>
ChainIterBase<HT>::ChainIterBase()
  : m_pHashTable(0), m_Index(0), m_HashValue(0), m_EndIndex(0) {
}

template<typename HT>
ChainIterBase<HT>::ChainIterBase(HT* pTable, const key_type& pKey)
  : m_pHashTable(pTable) {
  typename HT::hasher_type hasher;
  m_HashValue = hasher(pKey);
  m_EndIndex = m_Index = m_HashValue % m_pHashTable->numOfBuckets();
  const unsigned int probe = 1;
  while(true) {
    bucket_type &bucket = m_pHashTable->bucket(m_Index);
    if (hash_table::Tombstone() == bucket.entry) {
      // Ignore tombstones.
    }
    else if (m_HashValue == bucket.hash) {
      if (bucket.entry->key() == pKey) {
        m_EndIndex = m_Index;
        break;
      }
    }

    m_Index += probe;
    if (m_Index == m_pHashTable->numOfBuckets())
      m_Index = 0;
    // doesn't exist
    if (m_EndIndex == m_Index) {
      reset();
      break;
    }
  }
}
template<typename HT>
ChainIterBase<HT>::ChainIterBase(HT* pTable, unsigned int pIndex,
                                 unsigned int pHashValue, unsigned pEndIndex)
  : m_pHashTable(pTable), m_Index(pIndex), m_HashValue(pHashValue),
    m_EndIndex(pEndIndex) {
}

template<typename HT>
ChainIterBase<HT>::ChainIterBase(const ChainIterBase& pCopy)
  : m_pHashTable(pCopy.m_pHashTable),
    m_Index(pCopy.m_Index),
    m_HashValue(pCopy.m_HashValue),
    m_EndIndex(pCopy.m_EndIndex) {
}

template<typename HT> ChainIterBase<HT>&
ChainIterBase<HT>::assign(const ChainIterBase& pCopy)
{
  m_pHashTable = pCopy.m_pHashTable;
  m_Index = pCopy.m_Index;
  m_HashValue = pCopy.m_HashValue;
  m_EndIndex = pCopy.m_EndIndex;
  return *this;
}

template<typename HT>
typename ChainIterBase<HT>::bucket_type*
ChainIterBase<HT>::getBucket()
{
  if (nullptr == m_pHashTable)
    throw LogicError<InvalidIteratorEmpty>();
  return &(m_pHashTable->bucket(m_Index));
}

template<typename HT>
const typename ChainIterBase<HT>::bucket_type*
ChainIterBase<HT>::getBucket() const
{
  if (nullptr == m_pHashTable)
    throw LogicError<InvalidIteratorEmpty>();
  return &(m_pHashTable->bucket(m_Index));
}

template<typename HT>
const typename ChainIterBase<HT>::entry_type*
ChainIterBase<HT>::getEntry() const
{
  if (nullptr == m_pHashTable)
    throw LogicError<InvalidIteratorEmpty>();
  return m_pHashTable->bucket(m_Index).entry;
}

template<typename HT>
typename ChainIterBase<HT>::entry_type*
ChainIterBase<HT>::getEntry()
{
  if (nullptr == m_pHashTable)
    throw LogicError<InvalidIteratorEmpty>();
  return m_pHashTable->bucket(m_Index).entry;
}

template<typename HT>
void ChainIterBase<HT>::reset()
{
  m_pHashTable = NULL;
  m_Index = 0;
  m_EndIndex = 0;
  m_HashValue = 0;
}

template<typename HT>
void ChainIterBase<HT>::advance()
{
  if (0 == m_pHashTable)
    return;

  const unsigned int probe = 1;
  while(true) {
    m_Index += probe;
    if (m_Index == m_pHashTable->numOfBuckets())
      m_Index = 0;
    // reach end()
    if (m_Index == m_EndIndex) {
      reset();
      return;
    }

    const bucket_type &bucket = m_pHashTable->bucket(m_Index);

    if (hash_table::Tombstone() == bucket.entry ||
        hash_table::EmptyBucket() == bucket.entry) {
      // Ignore tombstones.
    }
    else if (m_HashValue == bucket.hash) {
      return;
    }
  }
}

template<typename HT> bool
ChainIterBase<HT>::equals(const ChainIterBase& pCopy) const
{
  if (m_pHashTable == pCopy.m_pHashTable) {
    if (0 == m_pHashTable)
      return true;
    return ((m_HashValue == pCopy.m_HashValue) &&
            (m_EndIndex == pCopy.m_EndIndex) &&
            (m_Index == pCopy.m_Index));
  }
  return false;
}

/*==------------------------------------------------------------------------==
  EntryIterBase
==------------------------------------------------------------------------==*/
template<typename HT>
EntryIterBase<HT>::EntryIterBase()
  : m_pHashTable(0), m_Index(0) {
}

template<typename HT>
EntryIterBase<HT>::EntryIterBase(HT* pTable, unsigned int pIndex)
  : m_pHashTable(pTable), m_Index(pIndex) {
}

template<typename HT>
EntryIterBase<HT>::EntryIterBase(const EntryIterBase& pCopy)
  : m_pHashTable(pCopy.m_pHashTable), m_Index(pCopy.m_Index) {
}

template<typename HT> EntryIterBase<HT>&
EntryIterBase<HT>::assign(const EntryIterBase& pCopy)
{
  m_pHashTable = pCopy.m_pHashTable;
  m_Index = pCopy.m_Index;
  return *this;
}

template<typename HT>
typename EntryIterBase<HT>::bucket_type*
EntryIterBase<HT>::getBucket()
{
  if (nullptr == m_pHashTable)
    throw LogicError<InvalidIteratorEmpty>();
  return &(m_pHashTable->bucket(m_Index));
}

template<typename HT>
const typename EntryIterBase<HT>::bucket_type*
EntryIterBase<HT>::getBucket() const
{
  if (nullptr == m_pHashTable)
    throw LogicError<InvalidIteratorEmpty>();
  return &(m_pHashTable->bucket(m_Index));
}

template<typename HT>
typename EntryIterBase<HT>::entry_type*
EntryIterBase<HT>::getEntry()
{
  if (nullptr == m_pHashTable)
    throw LogicError<InvalidIteratorEmpty>();
  return m_pHashTable->bucket(m_Index).entry;
}

template<typename HT>
const typename EntryIterBase<HT>::entry_type*
EntryIterBase<HT>::getEntry() const
{
  if (nullptr == m_pHashTable)
    throw LogicError<InvalidIteratorEmpty>();
  return m_pHashTable->bucket(m_Index).entry;
}

template<typename HT>
void EntryIterBase<HT>::reset()
{
  m_pHashTable = 0;
  m_Index = 0;
}

template<typename HT>
void EntryIterBase<HT>::advance()
{
  if (nullptr == m_pHashTable)
    throw LogicError<InvalidIteratorEmpty>();
  do {
    ++m_Index;
    if (m_pHashTable->numOfBuckets() == m_Index) { // to the end
      reset();
      return;
    }
  } while(hash_table::EmptyBucket() == m_pHashTable->bucket(m_Index).entry ||
          hash_table::Tombstone() == m_pHashTable->bucket(m_Index).entry);
}

template<typename HT>
bool EntryIterBase<HT>::equals(const EntryIterBase& pCopy) const
{
  return ((m_pHashTable == pCopy.m_pHashTable) && (m_Index == pCopy.m_Index));
}
