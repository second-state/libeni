/*==- lity/diagnostic/Exception.h ------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==------------------------------------------------------------------------==*/
#ifndef ENI_DIAGNOSTIC_EXCEPTION
#define ENI_DIAGNOSTIC_EXCEPTION

#include <exception>
#include <stdexcept>
#include <string>

namespace eni {

enum DiagID {
#define DIAG(ID, MSG) ID,
#include <diagnostic/DiagList.inc>
#undef DIAG
  NumberOfDiagIDs
};

namespace internal {

template<DiagID ID>
struct ExceptionBase
{
  static const std::string ErrStr;
};

#define DIAG(ID, MSG) \
  template<> struct ExceptionBase<ID> { static const std::string ErrStr; };
#include <diagnostic/DiagList.inc>

#undef DIAG

} // namespace of internal

template<DiagID ID, typename BaseType = std::exception>
class Exception : private internal::ExceptionBase<ID>, public BaseType
{
private:
  using internal::ExceptionBase<ID>::ErrStr;

public:
  Exception() : BaseType() { }

  const char* what() const noexcept override {
    return ErrStr.c_str();
  }
};

/*==------------------------------------------------------------------------==
  Exception (partial template specialization goes here)
==------------------------------------------------------------------------==*/
template<DiagID ID>
class Exception<ID, std::logic_error> : private internal::ExceptionBase<ID>,
                                        public std::logic_error
{
private:
  using internal::ExceptionBase<ID>::ErrStr;

public:
  Exception() : std::logic_error(ErrStr) { }

  const char* what() const noexcept override {
    return ErrStr.c_str();
  }
};

template<DiagID ID>
using LogicError = Exception<ID, std::logic_error>;

} // namespace of eni

#endif
