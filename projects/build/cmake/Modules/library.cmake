# library.cmake 													   01:37 23.11.2010
# library setup
# by Jedzia (c) 2010
#
# MACRO ADD_LIBRARY_X
# Vars: TODO
# ---------------------------------------------------------------------------------
# * DEBUG_MEMORY			Use CRT Memory Debugging. Defines -DDEBUG_MEMORY
# * DEBUG_MEMORY_STDOUT		Use console stdout for memory debugging output.
#
# Description:
# ---------------------------------------------------------------------------------
# Use these settings and defines in conjunction with debug.h and the macro
#
# Function export visibility -DPLATFORM_ALL_DYN_LINK or -D${PROJECT_NAME}_ALL_DYN_LINK
# describe that shared DLL-Linkage is used.
# -DPLATFORM_SOURCE or -D${PROJECT_NAME}_SOURCE or -D${PROJECT_NAME}_Exports (set by CMake)
# switches the generation of a DLL on.
# -D${PROJECT_NAME}_ALL_STATIC_LINK enables static linking. TODO: Test it!
# ---------------------------------------------------------------------------------
message( STATUS "Setting Library Config for ${PROJECT_NAME}")
cmake_policy(SET  CMP0026  OLD)

#include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/build/cmake/include)
set( ${PROJECT_NAME}_MAIN_DIR ${PROJECT_SOURCE_DIR} CACHE PATH "$(PROJECT) project root directory." FORCE)
set( ${PROJECT_NAME}_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/.. CACHE PATH "$(PROJECT) project internal include directory." FORCE)
#set( ${PROJECT_NAME}_INTERFACE_DIR ${${PROJECT_NAME}_INCLUDE_DIR}/${PROJECT_NAME} CACHE PATH "$(PROJECT) project interface include directory." FORCE)
set( ${PROJECT_NAME}_INTERFACE_DIR ${${PROJECT_NAME}_INCLUDE_DIR}/${PROJECT_NAME} CACHE PATH "$(PROJECT) project interface include directory." FORCE)
#set( ${PROJECT_NAME}_LIBRARY_DIR ${PROJECT_BINARY_DIR} CACHE PATH "$(PROJECT) project library directory." FORCE)
#set( ${PROJECT_NAME}_LIBRARY_XXX ${PROJECT_BINARY_DIR} CACHE PATH "$(PROJECT) project library directory." FORCE)
mark_as_advanced(${PROJECT_NAME}_MAIN_DIR)
mark_as_advanced(${PROJECT_NAME}_INCLUDE_DIR)
mark_as_advanced(${PROJECT_NAME}_INTERFACE_DIR)

include_directories(${${PROJECT_NAME}_INCLUDE_DIR})
# stdafx.h, config, etc. location
#include_directories(${${PROJECT_NAME}_MAIN_DIR})

if(WIN32)
  set(LIBRARY_LOCAL_DEFINITION_INCLUDES ${CMAKE_SOURCE_DIR}/build/cmake/include/platform/win32.h)
else(WIN32)
  set(LIBRARY_LOCAL_DEFINITION_INCLUDES ${CMAKE_SOURCE_DIR}/build/cmake/include/platform/linux.hpp)
endif(WIN32)

set (LIBRARY_DEFINITION_INCLUDES
	${CMAKE_SOURCE_DIR}/build/cmake/include/platform.h
	${LIBRARY_LOCAL_DEFINITION_INCLUDES}
)
source_group(GlobalHeader FILES ${LIBRARY_DEFINITION_INCLUDES})

macro(ENSURE_DOCS_ARE_PRESENT)
set(${PROJECT_NAME}_documents
		Readme.md
		docs/!DevelNotes.txt
)
source_group(Docs FILES ${${PROJECT_NAME}_documents})
set(${${PROJECT_NAME}_documents} ${ARGV1})
endmacro(ENSURE_DOCS_ARE_PRESENT)

macro(ADD_LIBRARY_X)
	add_library(${ARGV})
	add_definitions("-DPLATFORM_SOURCE")
	add_definitions("-D${PROJECT_NAME}_SOURCE")

	string(TOUPPER ${ARGV1} ARGV1_UPPERCASE)
	if(${ARGV1_UPPERCASE} STREQUAL "SHARED")
		add_definitions("-DPLATFORM_ALL_DYN_LINK")
		add_definitions("-D${PROJECT_NAME}_ALL_DYN_LINK")
		#set( ${PROJECT_NAME}_DEFINITIONS "-DPLATFORM_ALL_DYN_LINK -D${PROJECT_NAME}_ALL_DYN_LINK" CACHE PATH "$(PROJECT) project include declarations." FORCE)
		set( ${PROJECT_NAME}_DEFINITIONS "-D${PROJECT_NAME}_ALL_DYN_LINK" CACHE PATH "$(PROJECT) project include declarations." FORCE)
		message( STATUS "ADD_LIBRARY_X: Building ${PROJECT_NAME} as shared library.")
	elseif(${ARGV1_UPPERCASE} STREQUAL "STATIC")
		#set( ${PROJECT_NAME}_DEFINITIONS "-DPLATFORM_ALL_STATIC_LINK -D${PROJECT_NAME}_ALL_STATIC_LINK" CACHE PATH "$(PROJECT) project include declarations." FORCE)
		add_definitions("-D${PROJECT_NAME}_ALL_STATIC_LINK")
		set( ${PROJECT_NAME}_DEFINITIONS "-D${PROJECT_NAME}_ALL_STATIC_LINK" CACHE PATH "$(PROJECT) project include declarations." FORCE)
		message( STATUS "ADD_LIBRARY_X: Building ${PROJECT_NAME} as static library.")
	endif()
	mark_as_advanced(${PROJECT_NAME}_DEFINITIONS)


	#message( WARNING "THE           - ${${PROJECT_NAME}_LIBRARY_DEBUG}")

	#get_target_property(TEMP_LIB_D ${ARGV0} LINK_FLAGS)
	get_target_property(TEMP_EXE_D ${ARGV0} LOCATION_DEBUG)
	
#	# policy CMP0026  Test stuff
#	message( WARNING "--------------------------------------------------")
#	message( WARNING "TEMP_EXE_D: '${TEMP_EXE_D}'")
#	set(BLAFASL $<TARGET_FILE:${ARGV0}>)
#	message( WARNING "BLAFASL: '${BLAFASL}'")
	
	get_target_property(TEMP_EXE ${ARGV0} LOCATION)
	get_target_property(TEMP_EXE_R ${ARGV0} LOCATION_RELEASE)
	get_filename_component(TEMP_LIB_D_PATH ${TEMP_EXE_D} PATH)
	get_filename_component(TEMP_LIB_D_NAMEW ${TEMP_EXE_D} NAME_WE)
	get_filename_component(TEMP_LIB_R_PATH ${TEMP_EXE_R} PATH)
	get_filename_component(TEMP_LIB_R_NAMEW ${TEMP_EXE_R} NAME_WE)
	set(TEMP_LIB_D ${TEMP_LIB_D_PATH}/${TEMP_LIB_D_NAMEW}.lib)
	set(TEMP_LIB_R ${TEMP_LIB_R_PATH}/${TEMP_LIB_R_NAMEW}.lib)
	#message( STATUS "ADD_LIBRARY_X:TEMP_LIB_D - ${TEMP_LIB_D}")
	#message( STATUS "ADD_LIBRARY_X:TEMP_LIB_R - ${TEMP_LIB_R}")
	#message( STATUS "ADD_LIBRARY_X:TEMP_EXE_D - ${TEMP_EXE_D}")
	#message( STATUS "ADD_LIBRARY_X:TEMP_EXE_R - ${TEMP_EXE_R}")

	set( ${PROJECT_NAME}_LIBRARY_DEBUG ${TEMP_LIB_D} CACHE PATH "$(PROJECT) project debug library." FORCE)
	set( ${PROJECT_NAME}_LIBRARY_RELEASE ${TEMP_LIB_R} CACHE PATH "$(PROJECT) project release library." FORCE)
	set( ${PROJECT_NAME}_LIBRARY optimized ${TEMP_LIB_R} debug ${TEMP_LIB_D} CACHE PATH "$(PROJECT) project link-library." FORCE)
	set( ${PROJECT_NAME}_DLL_DEBUG ${TEMP_EXE_D} CACHE PATH "$(PROJECT) project debug dll." FORCE)
	set( ${PROJECT_NAME}_DLL_RELEASE ${TEMP_EXE_R} CACHE PATH "$(PROJECT) project release dll." FORCE)
	set( ${PROJECT_NAME}_DLL ${TEMP_EXE} CACHE PATH "$(PROJECT) project temp exe." FORCE)
    mark_as_advanced(${PROJECT_NAME}_LIBRARY_DEBUG)
    mark_as_advanced(${PROJECT_NAME}_LIBRARY_RELEASE)
    mark_as_advanced(${PROJECT_NAME}_LIBRARY)
    mark_as_advanced(${PROJECT_NAME}_DLL_DEBUG)
    mark_as_advanced(${PROJECT_NAME}_DLL_RELEASE)
    mark_as_advanced(${PROJECT_NAME}_DLL)

    set_property(TARGET ${ARGV0} PROPERTY FOLDER "Library")

endmacro(ADD_LIBRARY_X)

