# Locate SDL_ttf library
# This module defines
# SDLTTF_LIBRARY, the name of the library to link against
# SDLTTF_FOUND, if false, do not try to link to SDL
# SDLTTF_INCLUDE_DIR, where to find SDL/SDL.h
#
# $SDLDIR is an environment variable that would
# correspond to the ./configure --prefix=$SDLDIR
# used in building SDL.
#
# Created by Eric Wing. This was influenced by the FindSDL.cmake 
# module, but with modifications to recognize OS X frameworks and 
# additional Unix paths (FreeBSD, etc).

#=============================================================================
# Copyright 2005-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

SET(_DEP_PATH ${CMAKE_BINARY_DIR}/DEPS/SDL_ttf-2.0.11)

FIND_PATH(SDLTTF_INCLUDE_DIR SDL_ttf.h
  HINTS
  $ENV{SDLTTFDIR}
  $ENV{SDLDIR}
  PATH_SUFFIXES include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include/SDL
  /usr/include/SDL
  /usr/local/include/SDL12
  /usr/local/include/SDL11 # FreeBSD ports
  /usr/include/SDL12
  /usr/include/SDL11
  /usr/local/include
  /usr/include
  /sw/include/SDL # Fink
  /sw/include
  /opt/local/include/SDL # DarwinPorts
  /opt/local/include
  /opt/csw/include/SDL # Blastwave
  /opt/csw/include 
  /opt/include/SDL
  /opt/include
  ${_DEP_PATH}
)

FIND_LIBRARY(SDLTTF_LIBRARY_RELEASE 
  NAMES SDL_ttf
  HINTS
  $ENV{SDLTTFDIR}
  $ENV{SDLDIR}
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
  ${_DEP_PATH}/VisualC/Release
  ${_DEP_PATH}/VisualC/x64/Release
    PATH_SUFFIXES lib64 lib
)
SET(SDLTTF_LIBRARY "optimized;${SDLTTF_LIBRARY_RELEASE};debug;${SDLTTF_LIBRARY_RELEASE}"  CACHE STRING "SDL true type font library" FORCE)

IF(WIN32)

    FIND_FILE(SDLTTF_LIBRARY_DLL_RELEASE NAMES SDL_ttf.dll PATHS
    	/lib
		/usr/lib
		/usr/local/lib
		${_DEP_PATH}/VisualC/Release
		${_DEP_PATH}/VisualC/x64/Release
    )
    FIND_FILE(SDLTTF_LIBRARY_DLL_DEBUG NAMES SDL_ttf.dll PATHS
    	/lib
		/usr/lib
		/usr/local/lib
		${_DEP_PATH}/VisualC/Debug
		${_DEP_PATH}/VisualC/x64/Debug
    )

    # // Todo: extra libfreetype-6
    #FIND_FILE(SDLTTF_LIBRARY_DLL_EXT NAMES libfreetype-6 PATHS
	#	${_DEP_PATH}/VisualC/external/lib/x86
    #)
    #FILE(GLOB SDLTTF_LIBRARY_DLLS_EXTS ${_DEP_PATH}/VisualC/external/lib/x86/*.dll)
	#SET(SDLTTF_LIBRARY_DLLS_EXT "${SDLTTF_LIBRARY_DLLS_EXTS}"  CACHE STRING "SDL ttf helper libraries" FORCE)
	IF( CMAKE_SIZEOF_VOID_P EQUAL 4 )
	 SET( _sdlttf_library_dlls_ext_path x86 )
	ELSE( CMAKE_SIZEOF_VOID_P EQUAL 4 )
	 SET( _sdlttf_library_dlls_ext_path x64 )
	ENDIF( CMAKE_SIZEOF_VOID_P EQUAL 4 )

    FILE(GLOB SDLTTF_LIBRARY_DLLS_EXTS ${_DEP_PATH}/VisualC/external/lib/${_sdlttf_library_dlls_ext_path}/*.dll)
	SET(SDLTTF_LIBRARY_DLLS_EXT "${SDLTTF_LIBRARY_DLLS_EXTS}"  CACHE STRING "SDL ttf helper libraries" FORCE)

	
ENDIF(WIN32)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDLTTF
                                  REQUIRED_VARS SDLTTF_LIBRARY SDLTTF_INCLUDE_DIR)
