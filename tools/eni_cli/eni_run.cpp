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
  Opt opt("eni_run",
    "run the ENI operation and print the result in JSON format");
  if (!opt.parse(argc, argv)) {
    opt.help(std::cerr);
    return 1;
  }

  void* handle = ::dlopen(opt.lib().c_str(), RTLD_LAZY);
  NULL_RETURN(handle, ExitLoadError);

  eni_op_t* eni_run = (eni_op_t*)::dlsym(handle, (opt.op() + "_run").c_str());
  NULL_RETURN(eni_run, ExitSymError);

  char* str = (char*)eni_run(const_cast<char*>(opt.params().c_str()));
  NULL_RETURN(str, ExitRunError);
  ::dlclose(handle);

  std::cout << str << std::endl;
  ::free(str);
  return ExitSuccess;
}
