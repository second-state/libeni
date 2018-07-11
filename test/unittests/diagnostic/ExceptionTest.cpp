/*==- test/json/unittests/diagnostic/ExceptionTest.cpp ---------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <skypat/skypat.h>
#include <diagnostic/Exception.h>
#include <cstring>

using namespace eni;

SKYPAT_F(ExceptionTest, unknown_exception)
{
  Exception<Unknown> e;
  EXPECT_EQ(::strcmp(e.what(), "unknown"), 0);
}

SKYPAT_F(ExceptionTest, specific_exception_parent)
{
  bool found = false;
  try {
    throw Exception<Unknown, std::bad_alloc>();
  }
  catch (const std::bad_alloc& e) {
    found = true;
    EXPECT_EQ(::strcmp(e.what(), "unknown"), 0);
  }
  ASSERT_TRUE(found);
}
