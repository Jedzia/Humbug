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

cmake_minimum_required(VERSION 2.8.7)
cmake_policy(SET  CMP0026  OLD)
cmake_policy(SET  CMP0054  OLD)

if ( CYGWIN )
  set(CMAKE_LEGACY_CYGWIN_WIN32 1)
endif( CYGWIN )

project( HumbugGL )
set(CMAKE_BUILD_TYPE "Debug"  CACHE STRING "CMake Build Type")

set(P_ROOT_PATH "${CMAKE_SOURCE_DIR}/../")
set(P_BUILD_PATH "${CMAKE_SOURCE_DIR}/build")
set(P_MODULE_PATH "${P_BUILD_PATH}/cmake/Modules")
set(CMAKE_MODULE_PATH "${P_MODULE_PATH};${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}")
set(BUILD_ROOT_PATH "${CMAKE_CURRENT_BINARY_DIR}")
set(_prj_name ${CMAKE_PROJECT_NAME})

if ( WIN32 )
  include (install)
endif( WIN32 )
include (setup)
include (debug)
#include (dependencies)

#set(BUILD_SHARED_LIBS ON)
# Do not use the CorePlug dependency for CppStructz
set(CppStructz_No_CorePlug 1)

set(LUABIND_INSTALL OFF)# "Install the LuaBind library and headers" ON)
set(LUABIND_APPEND_VERSION_SUFFIX OFF)# "Append a version suffix to the library name (like luabind09)?" ON)
set(LUABIND_NO_ERROR_CHECKING OFF)# "Build so that all the Lua code is expected only to make legal calls?" OFF)
set(LUABIND_NO_EXCEPTIONS OFF)# "Disable all usage of try, catch, and throw?" OFF)
set(LUABIND_CPLUSPLUS_LUA OFF)# "Was Lua built as C++?" OFF)
set(LUABIND_DYNAMIC_LINK OFF)# "Build luabind as a shared library?" OFF)
set(LUABIND_NOT_THREADSAFE OFF)# "Permit the use of static variables, thus making Luabind usable only from one of your system threads." OFF)
set(LUABIND_ENABLE_WARNINGS ON)# "Enable extra warnings during the build of the library and tests" ON)
set(LUABIND_USE_CXX11 OFF)# "Build Luabind using C++11 features?" ${LUABIND_CXX11_DEFAULT})



# Include CMakeLists.txt from subdirectories. Say, here comes the project stuff.
add_subdirectory(SupportLibs)
#add_subdirectory(CppStructz)
add_subdirectory(HumbugGLLib)
add_subdirectory(HumbugGLShared)

add_subdirectory(GuiLib)
add_subdirectory(HumbugGLCore)
add_subdirectory(HumbugGLSerialization)
add_subdirectory(HumbugGL )
add_subdirectory(Playground)
#add_subdirectory(build/Templates/src/Templates)

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
#message(STATUS "SDL_LIBRARY_BLA is ${SDL_LIBRARY_BLA}")
#message(STATUS "SDL_LIBRARY_TEMP is ${SDL_LIBRARY_TEMP}")
#message(STATUS "SDL_LIBRARY is ${SDL_LIBRARY}")
message(STATUS "================================================================================")

#message(STATUS "CMAKE_CFG_INTDIR is ${CMAKE_CFG_INTDIR}")
