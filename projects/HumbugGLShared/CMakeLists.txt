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

PROJECT( HumbugGLShared )
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

SET(HumbugGLShared_headers 
	GB.h
	
	VFS/fileio.h
	VFS/static_assert.h
#	VFS/stdafx.h
#	VFS/stdint.h
	VFS/zfsystem.h
	VFS/ziphdr.h
	VFS/zstream.h
	VFS/zstream_zlib.h
#	Project/ProcessProject.h
#	Project/ProcessProjectPrivate.h
)

SET(HumbugGLShared_GameObject_headers 
	GameObjects/Template.h
	GameObjects/GameObject.h
	GameObjects/GVector2D.h
	GameObjects/GPoint2D.h
	GameObjects/Player.h
)

SET(HumbugGLShared_GameObject_sources 
	GameObjects/Template.cpp
	GameObjects/GameObject.cpp
	GameObjects/GVector2D.cpp
	GameObjects/GPoint2D.cpp
	GameObjects/Player.cpp
)

SET(HumbugGLShared_ScriptHost_headers 
	ScriptHost/LuaScript.h
	ScriptHost/ScriptHostIO.h
	ScriptHost/ScriptHostPrivate.h
	ScriptHost/ScriptHostImpl.h
	ScriptHost/ScriptHost.h
)

SET(HumbugGLShared_ScriptHost_sources 
	ScriptHost/ScriptHost.cpp
	ScriptHost/LuaScript.cpp
)


SET(HumbugGLShared_sources 
	GB.cpp

	VFS/zfsystem.cpp
	VFS/ziphdr.cpp
	VFS/zstream.cpp
#	Project/ProcessProject.cpp
#	Project/ProcessProjectPrivate.cpp
)

#SET(HumbugGLShared_INCLUDE_DIR ${HumbugGLShared_IncludePath} CACHE PATH "HumbugGLShared include directory." FORCE)


SET(HumbugGLShared_resfiles 
#  mainwindow.qrc
)

#SET(CMAKE_BUILD_TYPE DEBUG)


INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${HumbugGLLib_INCLUDE_DIR})
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
SOURCE_GROUP(Resources FILES ${HumbugGLShared_resfiles})
SOURCE_GROUP(GameObject FILES ${HumbugGLShared_GameObject_headers})
SOURCE_GROUP(GameObject FILES ${HumbugGLShared_GameObject_sources})
SOURCE_GROUP(ScriptHost FILES ${HumbugGLShared_ScriptHost_headers})
SOURCE_GROUP(ScriptHost FILES ${HumbugGLShared_ScriptHost_sources})
SOURCE_GROUP(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
SOURCE_GROUP(THeaders FILES ${HumbugGLShared_headers})
SOURCE_GROUP(TSources FILES ${HumbugGLShared_sources})

SET(HumbugGLShared_pre_sources 
    ${HumbugGLShared_GameObject_sources}
    ${HumbugGLShared_ScriptHost_sources}
    ${HumbugGLShared_sources} 
)

ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" HumbugGLShared_pre_sources)
#ADD_DEFINITIONS("-DMYENGINE_EXPORTS")
ADD_LIBRARY_X(HumbugGLShared ${LIBRARY_TYPE}
        stdafx.h
        ${DEBUG_DEFINITION_INCLUDES}
        defs.h 

    	${HumbugGLShared_pre_sources}
    	${HumbugGLShared_ScriptHost_headers}
    	${HumbugGLShared_GameObject_headers}
        ${HumbugGLShared_headers}
        ${res_outfiles} 
        ${moc_outfiles} 
        ${ui_outfiles}
)

TARGET_LINK_LIBRARIES(HumbugGLShared ${ZLIB_LIBRARY} )
TARGET_LINK_LIBRARIES(HumbugGLShared luabind)
ADD_DEPENDENCIES(HumbugGLShared luabind)
TargetLinkBoost(HumbugGLShared "filesystem;system;regex")
#ADD_DEPENDENCIES(HumbugGLShared CppStructz)
ADD_PRECOMPILED_HEADER(HumbugGLShared stdafx.h stdafx.h.gch)

ADD_SUBDIRECTORY( UnitTests )
