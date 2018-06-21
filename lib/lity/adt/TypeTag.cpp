/*===-- TypeTag.cpp -----------------------------------------------------===

	This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==----------------------------------------------------------------------===*/
#include <lity/adt/TypeTag.h>

//===----------------------------------------------------------------------===//
// Type Tags
//===----------------------------------------------------------------------===//
template<> lity::TypeTag lity::type_tag<bool>()
{
  static bool instance;
  return &instance;
}

template<> lity::TypeTag lity::type_tag<int>()
{
  static bool instance;
  return &instance;
}

template<> lity::TypeTag lity::type_tag<long>()
{
  static bool instance;
  return &instance;
}

template<> lity::TypeTag lity::type_tag<unsigned int>()
{
  static bool instance;
  return &instance;
}

template<> lity::TypeTag lity::type_tag<unsigned long>()
{
  static bool instance;
  return &instance;
}

template<> lity::TypeTag lity::type_tag<float>()
{
  static bool instance;
  return &instance;
}

template<> lity::TypeTag lity::type_tag<double>()
{
  static bool instance;
  return &instance;
}

template<> lity::TypeTag lity::type_tag<const char*>()
{
  static bool instance;
  return &instance;
}
