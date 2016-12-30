# debug.cmake 													   01:37 23.11.2010
# debugging setup 
# by Jedzia (c) 2010
#
# Vars:
# ---------------------------------------------------------------------------------
# * DEBUG_MEMORY			Use CRT Memory Debugging. Defines -DDEBUG_MEMORY
# * DEBUG_MEMORY_STDOUT		Use console stdout for memory debugging output.
#
# Description:
# ---------------------------------------------------------------------------------
# Use these settings and defines in conjunction with debug.h and the macro
# _CRT_DEBUG_BLOCK in the main function to start memory leak detection at that
# location. The header debug.h has to be included in every cpp code as the last
# #include preprocessor instruction. If you are using QT, then there are problems
# with the CRT Memory debugging and you get errors if debug.h with the malloc() and 
# free() hooks is not placed after the QT includes.
#
# ---------------------------------------------------------------------------------

MESSAGE( STATUS "Setting Debug Vars")

SET(DEBUG_MEMORY FALSE CACHE BOOL "Use CRT Memory Debugging")
SET(DEBUG_MEMORY_STDOUT FALSE CACHE BOOL "Memory Debugging to console")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})
SET (DEBUG_DEFINITION_INCLUDES 
	${CMAKE_SOURCE_DIR}/build/cmake/include/debug.h  
)

SOURCE_GROUP(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
#SET_SOURCE_FILES_PROPERTIES( ${DEBUG_DEFINITION_INCLUDES}
#	PROPERTIES SOURCE_GROUP "GlobalHeader"
#)

IF(MSVC)
  IF(DEBUG_MEMORY)
    ADD_DEFINITIONS("-DDEBUG_MEMORY")
    #ADD_DEFINITIONS("-DDEBUG_MEMORY_INCLUDE=<build/cmake/include/debug.h>")
	IF(DEBUG_MEMORY_STDOUT)
		ADD_DEFINITIONS("-DDEBUG_MEMORY_STDOUT")
	ENDIF(DEBUG_MEMORY_STDOUT)
  ENDIF(DEBUG_MEMORY)
ENDIF(MSVC)
