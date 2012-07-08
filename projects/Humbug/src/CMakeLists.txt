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
INCLUDE (ZipPackage)

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
SET(USE_SDL TRUE)
SET(USE_SDL_IMAGE TRUE)

# local project settings
INCLUDE (bindings)

# Link explicitely to Microsoft.VC90.CRT version=9.0.30729.1
#ADD_DEFINITIONS("-D_BIND_TO_CURRENT_VCLIBS_VERSION=1")
# this does the same as above
#ADD_DEFINITIONS("-D_BIND_TO_CURRENT_MFC_VERSION=2")
#ADD_DEFINITIONS("-D_BIND_TO_CURRENT_CRT_VERSION=2")


SET(Humbug_GUI_sources 
		GUI/Visual/Application.cpp
		GUI/Visual/EventHandler.cpp
		GUI/Visual/MessageHandler.cpp
		GUI/Visual/Thread.cpp
		GUI/Visual/Timer.cpp

		GUI/TestEventHandler.cpp
		GUI/TestThread.cpp
		GUI/TestTimer.cpp
)

SET(Humbug_GUI_headers 
		GUI/Visual/Application.h
		GUI/Visual/EventHandler.h
		GUI/Visual/MessageHandler.h
		GUI/Visual/Thread.h
		GUI/Visual/Timer.h

		GUI/TestEventHandler.h
		GUI/TestThread.h
		GUI/TestTimer.h
)

SET(Humbug_headers 
		${Humbug_GUI_headers}
		fs/FileLoader.h
#        qpid/InlineAllocator.h
#        qpid/InlineVector.h
#        qpid/RangeSet.h
        Project/ProjectModel.h
)


SET(Humbug_sources 
		${Humbug_GUI_sources}
		fs/FileLoader.cpp

        main.cpp 
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

SET(Humbug_mocfiles 
#        SelectionDialog.h
#        calculatorform.h
#        mainwindow.h
#        lexerdsl.h
#        CodeEditor.h
#        XCodeEditor.h
)

SET(Humbug_uifiles 
#  calculatorform.ui
#  mainwindow.ui
#  SelectionDialog.ui
)

SET(Humbug_resfiles 
#  mainwindow.qrc
)

#SET(CMAKE_BUILD_TYPE DEBUG)

#QT4_WRAP_CPP( moc_outfiles  ${Humbug_mocfiles} )
#MESSAGE(STATUS "moc_outfiles: ${moc_outfiles} ")
#QT4_WRAP_UI( ui_outfiles  ${Humbug_uifiles} )
#MESSAGE(STATUS "ui_outfiles: ${ui_outfiles} ")

#INCLUDE_DIRECTORIES( ${PROJECT_BINARY_DIR} )
#INCLUDE_DIRECTORIES( ${XSD_INCLUDE_DIR} )
#INCLUDE_DIRECTORIES( ${CppStructz_INCLUDE_DIR} )
#ADD_DEFINITIONS("-DHAVE_OPENGL")
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${SDLIMAGE_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${HumbugShared_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR})

IF(LINUX)
  INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
ENDIF(LINUX)


#ADD_DEFINITIONS(${QT_DEFINITIONS})
#ADD_DEFINITIONS("-DQSCINTILLA_DLL")
ADD_DEFINITIONS(${HumbugShared_DEFINITIONS})
IF(LINUX)
  ADD_DEFINITIONS("-DLINUX")
ENDIF(LINUX)

ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" Humbug_sources)
QT4_ADD_RESOURCES(res_outfiles ${Humbug_resfiles} )

SOURCE_GROUP(Generated FILES ${res_outfiles} ${moc_outfiles} ${ui_outfiles} )
#SOURCE_GROUP(Xsd FILES ${Humbug_XSD_sources} )
SOURCE_GROUP(Resources FILES ${Humbug_resfiles})
SOURCE_GROUP(GUI FILES ${Humbug_uifiles})
SOURCE_GROUP(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
SOURCE_GROUP(THeaders FILES ${Humbug_headers})
SOURCE_GROUP(TSources FILES ${Humbug_sources})


SET(_GUI_DEP )
IF(WIN32)
  SET(_GUI_DEP WIN32)
ENDIF(WIN32)
ADD_EXECUTABLE(Humbug ${_GUI_DEP}
        stdafx.h
        ${DEBUG_DEFINITION_INCLUDES}
        defs.h 

        ${Humbug_sources} 
        ${Humbug_headers}
#        ${Humbug_XSD_sources}
#        ${Humbug_mocfiles} 
        ${res_outfiles} 
        ${moc_outfiles} 
        ${ui_outfiles}
)


#set_target_properties(Humbug 
#                        PROPERTIES RESOURCE icons/blue.png
##                        prop2 value2 ...
#)
Copy_File_To_Target(Humbug ${PROJECT_SOURCE_DIR}/icons/blue.png)
Copy_File_To_Target(Humbug ${P_ROOT_PATH}/Artwork/footer.png)

# Copy linked dll to the executables bin dir
# We need to check if shared or static .... and put this into a macro.
#   ADD_CUSTOM_COMMAND(
#           TARGET Humbug 
#           POST_BUILD
#           COMMAND ${CMAKE_COMMAND}
#           ARGS -E copy_if_different "${PROJECT_SOURCE_DIR}/mainwindow.cpp" "${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}"
#           COMMENT "source copy dlls and essential files"
#   )

SET(Pak01_PACKAGE_SOURCE_FILES 
		${PROJECT_SOURCE_DIR}/icons/
		#${PROJECT_SOURCE_DIR}/icons/blue.png
	    ${P_ROOT_PATH}/Artwork/footer.png
)
CREATEPACKAGE(Humbug MakeVFS "${Pak01_PACKAGE_SOURCE_FILES}" base_data Pak01.zip)

SET(Pak02_PACKAGE_SOURCE_FILES 
	    ${P_ROOT_PATH}/Artwork/footer.psd
)
CREATEPACKAGE(MakeVFS MakeVFS01 "${Pak02_PACKAGE_SOURCE_FILES}" base_data Pak02.zip)

#ADD_CUSTOM_TARGET(generate_foo DEPENDS ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${XSD_LIBRARY_DEBUG})

#Copy_File_To_Target(Humbug "${PROJECT_SOURCE_DIR}/mainwindow.cpp")
#Copy_DLL_To_Target(Humbug CppStructz)
#Copy_DLL_To_Target(Humbug XSD)
#Copy_DLL_To_Target(Humbug QSCINTILLA)
##Copy_DLL_To_Target(Humbug HumbugShared)
Copy_DLL_To_Target(Humbug SDL_LIBRARY)
Copy_DLL_To_Target(Humbug SDLIMAGE_LIBRARY)
Copy_Files_To_Target(Humbug "${SDLIMAGE_LIBRARY_DLLS_EXT}")
#Copy_ReleaseDLL_To_Target(Humbug ICU)
##SET(XSDE_LIB "${XSDE_LIBRARY_DIR}/vc-8.0/xerces-c_3.lib")
##SET(QSCINTILLA2_LIB "optimized;${QT_LIBRARY_DIR}/qscintilla2.lib;debug;${QT_LIBRARY_DIR}/qscintilla2d.lib")
##optimized;D:/boost/Boost_1_45_0_beta1/stage/lib/boost_filesystem-vc80-mt-1_45.lib;debug;D:/boost/Boost_1_45_0_beta1/stage/lib/boost_filesystem-vc80-mt-gd-1_45.lib

#TARGET_LINK_LIBRARIES(Humbug ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY} ${XSD_LIBRARY} 
#                        ${QSCINTILLA2_LIB} CppStructz )
TargetLinkBoost(Humbug "filesystem;system;regex")
TARGET_LINK_LIBRARIES(Humbug HumbugShared)
TARGET_LINK_LIBRARIES(Humbug ${SDL_LIBRARY})
TARGET_LINK_LIBRARIES(Humbug ${SDLIMAGE_LIBRARY})



#SET_SOURCE_FILES_PROPERTIES( main.cpp
#       PROPERTIES OBJECT_DEPENDS ${CppStructz_DLL_DEBUG}
#)

#SET_SOURCE_FILES_PROPERTIES( ${Humbug_sources} #main.cpp
#       PROPERTIES OBJECT_DEPENDS "d:/Eigene Dateien/Projects/C++/Humbug/src/CppStructz/TestClass.cpp"
#)
#copy_resources_to_build_tree(Humbug)

INSTALL(TARGETS Humbug 
	COMPONENT Application
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib/static
)
INSTALL(FILES 
		${SDL_LIBRARY_DLL_RELEASE} 
		${SDLIMAGE_LIBRARY_DLL_RELEASE} 
		${SDLIMAGE_LIBRARY_DLLS_EXT} 
	DESTINATION bin
	COMPONENT Libraries
)

# ===========================  HumbugConsole Executable  ===========================

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
TARGET_LINK_LIBRARIES(HumbugConsole HumbugShared)
#TARGET_LINK_LIBRARIES(HumbugConsole ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY} ${XSD_LIBRARY} 
#                        ${QSCINTILLA2_LIB} CppStructz )
#Copy_DLL_To_Target(HumbugConsole CppStructz)
IF(USE_NLS)
  Copy_DLL_To_Target(HumbugConsole LIBINTL)
  Copy_DLL_To_Target(HumbugConsole ICONV)
ENDIF(USE_NLS)


