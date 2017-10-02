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

project( HumbugSerialization )
#set(LIBRARY_TYPE SHARED)
set(LIBRARY_TYPE STATIC)

message(STATUS         "!!!!!!!!!!!!!!!! CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME} !!!!!!!!!!")
include (BoostExtensions)
include (PCHSupport)
include (library)
include (CopyResourcesToBuildTree)
include (helpers)

ENSURE_DOCS_ARE_PRESENT(HumbugSerialization_documents)

set(USE_LIB_BOOST_COMPONENTS "system;filesystem;signals;program_options")
#set(USE_LIB_BOOST TRUE CACHE BOOL "Use Boost libraries")
# Use Boost libraries for this project.
set(USE_LIB_BOOST TRUE)
set(USE_LIB_ZLIB TRUE)
set(USE_LUA TRUE)

#set(USE_LIB_QT4 TRUE CACHE BOOL "Use QT4 libraries")
# Use QT4 libraries for this project.
#set(USE_LIB_QT4 TRUE)

# Use QSCINTILLA libraries for this project.
#set(USE_LIB_QSCINTILLA TRUE)

#set(USE_LIB_XSD TRUE CACHE BOOL "Use XSD xerces libraries")
# Use XSD xerces libraries for this project.
#set(USE_LIB_XSD TRUE)

# local project settings
include (bindings)

# Link explicitely to Microsoft.VC90.CRT version=9.0.30729.1
#add_definitions("-D_BIND_TO_CURRENT_VCLIBS_VERSION=1")
# this does the same as above
#add_definitions("-D_BIND_TO_CURRENT_MFC_VERSION=2")
#add_definitions("-D_BIND_TO_CURRENT_CRT_VERSION=2")

set(HumbugSerialization_GameObject_headers 
#	GameObjects/Template.h
#	GameObjects/GameObject.h
#	GameObjects/GVector2D.h
#	GameObjects/GPoint2D.h
#	GameObjects/Player.h
)

set(HumbugSerialization_GameObject_sources 
#	GameObjects/Template.cpp
#	GameObjects/GameObject.cpp
#	GameObjects/GVector2D.cpp
#	GameObjects/GPoint2D.cpp
#	GameObjects/Player.cpp
)

set(HumbugSerialization_Serialization_headers 
	Serialization/Test.h
	Serialization/LoadTest.h
	Serialization/SerializationHelpers.h
	Serialization/Token.h
	Serialization/VersionToken.h

	Serialization/InfoTextLoader.h
)

set(HumbugSerialization_Serialization_sources 
	Serialization/Test.cpp
	Serialization/LoadTest.cpp
	Serialization/SerializationHelpers.cpp
	Serialization/Token.cpp
	Serialization/VersionToken.cpp

	Serialization/InfoTextLoader.cpp
)


set(HumbugSerialization_headers 
#	GB.h

#	Project/ProcessProjectPrivate.h
)

set(HumbugSerialization_sources 
#	GB.cpp

#	Project/ProcessProjectPrivate.cpp
)

#set(HumbugSerialization_INCLUDE_DIR ${HumbugSerialization_IncludePath} CACHE PATH "HumbugSerialization include directory." FORCE)


set(HumbugSerialization_resfiles 
#  mainwindow.qrc
)

#set(CMAKE_BUILD_TYPE DEBUG)


include_directories(${PROJECT_BINARY_DIR})
include_directories(${ZLIB_INCLUDE_DIR})
include_directories(${HumbugLib_INCLUDE_DIR})
include_directories(${LUA_INCLUDE_DIR})
include_directories(${LUABIND_INCLUDE_DIR})
#include_directories( ${CppStructz_INCLUDE_DIR} )

if(LINUX)
  include_directories( ${PROJECT_SOURCE_DIR} )
endif(LINUX)


#add_definitions(${CppStructz_DEFINITIONS})
if(LINUX)
  add_definitions("-DLINUX")
  add_definitions("-DUNIX")
endif(LINUX)
if(MSYS)
  add_definitions("-DUNIX")
endif(MSYS)


source_group(Generated FILES ${res_outfiles} ${moc_outfiles} ${ui_outfiles} )
source_group(Resources FILES ${HumbugSerialization_resfiles})
source_group(GameObject FILES ${HumbugSerialization_GameObject_headers})
source_group(GameObject FILES ${HumbugSerialization_GameObject_sources})
source_group(SerializationHeader FILES ${HumbugSerialization_Serialization_headers})
source_group(SerializationSources FILES ${HumbugSerialization_Serialization_sources})
source_group(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
source_group(THeaders FILES ${HumbugSerialization_headers})
source_group(TSources FILES ${HumbugSerialization_sources})

set(HumbugSerialization_pre_sources 
    ${HumbugSerialization_GameObject_sources}
    ${HumbugSerialization_Serialization_sources}
    ${HumbugSerialization_sources} 
)

ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" HumbugSerialization_pre_sources)
#add_definitions("-DMYENGINE_EXPORTS")
ADD_LIBRARY_X(HumbugSerialization ${LIBRARY_TYPE}
        stdafx.h
        ${DEBUG_DEFINITION_INCLUDES}
        stddefs.h 
        global.h 

    	${HumbugSerialization_pre_sources}
    	${HumbugSerialization_Serialization_headers}
    	${HumbugSerialization_GameObject_headers}
        ${HumbugSerialization_headers}
        ${res_outfiles} 
        ${moc_outfiles} 
        ${ui_outfiles}
		${HumbugSerialization_documents}
)

target_link_libraries(HumbugSerialization ${ZLIB_LIBRARY} )
target_link_libraries(HumbugSerialization luabind)
add_dependencies(HumbugSerialization luabind)
TargetLinkBoost(HumbugSerialization "filesystem;system;regex")
#add_dependencies(HumbugSerialization CppStructz)
ADD_PRECOMPILED_HEADER(HumbugSerialization stdafx.h stdafx.h.gch)

add_subdirectory( docs )
add_subdirectory( UnitTests )
