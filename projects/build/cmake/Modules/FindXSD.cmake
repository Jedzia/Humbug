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

SET(XERCES_BASE xerces-c)
SET(XERCES_NAME ${XERCES_BASE}-3.1)
SET(XERCES_LINKLIB ${XERCES_BASE}_3)

if(NOT XSD_LIBRARY_DIR OR NOT XSD_INCLUDE_DIR OR NOT XSD_EXECUTABLE OR NOT XSD_DIR OR NOT Xsd_ROOT)
        SET(XSD_FOUND FALSE)
        SET(XSD_LIBRARY_FOUND FALSE CACHE INTERNAL BOOL)
        #SET(XSD_LIBRARY_DIR "" CACHE PATH "xsd library path")
        IF(XSD_LIBRARY_DIR STREQUAL  "xsd-library-NOTFOUND")
          # SET(XSD_LIBRARY_DIR "")
        ENDIF()
endif()

SET(xsd_local_root $ENV{XSD_ROOTDIR})
#MESSAGE( FATAL_ERROR " xsd_local_root=${xsd_local_root}" )
IF(EXISTS "${xsd_local_root}" AND NOT $ENV{XSD_ROOTDIR})
    SET(Xsd_ROOT $ENV{XSD_ROOTDIR} CACHE PATH "XSD root directory.")
ENDIF()

#SET(Xsd_ROOT "C:/Program Files/CodeSynthesis XSD 3.3" CACHE PATH "fuck you")
#
#SET(XSD_FOUND FALSE)

if(WIN32)
        SET(__XSD_NAME xsd.exe)
else(WIN32)
        SET(__XSD_NAME xsdcxx)
endif(WIN32)

#if(XSD_LIBRARY_FOUND)
if(XSD_LIBRARY_FOUND)
        #in cache already
        SET(XSD_FOUND TRUE)
else()

	IF(NOT Xsd_ROOT)
		find_path(Xsd_ROOT NAMES bin/${__XSD_NAME}
		    PATHS
			/usr
			/usr/local
			"C:/Program Files/CodeSynthesis XSD 3.3"
		)
	ENDIF()        
        SET(XSD_DIR ${Xsd_ROOT} CACHE PATH "XSD root directory." FORCE)
        MARK_AS_ADVANCED(XSD_DIR)

#MESSAGE( FATAL_ERROR " XSD_DIR=${XSD_DIR}" )
        find_file(XSD_EXECUTABLE NAMES ${__XSD_NAME}
             PATHS
                 ${XSD_DIR}/bin
                /usr/bin
                /usr/local/bin
                "C:/Program Files/CodeSynthesis XSD 3.3/bin"
        NO_DEFAULT_PATH
        )

        if(XSD_EXECUTABLE)
               # SET(XSD_FOUND TRUE)
        else(XSD_EXECUTABLE)
                SET(XSD_EXECUTABLE "xsd-NOTFOUND" CACHE FILE "xsd executable path")
        endif(XSD_EXECUTABLE)

        IF(WIN32)
        find_path(XSD_INCLUDE_DIR NAMES xsd
            PATHS
                ${XSD_DIR}/include
                /usr/include
                /usr/local/include
                "C:/Program Files/CodeSynthesis XSD 3.3/include"

        )
        ELSE(WIN32)
        find_path(XSD_INCLUDE_DIR NAMES xsd/cxx
            PATHS
                ${XSD_DIR}/include
                /usr/include
                /usr/local/include

        )
        ENDIF(WIN32)
        MARK_AS_ADVANCED(XSD_INCLUDE_DIR)

        if(XSD_INCLUDE_DIR)
             #   SET(XSD_FOUND TRUE)
        else(XSD_INCLUDE_DIR)
                SET(XSD_INCLUDE_DIR "xsd-include-NOTFOUND" CACHE PATH "xsd include path")
        endif(XSD_INCLUDE_DIR)

		IF(WIN32)
			SET(XSD_LIBNAME "${XERCES_BASE}_3.lib" )
			#MESSAGE( "MSVC_VERSION ${MSVC_VERSION}")
			IF(MSVC80)
				SET(XSD_COMPILER_SUFFIX "vc-8.0" )
				SET(XSD_DLL_SUFFIX "vc80" )
			ELSEIF(MSVC90)
				SET(XSD_COMPILER_SUFFIX "vc-9.0" )
				SET(XSD_DLL_SUFFIX "vc90" )
			ELSEIF(MSVC10)
				SET(XSD_COMPILER_SUFFIX "vc-10.0" )
				SET(XSD_DLL_SUFFIX "vc100" )
			ENDIF()
		ELSE(WIN32)
			#libxerces-c-3.1.so
			SET(XSD_LIBNAME "lib${XERCES_BASE}.la" )
			SET(XSD_DLL_SUFFIX "" )
		ENDIF(WIN32)

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
        MARK_AS_ADVANCED(XSD_LIBRARY_DIR)

#find dlls
	IF(WIN32)
		SET(__XSD_DLL_NAME ${XERCES_BASE}_3_1)
		SET(__XSD_DLL_DEBUG_NAME "${__XSD_DLL_NAME}D_${XSD_DLL_SUFFIX}.dll")
		SET(__XSD_DLL_RELEASE_NAME "${__XSD_DLL_NAME}_${XSD_DLL_SUFFIX}.dll")
	ELSE(WIN32)

		SET(__XSD_DLL_NAME lib${XERCES_NAME})
		#SET(__XSD_DLL_NAME libxerces-c-3.1)
		SET(__XSD_DLL_DEBUG_NAME "${__XSD_DLL_NAME}.so")
		SET(__XSD_DLL_RELEASE_NAME "${__XSD_DLL_NAME}.so")
	ENDIF(WIN32)

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


	IF(WIN32)
		FIND_LIBRARY(XSD_LIBRARY_RELEASE NAMES ${XERCES_LINKLIB} PATHS ${XSD_LIBRARY_DIR} NO_DEFAULT_PATH)
		FIND_LIBRARY(XSD_LIBRARY_DEBUG NAMES ${XERCES_LINKLIB}d PATHS ${XSD_LIBRARY_DIR} NO_DEFAULT_PATH)
	ELSE(WIN32)
		FIND_LIBRARY(XSD_LIBRARY_RELEASE NAMES ${XERCES_NAME} PATHS ${XSD_LIBRARY_DIR} NO_DEFAULT_PATH)
		FIND_LIBRARY(XSD_LIBRARY_DEBUG NAMES ${XERCES_NAME} PATHS ${XSD_LIBRARY_DIR} NO_DEFAULT_PATH)
		#FIND_LIBRARY(XSD_LIBRARY_RELEASE NAMES xerces-c-3.1 PATHS ${XSD_LIBRARY_DIR} NO_DEFAULT_PATH)
		#FIND_LIBRARY(XSD_LIBRARY_DEBUG NAMES xerces-c_3d PATHS ${XSD_LIBRARY_DIR} NO_DEFAULT_PATH)
	ENDIF(WIN32)
        SET(XSD_LIBRARY_RELEASE ${XSD_LIBRARY_RELEASE} CACHE PATH "xsd release lib")
        SET(XSD_LIBRARY_DEBUG ${XSD_LIBRARY_DEBUG} CACHE PATH "xsd debug lib")
        SET(XSD_LIBRARY optimized ${XSD_LIBRARY_RELEASE} debug ${XSD_LIBRARY_DEBUG} CACHE STRING "xsd library" FORCE)
        MARK_AS_ADVANCED(XSD_DLL_RELEASE)
        MARK_AS_ADVANCED(XSD_DLL_DEBUG)
        MARK_AS_ADVANCED(XSD_LIBRARY_RELEASE)
        MARK_AS_ADVANCED(XSD_LIBRARY_DEBUG)
        MARK_AS_ADVANCED(XSD_LIBRARY)

                #MESSAGE( FUCKING XSD_LIBRARY_DIR ${XSD_LIBRARY_DIR})
                #MESSAGE( XSD_LIBRARY_RELEASE ${XSD_LIBRARY_RELEASE})
                #MESSAGE( XSD_LIBRARY_DEBUG ${XSD_LIBRARY_DEBUG})

                #if(XSD_LIBRARY_DIR)
                #        SET(XSD_FOUND TRUE)
                #else(XSD_LIBRARY_DIR)
                #        SET(XSD_LIBRARY_DIR "xsd-library-NOTFOUND" CACHE PATH "xsd library path" )
                #endif(XSD_LIBRARY_DIR)

                if(XSD_LIBRARY_DIR AND XSD_INCLUDE_DIR AND XSD_EXECUTABLE AND XSD_LIBRARY_RELEASE)
                        SET(XSD_FOUND TRUE )
                        SET(XSD_LIBRARY_FOUND TRUE CACHE INTERNAL BOOL FORCE)
                endif(XSD_LIBRARY_DIR AND XSD_INCLUDE_DIR AND XSD_EXECUTABLE AND XSD_LIBRARY_RELEASE)


IF( NOT XSD_FOUND)
    IF(XSD_FIND_REQUIRED)
      MESSAGE( FATAL_ERROR "Could NOT find XSD LIBRARY")
    ENDIF(XSD_FIND_REQUIRED)
  ENDIF( NOT XSD_FOUND)

endif()



FUNCTION(XSD_EXTRACT_OPTIONS _xsd_files _xsd_options)
        foreach(current_arg ${ARGN})
                IF(${current_arg} STREQUAL "OPTIONS")
                        SET(_XSD_DOING_OPTIONS TRUE)
                else(${current_arg} STREQUAL "OPTIONS")
                        if(_XSD_DOING_OPTIONS)
                                SET(_xsd_options_p ${_xsd_options_p} ${current_arg})
                        else(_XSD_DOING_OPTIONS)
                                SET(_xsd_files_p ${_xsd_files_p} ${current_arg})
                        endif(_XSD_DOING_OPTIONS)
                endif(${current_arg} STREQUAL "OPTIONS")
        endforeach(current_arg)
        SET(${_xsd_files} ${_xsd_files_p} PARENT_SCOPE)
        SET(${_xsd_options} ${_xsd_options_p} PARENT_SCOPE)
ENDFUNCTION(XSD_EXTRACT_OPTIONS)

# http://www.codesynthesis.com/projects/xsd/documentation/xsd.xhtml
# http://wiki.codesynthesis.com/XSD
FUNCTION(WRAP_XSD XSD_SRCS XSD_INCLUDES OUT_PATH)
        SET(OUTPUT_DIR  ${OUT_PATH}/src/xsd)
        FILE(MAKE_DIRECTORY ${OUTPUT_DIR})
        SET(${XSD_INCLUDES} ${OUTPUT_DIR} PARENT_SCOPE)
        XSD_EXTRACT_OPTIONS(xsd_files xsd_options ${ARGN})
        FOREACH(it ${xsd_files})
                STRING(REGEX REPLACE ".*/" "" BARE_XSD "${it}" )
                STRING(REGEX REPLACE ".xsd" ".cxx" SOURCE "${BARE_XSD}" )
                STRING(REGEX REPLACE ".xsd" ".hxx" HEADER "${BARE_XSD}" )
                CONFIGURE_FILE(${it} ${OUT_PATH}/${BARE_XSD} COPY_ONLY)
                SET(SOURCE ${OUTPUT_DIR}/${SOURCE})
                SET(HEADER ${OUTPUT_DIR}/${HEADER})
# --cxx-suffix suffix
# Use the provided suffix instead of the default .cxx to construct the name of the source file.
# --hxx-suffix suffix
                ADD_CUSTOM_COMMAND(OUTPUT ${SOURCE} ${HEADER}
                                COMMAND ${XSD_EXECUTABLE} ${xsd_options} "--output-dir" ${OUTPUT_DIR} ${OUT_PATH}/${BARE_XSD}
                                DEPENDS ${it}
                                VERBATIM
                )
#MESSAGE(STATUS "XSD SOURCE: ${SOURCE} ")
                set_source_files_properties(${HEADER} PROPERTIES GENERATED TRUE)
                set_source_files_properties(${SOURCE} PROPERTIES GENERATED TRUE)
                SET(_XSD_SRCS ${_XSD_SRCS} ${SOURCE} ${HEADER})
        ENDFOREACH(it)
        SET(${XSD_SRCS} ${_XSD_SRCS} PARENT_SCOPE)
ENDFUNCTION(WRAP_XSD)

