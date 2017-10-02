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

project( Playground )
set(PACKAGE Playground)


message(STATUS         "!!!!!!!!!!!!!!!! CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME} !!!!!!!!!!")
include (BoostExtensions)
include (PCHSupport)
include (helpers)

set(USE_LIB_BOOST_COMPONENTS "system;filesystem;signals;serialization")
#set(USE_LIB_BOOST TRUE CACHE BOOL "Use Boost libraries")
# Use Boost libraries for this project.
set(USE_LIB_BOOST TRUE)

#set(USE_LIB_QT4 TRUE CACHE BOOL "Use QT4 libraries")
# Use QT4 libraries for this project.
#set(USE_LIB_QT4 TRUE)

# Use QSCINTILLA libraries for this project.
#set(USE_LIB_QSCINTILLA TRUE)

#set(USE_LIB_XSD TRUE CACHE BOOL "Use XSD xerces libraries")
# Use XSD xerces libraries for this project.
#set(USE_LIB_XSD TRUE)

set(USE_SDL TRUE)
set(USE_SDL_IMAGE TRUE)
#set(USE_LUA TRUE)

# local project settings
include (bindings)

# Link explicitely to Microsoft.VC90.CRT version=9.0.30729.1
#add_definitions("-D_BIND_TO_CURRENT_VCLIBS_VERSION=1")
# this does the same as above
#add_definitions("-D_BIND_TO_CURRENT_MFC_VERSION=2")
#add_definitions("-D_BIND_TO_CURRENT_CRT_VERSION=2")





set(Playground_sources 
        error/error.cpp 
)

if(WIN32 AND NOT CYGWIN)
set(Playground_XSD_sources 
#Todo: LINUX xsdcxx xerces build isn't working correct.        
)
endif()

set(Playground_mocfiles 
)

set(Playground_uifiles 
)

set(Playground_resfiles 
)

#set(CMAKE_BUILD_TYPE DEBUG)


QT4_WRAP_CPP( moc_outfiles  ${Playground_mocfiles} )
message(STATUS "moc_outfiles: ${moc_outfiles} ")
QT4_WRAP_UI( ui_outfiles  ${Playground_uifiles} )
message(STATUS "ui_outfiles: ${ui_outfiles} ")

include_directories( ${PROJECT_BINARY_DIR} )
#include_directories( ${XSD_INCLUDE_DIR} )
include_directories( ${CppStructz_INCLUDE_DIR} )

if(LINUX)
  include_directories( ${PROJECT_SOURCE_DIR} )
endif(LINUX)


add_definitions("-DUNICODE=1")
add_definitions(${QT_DEFINITIONS})
add_definitions("-DQSCINTILLA_DLL")
add_definitions(${CppStructz_DEFINITIONS})
if(LINUX)
  add_definitions("-DLINUX")
endif(LINUX)

#ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" Playground_sources)
QT4_ADD_RESOURCES(res_outfiles ${Playground_resfiles} )

source_group(Generated FILES ${res_outfiles} ${moc_outfiles} ${ui_outfiles} )
source_group(Xsd FILES ${Playground_XSD_sources} )
source_group(Resources FILES ${Playground_resfiles})
source_group(GUI FILES ${Playground_uifiles})
source_group(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})

if(FALSE)
add_executable(Playground #WIN32
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
        add_custom_command(
                #   TARGET CopyDllCfg POST_BUILD
                TARGET Playground 
                POST_BUILD
                COMMAND ${CMAKE_COMMAND}
                ARGS -E copy_if_different "${CppStructz_DLL}" "${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}"
                COMMENT "source copy dlls and essential files"
        )
        #  endforeach(file)

#set(XSDE_LIB "${XSDE_LIBRARY_DIR}/vc-8.0/xerces-c_3.lib")
#set(QSCINTILLA2_LIB "optimized;${QT_LIBRARY_DIR}/qscintilla2.lib;debug;${QT_LIBRARY_DIR}/qscintilla2d.lib")
#optimized;D:/boost/Boost_1_45_0_beta1/stage/lib/boost_filesystem-vc80-mt-1_45.lib;debug;D:/boost/Boost_1_45_0_beta1/stage/lib/boost_filesystem-vc80-mt-gd-1_45.lib

target_link_libraries(Playground ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY} ${XSD_LIBRARY} ${QSCINTILLA2_LIB} CppStructz)
TargetLinkBoost(Playground "filesystem;system")

endif(FALSE)


# example source files
set(PLAYGROUND_CPP_FILES *.cpp)
set(PLAYGROUND_HPP_FILES *.h)
set(PLAYGROUND_MOC_FILES moc_*.cpp)

#file(GLOB playground_sources ${TOP_SRC_DIR}/src/insets/${PLAYGROUND_CPP_FILES})
file(GLOB playground_sources ${PROJECT_SOURCE_DIR}/${PLAYGROUND_CPP_FILES})
file(GLOB playground_headers ${PROJECT_SOURCE_DIR}/${PLAYGROUND_HPP_FILES})

#list(REMOVE_ITEM playground_sources ${TOP_SRC_DIR}/src/insets/InsetTheorem.cpp)

foreach(f ${playground_sources})
	get_filename_component(_target_name  ${f} NAME_WE)
	if(${_target_name} STREQUAL "stdafx")
	else(${_target_name} STREQUAL "stdafx")
		add_executable(${_target_name} ${f})
		TargetLinkBoost(${_target_name} "filesystem;system;serialization")
		#set_property(TARGET throw_error PROPERTY FOLDER "Playground/3rdParty")
		set_property(TARGET ${_target_name} PROPERTY FOLDER "Playground")

		set_target_properties(${_target_name}
		PROPERTIES
#		EXCLUDE_FROM_DEFAULT_BUILD
		EXCLUDE_FROM_ALL_BUILD
		TRUE)
		message(STATUS "[GLOB EXAMPLE] Adding Example Project: ${_target_name}")
	endif(${_target_name} STREQUAL "stdafx")
endforeach()


#add an extra target.
add_executable(throw_error error/error.cpp)
TargetLinkBoost(throw_error "filesystem;system")
#set_property(TARGET throw_error PROPERTY FOLDER "Playground/3rdParty")
set_property(TARGET throw_error PROPERTY FOLDER "Playground")


# zfs example
include_directories( ${HumbugShared_INCLUDE_DIR} ${ZLIB_INCLUDE_DIR} )
target_link_libraries(zfs HumbugShared)

# csz_textdocument example
#target_link_libraries(Humbug ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY} ${XSD_LIBRARY} ${QSCINTILLA2_LIB} CppStructz)
#target_link_libraries(csz_textdocument CppStructz)
#TargetLinkBoost(csz_textdocument "filesystem;system;regex")
#Copy_DLL_To_Target(csz_textdocument CppStructz)
#Copy_ReleaseDLL_To_Target(csz_textdocument ICU)

# unicode/ICU example
#target_link_libraries(unicode ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY} ${XSD_LIBRARY} ${QSCINTILLA2_LIB} CppStructz)
#TargetLinkBoost(unicode "filesystem;system;regex")
#Copy_DLL_To_Target(unicode CppStructz)
#Copy_ReleaseDLL_To_Target(unicode ICU)

# intl example
if(USE_NLS)
  set(POTSRC ${CMAKE_CURRENT_SOURCE_DIR}/po-test)
  #include(po-test/buildpot.cmake)
  add_subdirectory( po-test )

  add_definitions("-DUSE_NLS")
  include_directories(${LIBINTL_INCLUDE_DIR})
  include_directories( ${ICONV_INCLUDE_DIR} )
  add_executable(intl po-test/intl.cpp)
  target_link_libraries(intl CppStructz)
  target_link_libraries(intl ${LIBINTL_LIBRARIES})
  target_link_libraries(intl ${ICONV_LIBRARY})
  Copy_DLL_To_Target(intl LIBINTL)
  Copy_DLL_To_Target(intl ICONV)
  Copy_DLL_To_Target(intl CppStructz)

  set_property(TARGET intl PROPERTY FOLDER "Playground")
  set_target_properties(intl
  PROPERTIES
  #EXCLUDE_FROM_DEFAULT_BUILD
  EXCLUDE_FROM_ALL_BUILD
  TRUE)
endif(USE_NLS)


# loki example
#target_link_libraries(loki1 CppStructz)

# Zlib test example
#set(USE_LIB_ZLIB TRUE)

#include_directories(${ZLIB_INCLUDE_DIR})
#target_link_libraries(zlibtest ${ZLIB_LIBRARY})
#if(WIN32)
#  target_link_libraries(zlibtest "C:/gnuwin32/lib/zdll.lib")
#else(WIN32)
#  target_link_libraries(zlibtest ${ZLIB_LIBRARY})
#endif(WIN32)

# doc_view_acm.cpp
TargetLinkBoost(doc_view_acm "signals")


# ----- SDL Part -----

include_directories(${SDL_INCLUDE_DIR})
include_directories(${SDLIMAGE_INCLUDE_DIR})
add_definitions("-DHAVE_OPENGL")

file(GLOB playground_SDL_sources ${PROJECT_SOURCE_DIR}/SDL/*.c;${PROJECT_SOURCE_DIR}/SDL/*.cpp)
file(GLOB playground_SDL_headers ${PROJECT_SOURCE_DIR}/SDL/${PLAYGROUND_HPP_FILES})

foreach(f ${playground_SDL_sources})
	get_filename_component(_target_name  ${f} NAME_WE)
	if(${_target_name} STREQUAL "stdafx")
	else(${_target_name} STREQUAL "stdafx")
		set(_target_name "SDL_${_target_name}")
		add_executable(${_target_name} ${f})
#		TargetLinkBoost(${_target_name} "filesystem;system")
if(LINUX)
		target_link_libraries(${_target_name} ${SDL_LIBRARY} m)
else()
		target_link_libraries(${_target_name} ${SDL_LIBRARY})
endif()
		set_property(TARGET ${_target_name} PROPERTY FOLDER "Playground/SDL")
		set_target_properties(${_target_name}
		PROPERTIES
		EXCLUDE_FROM_ALL_BUILD
		TRUE)
		message(STATUS "[GLOB EXAMPLE] Adding Example Project: ${_target_name}")
		Copy_DLL_To_Target(${_target_name} SDL_LIBRARY)
	endif(${_target_name} STREQUAL "stdafx")
endforeach()

#Copy_File_To_Target(SDL_testsprite "${PROJECT_SOURCE_DIR}/SDL/icon.bmp")
#Copy_File_To_Target(SDL_testblitspeed "${PROJECT_SOURCE_DIR}/SDL/sample.bmp")

target_link_libraries(SDL_lesson21 ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY})
Copy_File_To_Target(SDL_lesson21 "${PROJECT_SOURCE_DIR}/SDL/bg.png")
Copy_File_To_Target(SDL_lesson21 "${PROJECT_SOURCE_DIR}/SDL/dot.bmp")
Copy_DLL_To_Target(SDL_lesson21 SDLIMAGE_LIBRARY)
Copy_Files_To_Target(SDL_lesson21 "${SDLIMAGE_LIBRARY_DLLS_EXT}")


