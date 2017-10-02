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

project( HumbugCore )
#set(LIBRARY_TYPE SHARED)
set(LIBRARY_TYPE STATIC)

message(STATUS         "!!!!!!!!!!!!!!!! CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME} !!!!!!!!!!")
include (BoostExtensions)
include (PCHSupport)
include (library)
include (CopyResourcesToBuildTree)
include (helpers)

ENSURE_DOCS_ARE_PRESENT(HumbugCore_documents)

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

set(HumbugCore_GameObject_headers 
#	GameObjects/Template.h
#	GameObjects/GameObject.h
#	GameObjects/GVector2D.h
#	GameObjects/GPoint2D.h
#	GameObjects/Player.h
)

set(HumbugCore_GameObject_sources 
#	GameObjects/Template.cpp
#	GameObjects/GameObject.cpp
#	GameObjects/GVector2D.cpp
#	GameObjects/GPoint2D.cpp
#	GameObjects/Player.cpp
)

set(HumbugCore_Serialization_headers 
	Serialization/Test.h
	Serialization/LoadTest.h
)

set(HumbugCore_Serialization_sources 
	Serialization/Test.cpp
	Serialization/LoadTest.cpp
)


set(HumbugCore_headers 
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

set(HumbugCore_sources 
#	GB.cpp

#	VFS/zfsystem.cpp
#	VFS/ziphdr.cpp
#	VFS/zstream.cpp
)

#set(HumbugCore_INCLUDE_DIR ${HumbugCore_IncludePath} CACHE PATH "HumbugCore include directory." FORCE)


set(HumbugCore_resfiles 
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
source_group(Resources FILES ${HumbugCore_resfiles})
source_group(GameObject FILES ${HumbugCore_GameObject_headers})
source_group(GameObject FILES ${HumbugCore_GameObject_sources})
source_group(SerializationHeader FILES ${HumbugCore_Serialization_headers})
source_group(SerializationSources FILES ${HumbugCore_Serialization_sources})
source_group(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
source_group(THeaders FILES ${HumbugCore_headers})
source_group(TSources FILES ${HumbugCore_sources})

set(HumbugCore_pre_sources 
    ${HumbugCore_GameObject_sources}
    ${HumbugCore_Serialization_sources}
    ${HumbugCore_sources} 
)

ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" HumbugCore_pre_sources)
#add_definitions("-DMYENGINE_EXPORTS")
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
		${HumbugCore_documents}
)

target_link_libraries(HumbugCore ${ZLIB_LIBRARY} )
target_link_libraries(HumbugCore luabind)
add_dependencies(HumbugCore luabind)
TargetLinkBoost(HumbugCore "filesystem;system;regex")
#add_dependencies(HumbugCore CppStructz)
ADD_PRECOMPILED_HEADER(HumbugCore stdafx.h stdafx.h.gch)

add_subdirectory( docs )
add_subdirectory( UnitTests )
