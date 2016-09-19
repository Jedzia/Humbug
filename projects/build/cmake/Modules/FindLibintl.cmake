# Try to find Libintl functionality
# Once done this will define
#
#  LIBINTL_FOUND - system has Libintl
#  LIBINTL_INCLUDE_DIR - Libintl include directory
#  LIBINTL_LIBRARIES - Libraries needed to use Libintl
#
# TODO: This will enable translations only if Gettext functionality is
# present in libc. Must have more robust system for release, where Gettext
# functionality can also reside in standalone Gettext library, or the one
# embedded within kdelibs (cf. gettext.m4 from Gettext source).

# Copyright (c) 2006, Chusslove Illich, <caslav.ilic@gmx.net>
# Copyright (c) 2007, Alexander Neundorf, <neundorf@kde.org>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if(LIBINTL_INCLUDE_DIR AND LIBINTL_LIB_FOUND)
  set(Libintl_FIND_QUIETLY TRUE)
endif(LIBINTL_INCLUDE_DIR AND LIBINTL_LIB_FOUND)

find_path(LIBINTL_INCLUDE_DIR libintl.h HINTS c:/usr/include )
find_path(LIBINTL_INCLUDE_DIR libintl.h HINTS ${GNUWIN32_DIR}/include)

find_file(LIBINTL_HEADER libintl.h
	PATHS ${LIBINTL_INCLUDE_DIR} NO_DEFAULT_PATH)
	
set(LIBINTL_LIB_FOUND FALSE)

if(LIBINTL_INCLUDE_DIR)
  include(CheckFunctionExists)
  check_function_exists(dgettext LIBINTL_LIBC_HAS_DGETTEXT)

  if (LIBINTL_LIBC_HAS_DGETTEXT)
    set(LIBINTL_LIBRARIES)
    set(LIBINTL_LIB_FOUND TRUE)
  else (LIBINTL_LIBC_HAS_DGETTEXT)

if(WIN32)
        SET(__LIBINTL_LIBNAME_REL LIBINTL3j.lib)
        SET(__LIBINTL_LIBNAME_DEB LIBINTL3jd.lib)
        SET(__LIBINTL_DLL_REL libintl3j.dll libintl3.dll)
        SET(__LIBINTL_DLL_DEB libintl3j.dll libintl3.dll)
else(WIN32)
        SET(__LIBINTL_LIBNAME_REL LIBINTL2)
        SET(__LIBINTL_LIBNAME_DEB LIBINTL2)
endif(WIN32)

  find_library(LIBINTL_LIBRARIES NAMES libintl3j intl libintl  HINTS c:/usr/lib)
  find_library(LIBINTL_LIBRARIES NAMES libintl3j intl libintl  HINTS ${GNUWIN32_DIR}/lib)
    if(LIBINTL_LIBRARIES)
      set(LIBINTL_LIB_FOUND TRUE)

	  
	FIND_FILE(LIBINTL_DLL_DEBUG NAMES ${__LIBINTL_DLL_DEB} PATHS 
	/usr/lib
	/usr/local/lib
	c:/usr/bin 
	${GNUWIN32_DIR}/bin
	NO_DEFAULT_PATH)

	FIND_FILE(LIBINTL_DLL_RELEASE NAMES ${__LIBINTL_DLL_REL} PATHS 
	/usr/lib
	/usr/local/lib
	c:/usr/bin 
	${GNUWIN32_DIR}/bin
	NO_DEFAULT_PATH)
	
    endif(LIBINTL_LIBRARIES)
  endif (LIBINTL_LIBC_HAS_DGETTEXT)

endif(LIBINTL_INCLUDE_DIR)

# \Todo: wrap this with LIBINTL_FOUND to prevent double checks.
#include(FindPackageHandleStandardArgs)
#find_package_handle_standard_args(Libintl  DEFAULT_MSG  LIBINTL_INCLUDE_DIR  LIBINTL_LIB_FOUND)

mark_as_advanced(LIBINTL_INCLUDE_DIR  LIBINTL_LIBRARIES  LIBINTL_LIBC_HAS_DGETTEXT  LIBINTL_LIB_FOUND
                 LIBINTL_DLL_DEBUG LIBINTL_DLL_RELEASE LIBINTL_HEADER
)
