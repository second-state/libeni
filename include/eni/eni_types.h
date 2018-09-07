/*==- eni_types.h ----------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#ifndef ENI_TYPES
#define ENI_TYPES

#include <boost/multiprecision/cpp_int.hpp>

namespace eni {

using u64 = boost::multiprecision::number<
  boost::multiprecision::cpp_int_backend<64, 64,
    boost::multiprecision::unsigned_magnitude,
    boost::multiprecision::unchecked, void>
>;
using u128 = boost::multiprecision::uint128_t;
using u256 = boost::multiprecision::uint256_t;
using s256 = boost::multiprecision::int256_t;
using u160 = boost::multiprecision::number<
  boost::multiprecision::cpp_int_backend<160, 160,
    boost::multiprecision::unsigned_magnitude,
    boost::multiprecision::unchecked, void>
>;

using Bool = bool;
using Int = s256;
using Address = u160;

} // namespace of eni

#endif
