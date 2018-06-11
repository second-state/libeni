/*==- test/json/unittests/ValueTest.cpp ------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <skypat/skypat.h>
#include <eni_types.h>
#include <json/Value.h>

using namespace json;

SKYPAT_F(JsonValueTest, move_constructor)
{
  eni::Int i(1);
  Value v(i);
  Value m(std::move(v));
  EXPECT_EQ(m.toInteger(), 1);
}

SKYPAT_F(JsonValueTest, type_test)
{
  eni::Int a(18);
  eni::Int b(7122);
  eni::Int c = a * b;

  Value x(c);
  EXPECT_EQ(x.toInteger(), 128196);
}
