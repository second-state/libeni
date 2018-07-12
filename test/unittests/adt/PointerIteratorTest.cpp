/*==- test/unittests/adt/PointerIteratorTest.cpp ---------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <skypat/skypat.h>
#include <adt/PointerIterator.h>

using namespace eni;

SKYPAT_F(PointerIteratorTest, typical)
{
  int array[] = { 1, 5, 2, 4, 3 };
  typedef PointerIterator<int> int_iterator;

  int_iterator it(array);
  EXPECT_EQ(it[0], 1);
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*++it, 2);
  EXPECT_EQ(*(it - 1), 5);
  EXPECT_EQ(*(it + 2), 3);

  int_iterator end(array + 5);
  EXPECT_TRUE(it < end);
  EXPECT_TRUE(it != end);
  EXPECT_TRUE((it + 3) >= end);
  EXPECT_EQ((end - it), 3);
}
