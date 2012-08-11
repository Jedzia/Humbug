
#SET(_HELPER_COPY_ENABLED (${WIN32} AND NOT ${MINGW}))
SET(_HELPER_COPY_ENABLED FALSE)
IF(MSVC)
	SET(_HELPER_COPY_ENABLED TRUE)
ENDIF()

IF(NOT HELPERS_COPY_CMAKE_DEBUG)
	SET(HELPERS_COPY_CMAKE_DEBUG OFF)
ENDIF()

IF(HELPERS_COPY_CMAKE_DEBUG)
	SET(_HELPERS_COPY_CMAKE_DEBUG_STR "--debug-output")
ENDIF()

MACRO(Copy_DLL_To_Target target libname)
IF(_HELPER_COPY_ENABLED)
	ADD_CUSTOM_COMMAND(
		TARGET ${target} 
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} ${_HELPERS_COPY_CMAKE_DEBUG_STR} -Dconfig=${CMAKE_CFG_INTDIR} -Dtgt="${PROJECT_BINARY_DIR}/" -Dreleasesrc="${${libname}_DLL_RELEASE}" -Ddebugsrc="${${libname}_DLL_DEBUG}" -P "${P_MODULE_PATH}/copy.cmake"
		DEPENDS Templater
		COMMENT "Copy ${libname} DLL." 
	)
ENDIF(_HELPER_COPY_ENABLED)
ENDMACRO()

MACRO(Copy_ReleaseDLL_To_Target target libname)
IF(_HELPER_COPY_ENABLED)
	ADD_CUSTOM_COMMAND(
		TARGET ${target} 
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} ${_HELPERS_COPY_CMAKE_DEBUG_STR} -Dconfig=${CMAKE_CFG_INTDIR} -Dtgt="${PROJECT_BINARY_DIR}/" -Dreleasesrc="${${libname}_DLL_RELEASE}" -Ddebugsrc="${${libname}_DLL_RELEASE}" -P "${P_MODULE_PATH}/copy.cmake"
		DEPENDS Templater
		COMMENT "Copy ${libname} DLL." 
	)
ENDIF(_HELPER_COPY_ENABLED)
ENDMACRO()

MACRO(Copy_DebugDLL_To_Target target libname)
IF(_HELPER_COPY_ENABLED)
	ADD_CUSTOM_COMMAND(
		TARGET ${target} 
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} ${_HELPERS_COPY_CMAKE_DEBUG_STR} -Dconfig=${CMAKE_CFG_INTDIR} -Dtgt="${PROJECT_BINARY_DIR}/" -Dreleasesrc="${${libname}_DLL_DEBUG}" -Ddebugsrc="${${libname}_DLL_DEBUG}" -P "${P_MODULE_PATH}/copy.cmake"
		DEPENDS Templater
		COMMENT "Copy ${libname} DLL." 
	)
ENDIF(_HELPER_COPY_ENABLED)
ENDMACRO()

MACRO(Copy_Files_To_Target target files)
IF(_HELPER_COPY_ENABLED)
	FOREACH(f ${files})
		Copy_File_To_Target(${target} ${f})
	ENDFOREACH()
ENDIF(_HELPER_COPY_ENABLED)
ENDMACRO()

MACRO(Copy_File_To_Target target file)
IF(_HELPER_COPY_ENABLED)
	ADD_CUSTOM_COMMAND(
		TARGET ${target} 
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} ${_HELPERS_COPY_CMAKE_DEBUG_STR} -Dconfig=${CMAKE_CFG_INTDIR} -Dtgt="${PROJECT_BINARY_DIR}/" -Dreleasesrc="${file}" -Ddebugsrc="${file}" -P "${P_MODULE_PATH}/copy.cmake"
		DEPENDS Templater
		COMMENT "Copy ${libname} DLL." 
	)
ENDIF(_HELPER_COPY_ENABLED)
ENDMACRO()

MACRO(Copy_Boost_DLL_To_Target target libname)
IF(_HELPER_COPY_ENABLED)
	set(_boost_my_lib ${libname})
    STRING(TOUPPER ${_boost_my_lib} UPPERCOMPONENT)
    SET(BoostDebugLibPath ${Boost_${UPPERCOMPONENT}_LIBRARY_DEBUG})
    SET(BoostReleaseLibPath ${Boost_${UPPERCOMPONENT}_LIBRARY_RELEASE})
    GET_FILENAME_COMPONENT(_boost_my_lib_path  ${BoostDebugLibPath} PATH)
    GET_FILENAME_COMPONENT(_boost_my_lib_name  ${BoostDebugLibPath} NAME_WE)
    SET(_boost_my_debugdll "${_boost_my_lib_path}/${_boost_my_lib_name}.dll")
    GET_FILENAME_COMPONENT(_boost_my_lib_path  ${BoostReleaseLibPath} PATH)
    GET_FILENAME_COMPONENT(_boost_my_lib_name  ${BoostReleaseLibPath} NAME_WE)
    SET(_boost_my_releasedll "${_boost_my_lib_path}/${_boost_my_lib_name}.dll")

	# Boost_*_DLL checking.
    #SET(Boost_${UPPERCOMPONENT}_DLL_DEBUG ${_boost_my_debugdll} CACHE PATH "boost ${_boost_my_lib} debug dll.")
    #SET(Boost_${UPPERCOMPONENT}_DLL_RELEASE ${_boost_my_releasedll} CACHE PATH "boost ${_boost_my_lib} release dll.")
	#MARK_AS_ADVANCED(Boost_${UPPERCOMPONENT}_DLL_DEBUG)
	#MARK_AS_ADVANCED(Boost_${UPPERCOMPONENT}_DLL_RELEASE)
	
	SET(tgt "${PROJECT_BINARY_DIR}/")
	ADD_CUSTOM_COMMAND(
		TARGET ${target} 
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} ${_HELPERS_COPY_CMAKE_DEBUG_STR} -Dconfig=${CMAKE_CFG_INTDIR} -Dtgt=${tgt} -Dreleasesrc=${_boost_my_releasedll} -Ddebugsrc=${_boost_my_debugdll} -P "${CMAKE_SOURCE_DIR}/build/cmake/Modules/copy.cmake"
		COMMENT "source copy dlls and essential files" 
	)
ENDIF(_HELPER_COPY_ENABLED)
ENDMACRO()
