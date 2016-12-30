# setup.cmake 													   01:36 23.11.2010
# global variables setup
# by Jedzia (c) 2010
#
# Vars:
# ---------------------------------------------------------------------------------
# LINUX				TRUE if building on Linux.
# Description:
# ---------------------------------------------------------------------------------
# Setup some usefuls vars.
#
# ---------------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8.2)

message(STATUS "Setting up global Vars")
message(STATUS "PROJECT_BINARY_DIR:  ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")

set(PACKAGE ${PROJECT_NAME})

#get_filename_component(${_prj_name}_dir_readme ${CMAKE_SOURCE_DIR}/README ABSOLUTE)
get_filename_component(${_prj_name}_dir_readme ${CMAKE_CURRENT_SOURCE_DIR}/README ABSOLUTE)
get_filename_component(TOP_SRC_DIR ${${_prj_name}_dir_readme} PATH)

include(GlobalPaths)

include(GetOperatingSystemArchitectureBitness)
GetOperatingSystemArchitectureBitness(VAR_PREFIX ${PROJECT_NAME})
message(STATUS "Configuring ${PROJECT_NAME} for ${${PROJECT_NAME}_OS}-${${PROJECT_NAME}_ARCHITECTURE} ${${PROJECT_NAME}_BITNESS}-bit")
if(${${PROJECT_NAME}_BITNESS} EQUAL 32)
#	message(STATUS "32-bit build")
	set(CMAKE_SYSTEM_X86 TRUE)
else(${${PROJECT_NAME}_BITNESS} EQUAL 64)
#	message(STATUS "64-bit build")
	set(CMAKE_SYSTEM_X64 TRUE)
else()
	message(FATAL_ERROR "Can't determine bitness of the build system.")
endif()



include(ProjectMacros)

PRJ_OPTION_INIT()

string(COMPARE EQUAL "Linux" ${CMAKE_SYSTEM_NAME} LINUX)

if(MINGW)
	set(MSYS 1)
endif(MINGW)

if(MSYS)
	#add_definitions(-g -DMSYS -DDEBUG)
	add_definitions(-DMSYS)
endif(MSYS)

if(LINUX)
        set(CMAKE_BUILD_TYPE DEBUG)
endif(LINUX)


if(CMAKE_BUILD_TYPE STREQUAL Debug)
    message(STATUS "Do debug stuff")
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
    message(STATUS "Do release stuff")
elseif(CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
    message(STATUS "Do release with debug info stuff")
elseif(CMAKE_BUILD_TYPE STREQUAL MinSizeRel)
    message(STATUS "Do minimal size release stuff")
endif()

# gcc -std=c++0x
if(CMAKE_COMPILER_IS_GNUCXX)
        #set(CMAKE_CXX_FLAGS_DEBUG      "${CMAKE_CXX_FLAGS_DEBUG} -std=c++0x")
        #set(CMAKE_CXX_FLAGS_RELEASE      "${CMAKE_CXX_FLAGS_RELEASE} -std=c++0x")
        #set(CMAKE_CXX_FLAGS      "${CMAKE_CXX_FLAGS} -std=c++0x")
	add_definitions(-std=c++0x)
        #message( "GGGGGG CCCCCCCCCCCCCCCCCCCC")
endif(CMAKE_COMPILER_IS_GNUCXX)

# Single build directory option
set(USE_SINGLE_BUILDDIR FALSE CACHE BOOL "One build directory is used for all executables and libraries.")
mark_as_advanced(USE_SINGLE_BUILDDIR)
if(USE_SINGLE_BUILDDIR)
	# ---------- Setup output Directories -------------------------
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY
	   ${PROJECT_BINARY_DIR}/bin
	   CACHE PATH
	   "Single Directory for all Libraries"
	)

	# --------- Setup the Executable output Directory -------------
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY
	   ${PROJECT_BINARY_DIR}/bin
	   CACHE PATH
	   "Single Directory for all Executables."
	)

	# --------- Setup the Executable output Directory -------------
	set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
	   ${PROJECT_BINARY_DIR}/bin
	   CACHE PATH
	   "Single Directory for all static libraries."
	)
endif(USE_SINGLE_BUILDDIR)


#Use Solution Folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#Variable for test building the test projects
set(BUILD_TESTING FALSE CACHE BOOL "Build the test projects.")
if(BUILD_TESTING)
	enable_testing()
endif(BUILD_TESTING)


# --------- Linker: Link Time Compile Generated Code Optimization (LTCG/LTO) -------------
PRJ_OPTION(LTO "Link Time Optimization for MinGW or MSVC" OFF ALL)
#PRJ_OPTION(Blafsel_Check "Link Time Optimization for MinGW or MSVC" OFF ALL)

if(MSVC)
	if(${${_prj_name}_LTO})
		# enable link time code generation stuff
		#set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG" CACHE TYPE STRING FORCE)
		set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
		set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS_RELEASE} /LTCG")
		set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /LTCG")
	endif(${${_prj_name}_LTO})
endif()

if(MSVC10)
	#set(${_prj_name}_USE_TR1 1)
	#set(LYX_USE_TR1_REGEX 1) #TODO should we use it in ECMAScript mode?
endif()

if(NOT MSVC)
	PRJ_OPTION(QUIET            "Don't generate verbose makefiles" OFF ALL)
	if(NOT ${_prj_name}_QUIET)
		set(CMAKE_VERBOSE_MAKEFILE ON)
	endif()
	set(${_prj_name}_CXX_FLAGS "-Wall -Wunused-parameter")
	if(${_prj_name}_STDLIB_DEBUG)
		set(${_prj_name}_CXX_FLAGS "${${_prj_name}_CXX_FLAGS} -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC")
	endif()

	PRJ_OPTION(CONCEPT_CHECKS       "Enable concept-checks" OFF GCC)
	#if(${_prj_name}_CONCEPT_CHECKS)
	#	set(${_prj_name}_CXX_FLAGS "${${_prj_name}_CXX_FLAGS} -D_GLIBCPP_CONCEPT_CHECKS")
	#endif()
	#set(CMAKE_CXX_FLAGS       "${${_prj_name}_CXX_FLAGS} -fno-strict-aliasing " CACHE TYPE STRING FORCE)
	set(CMAKE_CXX_FLAGS       "${${_prj_name}_CXX_FLAGS} -fno-strict-aliasing ")
	set(CMAKE_CXX_FLAGS_DEBUG "${${_prj_name}_CXX_FLAGS} -fno-strict-aliasing -O0 -g -D_DEBUG")
	if(MINGW)
		if(${${_prj_name}_LTO})
			#set(CMAKE_CXX_FLAGS_RELEASE "${LYX_CXX_FLAGS} -O2 -DNDEBUG" CACHE TYPE STRING FORCE)
			set(CMAKE_CXX_FLAGS_RELEASE "${${_prj_name}_CXX_FLAGS} -O3 -flto -DNDEBUG")
		else(${${_prj_name}_LTO})
		set(CMAKE_CXX_FLAGS_RELEASE "${${_prj_name}_CXX_FLAGS} -O2 -DNDEBUG")
		endif(${${_prj_name}_LTO})
	else()
		set(CMAKE_CXX_FLAGS_RELEASE "${${_prj_name}_CXX_FLAGS} -O3 -DNDEBUG")
	endif()
	set(CMAKE_CXX_FLAGS_PROFILE "${CMAKE_CXX_FLAGS_RELEASE} -pg")
endif()

if(WIN32)
PRJ_OPTION(CONSOLE               "Show console on Windows" ON MSVC)
PRJ_OPTION(WCHAR_EXTERNAL               "Treat wchar_t as external type." OFF MSVC)
	if(NOT ${${_prj_name}_CONSOLE})
		set(WIN32_CONSOLE WIN32)
	endif()
	if(MSVC)
	if(${${_prj_name}_WCHAR_EXTERNAL})
		set(CMAKE_CXX_FLAGS_DEBUG      "${CMAKE_CXX_FLAGS_DEBUG} /Zc:wchar_t-")
		set(CMAKE_CXX_FLAGS_RELEASE    "${CMAKE_CXX_FLAGS_RELEASE} /Zc:wchar_t-")
		set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /Zc:wchar_t-")
	endif()
		add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -DNOMINMAX)
		if(${${_prj_name}_LTO})
		# disable checked iterators for msvc release builds to get maximum speed
			# enable link time code generation stuff
			#set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} /D_SECURE_SCL=0 /GL")
			set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} /GL")
		else(${${_prj_name}_LTO})
			# disable checked iterators for msvc release builds to get maximum speed
			#set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} /D_SECURE_SCL=0")
		endif(${${_prj_name}_LTO})
	else()
		add_definitions(-DWINVER=0x0500)
	endif()
endif(WIN32)

# ---------  PCH Debugging -------------
PRJ_OPTION(PCH_DEBUG               "Output GCC Precompiled Header Debugging." OFF CMAKE_COMPILER_IS_GNUCXX)
        if(${${_prj_name}_PCH_DEBUG})
                set( PCH_ADDITIONAL_COMPILER_FLAGS "-H" )
        endif(${${_prj_name}_PCH_DEBUG})

# ---------  NLS Support -------------
PRJ_OPTION(NLS              "Enable Native Language Support (NLS)" OFF ALL)
        if(${${_prj_name}_NLS})
                #set( PCH_ADDITIONAL_COMPILER_FLAGS "-H" )
                set(USE_NLS TRUE)
				# LOCALE Directory
				if(NOT ${_prj_name}_LOCALEDIR)
					if (WIN32)
						set(${_prj_name}_LOCALEDIR "locale" CACHE STRING "NLS locale subdirectory for all ${_prj_name}-language-data" FORCE)
					else()
						set(${_prj_name}_LOCALEDIR "locale" CACHE STRING "NLS locale subdirectory for all ${_prj_name}-language-data" FORCE)
					endif()
				endif()
        endif(${${_prj_name}_NLS})


PRJ_OPTION(EXTERNAL_ZLIB "Use external zlib" ON ALL)

# --------- Set GNUWIN Directory -------------

if(WIN32)
set (GNUWIN32_DIR C:/gnuwin32 CACHE PATH
	   "GNUWIN32 binary directory"
)
endif()

# --------- INSTALL_PREFIX -------------
PRJ_OPTION(INSTALL_PREFIX   "Install path for LyX" OFF ALL)
if(${_prj_name}_INSTALL_PREFIX)
	set(CMAKE_INSTALL_PREFIX ${${_prj_name}_INSTALL_PREFIX} CACHE PATH "${_prj_name} user's choice install prefix" FORCE)
	set(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
endif()
PRJ_OPTION(INSTALL_Devel   "Development Installation of ${_prj_name}" OFF ALL)
if(${_prj_name}_INSTALL_Devel)
    if(${_prj_name}_INSTALL_PREFIX)
		set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/${${_prj_name}_INSTALL_PREFIX} CACHE PATH "${_prj_name} user's choice install prefix" FORCE)
		#set(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    else(${_prj_name}_INSTALL_PREFIX)
		set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/${_prj_name}Devel CACHE PATH "${_prj_name} user's choice install prefix" FORCE)
		#set(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    endif(${_prj_name}_INSTALL_PREFIX)
endif()

set(${_prj_name}_INSTALL_PREFIX ${${_prj_name}_INSTALL_PREFIX} CACHE PATH "${_prj_name} user's choice install prefix" FORCE)

# --------- Set DATA Directory -------------
if(NOT ${_prj_name}_DATA_SUBDIR)
	if (WIN32)
		set(${_prj_name}_DATA_SUBDIR "Resources/" CACHE STRING "Subdirectory for all ${_prj_name}-system-data" FORCE)
	else()
		set(${_prj_name}_DATA_SUBDIR "" CACHE STRING "Subdirectory for all ${_prj_name}-system-data" FORCE)
	endif()
endif()
set(${_prj_name}_ABS_INSTALLED_DATADIR "${CMAKE_INSTALL_PREFIX}")
set(${_prj_name}_ABS_INSTALLED_LOCALEDIR "${${_prj_name}_ABS_INSTALLED_DATADIR}/${${_prj_name}_DATA_SUBDIR}${${_prj_name}_LOCALEDIR}")
set(${_prj_name}_ABS_TOP_SRCDIR "${TOP_SRC_DIR}")

# --------- Help Display -------------

if(help OR HELP)
	message(STATUS)
	message(STATUS "Available options: (dis/enable with -D[Option_Name]=0/1)")
	message(STATUS)
	PRJ_OPTION_LIST_ALL(help)
	message(STATUS)
	STOP()
endif()


