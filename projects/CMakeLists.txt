##---------------------------------------------------------------------------
## $RCSfile$
## $Source$
## $Revision$
## $Date$
##---------------------------------------------------------------------------
## Author:      Jedzia
## Copyright:   (c) Jedzia, 2010
## License:     GPL License
##---------------------------------------------------------------------------
##---------------------------------------------------
##
##---------------------------------------------------
## !!!!!! CMake Help: http://www.cmake.org/cmake/help/cmake-2-8-docs.html !!!!!
## CMake Useful Variables: http://cmake.org/Wiki/CMake_Useful_Variables

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.2)
if ( CYGWIN )
  set(CMAKE_LEGACY_CYGWIN_WIN32 1)
endif( CYGWIN )

PROJECT( Humbug )
SET(CMAKE_BUILD_TYPE "Debug"  CACHE STRING "CMake Build Type")

SET(P_ROOT_PATH "${CMAKE_SOURCE_DIR}/../")
SET(P_BUILD_PATH "${CMAKE_SOURCE_DIR}/build")
SET(P_MODULE_PATH "${P_BUILD_PATH}/cmake/Modules")
SET(CMAKE_MODULE_PATH "${P_MODULE_PATH};${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}")
SET(_prj_name ${CMAKE_PROJECT_NAME})

INCLUDE (install)
INCLUDE (setup)
INCLUDE (debug)

#SET(BUILD_SHARED_LIBS ON)
# Do not use the CorePlug dependency for CppStructz
SET(CppStructz_No_CorePlug 1)




# Include CMakeLists.txt from subdirectories. Say, here comes the project stuff.
#ADD_SUBDIRECTORY(SupportLibs)
#ADD_SUBDIRECTORY(CppStructz)
ADD_SUBDIRECTORY(HumbugLib)

#ADD_SUBDIRECTORY(QBounce)
ADD_SUBDIRECTORY(Humbug )
ADD_SUBDIRECTORY(Playground)
#ADD_SUBDIRECTORY(build/Templates/src/Templates)

# Spit out a configuration summary. 
message(STATUS)
message(STATUS)
message(STATUS "================================================================================")
message(STATUS "Build options, switch ${_prj_name}_* variables by -D${_prj_name}_*=1 or 0:")
message(STATUS "================================================================================")
#PRJ_OPTION_LIST_ALL(help)
message(STATUS)
message(STATUS "       ========== Summary Information for ${_prj_name} ==========           ")
message(STATUS)
PRJ_OPTION_LIST_ALL(used)

message(STATUS)
message(STATUS "       ========== Module Information for ${_prj_name} ==========           ")
#MODUSE_SUMMARY_LIST_ALL(help)
MODUSE_SUMMARY_LIST_ALL(used)
#message(STATUS "MODUSE_SUMMARYS LIST = ${MODUSE_SUMMARYS}")
message(STATUS "================================================================================")


message(STATUS)
message(STATUS "${_prj_name}_ABS_TOP_SRCDIR=${${_prj_name}_ABS_TOP_SRCDIR}")
message(STATUS "${_prj_name}_ABS_INSTALLED_DATADIR=${${_prj_name}_ABS_INSTALLED_DATADIR}")
message(STATUS "${_prj_name}_DATA_SUBDIR=${${_prj_name}_DATA_SUBDIR}")
message(STATUS)
if(${${_prj_name}_NLS})
	message(STATUS)
	message(STATUS "${_prj_name}_ABS_INSTALLED_LOCALEDIR=${${_prj_name}_ABS_INSTALLED_LOCALEDIR}")
	message(STATUS "using LOCALEDIR=${${_prj_name}_LOCALEDIR}")
	message(STATUS)
	message(STATUS "Building Native Language Support (${_prj_name}_NLS is set), used libraries:")
	message(STATUS)
	message(STATUS "  * intl")
	message(STATUS "     - header : ${LIBINTL_HEADER}")
	message(STATUS "     - library: ${LIBINTL_LIBRARIES}")
	message(STATUS "  * iconv")
	message(STATUS "     - header : ${ICONV_HEADER}")
	message(STATUS "     - library: ${ICONV_LIBRARY}")
	message(STATUS "  * zlib")
	message(STATUS "     - header : ${ZLIB_HEADER}")
	message(STATUS "     - library: ${ZLIB_LIBRARY}")
	message(STATUS)
endif()
#MESSAGE(STATUS "SDL_LIBRARY_BLA is ${SDL_LIBRARY_BLA}")
#MESSAGE(STATUS "SDL_LIBRARY_TEMP is ${SDL_LIBRARY_TEMP}")
#MESSAGE(STATUS "SDL_LIBRARY is ${SDL_LIBRARY}")
message(STATUS "================================================================================")

#MESSAGE(STATUS "CMAKE_CFG_INTDIR is ${CMAKE_CFG_INTDIR}")
