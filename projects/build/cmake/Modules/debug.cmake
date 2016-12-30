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

message( STATUS "Setting Debug Vars")

set(DEBUG_MEMORY FALSE CACHE BOOL "Use CRT Memory Debugging")
set(DEBUG_MEMORY_STDOUT FALSE CACHE BOOL "Memory Debugging to console")

include_directories(${CMAKE_SOURCE_DIR})
set (DEBUG_DEFINITION_INCLUDES 
	${CMAKE_SOURCE_DIR}/build/cmake/include/debug.h  
)

source_group(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
#set_source_files_properties( ${DEBUG_DEFINITION_INCLUDES}
#	PROPERTIES SOURCE_GROUP "GlobalHeader"
#)

if(MSVC)
  if(DEBUG_MEMORY)
    add_definitions("-DDEBUG_MEMORY")
    #add_definitions("-DDEBUG_MEMORY_INCLUDE=<build/cmake/include/debug.h>")
	if(DEBUG_MEMORY_STDOUT)
		add_definitions("-DDEBUG_MEMORY_STDOUT")
	endif(DEBUG_MEMORY_STDOUT)
  endif(DEBUG_MEMORY)
endif(MSVC)
