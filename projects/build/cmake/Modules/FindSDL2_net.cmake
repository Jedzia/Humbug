# Locate SDL_net library
# This module defines
# SDLNET_LIBRARY, the name of the library to link against
# SDLNET_FOUND, if false, do not try to link against
# SDLNET_INCLUDE_DIR, where to find the headers
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
set(_DEP_PATH ${CMAKE_BINARY_DIR}/DEPS/SDL2_net-2.0.0)

find_path(SDLNET_INCLUDE_DIR SDL_net.h
  HINTS
  $ENV{SDLNETDIR}
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
find_library(SDLNET_LIBRARY_RELEASE 
  NAMES SDL2_net
  HINTS
  $ENV{SDLNETDIR}
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
find_library(SDLNET_LIBRARY_DEBUG 
  NAMES SDL2_net
  HINTS
  $ENV{SDLNETDIR}
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
set(SDLNET_LIBRARY "optimized;${SDLNET_LIBRARY_RELEASE};debug;${SDLNET_LIBRARY_DEBUG}"  CACHE STRING "SDL networking library" FORCE)

if(WIN32)
    find_file(SDLNET_LIBRARY_DLL_RELEASE NAMES SDL2_net.dll PATHS
    	/lib
		/usr/lib
		/usr/local/lib
		${_DEP_PATH}/Release
		${_DEP_PATH}/VisualC/x64/Release
    )
    find_file(SDLNET_LIBRARY_DLL_DEBUG NAMES SDL2_net.dll PATHS
    	/lib
		/usr/lib
		/usr/local/lib
		${_DEP_PATH}/Debug
		${_DEP_PATH}/VisualC/x64/Debug
    )
endif(WIN32)

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDLNET
                                  REQUIRED_VARS SDLNET_LIBRARY SDLNET_INCLUDE_DIR)
