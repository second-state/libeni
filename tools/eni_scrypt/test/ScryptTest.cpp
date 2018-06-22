#include <skypat/skypat.h>
#include <eni.h>
#include <eni_scrypt.h>

SKYPAT_F(ScryptTest, scrypt_empty_string)
{
  Scrypt* functor = new Scrypt(R"([""])");
  char *hash = functor->start();
  delete functor;

  EXPECT_EQ(memcmp(hash, R"(["161d0876f3b93b1048cda1bdeaa7332ee210f7131b42013cb43913a6553a4b69"])", 68), 0);
  free(hash);
}

SKYPAT_F(ScryptTest, scrypt_all_zero)
{
  Scrypt* functor = new Scrypt(R"(["0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"])");
  char *hash = functor->start();
  delete functor;

  EXPECT_EQ(memcmp(hash, R"(["161d0876f3b93b1048cda1bdeaa7332ee210f7131b42013cb43913a6553a4b69"])", 68), 0);
  free(hash);
}

SKYPAT_F(ScryptTest, scrypt_all_ff)
{
  Scrypt* functor = new Scrypt(R"(["ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"])");
  char *hash = functor->start();
  delete functor;

  EXPECT_EQ(memcmp(hash, R"(["5253069c14ecedf978745486375ee37415e977f55cdbedac31ebee8bf33dd127"])", 68), 0);
  free(hash);
}

SKYPAT_F(ScryptTest, scrypt_truncate_oversized)
{
  Scrypt* functor = new Scrypt(R"(["ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff01"])");
  char *hash = functor->start();
  delete functor;

  EXPECT_EQ(memcmp(hash, R"(["5253069c14ecedf978745486375ee37415e977f55cdbedac31ebee8bf33dd127"])", 68), 0);
  free(hash);
}
