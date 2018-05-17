/*==- test/json/main.cpp ---------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <skypat/skypat.h>

int main(int argc, char* argv[])
{
  skypat::Test::Initialize("Unit-Tests for libeni/json");
  skypat::Test::RunAll();

  skypat::testing::UnitTest* tests = skypat::testing::UnitTest::self();
  return (tests->getNumOfFails() == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
