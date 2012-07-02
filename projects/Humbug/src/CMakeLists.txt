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

PROJECT( Humbug )

MESSAGE(STATUS         "!!!!!!!!!!!!!!!! CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME} !!!!!!!!!!")
INCLUDE (BoostExtensions)
INCLUDE (PCHSupport_MSVC)
INCLUDE (CopyResourcesToBuildTree)
INCLUDE (helpers)

SET(USE_LIB_BOOST_COMPONENTS "system;filesystem;signals;program_options")
#SET(USE_LIB_BOOST TRUE CACHE BOOL "Use Boost libraries")
# Use Boost libraries for this project.
SET(USE_LIB_BOOST TRUE)

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



SET(Humbug_headers 
        SelectionMarker.h
        Selection.h
        Customlexer.h
        qpid/InlineAllocator.h
        qpid/InlineVector.h
        qpid/RangeSet.h
        Project/ProjectModel.h
)


SET(Humbug_sources 
        main.cpp 
        calculatorform.cpp
        mainwindow.cpp
        SelectionMarker.cpp
        Selection.cpp
        SelectionDialog.cpp
        Customlexer.cpp
        lexerdsl.cpp
        CodeEditor.cpp
        XCodeEditor.cpp
        Project/ProjectModel.cpp
)

#WRAP_XSD(Humbug_XSDS_sources Humbug_XSDS_INCLUDE
#   ${CMAKE_CURRENT_BINARY_DIR}/XsdOut 
#   ../XSD/project.xsd
#   OPTIONS cxx-tree --root-element project
#)
#INCLUDE_DIRECTORIES(${Humbug_XSDS_INCLUDE})
#MESSAGE(STATUS "Humbug_XSDS_sources: ${Humbug_XSDS_sources} ")
#MESSAGE(STATUS "Humbug_XSDS_INCLUDE: ${Humbug_XSDS_INCLUDE} ")

IF(WIN32)
SET(Humbug_XSD_sources 
#Todo: LINUX xsdcxx xerces build isn't working correct.        
        ${Humbug_XSDS_sources}
        AssetList.hxx
        AssetList.cxx
)
ENDIF(WIN32)

SET(Humbug_mocfiles 
        SelectionDialog.h
        calculatorform.h
        mainwindow.h
        lexerdsl.h
        CodeEditor.h
        XCodeEditor.h
)

SET(Humbug_uifiles 
  calculatorform.ui
  mainwindow.ui
  SelectionDialog.ui
)

SET(Humbug_resfiles 
  mainwindow.qrc
)

#SET(CMAKE_BUILD_TYPE DEBUG)

QT4_WRAP_CPP( moc_outfiles  ${Humbug_mocfiles} )
MESSAGE(STATUS "moc_outfiles: ${moc_outfiles} ")
QT4_WRAP_UI( ui_outfiles  ${Humbug_uifiles} )
MESSAGE(STATUS "ui_outfiles: ${ui_outfiles} ")

INCLUDE_DIRECTORIES( ${PROJECT_BINARY_DIR} )
INCLUDE_DIRECTORIES( ${XSD_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${CppStructz_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${HumbugShared_INCLUDE_DIR})

IF(LINUX)
  INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
ENDIF(LINUX)


ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS("-DQSCINTILLA_DLL")
ADD_DEFINITIONS(${CppStructz_DEFINITIONS})
IF(LINUX)
  ADD_DEFINITIONS("-DLINUX")
ENDIF(LINUX)

ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" Humbug_sources)
QT4_ADD_RESOURCES(res_outfiles ${Humbug_resfiles} )

SOURCE_GROUP(Generated FILES ${res_outfiles} ${moc_outfiles} ${ui_outfiles} )
SOURCE_GROUP(Xsd FILES ${Humbug_XSD_sources} )
SOURCE_GROUP(Resources FILES ${Humbug_resfiles})
SOURCE_GROUP(GUI FILES ${Humbug_uifiles})
SOURCE_GROUP(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
SOURCE_GROUP(THeaders FILES ${Humbug_headers})
SOURCE_GROUP(TSources FILES ${Humbug_sources})

#ADD_EXECUTABLE(Humbug #WIN32
#        stdafx.h
#        ${DEBUG_DEFINITION_INCLUDES}
#        defs.h 
#
#        ${Humbug_sources} 
#        ${Humbug_headers}
#        ${Humbug_XSD_sources}
#        ${Humbug_mocfiles} 
#        ${res_outfiles} 
#        ${moc_outfiles} 
#        ${ui_outfiles}
#)

#copy_resources_to_build_tree(Humbug)

# Copy linked dll to the executables bin dir
# We need to check if shared or static .... and put this into a macro.
#   ADD_CUSTOM_COMMAND(
#           TARGET Humbug 
#           POST_BUILD
#           COMMAND ${CMAKE_COMMAND}
#           ARGS -E copy_if_different "${PROJECT_SOURCE_DIR}/mainwindow.cpp" "${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}"
#           COMMENT "source copy dlls and essential files"
#   )

    # POST_BUILD TARGET Copy XSD DLL. 
#   ADD_CUSTOM_COMMAND(
    #OUTPUT ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${XSD_LIBRARY_DEBUG}
#   TARGET Humbug 
#   POST_BUILD
#   COMMAND ${CMAKE_COMMAND} --debug-output -Dconfig=${CMAKE_CFG_INTDIR} -Dtgt="${PROJECT_BINARY_DIR}/" -Dreleasesrc="${XSD_DLL_RELEASE}" -Ddebugsrc="${XSD_DLL_DEBUG}" -P "${P_MODULE_PATH}/copy.cmake"
#   DEPENDS Humbug
#   COMMENT "Copy XSD DLL." 
#   )
#ADD_CUSTOM_TARGET(generate_foo DEPENDS ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${XSD_LIBRARY_DEBUG})

#Copy_File_To_Target(Humbug "${PROJECT_SOURCE_DIR}/mainwindow.cpp")
#Copy_DLL_To_Target(Humbug CppStructz)
#Copy_DLL_To_Target(Humbug XSD)
#Copy_DLL_To_Target(Humbug QSCINTILLA)
##Copy_DLL_To_Target(Humbug HumbugShared)
#Copy_ReleaseDLL_To_Target(Humbug ICU)
##SET(XSDE_LIB "${XSDE_LIBRARY_DIR}/vc-8.0/xerces-c_3.lib")
##SET(QSCINTILLA2_LIB "optimized;${QT_LIBRARY_DIR}/qscintilla2.lib;debug;${QT_LIBRARY_DIR}/qscintilla2d.lib")
##optimized;D:/boost/Boost_1_45_0_beta1/stage/lib/boost_filesystem-vc80-mt-1_45.lib;debug;D:/boost/Boost_1_45_0_beta1/stage/lib/boost_filesystem-vc80-mt-gd-1_45.lib

#TARGET_LINK_LIBRARIES(Humbug ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY} ${XSD_LIBRARY} 
#                        ${QSCINTILLA2_LIB} CppStructz )
#TargetLinkBoost(Humbug "filesystem;system;regex")
#TARGET_LINK_LIBRARIES(Humbug HumbugShared)


#ADD_DEPENDENCIES(Humbug CppStructz)

#SET_SOURCE_FILES_PROPERTIES( main.cpp
#       PROPERTIES OBJECT_DEPENDS ${CppStructz_DLL_DEBUG}
#)

#SET_SOURCE_FILES_PROPERTIES( ${Humbug_sources} #main.cpp
#       PROPERTIES OBJECT_DEPENDS "d:/Eigene Dateien/Projects/C++/Humbug/src/CppStructz/TestClass.cpp"
#)

SET(HumbugConsole_headers 
#        HumbugConsole/GB.h
        HumbugConsole/ProgOptions.h 
#        HumbugConsole/ProcessProject.h 
)

SET(HumbugConsole_sources 
#        HumbugConsole/GB.cpp 
        HumbugConsole/ProgOptions.cpp 
#        HumbugConsole/ProcessProject.cpp 
        HumbugConsole/main.cpp 
)

# see http://www.mail-archive.com/cmake@cmake.org/msg17661.html
ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
ADD_MSVC_PRECOMPILED_HEADER("HumbugConsole/stdafx.h" "HumbugConsole/stdafx.cpp" HumbugConsole_sources)
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
INCLUDE_DIRECTORIES( ${HumbugShared_INCLUDE_DIR})
#INCLUDE_DIRECTORIES( ${Crunchy_INCLUDE_DIR})

ADD_EXECUTABLE(HumbugConsole #WIN32
        HumbugConsole/stdafx.h
        ${DEBUG_DEFINITION_INCLUDES}
        #defs.h 

        ${HumbugConsole_sources} 
        ${HumbugConsole_headers}
        ${HumbugConsole_XSD_sources}
        ${HumbugConsole_mocfiles} 
        ${HumbugConsole_res_outfiles} 
        ${HumbugConsole_moc_outfiles} 
        ${HumbugConsole_ui_outfiles}
)

TargetLinkBoost(HumbugConsole "program_options")
TargetLinkBoost(HumbugConsole "filesystem;system;regex")
#TARGET_LINK_LIBRARIES(HumbugConsole CppStructz)
#TARGET_LINK_LIBRARIES(HumbugConsole HumbugShared)
#TARGET_LINK_LIBRARIES(HumbugConsole ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY} ${XSD_LIBRARY} 
#                        ${QSCINTILLA2_LIB} CppStructz )
#Copy_DLL_To_Target(HumbugConsole CppStructz)
IF(USE_NLS)
  Copy_DLL_To_Target(HumbugConsole LIBINTL)
  Copy_DLL_To_Target(HumbugConsole ICONV)
ENDIF(USE_NLS)


