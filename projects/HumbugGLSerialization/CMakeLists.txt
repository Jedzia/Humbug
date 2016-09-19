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

PROJECT( HumbugGLSerialization )
#SET(LIBRARY_TYPE SHARED)
SET(LIBRARY_TYPE STATIC)

MESSAGE(STATUS         "!!!!!!!!!!!!!!!! CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME} !!!!!!!!!!")
INCLUDE (BoostExtensions)
INCLUDE (PCHSupport)
INCLUDE (library)
INCLUDE (CopyResourcesToBuildTree)
INCLUDE (helpers)

ENSURE_DOCS_ARE_PRESENT(HumbugGLSerialization_documents)

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

SET(HumbugGLSerialization_GameObject_headers 
#	GameObjects/Template.h
#	GameObjects/GameObject.h
#	GameObjects/GVector2D.h
#	GameObjects/GPoint2D.h
#	GameObjects/Player.h
)

SET(HumbugGLSerialization_GameObject_sources 
#	GameObjects/Template.cpp
#	GameObjects/GameObject.cpp
#	GameObjects/GVector2D.cpp
#	GameObjects/GPoint2D.cpp
#	GameObjects/Player.cpp
)

SET(HumbugGLSerialization_Serialization_headers 
	Serialization/Test.h
	Serialization/LoadTest.h
	Serialization/SerializationHelpers.h
	Serialization/Token.h
	Serialization/VersionToken.h

	Serialization/InfoTextLoader.h
)

SET(HumbugGLSerialization_Serialization_sources 
	Serialization/Test.cpp
	Serialization/LoadTest.cpp
	Serialization/SerializationHelpers.cpp
	Serialization/Token.cpp
	Serialization/VersionToken.cpp

	Serialization/InfoTextLoader.cpp
)


SET(HumbugGLSerialization_headers 
#	GB.h

#	Project/ProcessProjectPrivate.h
)

SET(HumbugGLSerialization_sources 
#	GB.cpp

#	Project/ProcessProjectPrivate.cpp
)

#SET(HumbugGLSerialization_INCLUDE_DIR ${HumbugGLSerialization_IncludePath} CACHE PATH "HumbugGLSerialization include directory." FORCE)


SET(HumbugGLSerialization_resfiles 
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
SOURCE_GROUP(Resources FILES ${HumbugGLSerialization_resfiles})
SOURCE_GROUP(GameObject FILES ${HumbugGLSerialization_GameObject_headers})
SOURCE_GROUP(GameObject FILES ${HumbugGLSerialization_GameObject_sources})
SOURCE_GROUP(SerializationHeader FILES ${HumbugGLSerialization_Serialization_headers})
SOURCE_GROUP(SerializationSources FILES ${HumbugGLSerialization_Serialization_sources})
SOURCE_GROUP(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
SOURCE_GROUP(THeaders FILES ${HumbugGLSerialization_headers})
SOURCE_GROUP(TSources FILES ${HumbugGLSerialization_sources})

SET(HumbugGLSerialization_pre_sources 
    ${HumbugGLSerialization_GameObject_sources}
    ${HumbugGLSerialization_Serialization_sources}
    ${HumbugGLSerialization_sources} 
)

ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" HumbugGLSerialization_pre_sources)
#ADD_DEFINITIONS("-DMYENGINE_EXPORTS")
ADD_LIBRARY_X(HumbugGLSerialization ${LIBRARY_TYPE}
        stdafx.h
        ${DEBUG_DEFINITION_INCLUDES}
        stddefs.h 
        global.h 

    	${HumbugGLSerialization_pre_sources}
    	${HumbugGLSerialization_Serialization_headers}
    	${HumbugGLSerialization_GameObject_headers}
        ${HumbugGLSerialization_headers}
        ${res_outfiles} 
        ${moc_outfiles} 
        ${ui_outfiles}
		${HumbugGLSerialization_documents}
)

TARGET_LINK_LIBRARIES(HumbugGLSerialization ${ZLIB_LIBRARY} )
TARGET_LINK_LIBRARIES(HumbugGLSerialization luabind)
ADD_DEPENDENCIES(HumbugGLSerialization luabind)
TargetLinkBoost(HumbugGLSerialization "filesystem;system;regex")
#ADD_DEPENDENCIES(HumbugGLSerialization CppStructz)
ADD_PRECOMPILED_HEADER(HumbugGLSerialization stdafx.h stdafx.h.gch)

ADD_SUBDIRECTORY( docs )
ADD_SUBDIRECTORY( UnitTests )
