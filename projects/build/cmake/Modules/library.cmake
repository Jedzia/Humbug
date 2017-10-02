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
MESSAGE( STATUS "Setting Library Config for ${PROJECT_NAME}")
cmake_policy(SET  CMP0026  OLD)

#INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/build/cmake/include)
SET( ${PROJECT_NAME}_MAIN_DIR ${PROJECT_SOURCE_DIR} CACHE PATH "$(PROJECT) project root directory." FORCE)
SET( ${PROJECT_NAME}_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/.. CACHE PATH "$(PROJECT) project internal include directory." FORCE)
#SET( ${PROJECT_NAME}_INTERFACE_DIR ${${PROJECT_NAME}_INCLUDE_DIR}/${PROJECT_NAME} CACHE PATH "$(PROJECT) project interface include directory." FORCE)
SET( ${PROJECT_NAME}_INTERFACE_DIR ${${PROJECT_NAME}_INCLUDE_DIR}/${PROJECT_NAME} CACHE PATH "$(PROJECT) project interface include directory." FORCE)
#SET( ${PROJECT_NAME}_LIBRARY_DIR ${PROJECT_BINARY_DIR} CACHE PATH "$(PROJECT) project library directory." FORCE)
#SET( ${PROJECT_NAME}_LIBRARY_XXX ${PROJECT_BINARY_DIR} CACHE PATH "$(PROJECT) project library directory." FORCE)
MARK_AS_ADVANCED(${PROJECT_NAME}_MAIN_DIR)
MARK_AS_ADVANCED(${PROJECT_NAME}_INCLUDE_DIR)
MARK_AS_ADVANCED(${PROJECT_NAME}_INTERFACE_DIR)

INCLUDE_DIRECTORIES(${${PROJECT_NAME}_INCLUDE_DIR})
# stdafx.h, config, etc. location
#INCLUDE_DIRECTORIES(${${PROJECT_NAME}_MAIN_DIR})

IF(WIN32)
  SET(LIBRARY_LOCAL_DEFINITION_INCLUDES ${CMAKE_SOURCE_DIR}/build/cmake/include/platform/win32.hpp)
ELSE(WIN32)
  SET(LIBRARY_LOCAL_DEFINITION_INCLUDES ${CMAKE_SOURCE_DIR}/build/cmake/include/platform/linux.hpp)
ENDIF(WIN32)

SET (LIBRARY_DEFINITION_INCLUDES
	${CMAKE_SOURCE_DIR}/build/cmake/include/platform.h
	${LIBRARY_LOCAL_DEFINITION_INCLUDES}
)
SOURCE_GROUP(GlobalHeader FILES ${LIBRARY_DEFINITION_INCLUDES})

MACRO(ENSURE_DOCS_ARE_PRESENT)
SET(${PROJECT_NAME}_documents
		Readme.md
		docs/!DevelNotes.txt
)
SOURCE_GROUP(Docs FILES ${${PROJECT_NAME}_documents})
SET(${${PROJECT_NAME}_documents} ${ARGV1})
ENDMACRO(ENSURE_DOCS_ARE_PRESENT)

MACRO(ADD_LIBRARY_X)
	ADD_LIBRARY(${ARGV})
	ADD_DEFINITIONS("-DPLATFORM_SOURCE")
	ADD_DEFINITIONS("-D${PROJECT_NAME}_SOURCE")

	STRING(TOUPPER ${ARGV1} ARGV1_UPPERCASE)
	IF(${ARGV1_UPPERCASE} STREQUAL "SHARED")
		ADD_DEFINITIONS("-DPLATFORM_ALL_DYN_LINK")
		ADD_DEFINITIONS("-D${PROJECT_NAME}_ALL_DYN_LINK")
		#SET( ${PROJECT_NAME}_DEFINITIONS "-DPLATFORM_ALL_DYN_LINK -D${PROJECT_NAME}_ALL_DYN_LINK" CACHE PATH "$(PROJECT) project include declarations." FORCE)
		SET( ${PROJECT_NAME}_DEFINITIONS "-D${PROJECT_NAME}_ALL_DYN_LINK" CACHE PATH "$(PROJECT) project include declarations." FORCE)
		MESSAGE( STATUS "ADD_LIBRARY_X: Building ${PROJECT_NAME} as shared library.")
	ELSEIF(${ARGV1_UPPERCASE} STREQUAL "STATIC")
		#SET( ${PROJECT_NAME}_DEFINITIONS "-DPLATFORM_ALL_STATIC_LINK -D${PROJECT_NAME}_ALL_STATIC_LINK" CACHE PATH "$(PROJECT) project include declarations." FORCE)
		ADD_DEFINITIONS("-D${PROJECT_NAME}_ALL_STATIC_LINK")
		SET( ${PROJECT_NAME}_DEFINITIONS "-D${PROJECT_NAME}_ALL_STATIC_LINK" CACHE PATH "$(PROJECT) project include declarations." FORCE)
		MESSAGE( STATUS "ADD_LIBRARY_X: Building ${PROJECT_NAME} as static library.")
	ENDIF()
	MARK_AS_ADVANCED(${PROJECT_NAME}_DEFINITIONS)


	#MESSAGE( WARNING "THE           - ${${PROJECT_NAME}_LIBRARY_DEBUG}")

	#GET_TARGET_PROPERTY(TEMP_LIB_D ${ARGV0} LINK_FLAGS)
	GET_TARGET_PROPERTY(TEMP_EXE_D ${ARGV0} LOCATION_DEBUG)
	
#	# policy CMP0026  Test stuff
#	MESSAGE( WARNING "--------------------------------------------------")
#	MESSAGE( WARNING "TEMP_EXE_D: '${TEMP_EXE_D}'")
#	SET(BLAFASL $<TARGET_FILE:${ARGV0}>)
#	MESSAGE( WARNING "BLAFASL: '${BLAFASL}'")
	
	GET_TARGET_PROPERTY(TEMP_EXE ${ARGV0} LOCATION)
	GET_TARGET_PROPERTY(TEMP_EXE_R ${ARGV0} LOCATION_RELEASE)
	GET_FILENAME_COMPONENT(TEMP_LIB_D_PATH ${TEMP_EXE_D} PATH)
	GET_FILENAME_COMPONENT(TEMP_LIB_D_NAMEW ${TEMP_EXE_D} NAME_WE)
	GET_FILENAME_COMPONENT(TEMP_LIB_R_PATH ${TEMP_EXE_R} PATH)
	GET_FILENAME_COMPONENT(TEMP_LIB_R_NAMEW ${TEMP_EXE_R} NAME_WE)
	SET(TEMP_LIB_D ${TEMP_LIB_D_PATH}/${TEMP_LIB_D_NAMEW}.lib)
	SET(TEMP_LIB_R ${TEMP_LIB_R_PATH}/${TEMP_LIB_R_NAMEW}.lib)
	#MESSAGE( STATUS "ADD_LIBRARY_X:TEMP_LIB_D - ${TEMP_LIB_D}")
	#MESSAGE( STATUS "ADD_LIBRARY_X:TEMP_LIB_R - ${TEMP_LIB_R}")
	#MESSAGE( STATUS "ADD_LIBRARY_X:TEMP_EXE_D - ${TEMP_EXE_D}")
	#MESSAGE( STATUS "ADD_LIBRARY_X:TEMP_EXE_R - ${TEMP_EXE_R}")

	SET( ${PROJECT_NAME}_LIBRARY_DEBUG ${TEMP_LIB_D} CACHE PATH "$(PROJECT) project debug library." FORCE)
	SET( ${PROJECT_NAME}_LIBRARY_RELEASE ${TEMP_LIB_R} CACHE PATH "$(PROJECT) project release library." FORCE)
	SET( ${PROJECT_NAME}_LIBRARY optimized ${TEMP_LIB_R} debug ${TEMP_LIB_D} CACHE PATH "$(PROJECT) project link-library." FORCE)
	SET( ${PROJECT_NAME}_DLL_DEBUG ${TEMP_EXE_D} CACHE PATH "$(PROJECT) project debug dll." FORCE)
	SET( ${PROJECT_NAME}_DLL_RELEASE ${TEMP_EXE_R} CACHE PATH "$(PROJECT) project release dll." FORCE)
	SET( ${PROJECT_NAME}_DLL ${TEMP_EXE} CACHE PATH "$(PROJECT) project temp exe." FORCE)
    MARK_AS_ADVANCED(${PROJECT_NAME}_LIBRARY_DEBUG)
    MARK_AS_ADVANCED(${PROJECT_NAME}_LIBRARY_RELEASE)
    MARK_AS_ADVANCED(${PROJECT_NAME}_LIBRARY)
    MARK_AS_ADVANCED(${PROJECT_NAME}_DLL_DEBUG)
    MARK_AS_ADVANCED(${PROJECT_NAME}_DLL_RELEASE)
    MARK_AS_ADVANCED(${PROJECT_NAME}_DLL)

    SET_PROPERTY(TARGET ${ARGV0} PROPERTY FOLDER "Library")

ENDMACRO(ADD_LIBRARY_X)

