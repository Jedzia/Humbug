##---------------------------------------------------------------------------
## $RCSfile$
## $Source$
## $Revision$
## $Date$
##---------------------------------------------------------------------------
## Author:      Jedzia
## Copyright:   (c) Jedzia, 2011
## License:     GPL License
##---------------------------------------------------------------------------
##---------------------------------------------------
## 
##--------------------------------------------------- 

cmake_minimum_required(VERSION 2.8)

project( HumbugLib )
set(PACKAGE ${PROJECT_NAME})

include (BoostExtensions)
include (PCHSupport)
include (library)


# Check for wchar_t
#set(CHECK_STRINGS TRUE)

#set(USE_SDL TRUE)
#set(USE_LUA TRUE)
# apply the local project settings
include (bindings)

if(MSVC)
  #  Disable C4251 Compiler Warning
  add_definitions("/wd4251")
endif(MSVC)

if(LINUX)
  add_definitions("-DLINUX")
endif(LINUX)


# HumbugLib Library
set(HumbugLib_interface 
  ${HumbugLib_INTERFACE_DIR}/global.h
#  ${HumbugLib_INTERFACE_DIR}/TestClass.h
  ${HumbugLib_INTERFACE_DIR}/FileDetector.h
)
#Todo: Ein macro das in die SOURCE_GROUP Interface_FileSystem einordnet. Je nach directory.

set(HumbugLib_headers 
  stdafx.h
  AppGB.h
  Log.h
  LogManager.h
  Singleton.h
#  shared/Txt.h
#  shared/FileHelper.h
)

set(HumbugLib_sources 
#  shared/Txt.cpp
  FileDetector.cpp
  AppGB.cpp
  Log.cpp
  LogManager.cpp
#  Unzipper.cpp
#  Zipper.cpp
)
if(WIN32)
	set(HumbugLib_sources ${HumbugLib_sources}
		win32/appinit.cpp
	)  
endif(WIN32)
if(UNIX OR LINUX)
	set(HumbugLib_sources ${HumbugLib_sources}
		unix/appinit.cpp
	)  
endif(UNIX OR LINUX)
add_definitions(-DUNICODE=1)


#set(CMAKE_BUILD_TYPE DEBUG)


#include_directories( ${PROJECT_SOURCE_DIR} )
#include_directories( ${PROJECT_BINARY_DIR} )

# Source file filtering for the project.
source_group(Generated FILES ${res_outfiles} ${moc_outfiles} ${ui_outfiles} )
source_group(Resources FILES ${HumbugLib_resfiles})
source_group(GUI FILES ${HumbugLib_uifiles})
source_group(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
source_group(GlobalHeader FILES ${LIBRARY_DEFINITION_INCLUDES})
source_group(Interface FILES ${HumbugLib_interface})
source_group(HumbugLib FILES ${HumbugLib_sources})
source_group("Header Files" FILES ${HumbugLib_headers})
source_group(Global FILES "stdafx.cpp")

#set(LIBRARY_TYPE SHARED)
set(LIBRARY_TYPE STATIC)

#include(config)

add_definitions("-DMYENGINE_EXPORTS")
ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" HumbugLib_sources )
ADD_LIBRARY_X(HumbugLib ${LIBRARY_TYPE}
        ${HumbugLib_CONFIG_FILES}
        ${HumbugLib_interface}
        ${HumbugLib_headers}
        ${DEBUG_DEFINITION_INCLUDES}
        ${LIBRARY_DEFINITION_INCLUDES}
        ${HumbugLib_sources} 
)
#target_link_libraries(HumbugLib HumbugLibPackers)

# Precompiled header support.
ADD_PRECOMPILED_HEADER(HumbugLib stdafx.h stdafx.h.gch)

#include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
#include_directories( ${CMAKE_CURRENT_BINARY_DIR}/../ )
