#include <eni_crypto.h>
#include <cassert> // replace with a testing framework such as SkyPat
#include <iostream>

using namespace eni_crypto;

int main(int argc, char* argv[])
{
  if (argc < 2)
    return -1;

  const std::string msg(argv[1]);

  std::string hexs, orig;
  if (!str2hex(msg, hexs))
    return 1;
  std::cout << hexs << std::endl;

  if (!hex2str(hexs, orig))
    return 2;
  std::cout << orig << std::endl;

  assert((msg == orig));
  return 0;
}
