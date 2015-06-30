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

MESSAGE( STATUS "binding setup")

#INCLUDE (${CMAKE_ROOT}/Modules/FindDoxygen.cmake OPTIONAL)
#INCLUDE (${CMAKE_ROOT}/Modules/FindPerl.cmake    OPTIONAL)
IF(USE_PERL)
	FIND_PACKAGE(Perl)
	MESSAGE( STATUS "PERL_EXECUTABLE: " ${PERL_EXECUTABLE} )
ENDIF(USE_PERL)

IF(USE_DOXYGEN)
	FIND_PACKAGE(Doxygen)
	MESSAGE( STATUS "DOXYGEN_EXECUTABLE: " ${DOXYGEN_EXECUTABLE} )
ENDIF(USE_DOXYGEN)


IF(USE_LIB_BOOST)

  #IF(NOT USE_LIB_BOOST_COMPONENTS)
	#SET(USE_LIB_BOOST_COMPONENTS "system;filesystem;signals;program_options;unit_test_framework")
	SET(USE_LIB_BOOST_COMPONENTS "system;filesystem;signals;regex;program_options;unit_test_framework;serialization")
  #ENDIF()

  SET(boost_local_root $ENV{BOOST_ROOTDIR})
  IF(NOT boost_local_root)
    SET(boost_local_root "E:/Devel/CPP/Libs/boost/boost-1.55.0")
  ENDIF()
  #SET(boost_local_root E:/Devel/CPP/Libs/boost/boost-svn)
  IF(EXISTS "${boost_local_root}" AND NOT BOOST_ROOT)
	SET(BOOST_ROOT "${boost_local_root}" CACHE PATH "Boost root directory" FORCE)
  ELSE()
  	#SET(BOOST_ROOT "" CACHE PATH "Boost root directory")
  ENDIF()
	#### SET(BOOST_ROOT "E:/Devel/CPP/Libs/boost/boost-svn" CACHE PATH "Boost root directory")
	#MESSAGE( FATAL_ERROR " BLAAAA " )

  IF(BOOST_ROOT)
    # If the user specified a non system path for the boost libraries,
    # then prevent from using the systems boost libraries.
    SET(Boost_NO_SYSTEM_PATHS TRUE)
  ENDIF(BOOST_ROOT)
  #SET(Boost_INCLUDE_DIR "" CACHE PATH "Boost root directory")
  #SET(Boost_COMPILER "")
  #SET(Boost_ADDITIONAL_VERSIONS "1.45" "1.45.1" "1.46" "1.46.0")

#Check for additional boost libs
SET(Boost_FIND_COMPONENTS ${USE_LIB_BOOST_COMPONENTS})
SET(boost_tmp_component_list)

  foreach(mCOMPONENT ${Boost_FIND_COMPONENTS})
    string(TOUPPER ${mCOMPONENT} COMPONENT)
    if("${Boost_${COMPONENT}_LIBRARY}" STREQUAL "")
      #MESSAGE("NOT YET FOUND: ${COMPONENT}")
       list(APPEND boost_tmp_component_list ${mCOMPONENT})
    else()
      #MESSAGE("ALREADY FOUND: ${COMPONENT}: ${Boost_${COMPONENT}_LIBRARY}")
    endif()
  endforeach(mCOMPONENT)


  SET(BOOST_ALWAYS_RERUN ON)
  SET(Boost_USE_STATIC_LIBS   OFF)
  SET(Boost_USE_MULTITHREADED ON)
  #SET(Boost_USE_STATIC_RUNTIME    ON)
  #SET(Boost_COMPAT_STATIC_RUNTIME ON)
  #SET(Boost_INCLUDE_DIR "")
  # Detailed findboost output
  #set(Boost_DEBUG TRUE)

  # You can call #ADD_DEFINITIONS(${Boost_LIB_DIAGNOSTIC_DEFINITIONS}) to have diagnostic
  # information about Boost's #automatic linking outputted during compilation time.
  ADD_DEFINITIONS(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})
  ADD_DEFINITIONS("-DUSE_LIB_BOOST")

  IF(NOT Boost_USE_STATIC_LIBS)
	MESSAGE( STATUS " Using dynamically linked boost libs " )
	# Linker Flag to use the dynamically linked boost libs.
	ADD_DEFINITIONS("-DBOOST_ALL_DYN_LINK")
	# mal schauen wie ich das einbaue
	#ADD_DEFINITIONS("-DBOOST_DYN_LINK")
	#ADD_DEFINITIONS("-DBOOST_ALL_DYN_LINK")
  ENDIF()

#  # Only run the modified boost check if the library not yet detected.
#  # Correct this fuck with an END of the day libfetch...
#  #MESSAGE( " boost_tmp_component_list: ${boost_tmp_component_list} " )
#  list(LENGTH boost_tmp_component_list boost_tmp_component_list_count)
#  #MESSAGE( " boost_tmp_component_list_count: ${boost_tmp_component_list_count} " )
#  #MESSAGE( " Boost_FOUND_INT: ${Boost_FOUND_INT} " )
#  IF( boost_tmp_component_list_count GREATER 1)
#    SET(_plural "s")
#  ELSE()	
#    SET(_plural "")
#  ENDIF()
#  IF( boost_tmp_component_list_count GREATER 0 AND Boost_INCLUDE_DIR)
#    MESSAGE( WARNING "\n\nAttempting to load additional boost libraries with a rerun. But rerunning "
#	  "bindings.cmake in that way is not implemented, yet :(\n"
#	  "Include the \"${boost_tmp_component_list}\" component${_plural} at a call to FIND_PACKAGE( Boost ) at one central location:"
#	  " Here, in this script above at \nSET(USE_LIB_BOOST_COMPONENTS ...)\n"
#	  "After that, erase all Boost* CMake-Variables and reconfigure ${_prj_name}.\n"
#	)
#  ENDIF()

    FIND_PACKAGE( Boost 1.46.0 REQUIRED COMPONENTS ${boost_tmp_component_list} )
    if("${Boost_VERSION}0" LESS "1046000")
	set(_shared_msg
		"NOTE: boost:: targets and tests cannot "
		"be added: boost >= 1.46.0 required but not found. "
		"(found: '${Boost_VERSION}'; want >=104600) ")
	message(FATAL_ERROR
	${_shared_msg}
	"You may install the boost libraries on your system and set the"
	"BOOST_ROOT config var.")
    ENDIF()
    #IF( Boost_FOUND )
	#  set(Boost_FOUND_INT Boost_FOUND CACHE INTERNAL BOOL)
    #ENDIF( Boost_FOUND )

    #SET(Boost_TMP_INCLUDE_DIR ${Boost_INCLUDE_DIR})
  #ENDIF()
  #SET(Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIR})

  # Additional check for ICU Library
  FIND_PACKAGE( ICU )
  MARK_AS_ADVANCED(ICU_DLL_DEBUG)
  MARK_AS_ADVANCED(ICU_DLL_RELEASE)

ENDIF(USE_LIB_BOOST)

IF(USE_LIB_QT4)
	MESSAGE( STATUS " Using QT4 libs " )

	FIND_PACKAGE(Qt4 4.4.3 COMPONENTS QtCore QtGui QtXml REQUIRED )
	#FIND_PACKAGE(Qt4 4.4.3 COMPONENTS QtCore QtGui REQUIRED )
	INCLUDE(${QT_USE_FILE})
	ADD_DEFINITIONS("-DUSE_LIB_QT4")


ELSE(USE_LIB_QT4)
	MACRO(QT4_WRAP_CPP)
	ENDMACRO(QT4_WRAP_CPP)
	MACRO(QT4_WRAP_UI)
	ENDMACRO(QT4_WRAP_UI)
	MACRO(QT4_ADD_RESOURCES)
	ENDMACRO(QT4_ADD_RESOURCES)
ENDIF(USE_LIB_QT4)

IF(USE_LIB_QSCINTILLA)
#QSCINTILLA2 Library
if(WIN32)
        SET(__QSCINTILLA_LIBNAME_REL qscintilla2.lib)
        SET(__QSCINTILLA_LIBNAME_DEB qscintilla2d.lib)
        SET(__QSCINTILLA_DLL_REL qscintilla2.dll)
        SET(__QSCINTILLA_DLL_DEB qscintilla2d.dll)
else(WIN32)
        SET(__QSCINTILLA_LIBNAME_REL qscintilla2)
        SET(__QSCINTILLA_LIBNAME_DEB qscintilla2)
endif(WIN32)

    FIND_LIBRARY(QSCINTILLA_LIBRARY_RELEASE NAMES ${__QSCINTILLA_LIBNAME_REL} PATHS
	/usr/lib
	/usr/local/lib
	${QT_LIBRARY_DIR}
	 NO_DEFAULT_PATH)

    FIND_LIBRARY(QSCINTILLA_LIBRARY_DEBUG NAMES ${__QSCINTILLA_LIBNAME_DEB} PATHS
	/usr/lib
	/usr/local/lib
	${QT_LIBRARY_DIR}
	 NO_DEFAULT_PATH)

    FIND_FILE(QSCINTILLA_DLL_DEBUG NAMES ${__QSCINTILLA_DLL_DEB} PATHS
	/usr/lib
	/usr/local/lib
	${QT_LIBRARY_DIR}
	 NO_DEFAULT_PATH)

    FIND_FILE(QSCINTILLA_DLL_RELEASE NAMES ${__QSCINTILLA_DLL_REL} PATHS
	/usr/lib
	/usr/local/lib
	${QT_LIBRARY_DIR}
	 NO_DEFAULT_PATH)

	 SET(QSCINTILLA2_LIB "optimized;${QSCINTILLA_LIBRARY_RELEASE};debug;${QSCINTILLA_LIBRARY_DEBUG}"  CACHE STRING "qscintilla library" FORCE)
	 #MESSAGE( STATUS "QSCINTILLA2_LIB ${QSCINTILLA2_LIB}  " )
     MARK_AS_ADVANCED(QSCINTILLA2_LIB)
     MARK_AS_ADVANCED(QSCINTILLA_LIBRARY_DEBUG)
     MARK_AS_ADVANCED(QSCINTILLA_LIBRARY_RELEASE)
     MARK_AS_ADVANCED(QSCINTILLA_DLL_DEBUG)
     MARK_AS_ADVANCED(QSCINTILLA_DLL_RELEASE)
ENDIF(USE_LIB_QSCINTILLA)



IF(USE_LIB_XSD)
	MESSAGE( STATUS " Using XSD xerces libs " )

	#FIND_PACKAGE( XSDE REQUIRED )
	FIND_PACKAGE(XSD REQUIRED )
    ADD_DEFINITIONS("-DUSE_LIB_XSD")
ENDIF(USE_LIB_XSD)

IF(USE_LIB_ZLIB)
	IF(${${_prj_name}_EXTERNAL_ZLIB})
	FIND_PACKAGE(ZLIBex)
	MESSAGE( STATUS "ZLIB: " ${PERL_EXECUTABLE} )
	ELSE()
		SET(ZLIB_LIBRARY zlib)
	ENDIF()
ENDIF(USE_LIB_ZLIB)


IF(${${ROOT_PROJECT_NAME}_USE_SDL})
	STRING(TOUPPER ${PROJECT_NAME} PRJNAME_UPPER)
	ADD_DEFINITIONS("-DSDL_${PRJNAME_UPPER}_ENABLED")
ENDIF()

IF(USE_SDL)
	FIND_PACKAGE(SDL REQUIRED)
	IF( NOT SDL_FOUND )
		MESSAGE(FATAL_ERROR "SDL Library not found!")
	ENDIF( NOT SDL_FOUND )
	MODUSE_SUMMARY(SDL               "SDL has ${SDL_LIBRARY}" ON MSVC)
ENDIF(USE_SDL)

IF(USE_SDL_IMAGE)
	FIND_PACKAGE(SDL_image REQUIRED)
	IF( NOT SDLIMAGE_FOUND )
		MESSAGE(FATAL_ERROR "SDL_image Library not found!")
	ENDIF( NOT SDLIMAGE_FOUND )
	MODUSE_SUMMARY(SDL_IMAGE               "SDL has ${SDLIMAGE_LIBRARY}" ON MSVC)
ENDIF(USE_SDL_IMAGE)

IF(USE_SDL_TTF)
	FIND_PACKAGE(SDL_ttf REQUIRED)
	IF( NOT SDLTTF_FOUND )
		MESSAGE(FATAL_ERROR "SDL_ttf Library not found!")
	ENDIF( NOT SDLTTF_FOUND )
	MODUSE_SUMMARY(SDL_TTF               "SDL has ${SDLTTF_LIBRARY}" ON MSVC)
ENDIF(USE_SDL_TTF)

IF(USE_SDL_GFX)
	FIND_PACKAGE(SDL_gfx REQUIRED)
	IF( NOT SDLGFX_FOUND )
		MESSAGE(FATAL_ERROR "SDL_gfx Library not found!")
	ENDIF( NOT SDLGFX_FOUND )
	MODUSE_SUMMARY(SDL_GFX               "SDL has ${SDLGFX_LIBRARY}" ON MSVC)
ENDIF(USE_SDL_GFX)

IF(USE_LUA)
	FIND_PACKAGE(Lua52 REQUIRED)
	IF( NOT LUA52_FOUND )
		MESSAGE(FATAL_ERROR "LUA Library not found!")
	ENDIF( NOT LUA52_FOUND )
	MODUSE_SUMMARY(LUA               "LUA has ${LUA_LIBRARY}" ON MSVC)
ENDIF(USE_LUA)

IF(USE_NLS)
# --------- Native Language Support (NLS) -------------

#if(${${_prj_name}_NLS})
	FIND_PROGRAM(PYTHON_EXECUTABLE python HINTS ${GNUWIN32_DIR}/bin/python)
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
ENDIF(USE_NLS)

IF(CHECK_STRINGS)
	#SET(HAVE_WCHAR_T 1)
	INCLUDE (CheckTypeSize)
	SET(CMAKE_EXTRA_INCLUDE_FILES wchar.h)
	CHECK_TYPE_SIZE(wchar_t SIZEOF_WCHAR_T)
	IF(SIZEOF_WCHAR_T)
		SET(HAVE_WCHAR_T 1)
	ENDIF()
ENDIF(CHECK_STRINGS)

#ADD_DEFINITIONS("-DPACKAGE=${PACKAGE}")

# \Todo: USE_PERL ... usw hier entweder zuruecksetzen oder alles in richtung
# ${PROJECT_NAME}_USES_PERL umbauen ... Die defines dann auch 
#MESSAGE(FATAL_ERROR "DEPP ${PROJECT_NAME}_USES_PERL")
#SET(USE_PERL )
#...
#SET(CHECK_STRINGS )
# Besser wird es sein den PROJECT_NAME Ansatz zu nehmen, da die Variablen sonnst
# f\FCr den Aufrufer verloren sind.

IF(USE_MAGICK)
	FIND_PACKAGE(ImageMagick)
	IF( NOT ImageMagick_FOUND )
#		MESSAGE(FATAL_ERROR "SDL_image Library not found!")
	ENDIF( NOT ImageMagick_FOUND )
	MODUSE_SUMMARY(ImageMagick_EXE               "at ${ImageMagick_EXECUTABLE_DIR}" USE ALL)
ENDIF(USE_MAGICK)

IF(USE_INKSCAPE)
	FIND_PROGRAM(INKSCAPE_EXECUTABLE
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
	IF( INKSCAPE_EXECUTABLE )
#		MESSAGE(FATAL_ERROR "SDL_image Library not found!")
		MESSAGE(STATUS "Inkscape_executable found: ${INKSCAPE_EXECUTABLE}")
		SET(INKSCAPE_EXECUTABLE_FOUND TRUE)
	ELSE()
		MESSAGE(WARNING "Inkscape executable not found.")
	ENDIF()
	MODUSE_SUMMARY(Inkscape_EXE               "at ${INKSCAPE_EXECUTABLE}" USE ALL)
ENDIF(USE_INKSCAPE)

