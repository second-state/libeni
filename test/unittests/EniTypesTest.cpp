/*==- test/unittests/EniTypesTest.cpp --------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <skypat/skypat.h>
#include <eni_types.h>

namespace bmp = boost::multiprecision;

SKYPAT_F(EniTypesTest, to_string)
{
  eni::Int int32max(2147483647);
  EXPECT_EQ(eni::to_string(int32max), "2147483647");

  eni::Bool b(true);
  EXPECT_EQ(eni::to_string(b), "true");
}

SKYPAT_F(EniTypesTest, boundary)
{
  eni::u64 u64max = bmp::pow(eni::u64(2), 64) - 1;
  EXPECT_EQ(eni::to_string(u64max), "18446744073709551615");

  eni::u128 u128max = bmp::pow(eni::u128(2), 128) - 1;
  EXPECT_EQ(eni::to_string(u128max), "340282366920938463463374607431768211455");

  eni::u256 u256max = (eni::u256)u128max * u128max + (eni::u256)u128max * 2;
  EXPECT_EQ(eni::to_string(u256max),
    "115792089237316195423570985008687907853269984665640564039457584007913129639935");

  eni::s256 s256max = bmp::pow(eni::s256(2), 255) - 1;
  EXPECT_EQ(eni::to_string(s256max),
    "57896044618658097711785492504343953926634992332820282019728792003956564819967");
}
