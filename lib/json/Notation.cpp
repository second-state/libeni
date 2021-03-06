/*==- json/Notation.cpp ----------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <json/Notation.h>

using namespace json;

Notation::Notation()
  : m_Type(UNDEF) {
}

Notation::Notation(Type pType)
  : m_Type(pType) {
}

Notation::Notation(const Notation& pCopy)
  : m_Type(pCopy.m_Type) {
}

Notation::Notation(Notation&& pOther)
  : m_Type(UNDEF) {
  m_Type = pOther.m_Type;
  pOther.m_Type = UNDEF;
}

Notation& Notation::operator=(const Notation& pCopy)
{
  m_Type = pCopy.m_Type;
  return *this;
}

Notation& Notation::operator=(Notation&& pOther)
{
  if (this != &pOther) {
    m_Type = pOther.m_Type;
    pOther.m_Type = UNDEF;
  }
  return *this;
}
