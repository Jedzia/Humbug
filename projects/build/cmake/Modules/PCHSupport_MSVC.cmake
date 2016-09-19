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

IF(MSVC)
  SET(PCHSupport_FOUND TRUE)
ENDIF(MSVC)


MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
  IF(MSVC)
	#GET_FILENAME_COMPONENT(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
	SET(PrecompiledBasename ${PROJECT_NAME})
	SET(PrecompiledBinary "$(IntDir)/${PrecompiledBasename}.pch")

	FOREACH( component ${${SourcesVar}} )
		GET_FILENAME_COMPONENT(component_ex ${component} EXT)
		STRING( TOLOWER ${component_ex} _component_ex )
		#MESSAGE( STATUS "component ${component}")
		IF(${_component_ex} STREQUAL ".h" OR ${_component_ex} STREQUAL ".hxx"
		   OR ${_component_ex} STREQUAL ".hpp")
			#get_source_file_property(FileType ${component} HEADER_FILE_ONLY)
			#MESSAGE( STATUS "No PCH for ${component}")
		ELSE()
			#MESSAGE( STATUS "PCH for ${component}")
			list(APPEND Sources ${component})
		ENDIF()
	ENDFOREACH( component )
	#MESSAGE( STATUS "Sources ${Sources}")


	#SET(Sources ${${SourcesVar}})
	#MESSAGE( STATUS "Sources ${Sources}")

	SET_SOURCE_FILES_PROPERTIES(${PrecompiledSource}
								PROPERTIES COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
										   OBJECT_OUTPUTS "${PrecompiledBinary}")
	SET_SOURCE_FILES_PROPERTIES(${Sources}
								PROPERTIES COMPILE_FLAGS "/Yu\"${PrecompiledHeader}\" /FI\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
										   OBJECT_DEPENDS "${PrecompiledBinary}")
	# Add precompiled header to SourcesVar
	LIST(APPEND ${SourcesVar} ${PrecompiledSource})
  ENDIF(MSVC)
ENDMACRO(ADD_MSVC_PRECOMPILED_HEADER)
