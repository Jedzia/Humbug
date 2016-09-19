# Locate SDL_gfx library
# This module defines
# SDLGFX_LIBRARY, the name of the library to link against
# SDLGFX_FOUND, if false, do not try to link to SDL
# SDLGFX_INCLUDE_DIR, where to find SDL/SDL.h
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

SET(_DEP_PATH ${CMAKE_BINARY_DIR}/DEPS/SDL_gfx-2.0.23)

FIND_PATH(SDLGFX_INCLUDE_DIR SDL_gfxPrimitives.h
  HINTS
  $ENV{SDLGFXDIR}
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

FIND_LIBRARY(SDLGFX_LIBRARY_RELEASE 
  NAMES SDL_gfx
  HINTS
  $ENV{SDLGFXDIR}
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
  ${_DEP_PATH}/Release
  ${_DEP_PATH}/x64/Release
    PATH_SUFFIXES lib64 lib
)
SET(SDLGFX_LIBRARY "optimized;${SDLGFX_LIBRARY_RELEASE};debug;${SDLGFX_LIBRARY_RELEASE}"  CACHE STRING "SDL true type font library" FORCE)

IF(WIN32)

    FIND_FILE(SDLGFX_LIBRARY_DLL_RELEASE NAMES SDL_gfx.dll PATHS
    	/lib
		/usr/lib
		/usr/local/lib
		${_DEP_PATH}/Release
		${_DEP_PATH}/x64/Release
    )
    FIND_FILE(SDLGFX_LIBRARY_DLL_DEBUG NAMES SDL_gfx.dll PATHS
    	/lib
		/usr/lib
		/usr/local/lib
		${_DEP_PATH}/Debug
		${_DEP_PATH}/x64/Debug
    )

    #FIND_FILE(SDLIMAGE_LIBRARY_DLL_EXT NAMES libjpeg-8.dll libpng15-15.dll PATHS
	#	${_DEP_PATH}/VisualC/external/lib/x86
    #)
    #FILE(GLOB SDLIMAGE_LIBRARY_DLLS_EXT ${_DEP_PATH}/VisualC/external/lib/x86/*.dll)
	#SET(SDLIMAGE_LIBRARY_DLLS_EXT "${SDLIMAGE_LIBRARY_DLLS_EXT}"  CACHE STRING "SDL image helper libraries" FORCE)

ENDIF(WIN32)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDLGFX
                                  REQUIRED_VARS SDLGFX_LIBRARY SDLGFX_INCLUDE_DIR)
