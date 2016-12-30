# BoostExtensions.cmake											   16:27 17.11.2010
# Auto link and copy boost dlls to executable dirs macro.
# by Jedzia (c) 2010
#
# Call with:
# ---------------------------------------------------------------------------------
# In a higher level CMakeLists.txt File:
#
# set(USE_Boost_COMPONENTS "system;filesystem;signals")
# find_package( Boost 1.44.0 REQUIRED COMPONENTS ${USE_Boost_COMPONENTS} )
# *****
# 
# In the project level CMakeLists.txt File:
#
# set(executable_Boost_Libraries 
#  "filesystem;system"
# )
# add_executable(executable simple_ls.cpp)
# TargetLinkBoost(executable "${executable_Boost_Libraries}")
#
# ---------------------------------------------------------------------------------
# The libs are checked if present and then added with TARGET_LINK_LIBRARIES and
# a POST_BUILD Event is attached to each library. The event copies the necessary 
# boost dll's to the output directory of each executable.
#
# ---------------------------------------------------------------------------------


if(NOT BOOSTEXTENSIONS_CMAKE_DEBUG)
	set(BOOSTEXTENSIONS_CMAKE_DEBUG OFF)
endif()

macro(TargetLinkBoost target liblist)

include_directories(${Boost_INCLUDE_DIRS})
foreach(_boost_my_lib ${liblist})
        string(TOUPPER ${_boost_my_lib} UPPERCOMPONENT)
        if ( "${Boost_${UPPERCOMPONENT}_LIBRARY}" STREQUAL "" )
          message( FATAL_ERROR "${target}: Boost Library ${_boost_my_lib} is not known!")
        endif ()
        target_link_libraries(${target} ${Boost_${UPPERCOMPONENT}_LIBRARY})
        
		if(BOOSTEXTENSIONS_CMAKE_DEBUG)
			message( STATUS "linking ${target} to  ${Boost_${UPPERCOMPONENT}_LIBRARY}")
		endif()
endforeach()


if(TRUE)

# Copy these files to the build tree.
# We cannot determine whether Release or Debug is being used.
#if(TARGET CopyDllCfg)
#else()
#add_custom_target(CopyDllCfg ALL echo "Copying dlls and essential files ...")
#endif()
message(STATUS ">>>>>>>>>>>>>>>>>>>> CMAKE_CFG_INTDIR is ${CMAKE_CFG_INTDIR}")

#if((CMAKE_CFG_INTDIR STREQUAL "Debug") OR (CMAKE_CFG_INTDIR STREQUAL "Release"))
	set(BOOSTCOPY_CMAKE_CFG_INTDIR ${CMAKE_CFG_INTDIR})
	set(BOOSTCOPY_CMAKE_NO_INTDIR )
#else()
#	set(BOOSTCOPY_CMAKE_CFG_INTDIR ${CMAKE_BUILD_TYPE})
#	set(BOOSTCOPY_CMAKE_NO_INTDIR TRUE)
#endif()

#foreach(_boost_my_lib ${USE_Boost_COMPONENTS})
#foreach(_boost_my_lib ${foo_Boost_Libraries})
foreach(_boost_my_lib ${liblist})
    string(TOUPPER ${_boost_my_lib} UPPERCOMPONENT)
    #set(BoostDebugLibPath "Boost_${UPPERCOMPONENT}_LIBRARY")
    set(BoostDebugLibPath ${Boost_${UPPERCOMPONENT}_LIBRARY_DEBUG})
    set(BoostReleaseLibPath ${Boost_${UPPERCOMPONENT}_LIBRARY_RELEASE})
    #get_filename_component(_boost_my_lib_path  ${Boost_${UPPERCOMPONENT}_LIBRARY} PATH)
    #list(APPEND Boost_LIBRARY_DIRS ${_boost_my_lib_path})
    #message( WARNING "lib:  ${BoostDebugLibPath}")
    get_filename_component(_boost_my_lib_path  ${BoostDebugLibPath} PATH)
    get_filename_component(_boost_my_lib_name  ${BoostDebugLibPath} NAME_WE)
    #message( WARNING "path:  ${_boost_my_lib_path} name: ${_boost_my_lib_name}")
    set(_boost_my_debugdll "${_boost_my_lib_path}/${_boost_my_lib_name}.dll")
    #message( STATUS "dll:  ${_boost_my_debugdll}")
    get_filename_component(_boost_my_lib_path  ${BoostReleaseLibPath} PATH)
    get_filename_component(_boost_my_lib_name  ${BoostReleaseLibPath} NAME_WE)
    set(_boost_my_releasedll "${_boost_my_lib_path}/${_boost_my_lib_name}.dll")

	# Boost_*_DLL checking.
    #set(Boost_${UPPERCOMPONENT}_DLL_DEBUG ${_boost_my_debugdll} CACHE PATH "boost ${_boost_my_lib} debug dll.")
    #set(Boost_${UPPERCOMPONENT}_DLL_RELEASE ${_boost_my_releasedll} CACHE PATH "boost ${_boost_my_lib} release dll.")
	#mark_as_advanced(Boost_${UPPERCOMPONENT}_DLL_DEBUG)
	#mark_as_advanced(Boost_${UPPERCOMPONENT}_DLL_RELEASE)
	
	# message( STATUS "${CMAKE_COMMAND} -Dconfig=${BOOSTCOPY_CMAKE_CFG_INTDIR} -P ${CMAKE_SOURCE_DIR}/build/cmake/Modules/copy.cmake")
	set(file ${_boost_my_debugdll})
	#  foreach(file ${ESSENTIAL_FILES_DEBUG})
	# get_filename_component(fn ${file} NAME)
	#set(tgt ${CMAKE_BINARY_DIR})
	set(tgt "${PROJECT_BINARY_DIR}/")
	set(src ${file})
	# message( STATUS "XXXXXXXX tgt: ${tgt}      src: ${src}")
	# message( STATUS "XXXXXXXX _boost_my_lib: ${_boost_my_lib}      src: ${src}")
	if(WIN32)
	add_custom_command(
	#   TARGET CopyDllCfg POST_BUILD
	TARGET ${target} 
	POST_BUILD
	#COMMAND ${CMAKE_COMMAND}
	COMMAND ${CMAKE_COMMAND} --debug-output -Dno_intdir=${BOOSTCOPY_CMAKE_NO_INTDIR} -Dconfig=${BOOSTCOPY_CMAKE_CFG_INTDIR} -Dtgt=${tgt} -Dreleasesrc=${_boost_my_releasedll} -Ddebugsrc=${_boost_my_debugdll} -P "${CMAKE_SOURCE_DIR}/build/cmake/Modules/copy.cmake"
		#   ARGS -E copy_if_different ${src} ${tgt}
		#   WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/build/cmake/Modules"
		COMMENT "Copy Boost ${UPPERCOMPONENT} dll to ${target}" 
	)

	install(FILES 
			${_boost_my_releasedll}
		DESTINATION bin
		COMPONENT Boost
	)
		
	#  endforeach(file)
	endif(WIN32)

	if(FALSE)
	set(file ${_boost_my_releasedll})
	#  foreach(file ${ESSENTIAL_FILES_DEBUG})
	# get_filename_component(fn ${file} NAME)
	#set(tgt ${CMAKE_BINARY_DIR})
	set(tgt "${PROJECT_BINARY_DIR}/Release/")
	set(src ${file})
	message( STATUS "tgt: ${tgt}      src: ${src}")
	add_custom_command(
		#   TARGET CopyDllCfg POST_BUILD
		TARGET ${target} 
		POST_BUILD
		COMMAND ${CMAKE_COMMAND}
		ARGS -E copy_if_different ${src} ${tgt}
		COMMENT "source copy dlls and essential files"
	)
	#  endforeach(file)
	endif(FALSE)


endforeach()
#list(REMOVE_DUPLICATES Boost_LIBRARY_DIRS)

endif()



endmacro()


