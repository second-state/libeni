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
using s256 = boost::multiprecision::int128_t;
using u160 = boost::multiprecision::number<
  boost::multiprecision::cpp_int_backend<160, 160,
    boost::multiprecision::unsigned_magnitude,
    boost::multiprecision::unchecked, void>
>;
using s160 = boost::multiprecision::number<
  boost::multiprecision::cpp_int_backend<160, 160,
    boost::multiprecision::signed_magnitude,
    boost::multiprecision::unchecked, void>
>;

using Bool = bool;
using Int = s256;
using Address = u160;

} // namespace of eni

#endif
