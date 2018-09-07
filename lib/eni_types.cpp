/*==- eni_types.cpp --------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <eni_types.h>
#include <boost/lexical_cast.hpp>

namespace eni {

template<typename T>
std::string to_string(T pValue)
{
  return boost::lexical_cast<std::string, T>(pValue);
}

// explicit instantiation
template std::string to_string(eni::u64);
template std::string to_string(eni::u128);
template std::string to_string(eni::u160);
template std::string to_string(eni::u256);
template std::string to_string(eni::s256);

// full specialization
template<>
std::string to_string(eni::Bool pValue)
{
  return pValue ? "true" : "false";
}

} // namespace of eni
