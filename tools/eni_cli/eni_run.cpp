/*==- eni_run.cpp ----------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include "optParser.h"
#include <eni.h>
#include <dlfcn.h>
#include <iostream>

int main(int argc, char* argv[])
{
  ceni::Opt opt("eni_run",
    "run the ENI operation and print the result in JSON format");
  if (!opt.parse(argc, argv)) {
    opt.help(std::cerr);
    return 1;
  }
  return 0;
}
