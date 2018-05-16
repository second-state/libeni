#include <skypat/skypat.h>
#include <eni_types.h>
#include <json/Value.h>

using namespace json;

SKYPAT_F(ValueTest, type_test)
{
  eni::Int a(18);
  eni::Int b(7122);
  eni::Int c = a * b;

  Value x(c);
  EXPECT_EQ(x.toInteger(), 128196);
}
