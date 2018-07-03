/*==- lity/support/DataTypes.h --------------------------------------------==

  This file is part of the Lity project distributed under GPL-3.0.
  See LICENSE for details.

==----------------------------------------------------------------------===*/
#ifndef LITY_SUPPORT_DATATYPES_H
#define LITY_SUPPORT_DATATYPES_H

/* Note that <inttypes.h> includes <stdint.h>, if this is a C99 system. */
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif

#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif

#include <cstddef>

/* Handle incorrect definition of uint64_t as u_int64_t */
#ifndef HAVE_UINT64_T
#ifdef HAVE_U_INT64_T
typedef u_int64_t uint64_t;
#else
# error "Don't have a definition for uint64_t on this platform"
#endif
#endif /*  HAVE_UINT64_T */

#include <limits.h>

#endif /* LITY_SUPPORT_DATATYPES_H */
