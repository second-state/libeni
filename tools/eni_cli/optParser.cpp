/*==- optParser.cpp --------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#include "optParser.h"
#include <cstring>

using namespace ceni;

bool Opt::parse(int pArgc, char* pArgv[])
{
  bool endOfOptions = false;
  int posCount = 0;
  for (int i = 1; i < pArgc; ++i) {
    char* arg = pArgv[i];
    int len = strlen(arg);
    if (('-' == arg[0]) && !endOfOptions) { //< options
      if ((2 == len) && ('-' == arg[1])) { //< double-dash
        endOfOptions = true;
        continue;
      }
      // TODO: add and parse options here
    }
    else { //< positional parameters
      switch (++posCount) {
        case 1:
          m_LibPath.assign(arg, len);
          break;
        case 2:
          m_OpName.assign(arg, len);
          break;
        case 3:
          m_Params.assign(arg, len);
          break;
        default:
          // TODO: too many arguments
          return false;
      }
    }
  }
  return true;
}
