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
## !!!!!! we should use the internal FindwxWidgets.cmake !!!!!

#cmake_policy(SET CMP0005 NEW) # 
cmake_minimum_required(VERSION 2.8)

PROJECT( HumbugCore )
#SET(LIBRARY_TYPE SHARED)
SET(LIBRARY_TYPE STATIC)

MESSAGE(STATUS         "!!!!!!!!!!!!!!!! CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME} !!!!!!!!!!")
INCLUDE (BoostExtensions)
INCLUDE (PCHSupport)
INCLUDE (library)
INCLUDE (CopyResourcesToBuildTree)
INCLUDE (helpers)

SET(USE_LIB_BOOST_COMPONENTS "system;filesystem;signals;program_options")
#SET(USE_LIB_BOOST TRUE CACHE BOOL "Use Boost libraries")
# Use Boost libraries for this project.
SET(USE_LIB_BOOST TRUE)
SET(USE_LIB_ZLIB TRUE)
SET(USE_LUA TRUE)

#SET(USE_LIB_QT4 TRUE CACHE BOOL "Use QT4 libraries")
# Use QT4 libraries for this project.
#SET(USE_LIB_QT4 TRUE)

# Use QSCINTILLA libraries for this project.
#SET(USE_LIB_QSCINTILLA TRUE)

#SET(USE_LIB_XSD TRUE CACHE BOOL "Use XSD xerces libraries")
# Use XSD xerces libraries for this project.
#SET(USE_LIB_XSD TRUE)

# local project settings
INCLUDE (bindings)

# Link explicitely to Microsoft.VC90.CRT version=9.0.30729.1
#ADD_DEFINITIONS("-D_BIND_TO_CURRENT_VCLIBS_VERSION=1")
# this does the same as above
#ADD_DEFINITIONS("-D_BIND_TO_CURRENT_MFC_VERSION=2")
#ADD_DEFINITIONS("-D_BIND_TO_CURRENT_CRT_VERSION=2")

SET(HumbugCore_GameObject_headers 
#	GameObjects/Template.h
#	GameObjects/GameObject.h
#	GameObjects/GVector2D.h
#	GameObjects/GPoint2D.h
#	GameObjects/Player.h
)

SET(HumbugCore_GameObject_sources 
#	GameObjects/Template.cpp
#	GameObjects/GameObject.cpp
#	GameObjects/GVector2D.cpp
#	GameObjects/GPoint2D.cpp
#	GameObjects/Player.cpp
)

SET(HumbugCore_Serialization_headers 
	Serialization/Test.h
)

SET(HumbugCore_Serialization_sources 
	Serialization/Test.cpp
)


SET(HumbugCore_headers 
#	GB.h
	
#	VFS/fileio.h
#	VFS/static_assert.h
#	VFS/stdafx.h
#	VFS/stdint.h
#	VFS/zfsystem.h
#	VFS/ziphdr.h
#	VFS/zstream.h
#	VFS/zstream_zlib.h
#	Project/ProcessProjectPrivate.h
)

SET(HumbugCore_sources 
#	GB.cpp

#	VFS/zfsystem.cpp
#	VFS/ziphdr.cpp
#	VFS/zstream.cpp
)

#SET(HumbugCore_INCLUDE_DIR ${HumbugCore_IncludePath} CACHE PATH "HumbugCore include directory." FORCE)


SET(HumbugCore_resfiles 
#  mainwindow.qrc
)

#SET(CMAKE_BUILD_TYPE DEBUG)


INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${HumbugLib_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${LUABIND_INCLUDE_DIR})
#INCLUDE_DIRECTORIES( ${CppStructz_INCLUDE_DIR} )

IF(LINUX)
  INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
ENDIF(LINUX)


#ADD_DEFINITIONS(${CppStructz_DEFINITIONS})
IF(LINUX)
  ADD_DEFINITIONS("-DLINUX")
  ADD_DEFINITIONS("-DUNIX")
ENDIF(LINUX)
IF(MSYS)
  ADD_DEFINITIONS("-DUNIX")
ENDIF(MSYS)


SOURCE_GROUP(Generated FILES ${res_outfiles} ${moc_outfiles} ${ui_outfiles} )
SOURCE_GROUP(Resources FILES ${HumbugCore_resfiles})
SOURCE_GROUP(GameObject FILES ${HumbugCore_GameObject_headers})
SOURCE_GROUP(GameObject FILES ${HumbugCore_GameObject_sources})
SOURCE_GROUP(Serialization FILES ${HumbugCore_Serialization_headers})
SOURCE_GROUP(Serialization FILES ${HumbugCore_Serialization_sources})
SOURCE_GROUP(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
SOURCE_GROUP(THeaders FILES ${HumbugCore_headers})
SOURCE_GROUP(TSources FILES ${HumbugCore_sources})

SET(HumbugCore_pre_sources 
    ${HumbugCore_GameObject_sources}
    ${HumbugCore_Serialization_sources}
    ${HumbugCore_sources} 
)

ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" HumbugCore_pre_sources)
#ADD_DEFINITIONS("-DMYENGINE_EXPORTS")
ADD_LIBRARY_X(HumbugCore ${LIBRARY_TYPE}
        stdafx.h
        ${DEBUG_DEFINITION_INCLUDES}
        stddefs.h 
        global.h 

    	${HumbugCore_pre_sources}
    	${HumbugCore_Serialization_headers}
    	${HumbugCore_GameObject_headers}
        ${HumbugCore_headers}
        ${res_outfiles} 
        ${moc_outfiles} 
        ${ui_outfiles}
)

TARGET_LINK_LIBRARIES(HumbugCore ${ZLIB_LIBRARY} )
TARGET_LINK_LIBRARIES(HumbugCore luabind)
ADD_DEPENDENCIES(HumbugCore luabind)
TargetLinkBoost(HumbugCore "filesystem;system;regex")
#ADD_DEPENDENCIES(HumbugCore CppStructz)
ADD_PRECOMPILED_HEADER(HumbugCore stdafx.h stdafx.h.gch)

ADD_SUBDIRECTORY( UnitTests )
