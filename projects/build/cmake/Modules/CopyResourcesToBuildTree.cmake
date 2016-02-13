# - Copy the resources your app needs to the build tree.
#
#  copy_resources_to_build_tree(<target_name>)
#
# Requires CMake 2.6 or newer (uses the 'function' command)
#
# Original Author:
# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu> <abiryan@ryand.net>
# http://academic.cleardefinition.com
# Iowa State University HCI Graduate Program/VRAC
#
# Copyright Iowa State University 2009-2010.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

if(__copy_resources_to_build_tree)
	return()
endif()
set(__copy_resources_to_build_tree YES)

function(copy_language_to_build_tree _target _lang _dest)
SET(_HELPER_COPY_ENABLED FALSE)
IF(MSVC)
	SET(_HELPER_COPY_ENABLED TRUE)
ENDIF()
	SET(_destPath ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${_dest} )
	get_target_property(_sources ${_target} SOURCES)
#	message(WARN "_sources='${_sources}'")
	foreach(_source ${_sources})
		get_source_file_property(_sourceLang ${_source} LANGUAGE)
		if("${_sourceLang}" MATCHES "${_lang}")
			get_source_file_property(_sourcePath ${_source} LOCATION)
#			message("${_source}: lang='${_sourceLang}', path='${_sourcePath}', dest='${_destPath}'")
			#Copy_File_To_Target(${_target} ${_sourcePath})
			IF(_HELPER_COPY_ENABLED)
				ADD_CUSTOM_COMMAND(
					TARGET ${_target} 
					POST_BUILD
#					COMMAND ${CMAKE_COMMAND} ${_HELPERS_COPY_CMAKE_DEBUG_STR} -Dconfig=${CMAKE_CFG_INTDIR} -Dtgt="${PROJECT_BINARY_DIR}/" -Dreleasesrc="${file}" -Ddebugsrc="${file}" -P "${P_MODULE_PATH}/copy.cmake"
					COMMAND ${CMAKE_COMMAND} -E copy_if_different "${_sourcePath}" "${_destPath}/${_source}"
					DEPENDS "${_sourcePath}"
					COMMENT "Copy ${_source} LUA Resource File." 
				)
			ENDIF(_HELPER_COPY_ENABLED)
		endif()
	endforeach()
endfunction()

function(copy_filesRelative_to_build_tree _target _sources _dest)
SET(_HELPER_COPY_ENABLED FALSE)
IF(MSVC)
	SET(_HELPER_COPY_ENABLED TRUE)
ENDIF()
	SET(_destPath ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${_dest} )
#	message(WARN "_sources='${_sources}'")
	foreach(_source ${_sources})
		get_source_file_property(_sourcePath ${_source} LOCATION)
		#	message("${_source}: lang='${_sourceLang}', path='${_sourcePath}', dest='${_destPath}'")
		#Copy_File_To_Target(${_target} ${_sourcePath})
		IF(_HELPER_COPY_ENABLED)
			ADD_CUSTOM_COMMAND(
				TARGET ${_target} 
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${_sourcePath}" "${_destPath}/${_source}"
				DEPENDS "${_sourcePath}"
				COMMENT "Copy ${_source} LUA Resource File." 
			)
		ENDIF(_HELPER_COPY_ENABLED)
	endforeach()
endfunction()

function(copy_files_to_build_tree _target _sources _dest)
SET(_HELPER_COPY_ENABLED FALSE)
IF(MSVC)
	SET(_HELPER_COPY_ENABLED TRUE)
ENDIF()
	SET(_destPath ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${_dest} )
#	message(WARN "_sources='${_sources}'")
	foreach(_source ${_sources})
		get_source_file_property(_sourcePath ${_source} LOCATION)
		get_filename_component(_name "${_source}" NAME)
			message("${_source}: _name='${_name}', path='${_sourcePath}', dest='${_destPath}'")
		#Copy_File_To_Target(${_target} ${_sourcePath})
		IF(_HELPER_COPY_ENABLED)
			ADD_CUSTOM_COMMAND(
				TARGET ${_target} 
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${_sourcePath}" "${_destPath}/${_name}"
				DEPENDS "${_sourcePath}"
				COMMENT "Copy ${_source} LUA Resource File." 
			)
		ENDIF(_HELPER_COPY_ENABLED)
	endforeach()
endfunction()

function(copy_resources_to_build_tree _target)
	get_target_property(_resources ${_target} RESOURCE)
	if(NOT _resources)
		# Bail if no resources
		message(STATUS
			"Told to copy resources for target ${_target}, but "
			"no resources are set!")
		return()
	endif()

	get_target_property(_path ${_target} LOCATION)
	get_filename_component(_path "${_path}" PATH)

	if(NOT MSVC AND NOT "${CMAKE_GENERATOR}" MATCHES "Makefiles")
		foreach(_config ${CMAKE_CONFIGURATION_TYPES})
			get_target_property(_path${_config} ${_target} LOCATION_${_config})
			get_filename_component(_path${_config} "${_path${_config}}" PATH)
			add_custom_command(TARGET ${_target}
						POST_BUILD
						COMMAND
						${CMAKE_COMMAND}
						ARGS -E make_directory "${_path${_config}}/"
						COMMENT "Creating directory ${_path${_config}}/")
		endforeach()
	endif()

	foreach(_res ${_resources})
		if(NOT IS_ABSOLUTE "${_res}")
			get_filename_component(_res "${_res}" ABSOLUTE)
		endif()
		get_filename_component(_name "${_res}" NAME)

		if(MSVC)
			# Working dir is solution file dir, not exe file dir.
			add_custom_command(TARGET ${_target}
				POST_BUILD
				COMMAND
				${CMAKE_COMMAND}
				ARGS -E copy "${_res}" "${CMAKE_BINARY_DIR}/"
				COMMENT "Copying ${_name} to ${CMAKE_BINARY_DIR}/ for MSVC")
		else()
			if("${CMAKE_GENERATOR}" MATCHES "Makefiles")
				add_custom_command(TARGET ${_target}
					POST_BUILD
					COMMAND
					${CMAKE_COMMAND}
					ARGS -E copy "${_res}" "${_path}/"
					COMMENT "Copying ${_name} to ${_path}/")
			else()
				foreach(_config ${CMAKE_CONFIGURATION_TYPES})
					add_custom_command(TARGET ${_target}
						POST_BUILD
						COMMAND
						${CMAKE_COMMAND}
						ARGS -E copy "${_res}" "${_path${_config}}"
						COMMENT "Copying ${_name} to ${_path${_config}}")
				endforeach()

			endif()
		endif()
	endforeach()
endfunction()
