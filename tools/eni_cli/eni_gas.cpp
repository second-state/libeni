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

  eni_create_t* eni_create =
    (eni_create_t*)::dlsym(handle, (opt.op() + "_create").c_str());
  NULL_RETURN(eni_create, ExitSymCreateError);

  eni_destroy_t* eni_destroy =
    (eni_destroy_t*)::dlsym(handle, (opt.op() + "_destroy").c_str());
  NULL_RETURN(eni_destroy, ExitSymDestroyError);

  void* functor = eni_create(const_cast<char*>(opt.params().c_str()));
  NULL_RETURN(functor, ExitCreateError);

  uint64_t gas = eni_gas(functor);
  eni_destroy(functor);
  ::dlclose(handle);

  if (0 == gas)
    return ExitFailure;

  std::cout << gas << std::endl;
  return ExitSuccess;
}
