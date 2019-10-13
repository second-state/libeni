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
  : m_Parsed(false), m_ParseSuccess(false), m_Args(), m_RetVals() {
  json::Parser parser(pArgStr);
  if (!parser) exit(87);
  m_Args = parser.getRoot();
  m_RetVals.delegate(*(new json::Array()));
}

EniBase::~EniBase()
{
  // implementation of pure virtual destructor
}
