##---------------------------------------------------------------------------
## $RCSfile$
## $Source$
## $Revision$
## $Date$
##---------------------------------------------------------------------------
## Author:      Jedzia
## Copyright:   (c) Jedzia, 2010
## License:     GPL License
##---------------------------------------------------------------------------
##---------------------------------------------------
## 
##--------------------------------------------------- 
## !!!!!! we should use the internal FindwxWidgets.cmake !!!!!

#cmake_policy(SET CMP0005 NEW) # 
cmake_minimum_required(VERSION 2.8)

PROJECT( Playground )
SET(PACKAGE Playground)


MESSAGE(STATUS         "!!!!!!!!!!!!!!!! CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME} !!!!!!!!!!")
INCLUDE (BoostExtensions)
INCLUDE (PCHSupport)
INCLUDE (helpers)

SET(USE_LIB_BOOST_COMPONENTS "system;filesystem;signals")
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
#SET(USE_LIB_XSD TRUE)

SET(USE_LIB_ZLIB TRUE)

# local project settings
INCLUDE (bindings)

# Link explicitely to Microsoft.VC90.CRT version=9.0.30729.1
#ADD_DEFINITIONS("-D_BIND_TO_CURRENT_VCLIBS_VERSION=1")
# this does the same as above
#ADD_DEFINITIONS("-D_BIND_TO_CURRENT_MFC_VERSION=2")
#ADD_DEFINITIONS("-D_BIND_TO_CURRENT_CRT_VERSION=2")





SET(Playground_sources 
        error/error.cpp 
)

IF(WIN32 and NOT CYGWIN)
SET(Playground_XSD_sources 
#Todo: LINUX xsdcxx xerces build isn't working correct.        
)
ENDIF()

SET(Playground_mocfiles 
)

SET(Playground_uifiles 
)

SET(Playground_resfiles 
)

#SET(CMAKE_BUILD_TYPE DEBUG)


QT4_WRAP_CPP( moc_outfiles  ${Playground_mocfiles} )
MESSAGE(STATUS "moc_outfiles: ${moc_outfiles} ")
QT4_WRAP_UI( ui_outfiles  ${Playground_uifiles} )
MESSAGE(STATUS "ui_outfiles: ${ui_outfiles} ")

INCLUDE_DIRECTORIES( ${PROJECT_BINARY_DIR} )
#INCLUDE_DIRECTORIES( ${XSD_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${CppStructz_INCLUDE_DIR} )

IF(LINUX)
  INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
ENDIF(LINUX)


ADD_DEFINITIONS("-DUNICODE=1")
ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS("-DQSCINTILLA_DLL")
ADD_DEFINITIONS(${CppStructz_DEFINITIONS})
IF(LINUX)
  ADD_DEFINITIONS("-DLINUX")
ENDIF(LINUX)

#ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" Playground_sources)
QT4_ADD_RESOURCES(res_outfiles ${Playground_resfiles} )

SOURCE_GROUP(Generated FILES ${res_outfiles} ${moc_outfiles} ${ui_outfiles} )
SOURCE_GROUP(Xsd FILES ${Playground_XSD_sources} )
SOURCE_GROUP(Resources FILES ${Playground_resfiles})
SOURCE_GROUP(GUI FILES ${Playground_uifiles})
SOURCE_GROUP(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})

IF(FALSE)
ADD_EXECUTABLE(Playground #WIN32
#        stdafx.h
        ${DEBUG_DEFINITION_INCLUDES}
#        defs.h 

        ${Playground_sources} 
        ${Playground_XSD_sources}
        ${Playground_mocfiles} 
        ${res_outfiles} 
        ${moc_outfiles} 
        ${ui_outfiles}
)

# Copy linked dll to the executables bin dir
# We need to check if shared or static .... and put this into a macro.
        ADD_CUSTOM_COMMAND(
                #   TARGET CopyDllCfg POST_BUILD
                TARGET Playground 
                POST_BUILD
                COMMAND ${CMAKE_COMMAND}
                ARGS -E copy_if_different "${CppStructz_DLL}" "${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}"
                COMMENT "source copy dlls and essential files"
        )
        #  ENDFOREACH(file)

#SET(XSDE_LIB "${XSDE_LIBRARY_DIR}/vc-8.0/xerces-c_3.lib")
#SET(QSCINTILLA2_LIB "optimized;${QT_LIBRARY_DIR}/qscintilla2.lib;debug;${QT_LIBRARY_DIR}/qscintilla2d.lib")
#optimized;D:/boost/Boost_1_45_0_beta1/stage/lib/boost_filesystem-vc80-mt-1_45.lib;debug;D:/boost/Boost_1_45_0_beta1/stage/lib/boost_filesystem-vc80-mt-gd-1_45.lib

TARGET_LINK_LIBRARIES(Playground ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY} ${XSD_LIBRARY} ${QSCINTILLA2_LIB} CppStructz)
TargetLinkBoost(Playground "filesystem;system")

ENDIF(FALSE)


# example source files
SET(PLAYGROUND_CPP_FILES *.cpp)
SET(PLAYGROUND_HPP_FILES *.h)
SET(PLAYGROUND_MOC_FILES moc_*.cpp)

#FILE(GLOB playground_sources ${TOP_SRC_DIR}/src/insets/${PLAYGROUND_CPP_FILES})
FILE(GLOB playground_sources ${PROJECT_SOURCE_DIR}/${PLAYGROUND_CPP_FILES})
FILE(GLOB playground_headers ${PROJECT_SOURCE_DIR}/${PLAYGROUND_HPP_FILES})

#LIST(REMOVE_ITEM playground_sources ${TOP_SRC_DIR}/src/insets/InsetTheorem.cpp)

FOREACH(f ${playground_sources})
	GET_FILENAME_COMPONENT(_target_name  ${f} NAME_WE)
	IF(${_target_name} STREQUAL "stdafx")
	ELSE(${_target_name} STREQUAL "stdafx")
		ADD_EXECUTABLE(${_target_name} ${f})
		TargetLinkBoost(${_target_name} "filesystem;system")
		#SET_PROPERTY(TARGET throw_error PROPERTY FOLDER "Playground/3rdParty")
		SET_PROPERTY(TARGET ${_target_name} PROPERTY FOLDER "Playground")

		SET_TARGET_PROPERTIES(${_target_name}
		PROPERTIES
#		EXCLUDE_FROM_DEFAULT_BUILD
		EXCLUDE_FROM_ALL_BUILD
		TRUE)
		MESSAGE(STATUS "[GLOB EXAMPLE] Adding Example Project: ${_target_name}")
	ENDIF(${_target_name} STREQUAL "stdafx")
ENDFOREACH()



#add an extra target.
ADD_EXECUTABLE(throw_error error/error.cpp)
TargetLinkBoost(throw_error "filesystem;system")
#SET_PROPERTY(TARGET throw_error PROPERTY FOLDER "Playground/3rdParty")
SET_PROPERTY(TARGET throw_error PROPERTY FOLDER "Playground")


# csz_textdocument example
#TARGET_LINK_LIBRARIES(Humbug ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY} ${XSD_LIBRARY} ${QSCINTILLA2_LIB} CppStructz)
#TARGET_LINK_LIBRARIES(csz_textdocument CppStructz)
#TargetLinkBoost(csz_textdocument "filesystem;system;regex")
#Copy_DLL_To_Target(csz_textdocument CppStructz)
#Copy_ReleaseDLL_To_Target(csz_textdocument ICU)

# unicode/ICU example
#TARGET_LINK_LIBRARIES(unicode ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY} ${XSD_LIBRARY} ${QSCINTILLA2_LIB} CppStructz)
#TargetLinkBoost(unicode "filesystem;system;regex")
#Copy_DLL_To_Target(unicode CppStructz)
#Copy_ReleaseDLL_To_Target(unicode ICU)

# intl example
IF(USE_NLS)
  SET(POTSRC ${CMAKE_CURRENT_SOURCE_DIR}/po-test)
  #INCLUDE(po-test/buildpot.cmake)
  ADD_SUBDIRECTORY( po-test )

  ADD_DEFINITIONS("-DUSE_NLS")
  INCLUDE_DIRECTORIES(${LIBINTL_INCLUDE_DIR})
  INCLUDE_DIRECTORIES( ${ICONV_INCLUDE_DIR} )
  ADD_EXECUTABLE(intl po-test/intl.cpp)
  TARGET_LINK_LIBRARIES(intl CppStructz)
  TARGET_LINK_LIBRARIES(intl ${LIBINTL_LIBRARIES})
  TARGET_LINK_LIBRARIES(intl ${ICONV_LIBRARY})
  Copy_DLL_To_Target(intl LIBINTL)
  Copy_DLL_To_Target(intl ICONV)
  Copy_DLL_To_Target(intl CppStructz)

  SET_PROPERTY(TARGET intl PROPERTY FOLDER "Playground")
  SET_TARGET_PROPERTIES(intl
  PROPERTIES
  #EXCLUDE_FROM_DEFAULT_BUILD
  EXCLUDE_FROM_ALL_BUILD
  TRUE)
ENDIF(USE_NLS)


# loki example
#TARGET_LINK_LIBRARIES(loki1 CppStructz)

# Zlib test example
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR})
#TARGET_LINK_LIBRARIES(zlibtest ${ZLIB_LIBRARY})
IF(WIN32)
  TARGET_LINK_LIBRARIES(zlibtest "C:/gnuwin32/lib/zdll.lib")
ELSE(WIN32)
  TARGET_LINK_LIBRARIES(zlibtest ${ZLIB_LIBRARY})
ENDIF(WIN32)
