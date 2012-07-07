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

PROJECT( HumbugShared )
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



SET(HumbugShared_headers 
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


SET(HumbugShared_sources 
	GB.cpp

	VFS/zfsystem.cpp
	VFS/ziphdr.cpp
	VFS/zstream.cpp
#	Project/ProcessProject.cpp
#	Project/ProcessProjectPrivate.cpp
)

#SET(HumbugShared_INCLUDE_DIR ${HumbugShared_IncludePath} CACHE PATH "HumbugShared include directory." FORCE)


SET(HumbugShared_mocfiles 
#        SelectionDialog.h
#        calculatorform.h
#        mainwindow.h
#        lexerdsl.h
#        CodeEditor.h
#        XCodeEditor.h
)

SET(HumbugShared_uifiles 
#  calculatorform.ui
#  mainwindow.ui
#  SelectionDialog.ui
)

SET(HumbugShared_resfiles 
#  mainwindow.qrc
)

#SET(CMAKE_BUILD_TYPE DEBUG)


INCLUDE_DIRECTORIES( ${PROJECT_BINARY_DIR} )
INCLUDE_DIRECTORIES( ${ZLIB_INCLUDE_DIR} )
#INCLUDE_DIRECTORIES( ${CppStructz_INCLUDE_DIR} )

IF(LINUX)
  INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
ENDIF(LINUX)


#ADD_DEFINITIONS(${CppStructz_DEFINITIONS})
IF(LINUX)
  ADD_DEFINITIONS("-DLINUX")
ENDIF(LINUX)


SOURCE_GROUP(Generated FILES ${res_outfiles} ${moc_outfiles} ${ui_outfiles} )
SOURCE_GROUP(Resources FILES ${HumbugShared_resfiles})
SOURCE_GROUP(GUI FILES ${HumbugShared_uifiles})
SOURCE_GROUP(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
SOURCE_GROUP(THeaders FILES ${HumbugShared_headers})
SOURCE_GROUP(TSources FILES ${HumbugShared_sources})

ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" HumbugShared_sources)
#ADD_DEFINITIONS("-DMYENGINE_EXPORTS")
ADD_LIBRARY_X(HumbugShared ${LIBRARY_TYPE}
        stdafx.h
        ${DEBUG_DEFINITION_INCLUDES}
        defs.h 

        ${HumbugShared_sources} 
        ${HumbugShared_headers}
        ${res_outfiles} 
        ${moc_outfiles} 
        ${ui_outfiles}
)

TARGET_LINK_LIBRARIES(HumbugShared ${ZLIB_LIBRARY} )
TargetLinkBoost(HumbugShared "filesystem;system;regex")
#ADD_DEPENDENCIES(HumbugShared CppStructz)
ADD_PRECOMPILED_HEADER(HumbugShared stdafx.h stdafx.h.gch)

