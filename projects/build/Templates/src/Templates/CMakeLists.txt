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

project( Templates )

message(STATUS         "!!!!!!!!!!!!!!!! CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME} !!!!!!!!!!")
include (BoostExtensions)
include (PCHSupport_MSVC)
include (library)
include (CopyResourcesToBuildTree)
include (helpers)

set(USE_LIB_BOOST_COMPONENTS "system;filesystem;signals;program_options")
#set(USE_LIB_BOOST TRUE CACHE BOOL "Use Boost libraries")
# Use Boost libraries for this project.
set(USE_LIB_BOOST TRUE)

#set(USE_LIB_QT4 TRUE CACHE BOOL "Use QT4 libraries")
# Use QT4 libraries for this project.
set(USE_LIB_QT4 TRUE)

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

# Headers of the public interface.
set(Templates_interface 
#  ${ZLIB_PUBLIC_HDRS}
#  ${unrar_public_headers}
  ${Templates_INTERFACE_DIR}/global.h
  ${Templates_INTERFACE_DIR}/Types/Host.h
  ${Templates_INTERFACE_DIR}/Types/Interface.h
  ${Templates_INTERFACE_DIR}/C++0x/Lambda.h
  ${Templates_INTERFACE_DIR}/C++0x/Constructors.h
  ${Templates_INTERFACE_DIR}/DesignPatterns/FactoryMethod.h
  ${Templates_INTERFACE_DIR}/DesignPatterns/Singleton.h
  ${Templates_INTERFACE_DIR}/DesignPatterns/Command.h
  ${Templates_INTERFACE_DIR}/DesignPatterns/Context.h
  ${Templates_INTERFACE_DIR}/DesignPatterns/Strategy.h
  ${Templates_INTERFACE_DIR}/DesignPatterns/ConcreteStrategy.h
  ${Templates_INTERFACE_DIR}/DesignPatterns/StrategyExample.h
  ${Templates_INTERFACE_DIR}/DesignPatterns/Visitor.h
  ${Templates_INTERFACE_DIR}/DesignPatterns/Color.h
  ${Templates_INTERFACE_DIR}/DesignPatterns/RedColor.h
  ${Templates_INTERFACE_DIR}/DesignPatterns/BlueColor.h
  ${Templates_INTERFACE_DIR}/DesignPatterns/CountVisitor.h
  ${Templates_INTERFACE_DIR}/DesignPatterns/CallVisitor.h
  ${Templates_INTERFACE_DIR}/DesignPatterns/VisitorClient.h
  ${Templates_INTERFACE_DIR}/Test/Document.h
  ${Templates_INTERFACE_DIR}/Test/Telephone.h
  ${Templates_INTERFACE_DIR}/Test/Setup.h
)

# private implementation headers.
set(Templates_headers 
#		GB.h
#		Types/Host.h
)

# Source files.
set(Templates_sources 
#		GB.cpp
		Types/Host.cpp
		Types/Interface.cpp
#		C++0x/Lambda.cpp
		C++0x/Constructors.cpp
		DesignPatterns/FactoryMethod.cpp
		DesignPatterns/Singleton.cpp
		DesignPatterns/Command.cpp
		DesignPatterns/Context.cpp
		DesignPatterns/Strategy.cpp
		DesignPatterns/ConcreteStrategy.cpp
		DesignPatterns/StrategyExample.cpp
		DesignPatterns/Visitor.cpp
		DesignPatterns/Color.cpp
		DesignPatterns/RedColor.cpp
		DesignPatterns/BlueColor.cpp
		DesignPatterns/CountVisitor.cpp
		DesignPatterns/CallVisitor.cpp
		DesignPatterns/VisitorClient.cpp
		Test/Document.cpp
		Test/Telephone.cpp
		Test/Setup.cpp
)

# Todo: make a WRAP macro with this below.
#WRAP_XSD(Templates_XSDS_sources Templates_XSDS_INCLUDE
#	${CMAKE_CURRENT_BINARY_DIR}/XsdOut 
##	${CMAKE_CURRENT_SOURCE_DIR}/XSD/project.xsd
#	../XSD/project.xsd
#	OPTIONS cxx-tree --root-element project
#)
#include_directories(${Templates_XSDS_INCLUDE})
#set(Templates_IncludePath ${PROJECT_SOURCE_DIR}/.. ${Templates_XSDS_INCLUDE})
#set(Templates_INCLUDE_DIR ${Templates_IncludePath} CACHE PATH "Templates include directory." FORCE)
#mark_as_advanced(Templates_XSDS_INCLUDE)

if(WIN32)
set(Templates_XSD_sources 
#Todo: LINUX xsdcxx xerces build isn't working correct.        
		${Templates_XSDS_sources}
#        AssetList.hxx
#        AssetList.cxx
)
endif(WIN32)

set(Templates_mocfiles 
#        SelectionDialog.h
#        calculatorform.h
#        mainwindow.h
#        lexerdsl.h
#        CodeEditor.h
#        XCodeEditor.h
)

set(Templates_uifiles 
#  calculatorform.ui
#  mainwindow.ui
#  SelectionDialog.ui
)

set(Templates_resfiles 
#  mainwindow.qrc
)

#set(CMAKE_BUILD_TYPE DEBUG)

QT4_WRAP_CPP( moc_outfiles  ${Templates_mocfiles} )
message(STATUS "moc_outfiles: ${moc_outfiles} ")
QT4_WRAP_UI( ui_outfiles  ${Templates_uifiles} )
message(STATUS "ui_outfiles: ${ui_outfiles} ")

include_directories( ${PROJECT_BINARY_DIR} )
#include_directories( ${XSD_INCLUDE_DIR} )
include_directories( ${CppStructz_INCLUDE_DIR} )
include_directories( ${Crunchy_INCLUDE_DIR})

if(LINUX)
  include_directories( ${PROJECT_SOURCE_DIR} )
endif(LINUX)


add_definitions(${QT_DEFINITIONS})
add_definitions("-DQSCINTILLA_DLL")
add_definitions(${CppStructz_DEFINITIONS})
add_definitions("-DVERBOSE_STATE_MACHINE")

if(LINUX)
  add_definitions("-DLINUX")
endif(LINUX)

ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" Templates_sources)
QT4_ADD_RESOURCES(res_outfiles ${Templates_resfiles} )

source_group(Generated FILES ${res_outfiles} ${moc_outfiles} ${ui_outfiles} )
source_group(Xsd FILES ${Templates_XSD_sources} )
source_group(Resources FILES ${Templates_resfiles})
source_group(GUI FILES ${Templates_uifiles})
source_group(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
source_group(GlobalHeader FILES ${LIBRARY_DEFINITION_INCLUDES})
source_group(Interface FILES ${Templates_interface})
source_group(THeaders FILES ${Templates_headers})
source_group(TSources FILES ${Templates_sources})

#set(LIBRARY_TYPE SHARED)
set(LIBRARY_TYPE STATIC)

#add_definitions("-DMYENGINE_EXPORTS")
ADD_LIBRARY_X(Templates ${LIBRARY_TYPE}
        stdafx.h
        defs.h 
        ${DEBUG_DEFINITION_INCLUDES}
    	${LIBRARY_DEFINITION_INCLUDES}
		${Templates_CONFIG_FILES}

		${Templates_interface}
        ${Templates_sources} 
        ${Templates_headers}
		${Templates_XSD_sources}
        ${Templates_mocfiles} 
        ${res_outfiles} 
        ${moc_outfiles} 
        ${ui_outfiles}
)

#copy_resources_to_build_tree(Templates)

# Copy linked dll to the executables bin dir
# We need to check if shared or static .... and put this into a macro.
#	add_custom_command(
#			TARGET Templates 
#			POST_BUILD
#			COMMAND ${CMAKE_COMMAND}
#			ARGS -E copy_if_different "${PROJECT_SOURCE_DIR}/mainwindow.cpp" "${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}"
#			COMMENT "source copy dlls and essential files"
#	)

	# POST_BUILD TARGET Copy XSD DLL. 
#	add_custom_command(
	#OUTPUT ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${XSD_LIBRARY_DEBUG}
#	TARGET Templates 
#	POST_BUILD
#	COMMAND ${CMAKE_COMMAND} --debug-output -Dconfig=${CMAKE_CFG_INTDIR} -Dtgt="${PROJECT_BINARY_DIR}/" -Dreleasesrc="${XSD_DLL_RELEASE}" -Ddebugsrc="${XSD_DLL_DEBUG}" -P "${P_MODULE_PATH}/copy.cmake"
#	DEPENDS Templates
#	COMMENT "Copy XSD DLL." 
#	)
#add_custom_target(generate_foo DEPENDS ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${XSD_LIBRARY_DEBUG})

#Copy_File_To_Target(Templates "${PROJECT_SOURCE_DIR}/mainwindow.cpp")
#Copy_DLL_To_Target(Templates CppStructz)
#Copy_DLL_To_Target(Templates QBounce)
#Copy_DLL_To_Target(Templates XSD)
#Copy_DLL_To_Target(Templates QSCINTILLA)
#Copy_ReleaseDLL_To_Target(Templates ICU)
#set(XSDE_LIB "${XSDE_LIBRARY_DIR}/vc-8.0/xerces-c_3.lib")
#set(QSCINTILLA2_LIB "optimized;${QT_LIBRARY_DIR}/qscintilla2.lib;debug;${QT_LIBRARY_DIR}/qscintilla2d.lib")
#optimized;D:/boost/Boost_1_45_0_beta1/stage/lib/boost_filesystem-vc80-mt-1_45.lib;debug;D:/boost/Boost_1_45_0_beta1/stage/lib/boost_filesystem-vc80-mt-gd-1_45.lib

target_link_libraries(Templates ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY}  #${XSD_LIBRARY} 
						${QSCINTILLA2_LIB} CppStructz CorePlug )
TargetLinkBoost(Templates "filesystem;system;regex;program_options")


add_dependencies(Templates CppStructz)

