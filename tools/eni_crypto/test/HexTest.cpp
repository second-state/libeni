#include <skypat/skypat.h>
#include <eni_crypto.h>

using namespace eni_crypto;

SKYPAT_F(HexTest, to_hex)
{
  const std::string msg("A+!");

  std::string hexs;
  ASSERT_TRUE(str2hex(msg, hexs));
  EXPECT_EQ(hexs, "412b21");
}

SKYPAT_F(HexTest, from_hex)
{
  const std::string hexs("412b21");

  std::string orig;
  ASSERT_TRUE(hex2str(hexs, orig));
  EXPECT_EQ(orig, "A+!");
}
