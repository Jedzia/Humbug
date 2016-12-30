# Locate SDL_mixer library
# This module defines
# SDLMIXER_LIBRARY, the name of the library to link against
# SDLMIXER_FOUND, if false, do not try to link to SDL
# SDLMIXER_INCLUDE_DIR, where to find SDL/SDL.h
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

# Todo: in all FindSDL scripts, use a way to find the lib via "SDL2_gfx", not the versioned path
SET(_DEP_PATH ${CMAKE_BINARY_DIR}/DEPS/SDL2_mixer-2.0.0)

FIND_PATH(SDLMIXER_INCLUDE_DIR SDL_mixer.h
  HINTS
  $ENV{SDLMIXERDIR}
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

FIND_LIBRARY(SDLMIXER_LIBRARY_RELEASE 
  NAMES SDL2_mixer
  HINTS
  $ENV{SDLMIXERDIR}
  $ENV{SDLDIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
  ${_DEP_PATH}/VisualC/x64/Release
)
FIND_LIBRARY(SDLMIXER_LIBRARY_DEBUG 
  NAMES SDL2_mixer
  HINTS
  $ENV{SDLMIXERDIR}
  $ENV{SDLDIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
  ${_DEP_PATH}/VisualC/x64/Debug
)
SET(SDLMIXER_LIBRARY "optimized;${SDLMIXER_LIBRARY_RELEASE};debug;${SDLMIXER_LIBRARY_DEBUG}"  CACHE STRING "SDL mixer library" FORCE)

IF(WIN32)
    FIND_FILE(SDLMIXER_LIBRARY_DLL_RELEASE NAMES SDL2_mixer.dll PATHS
    	/lib
		/usr/lib
		/usr/local/lib
		${_DEP_PATH}/Release
		${_DEP_PATH}/VisualC/x64/Release
    )
    FIND_FILE(SDLMIXER_LIBRARY_DLL_DEBUG NAMES SDL2_mixer.dll PATHS
    	/lib
		/usr/lib
		/usr/local/lib
		${_DEP_PATH}/Debug
		${_DEP_PATH}/VisualC/x64/Debug
    )
ENDIF(WIN32)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDLMIXER
                                  REQUIRED_VARS SDLMIXER_LIBRARY SDLMIXER_INCLUDE_DIR)
