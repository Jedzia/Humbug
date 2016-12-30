# - Try to find precompiled headers support for GCC 3.4 and 4.x
# Once done this will define:
#
# Variable:
#   PCHSupport_FOUND
#
# Macro:
#   ADD_PRECOMPILED_HEADER  _targetName _input  _dowarn
#   ADD_PRECOMPILED_HEADER_TO_TARGET _targetName _input _pch_output_to_use _dowarn
#   ADD_NATIVE_PRECOMPILED_HEADER _targetName _input _dowarn
#   GET_NATIVE_PRECOMPILED_HEADER _targetName _input

if(MSVC)
  set(PCHSupport_FOUND TRUE)
endif(MSVC)


macro(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
  if(MSVC)
	#get_filename_component(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
	set(PrecompiledBasename ${PROJECT_NAME})
	set(PrecompiledBinary "$(IntDir)/${PrecompiledBasename}.pch")

	foreach( component ${${SourcesVar}} )
		get_filename_component(component_ex ${component} EXT)
		string( TOLOWER ${component_ex} _component_ex )
		#message( STATUS "component ${component}")
		if(${_component_ex} STREQUAL ".h" OR ${_component_ex} STREQUAL ".hxx"
		   OR ${_component_ex} STREQUAL ".hpp")
			#get_source_file_property(FileType ${component} HEADER_FILE_ONLY)
			#message( STATUS "No PCH for ${component}")
		else()
			#message( STATUS "PCH for ${component}")
			list(APPEND Sources ${component})
		endif()
	endforeach( component )
	#message( STATUS "Sources ${Sources}")


	#set(Sources ${${SourcesVar}})
	#message( STATUS "Sources ${Sources}")

	set_source_files_properties(${PrecompiledSource}
								PROPERTIES COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
										   OBJECT_OUTPUTS "${PrecompiledBinary}")
	set_source_files_properties(${Sources}
								PROPERTIES COMPILE_FLAGS "/Yu\"${PrecompiledHeader}\" /FI\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
										   OBJECT_DEPENDS "${PrecompiledBinary}")
	# Add precompiled header to SourcesVar
	list(APPEND ${SourcesVar} ${PrecompiledSource})
  endif(MSVC)
endmacro(ADD_MSVC_PRECOMPILED_HEADER)
