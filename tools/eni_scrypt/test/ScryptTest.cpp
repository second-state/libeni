#include <skypat/skypat.h>
#include <eni.h>
#include <eni_scrypt.h>

SKYPAT_F(ScryptTest, scrypt_empty_string)
{
  Scrypt* functor = new Scrypt(R"([""])");
  EXPECT_EQ(functor->getGas(), 0);
  char *hash = functor->start();
  delete functor;

  EXPECT_EQ(memcmp(hash, R"(["161d0876f3b93b1048cda1bdeaa7332ee210f7131b42013cb43913a6553a4b69"])", 68), 0);
  free(hash);
}

SKYPAT_F(ScryptTest, scrypt_all_zero)
{
  Scrypt* functor = new Scrypt(R"(["0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"])");
  EXPECT_EQ(functor->getGas(), 800);
  char *hash = functor->start();
  delete functor;

  EXPECT_EQ(memcmp(hash, R"(["161d0876f3b93b1048cda1bdeaa7332ee210f7131b42013cb43913a6553a4b69"])", 68), 0);
  free(hash);
}

SKYPAT_F(ScryptTest, scrypt_all_ff)
{
  Scrypt* functor = new Scrypt(R"(["ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"])");
  EXPECT_EQ(functor->getGas(), 800);
  char *hash = functor->start();
  delete functor;

  EXPECT_EQ(memcmp(hash, R"(["5253069c14ecedf978745486375ee37415e977f55cdbedac31ebee8bf33dd127"])", 68), 0);
  free(hash);
}

SKYPAT_F(ScryptTest, scrypt_oversized)
{
  Scrypt* functor = new Scrypt(R"(["ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff01"])");
  EXPECT_EQ(functor->getGas(), 1500);
  char *hash = functor->start();
  delete functor;

  EXPECT_FALSE(hash);
  free(hash);
}

SKYPAT_F(ScryptTest, scrypt_invalid_hex)
{
  Scrypt* functor = new Scrypt(R"(["wxyz"])");
  EXPECT_EQ(functor->getGas(), 1500);
  char *hash = functor->start();
  delete functor;

  EXPECT_FALSE(hash);
  free(hash);
}

SKYPAT_F(ScryptTest, scrypt_prepend_zero)
{
  Scrypt* functor1 = new Scrypt(R"(["01"])");
  Scrypt* functor2 = new Scrypt(R"(["1"])");
  EXPECT_EQ(functor1->getGas(), 10);
  EXPECT_EQ(functor2->getGas(), 10);
  char *hash1 = functor1->start();
  char *hash2 = functor2->start();
  delete functor1;
  delete functor2;

  EXPECT_EQ(memcmp(hash1, hash2, 68), 0);
  free(hash1);
  free(hash2);
}

SKYPAT_F(ScryptTest, scrypt_upper_lower_case)
{
  Scrypt* functor1 = new Scrypt(R"(["0123456789abcdef"])");
  Scrypt* functor2 = new Scrypt(R"(["0123456789ABCDEF"])");
  EXPECT_EQ(functor1->getGas(), 80);
  EXPECT_EQ(functor2->getGas(), 80);
  char *hash1 = functor1->start();
  char *hash2 = functor2->start();
  delete functor1;
  delete functor2;

  EXPECT_EQ(memcmp(hash1, hash2, 68), 0);
  free(hash1);
  free(hash2);
}
