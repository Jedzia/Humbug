# bindings.cmake 													   01:36 23.11.2010
# include various libs
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

message( STATUS "binding setup")

#include (${CMAKE_ROOT}/Modules/FindDoxygen.cmake OPTIONAL)
#include (${CMAKE_ROOT}/Modules/FindPerl.cmake    OPTIONAL)
if(USE_PERL)
	find_package(Perl)
	message( STATUS "PERL_EXECUTABLE: " ${PERL_EXECUTABLE} )
endif(USE_PERL)

if(USE_DOXYGEN)
	find_package(Doxygen)
	message( STATUS "DOXYGEN_EXECUTABLE: " ${DOXYGEN_EXECUTABLE} )
endif(USE_DOXYGEN)


if(USE_LIB_BOOST)

  #if(NOT USE_LIB_BOOST_COMPONENTS)
	#set(USE_LIB_BOOST_COMPONENTS "system;filesystem;signals;program_options;unit_test_framework")
	set(USE_LIB_BOOST_COMPONENTS "system;filesystem;signals;regex;program_options;unit_test_framework;serialization")
  #endif()

  set(boost_local_root $ENV{BOOST_ROOTDIR})
  if(NOT boost_local_root)
    set(boost_local_root "E:/Devel/CPP/Libs/boost/boost-1.55.0")
  endif()
  #set(boost_local_root E:/Devel/CPP/Libs/boost/boost-svn)
  if(EXISTS "${boost_local_root}" AND NOT BOOST_ROOT)
	set(BOOST_ROOT "${boost_local_root}" CACHE PATH "Boost root directory" FORCE)
  else()
  	#set(BOOST_ROOT "" CACHE PATH "Boost root directory")
  endif()
	#### set(BOOST_ROOT "E:/Devel/CPP/Libs/boost/boost-svn" CACHE PATH "Boost root directory")
	#message( FATAL_ERROR " BLAAAA " )

  if(BOOST_ROOT)
    # If the user specified a non system path for the boost libraries,
    # then prevent from using the systems boost libraries.
    set(Boost_NO_SYSTEM_PATHS TRUE)
  endif(BOOST_ROOT)
  #set(Boost_INCLUDE_DIR "" CACHE PATH "Boost root directory")
  #set(Boost_COMPILER "")
  #set(Boost_ADDITIONAL_VERSIONS "1.45" "1.45.1" "1.46" "1.46.0")

#Check for additional boost libs
set(Boost_FIND_COMPONENTS ${USE_LIB_BOOST_COMPONENTS})
set(boost_tmp_component_list)

  foreach(mCOMPONENT ${Boost_FIND_COMPONENTS})
    string(TOUPPER ${mCOMPONENT} COMPONENT)
    if("${Boost_${COMPONENT}_LIBRARY}" STREQUAL "")
      #message("NOT YET FOUND: ${COMPONENT}")
       list(APPEND boost_tmp_component_list ${mCOMPONENT})
    else()
      #message("ALREADY FOUND: ${COMPONENT}: ${Boost_${COMPONENT}_LIBRARY}")
    endif()
  endforeach(mCOMPONENT)


  set(BOOST_ALWAYS_RERUN ON)
  set(Boost_USE_STATIC_LIBS   OFF)
  set(Boost_USE_MULTITHREADED ON)
  #set(Boost_USE_STATIC_RUNTIME    ON)
  #set(Boost_COMPAT_STATIC_RUNTIME ON)
  #set(Boost_INCLUDE_DIR "")
  # Detailed findboost output
  #set(Boost_DEBUG TRUE)

  # You can call #add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS}) to have diagnostic
  # information about Boost's #automatic linking outputted during compilation time.
  add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})
  add_definitions("-DUSE_LIB_BOOST")

  if(NOT Boost_USE_STATIC_LIBS)
	message( STATUS " Using dynamically linked boost libs " )
	# Linker Flag to use the dynamically linked boost libs.
	add_definitions("-DBOOST_ALL_DYN_LINK")
	# mal schauen wie ich das einbaue
	#add_definitions("-DBOOST_DYN_LINK")
	#add_definitions("-DBOOST_ALL_DYN_LINK")
  endif()

#  # Only run the modified boost check if the library not yet detected.
#  # Correct this fuck with an END of the day libfetch...
#  #message( " boost_tmp_component_list: ${boost_tmp_component_list} " )
#  list(LENGTH boost_tmp_component_list boost_tmp_component_list_count)
#  #message( " boost_tmp_component_list_count: ${boost_tmp_component_list_count} " )
#  #message( " Boost_FOUND_INT: ${Boost_FOUND_INT} " )
#  if( boost_tmp_component_list_count GREATER 1)
#    set(_plural "s")
#  else()	
#    set(_plural "")
#  endif()
#  if( boost_tmp_component_list_count GREATER 0 AND Boost_INCLUDE_DIR)
#    message( WARNING "\n\nAttempting to load additional boost libraries with a rerun. But rerunning "
#	  "bindings.cmake in that way is not implemented, yet :(\n"
#	  "Include the \"${boost_tmp_component_list}\" component${_plural} at a call to find_package( Boost ) at one central location:"
#	  " Here, in this script above at \nSET(USE_LIB_BOOST_COMPONENTS ...)\n"
#	  "After that, erase all Boost* CMake-Variables and reconfigure ${_prj_name}.\n"
#	)
#  endif()

    find_package( Boost 1.46.0 REQUIRED COMPONENTS ${boost_tmp_component_list} )
    if("${Boost_VERSION}0" LESS "1046000")
	set(_shared_msg
		"NOTE: boost:: targets and tests cannot "
		"be added: boost >= 1.46.0 required but not found. "
		"(found: '${Boost_VERSION}'; want >=104600) ")
	message(FATAL_ERROR
	${_shared_msg}
	"You may install the boost libraries on your system and set the"
	"BOOST_ROOT config var.")
    endif()
    #if( Boost_FOUND )
	#  set(Boost_FOUND_INT Boost_FOUND CACHE INTERNAL BOOL)
    #endif( Boost_FOUND )

    #set(Boost_TMP_INCLUDE_DIR ${Boost_INCLUDE_DIR})
  #endif()
  #set(Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIR})

  # Additional check for ICU Library
  find_package( ICU )
  mark_as_advanced(ICU_DLL_DEBUG)
  mark_as_advanced(ICU_DLL_RELEASE)

endif(USE_LIB_BOOST)

if(USE_LIB_QT4)
	message( STATUS " Using QT4 libs " )

	find_package(Qt4 4.4.3 COMPONENTS QtCore QtGui QtXml REQUIRED )
	#find_package(Qt4 4.4.3 COMPONENTS QtCore QtGui REQUIRED )
	include(${QT_USE_FILE})
	add_definitions("-DUSE_LIB_QT4")


else(USE_LIB_QT4)
	macro(QT4_WRAP_CPP)
	endmacro(QT4_WRAP_CPP)
	macro(QT4_WRAP_UI)
	endmacro(QT4_WRAP_UI)
	macro(QT4_ADD_RESOURCES)
	endmacro(QT4_ADD_RESOURCES)
endif(USE_LIB_QT4)

if(USE_LIB_QSCINTILLA)
#QSCINTILLA2 Library
if(WIN32)
        set(__QSCINTILLA_LIBNAME_REL qscintilla2.lib)
        set(__QSCINTILLA_LIBNAME_DEB qscintilla2d.lib)
        set(__QSCINTILLA_DLL_REL qscintilla2.dll)
        set(__QSCINTILLA_DLL_DEB qscintilla2d.dll)
else(WIN32)
        set(__QSCINTILLA_LIBNAME_REL qscintilla2)
        set(__QSCINTILLA_LIBNAME_DEB qscintilla2)
endif(WIN32)

    find_library(QSCINTILLA_LIBRARY_RELEASE NAMES ${__QSCINTILLA_LIBNAME_REL} PATHS
	/usr/lib
	/usr/local/lib
	${QT_LIBRARY_DIR}
	 NO_DEFAULT_PATH)

    find_library(QSCINTILLA_LIBRARY_DEBUG NAMES ${__QSCINTILLA_LIBNAME_DEB} PATHS
	/usr/lib
	/usr/local/lib
	${QT_LIBRARY_DIR}
	 NO_DEFAULT_PATH)

    find_file(QSCINTILLA_DLL_DEBUG NAMES ${__QSCINTILLA_DLL_DEB} PATHS
	/usr/lib
	/usr/local/lib
	${QT_LIBRARY_DIR}
	 NO_DEFAULT_PATH)

    find_file(QSCINTILLA_DLL_RELEASE NAMES ${__QSCINTILLA_DLL_REL} PATHS
	/usr/lib
	/usr/local/lib
	${QT_LIBRARY_DIR}
	 NO_DEFAULT_PATH)

	 set(QSCINTILLA2_LIB "optimized;${QSCINTILLA_LIBRARY_RELEASE};debug;${QSCINTILLA_LIBRARY_DEBUG}"  CACHE STRING "qscintilla library" FORCE)
	 #message( STATUS "QSCINTILLA2_LIB ${QSCINTILLA2_LIB}  " )
     mark_as_advanced(QSCINTILLA2_LIB)
     mark_as_advanced(QSCINTILLA_LIBRARY_DEBUG)
     mark_as_advanced(QSCINTILLA_LIBRARY_RELEASE)
     mark_as_advanced(QSCINTILLA_DLL_DEBUG)
     mark_as_advanced(QSCINTILLA_DLL_RELEASE)
endif(USE_LIB_QSCINTILLA)



if(USE_LIB_XSD)
	message( STATUS " Using XSD xerces libs " )

	#find_package( XSDE REQUIRED )
	find_package(XSD REQUIRED )
    add_definitions("-DUSE_LIB_XSD")
endif(USE_LIB_XSD)

if(USE_LIB_ZLIB)
	if(${${_prj_name}_EXTERNAL_ZLIB})
	find_package(ZLIBex)
	message( STATUS "ZLIB: " ${PERL_EXECUTABLE} )
	else()
		set(ZLIB_LIBRARY zlib)
	endif()
endif(USE_LIB_ZLIB)


if(${${ROOT_PROJECT_NAME}_USE_SDL})
	string(TOUPPER ${PROJECT_NAME} PRJNAME_UPPER)
	add_definitions("-DSDL_${PRJNAME_UPPER}_ENABLED")
endif()

if(USE_SDL)
	find_package(SDL2 REQUIRED)
	if( NOT SDL_FOUND )
		message(FATAL_ERROR "SDL2 Library not found!")
	endif( NOT SDL_FOUND )
	MODUSE_SUMMARY(SDL               "SDL has ${SDL_LIBRARY}" ON MSVC)
endif(USE_SDL)

if(USE_SDL_IMAGE)
	find_package(SDL2_image REQUIRED)
	if( NOT SDLIMAGE_FOUND )
		message(FATAL_ERROR "SDL2_image Library not found!")
	endif( NOT SDLIMAGE_FOUND )
	MODUSE_SUMMARY(SDL_IMAGE               "SDL has ${SDLIMAGE_LIBRARY}" ON MSVC)
endif(USE_SDL_IMAGE)

if(USE_SDL_TTF)
	find_package(SDL2_ttf REQUIRED)
	if( NOT SDLTTF_FOUND )
		message(FATAL_ERROR "SDL2_ttf Library not found!")
	endif( NOT SDLTTF_FOUND )
	MODUSE_SUMMARY(SDL_TTF               "SDL has ${SDLTTF_LIBRARY}" ON MSVC)
endif(USE_SDL_TTF)

if(USE_SDL_GFX)
	find_package(SDL2_gfx REQUIRED)
	if( NOT SDLGFX_FOUND )
		message(FATAL_ERROR "SDL2_gfx Library not found!")
	endif( NOT SDLGFX_FOUND )
	MODUSE_SUMMARY(SDL_GFX               "SDL has ${SDLGFX_LIBRARY}" ON MSVC)
endif(USE_SDL_GFX)

if(USE_SDL_NET)
	find_package(SDL2_net REQUIRED)
	if( NOT SDLNET_FOUND )
		message(FATAL_ERROR "SDL2_net Library not found!")
	endif( NOT SDLNET_FOUND )
	MODUSE_SUMMARY(SDL_GFX               "SDL has ${SDLNET_LIBRARY}" ON MSVC)
endif(USE_SDL_NET)

if(USE_SDL_MIXER)
	find_package(SDL2_mixer REQUIRED)
	if( NOT SDLMIXER_FOUND )
		message(FATAL_ERROR "SDL2_mixer Library not found!")
	endif( NOT SDLMIXER_FOUND )
	MODUSE_SUMMARY(SDL_MIXER               "SDL has ${SDLMIXER_LIBRARY}" ON MSVC)
endif(USE_SDL_MIXER)

if(USE_LUA)
	find_package(Lua52 REQUIRED)
	if( NOT LUA52_FOUND )
		message(FATAL_ERROR "LUA Library not found!")
	endif( NOT LUA52_FOUND )
	MODUSE_SUMMARY(LUA               "LUA has ${LUA_LIBRARY}" ON MSVC)
endif(USE_LUA)

if(USE_NLS)
# --------- Native Language Support (NLS) -------------

#if(${${_prj_name}_NLS})
	find_program(PYTHON_EXECUTABLE python HINTS ${GNUWIN32_DIR}/bin/python)
	if(${LYX_PYTHON_EXECUTABLE} MATCHES "-NOTFOUND")
		message(FATAL_ERROR "Python 2.6 needed!")
	endif()
	find_package(PRJGettext REQUIRED)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/po)
	#add_subdirectory(po "${TOP_BINARY_DIR}/po")
	#add_subdirectory(po )
#endif()

#if(${${_prj_name}_NLS})
#	if(LYX_EXTERNAL_LIBINTL)
		find_package(Libintl REQUIRED)
		if(DEFINED LIBINTL_LIBRARIES)
			# find getext when configuring
			list(APPEND CMAKE_REQUIRED_LIBRARIES ${LIBINTL_LIBRARIES})
			# on mac use iconv also form ports
			get_filename_component(ICONV_RELATIVE_TO_LIBINTL ${LIBINTL_LIBRARIES} PATH)
		endif()
#	else()
#		add_subdirectory(intl "${TOP_BINARY_DIR}/intl")
#	endif()
#endif()

find_package(ICONV REQUIRED)
endif(USE_NLS)

if(CHECK_STRINGS)
	#set(HAVE_WCHAR_T 1)
	include (CheckTypeSize)
	set(CMAKE_EXTRA_INCLUDE_FILES wchar.h)
	CHECK_TYPE_SIZE(wchar_t SIZEOF_WCHAR_T)
	if(SIZEOF_WCHAR_T)
		set(HAVE_WCHAR_T 1)
	endif()
endif(CHECK_STRINGS)

#add_definitions("-DPACKAGE=${PACKAGE}")

# \Todo: USE_PERL ... usw hier entweder zuruecksetzen oder alles in richtung
# ${PROJECT_NAME}_USES_PERL umbauen ... Die defines dann auch 
#message(FATAL_ERROR "DEPP ${PROJECT_NAME}_USES_PERL")
#set(USE_PERL )
#...
#set(CHECK_STRINGS )
# Besser wird es sein den PROJECT_NAME Ansatz zu nehmen, da die Variablen sonnst
# f\FCr den Aufrufer verloren sind.

if(USE_MAGICK)
	find_package(ImageMagick)
	if( NOT ImageMagick_FOUND )
#		message(FATAL_ERROR "SDL_image Library not found!")
	endif( NOT ImageMagick_FOUND )
	MODUSE_SUMMARY(ImageMagick_EXE               "at ${ImageMagick_EXECUTABLE_DIR}" USE ALL)
endif(USE_MAGICK)

if(USE_INKSCAPE)
	find_program(INKSCAPE_EXECUTABLE
	  NAMES inkscape.exe inkscape
	  PATHS
#		"[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\doxygen_is1;Inno Setup: App Path]/bin"
        "$ENV{ProgramFiles}/Inkscape"
        "C:/Program Files/Inkscape"
        "C:/Program Files (x86)/Inkscape"
        "D:/Program Files (x86)/Inkscape"
		"D:/Program Files/Inkscape/"
#		/Applications/Doxygen.app/Contents/Resources
#		/Applications/Doxygen.app/Contents/MacOS
	  DOC "Inkscape .... (http://www.inkscape.org)"
	)
	if( INKSCAPE_EXECUTABLE )
#		message(FATAL_ERROR "SDL_image Library not found!")
		message(STATUS "Inkscape_executable found: ${INKSCAPE_EXECUTABLE}")
		set(INKSCAPE_EXECUTABLE_FOUND TRUE)
	else()
		message(WARNING "Inkscape executable not found.")
	endif()
	MODUSE_SUMMARY(Inkscape_EXE               "at ${INKSCAPE_EXECUTABLE}" USE ALL)
endif(USE_INKSCAPE)

