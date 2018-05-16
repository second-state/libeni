#include <skypat/skypat.h>
#include <eni_crypto.h>
#include <fstream>
#include <streambuf>

using namespace eni_crypto;

namespace {

static inline bool readfile(const std::string& pName, std::string& pStr)
{
  std::ifstream ifs(pName);
  if (!ifs.is_open())
    return false;

  pStr.assign((std::istreambuf_iterator<char>(ifs)),
               std::istreambuf_iterator<char>());
  return true;
}

} // annonymous namespace

SKYPAT_F(RsaTest, read_privkey)
{
  std::string pemstr;
  ASSERT_TRUE(readfile("data/priv.pem", pemstr));
  RSA* privkey = rsa::create_privkey(pemstr);
  EXPECT_NE(privkey, NULL);

  rsa::destroy(privkey);
}

SKYPAT_F(RsaTest, read_pubkey)
{
  std::string pemstr;
  ASSERT_TRUE(readfile("data/pub.pem", pemstr));
  RSA* pubkey = rsa::create_pubkey(pemstr);
  EXPECT_NE(pubkey, NULL);

  rsa::destroy(pubkey);
}

SKYPAT_F(RsaTest, pub_encrypt_priv_decrypt)
{
  // Initialize.
  std::string pemstr;
  ASSERT_TRUE(readfile("data/priv.pem", pemstr));
  RSA* privkey = rsa::create_privkey(pemstr);
  ASSERT_NE(privkey, NULL);

  ASSERT_TRUE(readfile("data/pub.pem", pemstr));
  RSA* pubkey = rsa::create_pubkey(pemstr);
  ASSERT_NE(pubkey, NULL);

  // Encrypt, decrypt, and compare.
  const std::string msg("Hello World!");
  std::string encrypted, decrypted;
  ASSERT_TRUE(rsa::pub_encrypt(*pubkey, msg, encrypted));
  ASSERT_TRUE(rsa::priv_decrypt(*privkey, encrypted, decrypted));
  EXPECT_EQ(msg, decrypted);

  // Finalize.
  rsa::destroy(pubkey);
  rsa::destroy(privkey);
}

SKYPAT_F(RsaTest, priv_encrypt_pub_decrypt)
{
  // Initialize.
  std::string pemstr;
  ASSERT_TRUE(readfile("data/priv.pem", pemstr));
  RSA* privkey = rsa::create_privkey(pemstr);
  ASSERT_NE(privkey, NULL);

  ASSERT_TRUE(readfile("data/pub.pem", pemstr));
  RSA* pubkey = rsa::create_pubkey(pemstr);
  ASSERT_NE(pubkey, NULL);

  // Encrypt, decrypt, and compare.
  const std::string msg("Hello World!");
  std::string encrypted, decrypted;
  ASSERT_TRUE(rsa::priv_encrypt(*privkey, msg, encrypted));
  ASSERT_TRUE(rsa::pub_decrypt(*pubkey, encrypted, decrypted));
  EXPECT_EQ(msg, decrypted);

  // Finalize.
  rsa::destroy(pubkey);
  rsa::destroy(privkey);
}
