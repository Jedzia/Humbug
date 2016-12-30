# BoostExtensions.cmake											   16:27 17.11.2010
# Auto link and copy boost dlls to executable dirs macro.
# by Jedzia (c) 2010
#
# Call with:
# ---------------------------------------------------------------------------------
# In a higher level CMakeLists.txt File:
#
# SET(USE_Boost_COMPONENTS "system;filesystem;signals")
# find_package( Boost 1.44.0 REQUIRED COMPONENTS ${USE_Boost_COMPONENTS} )
# *****
# 
# In the project level CMakeLists.txt File:
#
# SET(executable_Boost_Libraries 
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


IF(NOT BOOSTEXTENSIONS_CMAKE_DEBUG)
	SET(BOOSTEXTENSIONS_CMAKE_DEBUG OFF)
ENDIF()

MACRO(TargetLinkBoost target liblist)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
FOREACH(_boost_my_lib ${liblist})
        STRING(TOUPPER ${_boost_my_lib} UPPERCOMPONENT)
        IF ( "${Boost_${UPPERCOMPONENT}_LIBRARY}" STREQUAL "" )
          MESSAGE( FATAL_ERROR "${target}: Boost Library ${_boost_my_lib} is not known!")
        ENDIF ()
        TARGET_LINK_LIBRARIES(${target} ${Boost_${UPPERCOMPONENT}_LIBRARY})
        
		IF(BOOSTEXTENSIONS_CMAKE_DEBUG)
			MESSAGE( STATUS "linking ${target} to  ${Boost_${UPPERCOMPONENT}_LIBRARY}")
		ENDIF()
ENDFOREACH()


IF(TRUE)

# Copy these files to the build tree.
# We cannot determine whether Release or Debug is being used.
#IF(TARGET CopyDllCfg)
#ELSE()
#ADD_CUSTOM_TARGET(CopyDllCfg ALL echo "Copying dlls and essential files ...")
#ENDIF()
MESSAGE(STATUS ">>>>>>>>>>>>>>>>>>>> CMAKE_CFG_INTDIR is ${CMAKE_CFG_INTDIR}")

#IF((CMAKE_CFG_INTDIR STREQUAL "Debug") OR (CMAKE_CFG_INTDIR STREQUAL "Release"))
	SET(BOOSTCOPY_CMAKE_CFG_INTDIR ${CMAKE_CFG_INTDIR})
	SET(BOOSTCOPY_CMAKE_NO_INTDIR )
#ELSE()
#	SET(BOOSTCOPY_CMAKE_CFG_INTDIR ${CMAKE_BUILD_TYPE})
#	SET(BOOSTCOPY_CMAKE_NO_INTDIR TRUE)
#ENDIF()

#FOREACH(_boost_my_lib ${USE_Boost_COMPONENTS})
#FOREACH(_boost_my_lib ${foo_Boost_Libraries})
FOREACH(_boost_my_lib ${liblist})
    STRING(TOUPPER ${_boost_my_lib} UPPERCOMPONENT)
    #SET(BoostDebugLibPath "Boost_${UPPERCOMPONENT}_LIBRARY")
    SET(BoostDebugLibPath ${Boost_${UPPERCOMPONENT}_LIBRARY_DEBUG})
    SET(BoostReleaseLibPath ${Boost_${UPPERCOMPONENT}_LIBRARY_RELEASE})
    #GET_FILENAME_COMPONENT(_boost_my_lib_path  ${Boost_${UPPERCOMPONENT}_LIBRARY} PATH)
    #LIST(APPEND Boost_LIBRARY_DIRS ${_boost_my_lib_path})
    #MESSAGE( WARNING "lib:  ${BoostDebugLibPath}")
    GET_FILENAME_COMPONENT(_boost_my_lib_path  ${BoostDebugLibPath} PATH)
    GET_FILENAME_COMPONENT(_boost_my_lib_name  ${BoostDebugLibPath} NAME_WE)
    #MESSAGE( WARNING "path:  ${_boost_my_lib_path} name: ${_boost_my_lib_name}")
    SET(_boost_my_debugdll "${_boost_my_lib_path}/${_boost_my_lib_name}.dll")
    #MESSAGE( STATUS "dll:  ${_boost_my_debugdll}")
    GET_FILENAME_COMPONENT(_boost_my_lib_path  ${BoostReleaseLibPath} PATH)
    GET_FILENAME_COMPONENT(_boost_my_lib_name  ${BoostReleaseLibPath} NAME_WE)
    SET(_boost_my_releasedll "${_boost_my_lib_path}/${_boost_my_lib_name}.dll")

	# Boost_*_DLL checking.
    #SET(Boost_${UPPERCOMPONENT}_DLL_DEBUG ${_boost_my_debugdll} CACHE PATH "boost ${_boost_my_lib} debug dll.")
    #SET(Boost_${UPPERCOMPONENT}_DLL_RELEASE ${_boost_my_releasedll} CACHE PATH "boost ${_boost_my_lib} release dll.")
	#MARK_AS_ADVANCED(Boost_${UPPERCOMPONENT}_DLL_DEBUG)
	#MARK_AS_ADVANCED(Boost_${UPPERCOMPONENT}_DLL_RELEASE)
	
	# MESSAGE( STATUS "${CMAKE_COMMAND} -Dconfig=${BOOSTCOPY_CMAKE_CFG_INTDIR} -P ${CMAKE_SOURCE_DIR}/build/cmake/Modules/copy.cmake")
	SET(file ${_boost_my_debugdll})
	#  FOREACH(file ${ESSENTIAL_FILES_DEBUG})
	# GET_FILENAME_COMPONENT(fn ${file} NAME)
	#SET(tgt ${CMAKE_BINARY_DIR})
	SET(tgt "${PROJECT_BINARY_DIR}/")
	SET(src ${file})
	# MESSAGE( STATUS "XXXXXXXX tgt: ${tgt}      src: ${src}")
	# MESSAGE( STATUS "XXXXXXXX _boost_my_lib: ${_boost_my_lib}      src: ${src}")
	IF(WIN32)
	ADD_CUSTOM_COMMAND(
	#   TARGET CopyDllCfg POST_BUILD
	TARGET ${target} 
	POST_BUILD
	#COMMAND ${CMAKE_COMMAND}
	COMMAND ${CMAKE_COMMAND} --debug-output -Dno_intdir=${BOOSTCOPY_CMAKE_NO_INTDIR} -Dconfig=${BOOSTCOPY_CMAKE_CFG_INTDIR} -Dtgt=${tgt} -Dreleasesrc=${_boost_my_releasedll} -Ddebugsrc=${_boost_my_debugdll} -P "${CMAKE_SOURCE_DIR}/build/cmake/Modules/copy.cmake"
		#   ARGS -E copy_if_different ${src} ${tgt}
		#   WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/build/cmake/Modules"
		COMMENT "Copy Boost ${UPPERCOMPONENT} dll to ${target}" 
	)

	INSTALL(FILES 
			${_boost_my_releasedll}
		DESTINATION bin
		COMPONENT Boost
	)
		
	#  ENDFOREACH(file)
	ENDIF(WIN32)

	IF(FALSE)
	SET(file ${_boost_my_releasedll})
	#  FOREACH(file ${ESSENTIAL_FILES_DEBUG})
	# GET_FILENAME_COMPONENT(fn ${file} NAME)
	#SET(tgt ${CMAKE_BINARY_DIR})
	SET(tgt "${PROJECT_BINARY_DIR}/Release/")
	SET(src ${file})
	MESSAGE( STATUS "tgt: ${tgt}      src: ${src}")
	ADD_CUSTOM_COMMAND(
		#   TARGET CopyDllCfg POST_BUILD
		TARGET ${target} 
		POST_BUILD
		COMMAND ${CMAKE_COMMAND}
		ARGS -E copy_if_different ${src} ${tgt}
		COMMENT "source copy dlls and essential files"
	)
	#  ENDFOREACH(file)
	ENDIF(FALSE)


ENDFOREACH()
#LIST(REMOVE_DUPLICATES Boost_LIBRARY_DIRS)

ENDIF()



ENDMACRO()


