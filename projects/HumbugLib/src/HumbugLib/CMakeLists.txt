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

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT( HumbugLib )
SET(PACKAGE ${PROJECT_NAME})

INCLUDE (BoostExtensions)
INCLUDE (PCHSupport)
INCLUDE (library)


# Check for wchar_t
#SET(CHECK_STRINGS TRUE)

#SET(USE_SDL TRUE)
#SET(USE_LUA TRUE)
# apply the local project settings
INCLUDE (bindings)

IF(MSVC)
  #  Disable C4251 Compiler Warning
  ADD_DEFINITIONS("/wd4251")
ENDIF(MSVC)

IF(LINUX)
  ADD_DEFINITIONS("-DLINUX")
ENDIF(LINUX)


# HumbugLib Library
SET(HumbugLib_interface 
  ${HumbugLib_INTERFACE_DIR}/global.h
#  ${HumbugLib_INTERFACE_DIR}/TestClass.h
  ${HumbugLib_INTERFACE_DIR}/FileDetector.h
)
#Todo: Ein macro das in die SOURCE_GROUP Interface_FileSystem einordnet. Je nach directory.

SET(HumbugLib_headers 
  stdafx.h
  AppGB.h
#  shared/Txt.h
#  shared/FileHelper.h
)

SET(HumbugLib_sources 
#  shared/Txt.cpp
  FileDetector.cpp
  AppGB.cpp
#  Unzipper.cpp
#  Zipper.cpp
)
IF(WIN32)
	SET(HumbugLib_sources ${HumbugLib_sources}
		win32/appinit.cpp
	)  
ENDIF(WIN32)
ADD_DEFINITIONS(-DUNICODE=1)


#SET(CMAKE_BUILD_TYPE DEBUG)


#INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
#INCLUDE_DIRECTORIES( ${PROJECT_BINARY_DIR} )

# Source file filtering for the project.
SOURCE_GROUP(Generated FILES ${res_outfiles} ${moc_outfiles} ${ui_outfiles} )
SOURCE_GROUP(Resources FILES ${HumbugLib_resfiles})
SOURCE_GROUP(GUI FILES ${HumbugLib_uifiles})
SOURCE_GROUP(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
SOURCE_GROUP(GlobalHeader FILES ${LIBRARY_DEFINITION_INCLUDES})
SOURCE_GROUP(Interface FILES ${HumbugLib_interface})
SOURCE_GROUP(HumbugLib FILES ${HumbugLib_sources})
SOURCE_GROUP("Header Files" FILES ${HumbugLib_headers})
SOURCE_GROUP(Global FILES "stdafx.cpp")

#SET(LIBRARY_TYPE SHARED)
SET(LIBRARY_TYPE STATIC)

#INCLUDE(config)

ADD_DEFINITIONS("-DMYENGINE_EXPORTS")
ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" HumbugLib_sources )
ADD_LIBRARY_X(HumbugLib ${LIBRARY_TYPE}
        ${HumbugLib_CONFIG_FILES}
        ${HumbugLib_interface}
        ${HumbugLib_headers}
        ${DEBUG_DEFINITION_INCLUDES}
        ${LIBRARY_DEFINITION_INCLUDES}
        ${HumbugLib_sources} 
)
#TARGET_LINK_LIBRARIES(HumbugLib HumbugLibPackers)

# Precompiled header support.
ADD_PRECOMPILED_HEADER(HumbugLib stdafx.h stdafx.h.gch)

#INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} )
#INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR}/../ )
