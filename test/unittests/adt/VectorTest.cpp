/*==- test/unittests/adt/VectorTest.cpp ------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <skypat/skypat.h>
#include <adt/Vector.h>

using namespace eni;

SKYPAT_F(VectorTest, copy_constructor)
{
  std::vector<int> vec(1, 101);
  Vector<int> cpy(vec);
  EXPECT_EQ(cpy.at(0), 101);
}

SKYPAT_F(VectorTest, constructor_initialize_list)
{
  Vector<int> v({234, 546, 563});
  EXPECT_EQ(234, v.at(0));
  EXPECT_EQ(546, v.at(1));
  EXPECT_EQ(563, v.at(2));
}

SKYPAT_F(VectorTest, at)
{
  Vector<int> v({123, 345, 456});
  EXPECT_EQ(123, v.at(0));
  EXPECT_EQ(345, v.at(1));
  v.at(1) = 876;
  EXPECT_EQ(876, v.at(1));
}

SKYPAT_F(VectorTest, begin)
{
  Vector<int> v({123, 345, 456});
  EXPECT_EQ(123, *(v.begin()));
}

SKYPAT_F(VectorTest, end)
{
  Vector<int> v({123, 345, 456});
  EXPECT_EQ(456, *(v.end() - 1));
}

SKYPAT_F(VectorTest, push_back)
{
  Vector<int> v;
  v.push_back(5656);
  v.push_back(3000);
  v.push_back(454);
  EXPECT_EQ(3, v.size());
  EXPECT_LE(3, v.capacity());
  EXPECT_EQ(5656, v.at(0));
}

SKYPAT_F(VectorTest, reserve)
{
  Vector<int> v;
  v.reserve(20);
  EXPECT_EQ(v.size(), 0);
}

SKYPAT_F(VectorTest, resize)
{
  Vector<int> v;
  v.resize(20);
  EXPECT_EQ(v.size(), 20);
}

SKYPAT_F(VectorTest, insert)
{
  Vector<int> v({1, 5, 2, 4, 3});
  Vector<int>::iterator it = v.insert(v.begin(), 7);
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(*it, 7);
  EXPECT_EQ(v.at(0), 7);
  EXPECT_EQ(v.at(1), 1);
  EXPECT_EQ(v.at(2), 5);

  v.insert(2, {9, 9, 9});
  EXPECT_EQ(v.size(), 9);
  EXPECT_EQ(v.at(1), 1);
  EXPECT_EQ(v.at(2), 9);
  EXPECT_EQ(v.at(3), 9);
  EXPECT_EQ(v.at(4), 9);
  EXPECT_EQ(v.at(5), 5);
}

SKYPAT_F(VectorTest, erase)
{
  Vector<int> v({1, 5, 2, 4, 3});
  Vector<int>::iterator it = v.erase(v.begin());
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(*it, 5);

  v.erase(0, 3);
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.at(0), 3);
}
