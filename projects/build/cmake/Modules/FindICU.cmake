# Finds the International Components for Unicode (ICU) Library
#
#  ICU_FOUND          - True if ICU found.
#  ICU_I18N_FOUND     - True if ICU's internationalization library found.
#  ICU_INCLUDE_DIRS   - Directory to include to get ICU headers
#                       Note: always include ICU headers as, e.g.,
#                       unicode/utypes.h
#  ICU_LIBRARIES      - Libraries to link against for the common ICU
#  ICU_I18N_LIBRARIES - Libraries to link against for ICU internationaliation
#                       (note: in addition to ICU_LIBRARIES)

# Look for the header file.
find_path(
  ICU_INCLUDE_DIR
  NAMES unicode/utypes.h
  DOC "Include directory for the ICU library"
  PATHS
  D:/boost/icu/include
  NO_DEFAULT_PATH)
mark_as_advanced(ICU_INCLUDE_DIR)

# Look for the library.
find_library(
  ICU_LIBRARY
  NAMES icuuc cygicuuc cygicuuc32
  DOC "Libraries to link against for the common parts of ICU"
  PATHS
  D:/boost/icu/lib
  NO_DEFAULT_PATH)
mark_as_advanced(ICU_LIBRARY)

if(WIN32)
 #       SET(__QSCINTILLA_LIBNAME_REL qscintilla2.lib)
 #       SET(__QSCINTILLA_LIBNAME_DEB qscintilla2d.lib)
        SET(__ICU_DLL_REL icuin44.dll)
        SET(__ICU_DLL_DEB icuin44d.dll)
else(WIN32)
#        SET(__QSCINTILLA_LIBNAME_REL qscintilla2)
#        SET(__QSCINTILLA_LIBNAME_DEB qscintilla2)
endif(WIN32)

if(WIN32)
FIND_FILE(ICU_DLL_DEBUG NAMES ${__ICU_DLL_DEB} PATHS 
/usr/lib
/usr/local/lib
D:/boost/icu/bin
 NO_DEFAULT_PATH)

FIND_FILE(ICU_DLL_RELEASE NAMES ${__ICU_DLL_REL} PATHS 
/usr/lib
/usr/local/lib
D:/boost/icu/bin
 NO_DEFAULT_PATH)
endif(WIN32)

# Copy the results to the output variables.
if(ICU_INCLUDE_DIR AND ICU_LIBRARY)
  set(ICU_FOUND 1)
  set(ICU_LIBRARIES ${ICU_LIBRARY})
  set(ICU_INCLUDE_DIRS ${ICU_INCLUDE_DIR})

  set(ICU_VERSION 0)
  set(ICU_MAJOR_VERSION 0)
  set(ICU_MINOR_VERSION 0)
  if (EXISTS "${ICU_INCLUDE_DIR}/unicode/uvernum.h")
    FILE(READ "${ICU_INCLUDE_DIR}/unicode/uvernum.h" _ICU_VERSION_CONENTS)
  else()
    FILE(READ "${ICU_INCLUDE_DIR}/unicode/uversion.h" _ICU_VERSION_CONENTS)
  endif()

  STRING(REGEX REPLACE ".*#define U_ICU_VERSION_MAJOR_NUM ([0-9]+).*" "\\1" ICU_MAJOR_VERSION "${_ICU_VERSION_CONENTS}")
  STRING(REGEX REPLACE ".*#define U_ICU_VERSION_MINOR_NUM ([0-9]+).*" "\\1" ICU_MINOR_VERSION "${_ICU_VERSION_CONENTS}")

  set(ICU_VERSION "${ICU_MAJOR_VERSION}.${ICU_MINOR_VERSION}")

  # Look for the ICU internationalization libraries
  find_library(
    ICU_I18N_LIBRARY
    NAMES icuin icui18n cygicuin cygicuin32
    DOC "Libraries to link against for ICU internationalization")
  mark_as_advanced(ICU_I18N_LIBRARY)
  if (ICU_I18N_LIBRARY)
    set(ICU_I18N_FOUND 1)
    set(ICU_I18N_LIBRARIES ${ICU_I18N_LIBRARY})
  else (ICU_I18N_LIBRARY)
    set(ICU_I18N_FOUND 0)
    set(ICU_I18N_LIBRARIES)
  endif (ICU_I18N_LIBRARY)
else(ICU_INCLUDE_DIR AND ICU_LIBRARY)
  set(ICU_FOUND 0)
  set(ICU_I18N_FOUND 0)
  set(ICU_LIBRARIES)
  set(ICU_I18N_LIBRARIES)
  set(ICU_INCLUDE_DIRS)
  set(ICU_VERSION)
  set(ICU_MAJOR_VERSION)
  set(ICU_MINOR_VERSION)
endif(ICU_INCLUDE_DIR AND ICU_LIBRARY)

IF(ICU_FOUND)
  IF( NOT ICU_FIND_QUIETLY )
    MESSAGE( STATUS "Found ICU header files in ${ICU_INCLUDE_DIRS}")
    MESSAGE( STATUS "Found ICU libraries: ${ICU_LIBRARIES}")
  ENDIF( NOT ICU_FIND_QUIETLY )
MARK_AS_ADVANCED(ICU_DLL_DEBUG)
MARK_AS_ADVANCED(ICU_DLL_RELEASE)
ELSE(ICU_FOUND)
	IF(ICU_FIND_REQUIRED)
		MESSAGE( FATAL_ERROR "Could not find ICU" )
	ELSE(ICU_FIND_REQUIRED)
		MESSAGE( STATUS "Optional package ICU was not found" )
	ENDIF(ICU_FIND_REQUIRED)
ENDIF(ICU_FOUND)
