
#set(_HELPER_COPY_ENABLED (${WIN32} AND NOT ${MINGW}))
set(_HELPER_COPY_ENABLED FALSE)
if(MSVC)
	set(_HELPER_COPY_ENABLED TRUE)
endif()

if(NOT HELPERS_COPY_CMAKE_DEBUG)
	set(HELPERS_COPY_CMAKE_DEBUG OFF)
endif()

if(HELPERS_COPY_CMAKE_DEBUG)
	set(_HELPERS_COPY_CMAKE_DEBUG_STR "--debug-output")
endif()

macro(Copy_DLL_To_Target target libname)
if(_HELPER_COPY_ENABLED)
	add_custom_command(
		TARGET ${target} 
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} ${_HELPERS_COPY_CMAKE_DEBUG_STR} -Dconfig=${CMAKE_CFG_INTDIR} -Dtgt="${PROJECT_BINARY_DIR}/" -Dreleasesrc="${${libname}_DLL_RELEASE}" -Ddebugsrc="${${libname}_DLL_DEBUG}" -P "${P_MODULE_PATH}/copy.cmake"
		DEPENDS Templater
		COMMENT "Copy ${libname} DLL." 
	)
endif(_HELPER_COPY_ENABLED)
endmacro()

macro(Copy_ReleaseDLL_To_Target target libname)
if(_HELPER_COPY_ENABLED)
	add_custom_command(
		TARGET ${target} 
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} ${_HELPERS_COPY_CMAKE_DEBUG_STR} -Dconfig=${CMAKE_CFG_INTDIR} -Dtgt="${PROJECT_BINARY_DIR}/" -Dreleasesrc="${${libname}_DLL_RELEASE}" -Ddebugsrc="${${libname}_DLL_RELEASE}" -P "${P_MODULE_PATH}/copy.cmake"
		DEPENDS Templater
		COMMENT "Copy ${libname} DLL." 
	)
endif(_HELPER_COPY_ENABLED)
endmacro()

macro(Copy_DebugDLL_To_Target target libname)
if(_HELPER_COPY_ENABLED)
	add_custom_command(
		TARGET ${target} 
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} ${_HELPERS_COPY_CMAKE_DEBUG_STR} -Dconfig=${CMAKE_CFG_INTDIR} -Dtgt="${PROJECT_BINARY_DIR}/" -Dreleasesrc="${${libname}_DLL_DEBUG}" -Ddebugsrc="${${libname}_DLL_DEBUG}" -P "${P_MODULE_PATH}/copy.cmake"
		DEPENDS Templater
		COMMENT "Copy ${libname} DLL." 
	)
endif(_HELPER_COPY_ENABLED)
endmacro()

macro(Copy_Files_To_Target target files)
if(_HELPER_COPY_ENABLED)
	foreach(f ${files})
		Copy_File_To_Target(${target} ${f})
	endforeach()
endif(_HELPER_COPY_ENABLED)
endmacro()

macro(Copy_File_To_Target target file)
if(_HELPER_COPY_ENABLED)
	add_custom_command(
		TARGET ${target} 
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} ${_HELPERS_COPY_CMAKE_DEBUG_STR} -Dconfig=${CMAKE_CFG_INTDIR} -Dtgt="${PROJECT_BINARY_DIR}/" -Dreleasesrc="${file}" -Ddebugsrc="${file}" -P "${P_MODULE_PATH}/copy.cmake"
		DEPENDS Templater
		COMMENT "Copy ${libname} DLL." 
	)
endif(_HELPER_COPY_ENABLED)
endmacro()

macro(Copy_Boost_DLL_To_Target target libname)
if(_HELPER_COPY_ENABLED)
	set(_boost_my_lib ${libname})
    string(TOUPPER ${_boost_my_lib} UPPERCOMPONENT)
    set(BoostDebugLibPath ${Boost_${UPPERCOMPONENT}_LIBRARY_DEBUG})
    set(BoostReleaseLibPath ${Boost_${UPPERCOMPONENT}_LIBRARY_RELEASE})
    get_filename_component(_boost_my_lib_path  ${BoostDebugLibPath} PATH)
    get_filename_component(_boost_my_lib_name  ${BoostDebugLibPath} NAME_WE)
    set(_boost_my_debugdll "${_boost_my_lib_path}/${_boost_my_lib_name}.dll")
    get_filename_component(_boost_my_lib_path  ${BoostReleaseLibPath} PATH)
    get_filename_component(_boost_my_lib_name  ${BoostReleaseLibPath} NAME_WE)
    set(_boost_my_releasedll "${_boost_my_lib_path}/${_boost_my_lib_name}.dll")

	# Boost_*_DLL checking.
    #set(Boost_${UPPERCOMPONENT}_DLL_DEBUG ${_boost_my_debugdll} CACHE PATH "boost ${_boost_my_lib} debug dll.")
    #set(Boost_${UPPERCOMPONENT}_DLL_RELEASE ${_boost_my_releasedll} CACHE PATH "boost ${_boost_my_lib} release dll.")
	#mark_as_advanced(Boost_${UPPERCOMPONENT}_DLL_DEBUG)
	#mark_as_advanced(Boost_${UPPERCOMPONENT}_DLL_RELEASE)
	
	set(tgt "${PROJECT_BINARY_DIR}/")
	add_custom_command(
		TARGET ${target} 
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} ${_HELPERS_COPY_CMAKE_DEBUG_STR} -Dconfig=${CMAKE_CFG_INTDIR} -Dtgt=${tgt} -Dreleasesrc=${_boost_my_releasedll} -Ddebugsrc=${_boost_my_debugdll} -P "${CMAKE_SOURCE_DIR}/build/cmake/Modules/copy.cmake"
		COMMENT "source copy dlls and essential files" 
	)
endif(_HELPER_COPY_ENABLED)
endmacro()
