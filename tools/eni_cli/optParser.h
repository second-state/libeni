/*==- optParser.h ----------------------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#ifndef ENI_CLI_OPT_PARSER
#define ENI_CLI_OPT_PARSER

#include <ostream>

namespace ceni {

class Opt {
public:
  typedef std::string Path;

public:
  Opt(const std::string& pProgName, const std::string& pDesc)
    : m_ProgName(pProgName), m_ProgDesc(pDesc) { }

  bool parse(int pArgc, char* pArgv[]);

  const std::string& lib() const { return m_LibPath; }
  const std::string& op() const { return m_OpName; }
  const std::string& params() const { return m_Params; }

  void help(std::ostream& pOS) const
  {
    pOS << "NAME" << std::endl
        << "\t" << m_ProgName << " - " << m_ProgDesc << std::endl
        << std::endl;
    pOS << "SYNOPSIS" << std::endl
        << "\t" << m_ProgName << " <LIBPATH> <OP> <JSON>" << std::endl
        << std::endl;
    pOS << "DESCRIPTION" << std::endl
        << "\tLIBPATH" << std::endl
        << "\t\tpath to the shared library" << std::endl
        << std::endl
        << "\tOP" << std::endl
        << "\t\tname of the ENI operation" << std::endl
        << std::endl
        << "\tJSON" << std::endl
        << "\t\tparameters passed to the operation in JSON format" << std::endl
        << std::endl;
  }

private:
  const std::string& m_ProgName;
  const std::string& m_ProgDesc;

  Path m_LibPath;
  std::string m_OpName;
  std::string m_Params;
};

} // namespace of ceni

#endif
