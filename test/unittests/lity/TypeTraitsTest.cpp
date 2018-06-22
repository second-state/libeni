/*===- TypeTraits.cpp -------------------------------------------------===

	This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==---------------------------------------------------------------------===*/
#include <skypat/skypat.h>
#include <lity/adt/TypeTag.h>

using namespace lity;

static void* global_ptr = NULL;

//===----------------------------------------------------------------------===//
// Test Functions
//===----------------------------------------------------------------------===//
SKYPAT_F(TypeTraits, type_tags_test)
{
  ASSERT_EQ(type_tag<bool>(), type_tag<bool>());
  ASSERT_NE(type_tag<bool>(), type_tag<int>());
  ASSERT_NE(type_tag<bool>(), type_tag<double>());
  ASSERT_NE(type_tag<bool>(), type_tag<float>());
  ASSERT_NE(type_tag<bool>(), type_tag<const char*>());
  ASSERT_NE(type_tag<double>(), type_tag<float>());
  ASSERT_NE(type_tag<int>(), type_tag<long>());
  ASSERT_NE(type_tag<int>(), type_tag<unsigned int>());
  ASSERT_NE(type_tag<long>(), type_tag<unsigned long>());

  global_ptr = type_tag<long>();
}

SKYPAT_F(TypeTraits, stack_type_tags_test)
{
  ASSERT_EQ(global_ptr, type_tag<long>());
}
