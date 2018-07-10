/*==- test/unittests/lity/adt/VectorTest.cpp -------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <skypat/skypat.h>
#include <lity/adt/Vector.h>

using namespace lity;

SKYPAT_F(VectorTest, constructor_initialize_list)
{
  Vector<int> v({234, 546, 563});
  EXPECT_EQ(234, v.at(0));
  EXPECT_EQ(546, v.at(1));
  EXPECT_EQ(563, v.at(2));
}

SKYPAT_F(VectorTest, at)
{
  Vector<int> v({123,345,456});
  EXPECT_EQ(123, v.at(0));
  EXPECT_EQ(345, v.at(1));
  v.at(1) = 876;
  EXPECT_EQ(876, v.at(1));
}

SKYPAT_F(VectorTest, begin)
{
  Vector<int> v({123,345,456});
  EXPECT_EQ(123, *(v.begin()));
}

SKYPAT_F(VectorTest, end)
{
  Vector<int> v({123,345,456});
  EXPECT_EQ(456, *(v.end() - 1));
}

SKYPAT_F(VectorTest, push_back)
{
  Vector<int> v;
  v.push_back(5656);
  v.push_back(3000);
  v.push_back(454);
  EXPECT_EQ(3, v.size());
  EXPECT_EQ(4, v.capacity());
  EXPECT_EQ(5656, v.at(0));
}

