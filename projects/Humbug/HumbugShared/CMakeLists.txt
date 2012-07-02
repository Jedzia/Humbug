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

#SET(USE_LIB_QT4 TRUE CACHE BOOL "Use QT4 libraries")
# Use QT4 libraries for this project.
SET(USE_LIB_QT4 TRUE)

# Use QSCINTILLA libraries for this project.
SET(USE_LIB_QSCINTILLA TRUE)

#SET(USE_LIB_XSD TRUE CACHE BOOL "Use XSD xerces libraries")
# Use XSD xerces libraries for this project.
SET(USE_LIB_XSD TRUE)

# local project settings
INCLUDE (bindings)

# Link explicitely to Microsoft.VC90.CRT version=9.0.30729.1
#ADD_DEFINITIONS("-D_BIND_TO_CURRENT_VCLIBS_VERSION=1")
# this does the same as above
#ADD_DEFINITIONS("-D_BIND_TO_CURRENT_MFC_VERSION=2")
#ADD_DEFINITIONS("-D_BIND_TO_CURRENT_CRT_VERSION=2")



SET(HumbugShared_headers 
	GB.h
	Project/ProcessProject.h
	Project/ProcessProjectPrivate.h
)


SET(HumbugShared_sources 
	GB.cpp
	Project/ProcessProject.cpp
	Project/ProcessProjectPrivate.cpp
)

WRAP_XSD(HumbugShared_XSDS_sources HumbugShared_XSDS_INCLUDE
	${CMAKE_CURRENT_BINARY_DIR}/XsdOut 
#	${CMAKE_CURRENT_SOURCE_DIR}/XSD/project.xsd
	../XSD/project.xsd
	OPTIONS cxx-tree --generate-serialization --root-element Project
)
INCLUDE_DIRECTORIES(${HumbugShared_XSDS_INCLUDE})
SET(HumbugShared_IncludePath ${PROJECT_SOURCE_DIR}/.. ${HumbugShared_XSDS_INCLUDE})
SET(HumbugShared_INCLUDE_DIR ${HumbugShared_IncludePath} CACHE PATH "HumbugShared include directory." FORCE)
#MARK_AS_ADVANCED(HumbugShared_XSDS_INCLUDE)
#MESSAGE(STATUS "HumbugShared_XSDS_sources: ${HumbugShared_XSDS_sources} ")
#MESSAGE(STATUS "HumbugShared_XSDS_INCLUDE: ${HumbugShared_XSDS_INCLUDE} ")

#IF(WIN32)
SET(HumbugShared_XSD_sources 
#Todo: LINUX xsdcxx xerces build isn't working correct.        
		${HumbugShared_XSDS_sources}
#        AssetList.hxx
#        AssetList.cxx
)
#ENDIF(WIN32)

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

QT4_WRAP_CPP( moc_outfiles  ${HumbugShared_mocfiles} )
MESSAGE(STATUS "moc_outfiles: ${moc_outfiles} ")
QT4_WRAP_UI( ui_outfiles  ${HumbugShared_uifiles} )
MESSAGE(STATUS "ui_outfiles: ${ui_outfiles} ")

INCLUDE_DIRECTORIES( ${PROJECT_BINARY_DIR} )
INCLUDE_DIRECTORIES( ${XSD_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${CppStructz_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${Crunchy_INCLUDE_DIR})

IF(LINUX)
  INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
ENDIF(LINUX)


ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS("-DQSCINTILLA_DLL")
ADD_DEFINITIONS(${CppStructz_DEFINITIONS})
IF(LINUX)
  ADD_DEFINITIONS("-DLINUX")
ENDIF(LINUX)

QT4_ADD_RESOURCES(res_outfiles ${HumbugShared_resfiles} )

SOURCE_GROUP(Generated FILES ${res_outfiles} ${moc_outfiles} ${ui_outfiles} )
SOURCE_GROUP(Xsd FILES ${HumbugShared_XSD_sources} )
SOURCE_GROUP(Resources FILES ${HumbugShared_resfiles})
SOURCE_GROUP(GUI FILES ${HumbugShared_uifiles})
SOURCE_GROUP(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
SOURCE_GROUP(THeaders FILES ${HumbugShared_headers})
SOURCE_GROUP(TSources FILES ${HumbugShared_sources})

#SET(LIBRARY_TYPE SHARED)
SET(LIBRARY_TYPE STATIC)

ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" HumbugShared_sources)
#ADD_DEFINITIONS("-DMYENGINE_EXPORTS")
ADD_LIBRARY_X(HumbugShared ${LIBRARY_TYPE}
        stdafx.h
        ${DEBUG_DEFINITION_INCLUDES}
        defs.h 

        ${HumbugShared_sources} 
        ${HumbugShared_headers}
		${HumbugShared_XSD_sources}
        ${HumbugShared_mocfiles} 
        ${res_outfiles} 
        ${moc_outfiles} 
        ${ui_outfiles}
)

#copy_resources_to_build_tree(HumbugShared)

# Copy linked dll to the executables bin dir
# We need to check if shared or static .... and put this into a macro.
#	ADD_CUSTOM_COMMAND(
#			TARGET HumbugShared 
#			POST_BUILD
#			COMMAND ${CMAKE_COMMAND}
#			ARGS -E copy_if_different "${PROJECT_SOURCE_DIR}/mainwindow.cpp" "${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}"
#			COMMENT "source copy dlls and essential files"
#	)

	# POST_BUILD TARGET Copy XSD DLL. 
#	ADD_CUSTOM_COMMAND(
	#OUTPUT ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${XSD_LIBRARY_DEBUG}
#	TARGET HumbugShared 
#	POST_BUILD
#	COMMAND ${CMAKE_COMMAND} --debug-output -Dconfig=${CMAKE_CFG_INTDIR} -Dtgt="${PROJECT_BINARY_DIR}/" -Dreleasesrc="${XSD_DLL_RELEASE}" -Ddebugsrc="${XSD_DLL_DEBUG}" -P "${P_MODULE_PATH}/copy.cmake"
#	DEPENDS HumbugShared
#	COMMENT "Copy XSD DLL." 
#	)
#ADD_CUSTOM_TARGET(generate_foo DEPENDS ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${XSD_LIBRARY_DEBUG})

#Copy_File_To_Target(HumbugShared "${PROJECT_SOURCE_DIR}/mainwindow.cpp")
#Copy_DLL_To_Target(HumbugShared CppStructz)
#Copy_DLL_To_Target(HumbugShared XSD)
#Copy_DLL_To_Target(HumbugShared QSCINTILLA)
#Copy_ReleaseDLL_To_Target(HumbugShared ICU)
#SET(XSDE_LIB "${XSDE_LIBRARY_DIR}/vc-8.0/xerces-c_3.lib")
#SET(QSCINTILLA2_LIB "optimized;${QT_LIBRARY_DIR}/qscintilla2.lib;debug;${QT_LIBRARY_DIR}/qscintilla2d.lib")
#optimized;D:/boost/Boost_1_45_0_beta1/stage/lib/boost_filesystem-vc80-mt-1_45.lib;debug;D:/boost/Boost_1_45_0_beta1/stage/lib/boost_filesystem-vc80-mt-gd-1_45.lib

TARGET_LINK_LIBRARIES(HumbugShared ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY} ${XSD_LIBRARY} 
						${QSCINTILLA2_LIB} CppStructz )
TargetLinkBoost(HumbugShared "filesystem;system;regex")

ADD_DEPENDENCIES(HumbugShared CppStructz)
IF(CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE STREQUAL DEBUG AND PCH_HumbugShared_ENABLED)
# \FIXME: Huh ... whats going on ? -DQT_DEBUG is missing on gcc pch generation.
# The xerces parser does not run when the pch is on.
  ADD_DEFINITIONS("-DQT_DEBUG")
ENDIF()
ADD_PRECOMPILED_HEADER(HumbugShared stdafx.h stdafx.h.gch)

