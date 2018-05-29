/*==- eni_run.cpp ----------------------------------------------------------==

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
  ceni::Opt opt("eni_run",
    "run the ENI operation and print the result in JSON format");
  if (!opt.parse(argc, argv)) {
    opt.help(std::cerr);
    return 1;
  }

  void* handle = ::dlopen(opt.lib().c_str(), RTLD_LAZY);
  NULL_RETURN(handle, ExitLoadError);

  const char* op_create = (opt.op() + "_create").c_str();
  eni_create_t* eni_create = (eni_create_t*)::dlsym(handle, op_create);
  NULL_RETURN(eni_create, ExitSymCreateError);

  const char* op_destroy = (opt.op() + "_destroy").c_str();
  eni_destroy_t* eni_destroy = (eni_destroy_t*)::dlsym(handle, op_destroy);
  NULL_RETURN(eni_destroy, ExitSymDestroyError);

  void* functor = eni_create(const_cast<char*>(opt.params().c_str()));
  NULL_RETURN(functor, ExitCreateError);

  char* str = eni_run(functor);
  eni_destroy(functor);
  ::dlclose(handle);

  if (NULL == str)
    return ExitFailure;

  std::cout << str << std::endl;
  return 0;
}
