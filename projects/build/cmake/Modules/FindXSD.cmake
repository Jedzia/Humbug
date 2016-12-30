# - Find CodeSource Xsd
# 23.11.2010, Jedzia
# This module can be used to find Xsd and it's include path
# Variables:
#       XSD_EXECUTABLE
#       XSD_INCLUDE_DIR
#       XSD_FOUND
# Only for Windows. Please check  msys/unix/etc. and send your changes
# to jed69@gmx.de :)
# \Todo: This need a(variable) tidy-up.

set(XERCES_BASE xerces-c)
set(XERCES_NAME ${XERCES_BASE}-3.1)
set(XERCES_LINKLIB ${XERCES_BASE}_3)

if(NOT XSD_LIBRARY_DIR OR NOT XSD_INCLUDE_DIR OR NOT XSD_EXECUTABLE OR NOT XSD_DIR OR NOT Xsd_ROOT)
        set(XSD_FOUND FALSE)
        set(XSD_LIBRARY_FOUND FALSE CACHE INTERNAL BOOL)
        #set(XSD_LIBRARY_DIR "" CACHE PATH "xsd library path")
        if(XSD_LIBRARY_DIR STREQUAL  "xsd-library-NOTFOUND")
          # set(XSD_LIBRARY_DIR "")
        endif()
endif()

set(xsd_local_root $ENV{XSD_ROOTDIR})
#message( FATAL_ERROR " xsd_local_root=${xsd_local_root}" )
if(EXISTS "${xsd_local_root}" AND NOT $ENV{XSD_ROOTDIR})
    set(Xsd_ROOT $ENV{XSD_ROOTDIR} CACHE PATH "XSD root directory.")
endif()

#set(Xsd_ROOT "C:/Program Files/CodeSynthesis XSD 3.3" CACHE PATH "fuck you")
#
#set(XSD_FOUND FALSE)

if(WIN32)
        set(__XSD_NAME xsd.exe)
else(WIN32)
        set(__XSD_NAME xsdcxx)
endif(WIN32)

#if(XSD_LIBRARY_FOUND)
if(XSD_LIBRARY_FOUND)
        #in cache already
        set(XSD_FOUND TRUE)
else()

	if(NOT Xsd_ROOT)
		find_path(Xsd_ROOT NAMES bin/${__XSD_NAME}
		    PATHS
			/usr
			/usr/local
			"C:/Program Files/CodeSynthesis XSD 3.3"
		)
	endif()        
        set(XSD_DIR ${Xsd_ROOT} CACHE PATH "XSD root directory." FORCE)
        mark_as_advanced(XSD_DIR)

#message( FATAL_ERROR " XSD_DIR=${XSD_DIR}" )
        find_file(XSD_EXECUTABLE NAMES ${__XSD_NAME}
             PATHS
                 ${XSD_DIR}/bin
                /usr/bin
                /usr/local/bin
                "C:/Program Files/CodeSynthesis XSD 3.3/bin"
        NO_DEFAULT_PATH
        )

        if(XSD_EXECUTABLE)
               # set(XSD_FOUND TRUE)
        else(XSD_EXECUTABLE)
                set(XSD_EXECUTABLE "xsd-NOTFOUND" CACHE FILE "xsd executable path")
        endif(XSD_EXECUTABLE)

        if(WIN32)
        find_path(XSD_INCLUDE_DIR NAMES xsd
            PATHS
                ${XSD_DIR}/include
                /usr/include
                /usr/local/include
                "C:/Program Files/CodeSynthesis XSD 3.3/include"

        )
        else(WIN32)
        find_path(XSD_INCLUDE_DIR NAMES xsd/cxx
            PATHS
                ${XSD_DIR}/include
                /usr/include
                /usr/local/include

        )
        endif(WIN32)
        mark_as_advanced(XSD_INCLUDE_DIR)

        if(XSD_INCLUDE_DIR)
             #   set(XSD_FOUND TRUE)
        else(XSD_INCLUDE_DIR)
                set(XSD_INCLUDE_DIR "xsd-include-NOTFOUND" CACHE PATH "xsd include path")
        endif(XSD_INCLUDE_DIR)

		if(WIN32)
			set(XSD_LIBNAME "${XERCES_BASE}_3.lib" )
			#message( "MSVC_VERSION ${MSVC_VERSION}")
			if(MSVC80)
				set(XSD_COMPILER_SUFFIX "vc-8.0" )
				set(XSD_DLL_SUFFIX "vc80" )
			elseif(MSVC90)
				set(XSD_COMPILER_SUFFIX "vc-9.0" )
				set(XSD_DLL_SUFFIX "vc90" )
			elseif(MSVC10)
				set(XSD_COMPILER_SUFFIX "vc-10.0" )
				set(XSD_DLL_SUFFIX "vc100" )
			endif()
		else(WIN32)
			#libxerces-c-3.1.so
			set(XSD_LIBNAME "lib${XERCES_BASE}.la" )
			set(XSD_DLL_SUFFIX "" )
		endif(WIN32)

		if(CMAKE_SIZEOF_VOID_P EQUAL 8)
			# x64
			set(XSD_LIB_64_Searchpath ${XSD_DIR}/lib64/${XSD_COMPILER_SUFFIX})
		endif()
		
        find_path(XSD_LIBRARY_DIR NAMES ${XSD_LIBNAME}
            PATHS
                ${XSD_LIB_64_Searchpath}
                ${XSD_DIR}/lib/${XSD_COMPILER_SUFFIX}
                /usr/lib
                /usr/local/lib
                #"C:/Program Files/CodeSynthesis XSD 3.3/lib/${XSD_COMPILER_SUFFIX}"
                NO_DEFAULT_PATH
        )
        mark_as_advanced(XSD_LIBRARY_DIR)

#find dlls
	if(WIN32)
		set(__XSD_DLL_NAME ${XERCES_BASE}_3_1)
		set(__XSD_DLL_DEBUG_NAME "${__XSD_DLL_NAME}D_${XSD_DLL_SUFFIX}.dll")
		set(__XSD_DLL_RELEASE_NAME "${__XSD_DLL_NAME}_${XSD_DLL_SUFFIX}.dll")
	else(WIN32)

		set(__XSD_DLL_NAME lib${XERCES_NAME})
		#set(__XSD_DLL_NAME libxerces-c-3.1)
		set(__XSD_DLL_DEBUG_NAME "${__XSD_DLL_NAME}.so")
		set(__XSD_DLL_RELEASE_NAME "${__XSD_DLL_NAME}.so")
	endif(WIN32)

	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		# x64
		set(XSD_DLL_64_Searchpath ${XSD_DIR}/bin64)
	endif()

	find_file(XSD_DLL_DEBUG NAMES ${__XSD_DLL_DEBUG_NAME}
		 PATHS
			${XSD_DLL_64_Searchpath}
			${XSD_DIR}/bin
			${XSD_LIBRARY_DIR}
			/usr/bin
			/usr/local/bin
			"C:/Program Files/CodeSynthesis XSD 3.3/bin"
	NO_DEFAULT_PATH
	)

        find_file(XSD_DLL_RELEASE NAMES ${__XSD_DLL_RELEASE_NAME}
             PATHS
   			    ${XSD_DLL_64_Searchpath}
                ${XSD_DIR}/bin
				${XSD_LIBRARY_DIR}
                /usr/bin
                /usr/local/bin
                "C:/Program Files/CodeSynthesis XSD 3.3/bin"
        NO_DEFAULT_PATH
        )


	if(WIN32)
		find_library(XSD_LIBRARY_RELEASE NAMES ${XERCES_LINKLIB} PATHS ${XSD_LIBRARY_DIR} NO_DEFAULT_PATH)
		find_library(XSD_LIBRARY_DEBUG NAMES ${XERCES_LINKLIB}d PATHS ${XSD_LIBRARY_DIR} NO_DEFAULT_PATH)
	else(WIN32)
		find_library(XSD_LIBRARY_RELEASE NAMES ${XERCES_NAME} PATHS ${XSD_LIBRARY_DIR} NO_DEFAULT_PATH)
		find_library(XSD_LIBRARY_DEBUG NAMES ${XERCES_NAME} PATHS ${XSD_LIBRARY_DIR} NO_DEFAULT_PATH)
		#find_library(XSD_LIBRARY_RELEASE NAMES xerces-c-3.1 PATHS ${XSD_LIBRARY_DIR} NO_DEFAULT_PATH)
		#find_library(XSD_LIBRARY_DEBUG NAMES xerces-c_3d PATHS ${XSD_LIBRARY_DIR} NO_DEFAULT_PATH)
	endif(WIN32)
        set(XSD_LIBRARY_RELEASE ${XSD_LIBRARY_RELEASE} CACHE PATH "xsd release lib")
        set(XSD_LIBRARY_DEBUG ${XSD_LIBRARY_DEBUG} CACHE PATH "xsd debug lib")
        set(XSD_LIBRARY optimized ${XSD_LIBRARY_RELEASE} debug ${XSD_LIBRARY_DEBUG} CACHE STRING "xsd library" FORCE)
        mark_as_advanced(XSD_DLL_RELEASE)
        mark_as_advanced(XSD_DLL_DEBUG)
        mark_as_advanced(XSD_LIBRARY_RELEASE)
        mark_as_advanced(XSD_LIBRARY_DEBUG)
        mark_as_advanced(XSD_LIBRARY)

                #message( FUCKING XSD_LIBRARY_DIR ${XSD_LIBRARY_DIR})
                #message( XSD_LIBRARY_RELEASE ${XSD_LIBRARY_RELEASE})
                #message( XSD_LIBRARY_DEBUG ${XSD_LIBRARY_DEBUG})

                #if(XSD_LIBRARY_DIR)
                #        set(XSD_FOUND TRUE)
                #else(XSD_LIBRARY_DIR)
                #        set(XSD_LIBRARY_DIR "xsd-library-NOTFOUND" CACHE PATH "xsd library path" )
                #endif(XSD_LIBRARY_DIR)

                if(XSD_LIBRARY_DIR AND XSD_INCLUDE_DIR AND XSD_EXECUTABLE AND XSD_LIBRARY_RELEASE)
                        set(XSD_FOUND TRUE )
                        set(XSD_LIBRARY_FOUND TRUE CACHE INTERNAL BOOL FORCE)
                endif(XSD_LIBRARY_DIR AND XSD_INCLUDE_DIR AND XSD_EXECUTABLE AND XSD_LIBRARY_RELEASE)


if( NOT XSD_FOUND)
    if(XSD_FIND_REQUIRED)
      message( FATAL_ERROR "Could NOT find XSD LIBRARY")
    endif(XSD_FIND_REQUIRED)
  endif( NOT XSD_FOUND)

endif()



function(XSD_EXTRACT_OPTIONS _xsd_files _xsd_options)
        foreach(current_arg ${ARGN})
                if(${current_arg} STREQUAL "OPTIONS")
                        set(_XSD_DOING_OPTIONS TRUE)
                else(${current_arg} STREQUAL "OPTIONS")
                        if(_XSD_DOING_OPTIONS)
                                set(_xsd_options_p ${_xsd_options_p} ${current_arg})
                        else(_XSD_DOING_OPTIONS)
                                set(_xsd_files_p ${_xsd_files_p} ${current_arg})
                        endif(_XSD_DOING_OPTIONS)
                endif(${current_arg} STREQUAL "OPTIONS")
        endforeach(current_arg)
        set(${_xsd_files} ${_xsd_files_p} PARENT_SCOPE)
        set(${_xsd_options} ${_xsd_options_p} PARENT_SCOPE)
endfunction(XSD_EXTRACT_OPTIONS)

# http://www.codesynthesis.com/projects/xsd/documentation/xsd.xhtml
# http://wiki.codesynthesis.com/XSD
function(WRAP_XSD XSD_SRCS XSD_INCLUDES OUT_PATH)
        set(OUTPUT_DIR  ${OUT_PATH}/src/xsd)
        file(MAKE_DIRECTORY ${OUTPUT_DIR})
        set(${XSD_INCLUDES} ${OUTPUT_DIR} PARENT_SCOPE)
        XSD_EXTRACT_OPTIONS(xsd_files xsd_options ${ARGN})
        foreach(it ${xsd_files})
                string(REGEX REPLACE ".*/" "" BARE_XSD "${it}" )
                string(REGEX REPLACE ".xsd" ".cxx" SOURCE "${BARE_XSD}" )
                string(REGEX REPLACE ".xsd" ".hxx" HEADER "${BARE_XSD}" )
                configure_file(${it} ${OUT_PATH}/${BARE_XSD} COPY_ONLY)
                set(SOURCE ${OUTPUT_DIR}/${SOURCE})
                set(HEADER ${OUTPUT_DIR}/${HEADER})
# --cxx-suffix suffix
# Use the provided suffix instead of the default .cxx to construct the name of the source file.
# --hxx-suffix suffix
                add_custom_command(OUTPUT ${SOURCE} ${HEADER}
                                COMMAND ${XSD_EXECUTABLE} ${xsd_options} "--output-dir" ${OUTPUT_DIR} ${OUT_PATH}/${BARE_XSD}
                                DEPENDS ${it}
                                VERBATIM
                )
#message(STATUS "XSD SOURCE: ${SOURCE} ")
                set_source_files_properties(${HEADER} PROPERTIES GENERATED TRUE)
                set_source_files_properties(${SOURCE} PROPERTIES GENERATED TRUE)
                set(_XSD_SRCS ${_XSD_SRCS} ${SOURCE} ${HEADER})
        endforeach(it)
        set(${XSD_SRCS} ${_XSD_SRCS} PARENT_SCOPE)
endfunction(WRAP_XSD)

