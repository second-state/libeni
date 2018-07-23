/*==- test/unittests/adt/StringMapTest.cpp ---------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <skypat/skypat.h>
#include <adt/StringMap.h>

using namespace eni;

/*==------------------------------------------------------------------------==
  StringMapTest
==------------------------------------------------------------------------==*/
SKYPAT_F(StringMapTest, typical)
{
  typedef StringMap<int> Map;
  const char* key = "first_key";
  const char* no_key = "not_exist";

  Map map;
  EXPECT_EQ(map.size(), 0);

  // operator[]
  map[key] = 10;
  ASSERT_EQ(map.size(), 1);
  EXPECT_EQ(map[key], 10);

  // at
  bool catched = false;
  try {
    map.at(no_key) = 10;
  }
  catch (const std::out_of_range&) {
    catched = true;
  }
  EXPECT_TRUE(catched);

  map.at(key) = 20;
  EXPECT_EQ(map.at(key), 20);

  // iterator
  Map::const_iterator it = map.begin();
  EXPECT_EQ(it->value(), 20);
  EXPECT_TRUE(++it == map.end());

  // find
  it = map.find(no_key);
  EXPECT_TRUE(it == map.end());

  // erase
  map.erase(key);
  EXPECT_TRUE(map.empty());
}
