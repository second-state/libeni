/*==- eni.cpp --------------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <eni.h>
#include <json/Parser.h>

using namespace eni;

/*==------------------------------------------------------------------------==
  EniBase
==------------------------------------------------------------------------==*/
EniBase::EniBase(const std::string& pArgStr)
  : m_Parsed(false), m_Args(), m_RetVals() {
  json::Parser parser(pArgStr);
  m_Args = parser.getRoot();
  m_RetVals.delegate(*(new json::Array()));
}

EniBase::~EniBase()
{
  // implementation of pure virtual destructor
}

/*==------------------------------------------------------------------------==
  C Interface for all eni-functors
==------------------------------------------------------------------------==*/
extern "C" uint64_t eni_gas(void* pFunctor) {
  return ((eni::EniBase*)pFunctor)->getGas();
}

extern "C" char* eni_run(void* pFunctor) {
  return ((eni::EniBase*)pFunctor)->start();
}
