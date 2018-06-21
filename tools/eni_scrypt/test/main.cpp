#include <skypat/skypat.h>

int main(int argc, char* argv[])
{
  skypat::Test::Initialize("Unit-Tests for eni/scrypt");
  skypat::Test::RunAll();

  skypat::testing::UnitTest* tests = skypat::testing::UnitTest::self();
  return (tests->getNumOfFails() == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
