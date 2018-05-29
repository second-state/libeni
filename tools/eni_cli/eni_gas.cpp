/*==- eni_gas.cpp ----------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include "optParser.h"
#include <eni.h>
#include <dlfcn.h>
#include <iostream>

int main(int argc, char* argv[])
{
  ceni::Opt opt("eni_gas",
    "the estimated gas cost when running the ENI operation");
  if (!opt.parse(argc, argv)) {
    opt.help(std::cerr);
    return 1;
  }
  return 0;
}
