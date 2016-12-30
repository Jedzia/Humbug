# Locate SDL_image library
# This module defines
# SDLIMAGE_LIBRARY, the name of the library to link against
# SDLIMAGE_FOUND, if false, do not try to link to SDL
# SDLIMAGE_INCLUDE_DIR, where to find SDL/SDL.h
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

#MESSAGE(FATAL_ERROR "SDL_image Library not ${CMAKE_SOURCE_DIR}!")
SET(_DEP_PATH ${CMAKE_BINARY_DIR}/DEPS/SDL_image-1.2.12)
MESSAGE(STATUS "_DEP_PATH: ${_DEP_PATH}")


FIND_PATH(SDLIMAGE_INCLUDE_DIR SDL_image.h
  HINTS
  $ENV{SDLIMAGEDIR}
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

FIND_LIBRARY(SDLIMAGE_LIBRARY_RELEASE 
  NAMES SDL_image
  HINTS
  $ENV{SDLIMAGEDIR}
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
  ${_DEP_PATH}/VisualC/Release
  ${_DEP_PATH}/VisualC/x64/Release
)
SET(SDLIMAGE_LIBRARY "optimized;${SDLIMAGE_LIBRARY_RELEASE};debug;${SDLIMAGE_LIBRARY_RELEASE}"  CACHE STRING "SDL image library" FORCE)

IF(WIN32)

    FIND_FILE(SDLIMAGE_LIBRARY_DLL_RELEASE NAMES SDL_image.dll PATHS
    	/lib
		/usr/lib
		/usr/local/lib
		${_DEP_PATH}/VisualC/Release
		${_DEP_PATH}/VisualC/x64/Release
    )
    FIND_FILE(SDLIMAGE_LIBRARY_DLL_DEBUG NAMES SDL_image.dll PATHS
    	/lib
		/usr/lib
		/usr/local/lib
		${_DEP_PATH}/VisualC/Debug
		${_DEP_PATH}/VisualC/x64/Debug
    )

    #FIND_FILE(SDLIMAGE_LIBRARY_DLL_EXT NAMES libjpeg-8.dll libpng15-15.dll PATHS
	#	${_DEP_PATH}/VisualC/external/lib/x86
    #)
	# check 64 bit
	IF( CMAKE_SIZEOF_VOID_P EQUAL 4 )
	 SET( _sdlimage_library_dlls_ext_path x86 )
	ELSE( CMAKE_SIZEOF_VOID_P EQUAL 4 )
	 SET( _sdlimage_library_dlls_ext_path x64 )
	ENDIF( CMAKE_SIZEOF_VOID_P EQUAL 4 )

    FILE(GLOB SDLIMAGE_LIBRARY_DLLS_EXT ${_DEP_PATH}/VisualC/external/lib/${_sdlimage_library_dlls_ext_path}/*.dll)
	SET(SDLIMAGE_LIBRARY_DLLS_EXT "${SDLIMAGE_LIBRARY_DLLS_EXT}"  CACHE STRING "SDL image helper libraries" FORCE)

ENDIF(WIN32)

#INCLUDE(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDLIMAGE
                                  REQUIRED_VARS SDLIMAGE_LIBRARY SDLIMAGE_INCLUDE_DIR)
