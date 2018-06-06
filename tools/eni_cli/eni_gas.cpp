/*==- eni_gas.cpp ----------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include "ceni.h"
#include "optParser.h"
#include <eni.h>
#include <dlfcn.h>
#include <iostream>

#define NULL_RETURN(VAR,ERR) \
  if (NULL == (VAR)) return ERR

using namespace ceni;

int main(int argc, char* argv[])
{
  Opt opt("eni_gas",
    "the estimated gas cost when running the ENI operation");
  if (!opt.parse(argc, argv)) {
    opt.help(std::cerr);
    return ExitParseError;
  }

  void* handle = ::dlopen(opt.lib().c_str(), RTLD_LAZY);
  NULL_RETURN(handle, ExitLoadError);

  eni_op_t* eni_gas = (eni_op_t*)::dlsym(handle, (opt.op() + "_gas").c_str());
  NULL_RETURN(eni_gas, ExitSymError);

  uint64_t* gas = (uint64_t*)eni_gas(const_cast<char*>(opt.params().c_str()));
  NULL_RETURN(gas, ExitRunError);
  ::dlclose(handle);

  std::cout << *gas << std::endl;
  delete gas;
  return ExitSuccess;
}
