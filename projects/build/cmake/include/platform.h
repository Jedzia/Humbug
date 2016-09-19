//  Boost compiler configuration selection header file

//  (C) Copyright John Maddock 2001 - 2002.
//  (C) Copyright Jens Maurer 2001.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

// locate which platform we are on and define PLATFORM_CONFIG as needed.
// Note that we define the headers to include using "header_name" not
// <header_name> in order to prevent macro expansion within the header
// name (for example "linux" is a macro on linux systems).
// if we don't have a compiler config set, try and find one:


#if !defined(PLATFORM_COMPILER_CONFIG) && !defined(PLATFORM_NO_COMPILER_CONFIG) && !defined(PLATFORM_NO_CONFIG)
#  include <build/cmake/include/select_compiler_config.hpp>
#endif
//#pragma message("PLATFORM_COMPILER_CONFIG:" STRING(PLATFORM_COMPILER_CONFIG))
// if we have a compiler config, include it now:
#ifdef PLATFORM_COMPILER_CONFIG
#  include PLATFORM_COMPILER_CONFIG
#endif

#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__GNU__) || defined(__GLIBC__)
// linux, also other platforms (Hurd etc) that use GLIBC, should these really have their own config headers though?
#  define PLATFORM_CONFIG "platform/linux.hpp"

#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
// BSD:
#  define PLATFORM_CONFIG "boost/config/platform/bsd.hpp"

#elif defined(sun) || defined(__sun)
// solaris:
#  define PLATFORM_CONFIG "boost/config/platform/solaris.hpp"

#elif defined(__sgi)
// SGI Irix:
#  define PLATFORM_CONFIG "boost/config/platform/irix.hpp"

#elif defined(__hpux)
// hp unix:
#  define PLATFORM_CONFIG "boost/config/platform/hpux.hpp"

#elif defined(__CYGWIN__)
// cygwin is not win32:
#  define PLATFORM_CONFIG "boost/config/platform/cygwin.hpp"

#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
// win32:
#  define PLATFORM_CONFIG "platform/win32.h"

#elif defined(__BEOS__)
// BeOS
#  define PLATFORM_CONFIG "boost/config/platform/beos.hpp"

#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
// MacOS
#  define PLATFORM_CONFIG "boost/config/platform/macos.hpp"

#elif defined(__IBMCPP__) || defined(_AIX)
// IBM
#  define PLATFORM_CONFIG "boost/config/platform/aix.hpp"

#elif defined(__amigaos__)
// AmigaOS
#  define PLATFORM_CONFIG "boost/config/platform/amigaos.hpp"

#elif defined(__QNXNTO__)
// QNX:
#  define PLATFORM_CONFIG "boost/config/platform/qnxnto.hpp"

#elif defined(__VXWORKS__)
// vxWorks:
#  define PLATFORM_CONFIG "boost/config/platform/vxworks.hpp"

#elif defined(__SYMBIAN32__)
// Symbian:
#  define PLATFORM_CONFIG "boost/config/platform/symbian.hpp"

#elif defined(__VMS)
// VMS:
#  define PLATFORM_CONFIG "boost/config/platform/vms.hpp"
#else

#  if defined(unix) \
      || defined(__unix) \
      || defined(_XOPEN_SOURCE) \
      || defined(_POSIX_SOURCE)

   // generic unix platform:

#  ifndef PLATFORM_HAS_UNISTD_H
#     define PLATFORM_HAS_UNISTD_H
#  endif

#  include "posix_features.hpp"

#  endif

#  if defined (PLATFORM_ASSERT_CONFIG)
      // this must come last - generate an error if we don't
      // recognise the platform:
#     error "Unknown platform - please configure and report the results to boost.org"
#  endif

#endif


//  enable dynamic linking -------------------------------------------------------------//
#include PLATFORM_CONFIG

#if defined(PLATFORM_ALL_DYN_LINK) || defined(PLATFORM_FILESYSTEM_DYN_LINK)
# if defined(PLATFORM_SOURCE)
#   define PLATFORM_DECL PLATFORM_SYMBOL_EXPORT
#   define LIBRARY_SYMBOL_EXPORT PLATFORM_SYMBOL_EXPORT
# else
#   define PLATFORM_DECL PLATFORM_SYMBOL_IMPORT
#   define LIBRARY_SYMBOL_IMPORT PLATFORM_SYMBOL_IMPORT
# endif
#else
# define PLATFORM_DECL
#endif



