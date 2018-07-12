/*==- test/unittests/json/ArrayTest.cpp ------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <skypat/skypat.h>
#include <json/Array.h>
#include <json/Value.h>

using namespace json;

SKYPAT_F(JsonArrayTest, copy_test)
{
  Array arr;
  arr.emplace_back(1);
  arr.emplace_back("two");
  ASSERT_EQ(arr.size(), 2);

  Array cpy(arr);
  EXPECT_EQ(cpy.size(), 2);
  ASSERT_TRUE(cpy.at(0).isInteger());
  EXPECT_EQ(cpy.at(0).toInteger(), 1);
  ASSERT_TRUE(cpy.at(1).isString());
  EXPECT_EQ(cpy.at(1).toString(), "two");
}

SKYPAT_F(JsonArrayTest, assign_test)
{
  Array arr;
  arr.emplace_back(1);
  arr.emplace_back("two");
  ASSERT_EQ(arr.size(), 2);

  Array asn(arr);
  EXPECT_EQ(asn.size(), 2);
  ASSERT_TRUE(asn.at(0).isInteger());
  EXPECT_EQ(asn.at(0).toInteger(), 1);
  ASSERT_TRUE(asn.at(1).isString());
  EXPECT_EQ(asn.at(1).toString(), "two");
}
