


set(TOP_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
#message(STATUS "TOP_BINARY_DIR: ${TOP_BINARY_DIR}")

set( ${PROJECT_NAME}_USE_CONFIG_H TRUE CACHE BOOL "$(PROJECT) project use config.h instead of compiler switch -Defines." )
mark_as_advanced(${PROJECT_NAME}_USE_CONFIG_H)

set(${PROJECT_NAME}_CONFIG_FILES)

#	add_definitions(-DBOOST_USER_CONFIG="<config.h>")
#	configure_file(${P_CONFIG_INCLUDE_PATH}/pcheaders.h      ${TOP_BINARY_DIR}/pcheaders.h)
#	configure_file(${P_CONFIG_INCLUDE_PATH}/config.cpp.cmake ${TOP_BINARY_DIR}/config_pch.cpp)
#   list(APPEND ${PROJECT_NAME}_CONFIG_FILES ${TOP_BINARY_DIR}/pcheaders.h)
#   list(APPEND ${PROJECT_NAME}_CONFIG_FILES ${TOP_BINARY_DIR}/config_pch.cpp)
#	add_definitions(-DLYX_ENABLE_PCH)

if(MSVC AND NOT LYX_CONFIGURE_CHECKS)
	configure_file(${P_CONFIG_INCLUDE_PATH}/configCompiler.h.msvc ${TOP_BINARY_DIR}/configCompiler.h)
    list(APPEND ${PROJECT_NAME}_CONFIG_FILES ${TOP_BINARY_DIR}/configCompiler.h)
else()
	include(${P_CONFIG_INCLUDE_PATH}/ConfigureChecks.cmake)
	configure_file(${P_CONFIG_INCLUDE_PATH}/configCompiler.h.cmake ${TOP_BINARY_DIR}/configCompiler.h)
    list(APPEND ${PROJECT_NAME}_CONFIG_FILES ${TOP_BINARY_DIR}/configCompiler.h)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${TOP_BINARY_DIR}/config.h)
list(APPEND ${PROJECT_NAME}_CONFIG_FILES ${TOP_BINARY_DIR}/config.h)
source_group(GlobalHeader FILES ${${PROJECT_NAME}_CONFIG_FILES})

if(${${PROJECT_NAME}_USE_CONFIG_H})
	add_definitions(-DHAVE_CONFIG_H)
	add_definitions(-DHAVE_${PROJECT_NAME}_CONFIG_H)
endif(${${PROJECT_NAME}_USE_CONFIG_H})

#Implement Install for the config files
