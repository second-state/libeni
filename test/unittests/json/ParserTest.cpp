/*==- test/unittests/json/ParserTest.cpp -----------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include <skypat/skypat.h>
#include <json/Parser.h>
#include <fstream>
#include <streambuf>

using namespace json;

SKYPAT_F(JsonParserTest, empty_object)
{
  Parser ps("{}");
  Value val = ps.getRoot();
  EXPECT_TRUE(val.isObject());
}

SKYPAT_F(JsonParserTest, empty_array)
{
  Parser ps("[]");
  Value val = ps.getRoot();
  EXPECT_TRUE(val.isArray());
}

SKYPAT_F(JsonParserTest, file_test)
{
  // TODO: parser directly read from file
  std::ifstream ifs("data/0.json");
  ASSERT_TRUE(ifs.is_open());

  Parser ps(std::string((std::istreambuf_iterator<char>(ifs)),
                         std::istreambuf_iterator<char>()));
  Value obj = ps.getRoot();
  ASSERT_TRUE(obj.isObject());

  Value array = obj["array"];
  ASSERT_TRUE(array.isArray());
  ASSERT_TRUE(array[0].isArray());
  EXPECT_EQ(array[0][0].toString(), "a");

  Value age = obj["age"];
  ASSERT_TRUE(age.isInteger());
  EXPECT_EQ(age.toInteger(), 18);

  Value str = obj["escape"];
  EXPECT_EQ(str.toString(), "\"\\n\"\u0001\u000A");
}
