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

IF(NOT PCHSUPPORT_CMAKE_DEBUG)
	SET(PCHSUPPORT_CMAKE_DEBUG OFF)
ENDIF()

IF(CMAKE_COMPILER_IS_GNUCXX)

    EXEC_PROGRAM(
    	${CMAKE_CXX_COMPILER}  
        ARGS 	${CMAKE_CXX_COMPILER_ARG1} -dumpversion 
        OUTPUT_VARIABLE gcc_compiler_version)
    #MESSAGE("GCC Version: ${gcc_compiler_version}")
    IF(gcc_compiler_version MATCHES "4\\.[0-9]\\.[0-9]")
        SET(PCHSupport_FOUND TRUE)
    ELSE(gcc_compiler_version MATCHES "4\\.[0-9]\\.[0-9]")
        IF(gcc_compiler_version MATCHES "3\\.4\\.[0-9]")
            SET(PCHSupport_FOUND TRUE)
        ENDIF(gcc_compiler_version MATCHES "3\\.4\\.[0-9]")
    ENDIF(gcc_compiler_version MATCHES "4\\.[0-9]\\.[0-9]")
    
	SET(_PCH_include_prefix "-I")

ELSE(CMAKE_COMPILER_IS_GNUCXX)
#	IF(WIN32)	
#		SET(PCHSupport_FOUND TRUE) # for experimental msvc support
#		SET(_PCH_include_prefix "/I")
#	ELSE(WIN32)
#		SET(PCHSupport_FOUND FALSE)
#	ENDIF(WIN32)	
MESSAGE(FATAL_ERROR "USE the PCHSupport_MSVC module for WIN32 support.")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)


MACRO(_PCH_GET_COMPILE_FLAGS _out_compile_flags)


  STRING(TOUPPER "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" _flags_var_name)
  SET(${_out_compile_flags} ${${_flags_var_name}} )
  
  IF(CMAKE_COMPILER_IS_GNUCXX)
    
    GET_TARGET_PROPERTY(_targetType ${_PCH_current_target} TYPE)
    IF(${_targetType} STREQUAL SHARED_LIBRARY)
      LIST(APPEND ${_out_compile_flags} "${${_out_compile_flags}} -fPIC")
    ENDIF(${_targetType} STREQUAL SHARED_LIBRARY)
    
  ELSE(CMAKE_COMPILER_IS_GNUCXX)
    ## TODO ... ? or does it work out of the box 
  ENDIF(CMAKE_COMPILER_IS_GNUCXX)
  
  GET_DIRECTORY_PROPERTY(DIRINC INCLUDE_DIRECTORIES )
  FOREACH(item ${DIRINC})
    LIST(APPEND ${_out_compile_flags} "${_PCH_include_prefix}${item}")
  ENDFOREACH(item)
  #MESSAGE(STATUS "[PCHSupport_26] _out_compile_flags ${_out_compile_flags}: ${${_out_compile_flags}}" )
  
  GET_DIRECTORY_PROPERTY(_directory_flags DEFINITIONS)
  #MESSAGE("_directory_flags ${_directory_flags}" )
  LIST(APPEND ${_out_compile_flags} ${_directory_flags})
  LIST(APPEND ${_out_compile_flags} ${CMAKE_CXX_FLAGS} )
  
  SEPARATE_ARGUMENTS(${_out_compile_flags})

ENDMACRO(_PCH_GET_COMPILE_FLAGS)


MACRO(_PCH_WRITE_PCHDEP_CXX _targetName _include_file _dephelp)

  SET(${_dephelp} ${CMAKE_CURRENT_BINARY_DIR}/${_targetName}_pch_dephelp.cxx)
  FILE(WRITE  ${${_dephelp}}
"#include \"${_include_file}\" 
int testfunction()
{
    return 0;
}
"
    ) 

ENDMACRO(_PCH_WRITE_PCHDEP_CXX )

MACRO(_PCH_GET_COMPILE_COMMAND out_command _input _output)

	FILE(TO_NATIVE_PATH ${_input} _native_input)
	FILE(TO_NATIVE_PATH ${_output} _native_output)
	

	IF(CMAKE_COMPILER_IS_GNUCXX)
          IF(CMAKE_CXX_COMPILER_ARG1)
	    # remove leading space in compiler argument
            STRING(REGEX REPLACE "^ +" "" pchsupport_compiler_cxx_arg1 ${CMAKE_CXX_COMPILER_ARG1})

	    SET(${out_command} 
	      ${CMAKE_CXX_COMPILER} ${pchsupport_compiler_cxx_arg1} ${_compile_FLAGS}	-x c++-header -o ${_output} ${_input} 
	      )
	  ELSE(CMAKE_CXX_COMPILER_ARG1)
	    SET(${out_command} 
	      ${CMAKE_CXX_COMPILER}  ${_compile_FLAGS}	-x c++-header -o ${_output} ${_input} 
	      )
          ENDIF(CMAKE_CXX_COMPILER_ARG1)
	ELSE(CMAKE_COMPILER_IS_GNUCXX)
		
		SET(_dummy_str "#include <${_input}>")
		FILE(WRITE ${CMAKE_CURRENT_BINARY_DIR}/pch_dummy.cpp ${_dummy_str})
	
		SET(${out_command} 
			${CMAKE_CXX_COMPILER} ${_compile_FLAGS} /c /Fp${_native_output} /Yc${_native_input} pch_dummy.cpp
		)	
		#/out:${_output}

	ENDIF(CMAKE_COMPILER_IS_GNUCXX)
	
  #MESSAGE(STATUS "[PCHSupport_26] out_command ${out_command}: ${${out_command}}" )
ENDMACRO(_PCH_GET_COMPILE_COMMAND )



MACRO(_PCH_GET_TARGET_COMPILE_FLAGS _cflags  _header_name _pch_path _outdir _dowarn )

  FILE(TO_NATIVE_PATH ${_pch_path} _native_pch_path)
  
  IF(CMAKE_COMPILER_IS_GNUCXX)
    # for use with distcc and gcc >4.0.1 if preprocessed files are accessible
    # on all remote machines set
    # PCH_ADDITIONAL_COMPILER_FLAGS to -fpch-preprocess
    # if you want warnings for invalid header files (which is very inconvenient
    # if you have different versions of the headers for different build types
    # you may set _pch_dowarn
    IF (_dowarn)
      SET(${_cflags} "${PCH_ADDITIONAL_COMPILER_FLAGS} -include ${_outdir}/${_header_name} -Winvalid-pch " )
    ELSE (_dowarn)
      SET(${_cflags} "${PCH_ADDITIONAL_COMPILER_FLAGS} -include ${_outdir}/${_header_name} " )
    ENDIF (_dowarn)
   #message("XX _outdir ${_outdir}")
   #message("XX _header_name ${_header_name}")
  ELSE(CMAKE_COMPILER_IS_GNUCXX)
   
    set(${_cflags} "/Fp${_native_pch_path} /Yu${_header_name}" )	
    
  ENDIF(CMAKE_COMPILER_IS_GNUCXX)	
  #message("_cflags  ${_cflags}")

ENDMACRO(_PCH_GET_TARGET_COMPILE_FLAGS )

MACRO(GET_PRECOMPILED_HEADER_OUTPUT _targetName _input _output)
  GET_FILENAME_COMPONENT(_name ${_input} NAME)
  GET_FILENAME_COMPONENT(_path ${_input} PATH)
  SET(_output "${CMAKE_CURRENT_BINARY_DIR}/${_name}.gch/${_targetName}_${CMAKE_BUILD_TYPE}.h++")
#  MESSAGE(STATUS "[PCHSupport_26] _output ${_output}: ${${_output}}" )
ENDMACRO(GET_PRECOMPILED_HEADER_OUTPUT _targetName _input)


MACRO(ADD_PRECOMPILED_HEADER_TO_TARGET _targetName _input _pch_output_to_use _outdir)
   
  # to do: test whether compiler flags match between target  _targetName
  # and _pch_output_to_use
  GET_FILENAME_COMPONENT(_name ${_input} NAME)

  IF( "${ARGN}" STREQUAL "0")
    SET(_dowarn 0)
  ELSE( "${ARGN}" STREQUAL "0")
    SET(_dowarn 1)
  ENDIF("${ARGN}" STREQUAL "0")


  _PCH_GET_TARGET_COMPILE_FLAGS(_target_cflags ${_name} ${_pch_output_to_use} ${_outdir} ${_dowarn})

  IF(PCHSUPPORT_CMAKE_DEBUG)
	  MESSAGE(STATUS "[PCHSupport_26] _PCH_GET_TARGET_COMPILE_FLAGS ${_target_cflags}=${_targetName} " )
	  MESSAGE(STATUS "[PCHSupport_26] _PCH_GET_TARGET_COMPILE_FLAGS _name=${_name} " )
	  MESSAGE(STATUS "[PCHSupport_26] _PCH_GET_TARGET_COMPILE_FLAGS _pch_output_to_use=${_pch_output_to_use} " )
	  MESSAGE(STATUS "[PCHSupport_26] _PCH_GET_TARGET_COMPILE_FLAGS _outdir=${_outdir} " )
	  MESSAGE(STATUS "[PCHSupport_26] _PCH_GET_TARGET_COMPILE_FLAGS _dowarn=${_dowarn} " )
  ENDIF()
  
  SET_TARGET_PROPERTIES(${_targetName} 
    PROPERTIES	
    COMPILE_FLAGS ${_target_cflags} 
    )
  #MESSAGE(STATUS "[PCHSupport_26] COMPILE_FLAGS: ${_target_cflags}" )
  
  ADD_CUSTOM_TARGET(pch_Generate_${_targetName}
    DEPENDS	${_pch_output_to_use} 
    )
  
  ADD_DEPENDENCIES(${_targetName} pch_Generate_${_targetName} )
  
ENDMACRO(ADD_PRECOMPILED_HEADER_TO_TARGET)

MACRO(ADD_PRECOMPILED_HEADER_TO_SOURCE _targetName _sourcefile _input _pch_output_to_use _outdir)
   
  # to do: test whether compiler flags match between target  _targetName
  # and _pch_output_to_use
  GET_FILENAME_COMPONENT(_name ${_input} NAME)

  IF( "${ARGN}" STREQUAL "0")
    SET(_dowarn 0)
  ELSE( "${ARGN}" STREQUAL "0")
    SET(_dowarn 1)
  ENDIF("${ARGN}" STREQUAL "0")


  _PCH_GET_TARGET_COMPILE_FLAGS(_target_cflags ${_name} ${_pch_output_to_use} ${_outdir} ${_dowarn})
  #   MESSAGE("Add flags ${_target_cflags} to ${_targetName} " )
SET_SOURCE_FILES_PROPERTIES(${_sourcefile}
#							PROPERTIES COMPILE_FLAGS "MOOOO"
							PROPERTIES COMPILE_FLAGS ${_target_cflags} 
#									   OBJECT_OUTPUTS "${PrecompiledBinary}"
)

#  SET_TARGET_PROPERTIES(${_targetName} 
#    PROPERTIES	
#    COMPILE_FLAGS ${_target_cflags} 
#    )
  #MESSAGE(STATUS "[PCHSupport_26] COMPILE_FLAGS: ${_target_cflags}" )
  
  #ADD_CUSTOM_TARGET(pch_Generate_${_targetName}
   # DEPENDS	${_pch_output_to_use} 
    #)
  
 # ADD_DEPENDENCIES(${_targetName} pch_Generate_${_targetName} )
  
ENDMACRO(ADD_PRECOMPILED_HEADER_TO_SOURCE)

MACRO(ADD_PRECOMPILED_HEADER_TARGET _targetName _input _pch_output_to_use _outdir)
   
 # to do: test whether compiler flags match between target  _targetName
  # and _pch_output_to_use
  GET_FILENAME_COMPONENT(_name ${_input} NAME)

  IF( "${ARGN}" STREQUAL "0")
    SET(_dowarn 0)
  ELSE( "${ARGN}" STREQUAL "0")
    SET(_dowarn 1)
  ENDIF("${ARGN}" STREQUAL "0")


  _PCH_GET_TARGET_COMPILE_FLAGS(_target_cflags ${_name} ${_pch_output_to_use} ${_outdir} ${_dowarn})
  IF(PCHSUPPORT_CMAKE_DEBUG)
	  MESSAGE(STATUS "[PCHSupport_26X] _PCH_GET_TARGET_COMPILE_FLAGS ${_target_cflags}=${_targetName} " )
	  MESSAGE(STATUS "[PCHSupport_26X] _PCH_GET_TARGET_COMPILE_FLAGS _name=${_name} " )
	  MESSAGE(STATUS "[PCHSupport_26X] _PCH_GET_TARGET_COMPILE_FLAGS _pch_output_to_use=${_pch_output_to_use} " )
	  MESSAGE(STATUS "[PCHSupport_26X] _PCH_GET_TARGET_COMPILE_FLAGS _outdir=${_outdir} " )
	  MESSAGE(STATUS "[PCHSupport_26X] _PCH_GET_TARGET_COMPILE_FLAGS _dowarn=${_dowarn} " )
  ENDIF()
   
  ADD_CUSTOM_TARGET(pch_Generate_${_targetName}
    DEPENDS	${_pch_output_to_use} 
  )
  
 ADD_DEPENDENCIES(${_targetName} pch_Generate_${_targetName} )
  
ENDMACRO(ADD_PRECOMPILED_HEADER_TARGET)

MACRO(ADD_PRECOMPILED_HEADER _targetName _inputx _gchx)

  IF(IS_ABSOLUTE "${_inputx}")
    SET( _input ${_inputx} )
  ELSE()
    SET( _input ${CMAKE_CURRENT_SOURCE_DIR}/${_inputx} )
  ENDIF()

  IF(IS_ABSOLUTE "${_gchx}")
    SET( _gch ${_gchx} )
  ELSE()
    SET( _gch ${CMAKE_CURRENT_BINARY_DIR}/${_gchx} )
  ENDIF()
  #message("_gch ${_gchx}")


  SET(_PCH_current_target ${_targetName})
  
  IF(NOT CMAKE_BUILD_TYPE)
    MESSAGE(FATAL_ERROR 
      "This is the ADD_PRECOMPILED_HEADER macro. " 
      "You must set CMAKE_BUILD_TYPE!"
      )
  ENDIF(NOT CMAKE_BUILD_TYPE)

  IF( "${ARGN}" STREQUAL "0")
    SET(_dowarn 0)
  ELSE( "${ARGN}" STREQUAL "0")
    SET(_dowarn 1)
  ENDIF("${ARGN}" STREQUAL "0")


  GET_FILENAME_COMPONENT(_name ${_input} NAME)
  GET_FILENAME_COMPONENT(_path ${_input} PATH)
  GET_PRECOMPILED_HEADER_OUTPUT( ${_targetName} ${_input} _output)

  GET_FILENAME_COMPONENT(_gchname ${_output} NAME)
  GET_FILENAME_COMPONENT(_outdir ${_output} PATH )
  GET_FILENAME_COMPONENT(_gchdir ${_gch} PATH )
  SET(_pch_source ${_output})
  SET(_pch_target "${_output}.gch")
  
  GET_TARGET_PROPERTY(_targetType ${_PCH_current_target} TYPE)
   _PCH_WRITE_PCHDEP_CXX(${_targetName} ${_input} _pch_dephelp_cxx)

  IF(${_targetType} STREQUAL SHARED_LIBRARY)
    ADD_LIBRARY(${_targetName}_pch_dephelp SHARED ${_pch_dephelp_cxx} )
  ELSE(${_targetType} STREQUAL SHARED_LIBRARY)
    ADD_LIBRARY(${_targetName}_pch_dephelp STATIC ${_pch_dephelp_cxx})
  ENDIF(${_targetType} STREQUAL SHARED_LIBRARY)



  FILE(MAKE_DIRECTORY ${_outdir})
  #FILE(MAKE_DIRECTORY ${_gchdir})
  #message("_gch ${_gch}")
  #message("_output ${_output}")
  #message("_outdir ${_outdir}")
  #message("_gchdir ${_gchdir}")
  #message("_pch_source_name ${_pch_source_name}")

  
  _PCH_GET_COMPILE_FLAGS(_compile_FLAGS)
  
  #MESSAGE("_compile_FLAGS: ${_compile_FLAGS}")
  #message("COMMAND ${CMAKE_CXX_COMPILER}	${_compile_FLAGS} -x c++-header -o ${_output} ${_input}")
  #SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/${_name} PROPERTIES GENERATED 1)
  SET_SOURCE_FILES_PROPERTIES(${_output} PROPERTIES GENERATED 1)
  #SET_SOURCE_FILES_PROPERTIES(${_pch_target} PROPERTIES GENERATED 1)
  
  ADD_CUSTOM_COMMAND(
   OUTPUT	${_output} 
   COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${_input} ${_output} # ensure same directory! Required by gcc
   DEPENDS ${_input}
  )
  
  _PCH_GET_COMPILE_COMMAND(_command   ${_output} ${_pch_target} )
  
  
  #message("_command  ${_command}")
  #message("_input ${_input}" )
  #message("_output ${_output}")
  #message("DEPENDS ${_input}   ${CMAKE_CURRENT_BINARY_DIR}/${_name} ${_targetName}_pch_dephelp")

  ADD_CUSTOM_COMMAND(
    OUTPUT ${_pch_target} 	
    COMMAND ${_command}
    DEPENDS ${_output} ${_input} ${_targetName}_pch_dephelp
  )

#list(LENGTH "${ARGV4}" _list_length)
#IF(_list_length GREATER 0)
IF("${ARGV4}" STREQUAL "")
  # This is the old thingy

  MESSAGE(STATUS "[PCHSupport_26] Using target-centric method on target ${_targetName}." )
  ADD_PRECOMPILED_HEADER_TO_TARGET(${_targetName} ${_output}  ${_pch_target} ${_outdir} ${_dowarn})
ELSE()
	MESSAGE(STATUS "[PCHSupport_26] Using file-centric method on target ${_targetName}." )
  
	SET(SourcesVar ${ARGV4})
	#MESSAGE(STATUS "[PCHSupport_26] SourcesVar: ${SourcesVar}" )

	FOREACH(file ${SourcesVar})
		GET_FILENAME_COMPONENT(_abs_file ${file} ABSOLUTE)
		ADD_PRECOMPILED_HEADER_TO_SOURCE(${_targetName} ${_abs_file} ${_output}  ${_pch_target} ${_outdir} ${_dowarn})
		#GET_SOURCE_FILE_PROPERTY(_src_prop ${_abs_file} COMPILE_FLAGS)
		#MESSAGE(STATUS "[PCHSupport_26] ${_abs_file}: ${_src_prop}" )
	ENDFOREACH()
	ADD_PRECOMPILED_HEADER_TARGET(${_targetName} ${_output}  ${_pch_target} ${_outdir} ${_dowarn})
ENDIF()
  
ENDMACRO(ADD_PRECOMPILED_HEADER)


# Generates the use of precompiled in a target,
# without using depency targets (2 extra for each target)
# Using Visual, must also add ${_targetName}_pch to sources
# Not needed by Xcode

MACRO(GET_NATIVE_PRECOMPILED_HEADER _targetName _input)

	if(CMAKE_GENERATOR MATCHES Visual*)

		SET(_dummy_str "#include \"${_input}\"\n"
										"// This is required to suppress LNK4221.  Very annoying.\n"
										"void *g_${_targetName}Dummy = 0\;\n")

		# Use of cxx extension for generated files (as Qt does)
		SET(${_targetName}_pch ${CMAKE_CURRENT_BINARY_DIR}/${_targetName}_pch.cxx)
		if(EXISTS ${${_targetName}_pch})
			# Check if contents is the same, if not rewrite
			# todo
		else(EXISTS ${${_targetName}_pch})
			FILE(WRITE ${${_targetName}_pch} ${_dummy_str})
		endif(EXISTS ${${_targetName}_pch})
	endif(CMAKE_GENERATOR MATCHES Visual*)

ENDMACRO(GET_NATIVE_PRECOMPILED_HEADER)


MACRO(ADD_NATIVE_PRECOMPILED_HEADER _targetName _input)

	IF( "${ARGN}" STREQUAL "0")
		SET(_dowarn 0)
	ELSE( "${ARGN}" STREQUAL "0")
		SET(_dowarn 1)
	ENDIF("${ARGN}" STREQUAL "0")
	
	if(CMAKE_GENERATOR MATCHES Visual*)
		# Auto include the precompile (useful for moc processing, since the use of 
		# precompiled is specified at the target level
		# and I don't want to specifiy /F- for each moc/res/ui generated files (using Qt)

		GET_TARGET_PROPERTY(oldProps ${_targetName} COMPILE_FLAGS)
		if (${oldProps} MATCHES NOTFOUND)
			SET(oldProps "")
		endif(${oldProps} MATCHES NOTFOUND)

		SET(newProperties "${oldProps} /Yu\"${_input}\" /FI\"${_input}\"")
		SET_TARGET_PROPERTIES(${_targetName} PROPERTIES COMPILE_FLAGS "${newProperties}")
		
		#also inlude ${oldProps} to have the same compile options 
		SET_SOURCE_FILES_PROPERTIES(${${_targetName}_pch} PROPERTIES COMPILE_FLAGS "${oldProps} /Yc\"${_input}\"")
		
	else(CMAKE_GENERATOR MATCHES Visual*)
	
		if (CMAKE_GENERATOR MATCHES Xcode)
			# For Xcode, cmake needs my patch to process
			# GCC_PREFIX_HEADER and GCC_PRECOMPILE_PREFIX_HEADER as target properties
			
			GET_TARGET_PROPERTY(oldProps ${_targetName} COMPILE_FLAGS)
			if (${oldProps} MATCHES NOTFOUND)
				SET(oldProps "")
			endif(${oldProps} MATCHES NOTFOUND)

			# When buiding out of the tree, precompiled may not be located
			# Use full path instead.
			GET_FILENAME_COMPONENT(fullPath ${_input} ABSOLUTE)

			SET_TARGET_PROPERTIES(${_targetName} PROPERTIES XCODE_ATTRIBUTE_GCC_PREFIX_HEADER "${fullPath}")
			SET_TARGET_PROPERTIES(${_targetName} PROPERTIES XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES")

		else (CMAKE_GENERATOR MATCHES Xcode)

			#Fallback to the "old" precompiled suppport
			#ADD_PRECOMPILED_HEADER(${_targetName} ${_input} ${_dowarn})
		endif(CMAKE_GENERATOR MATCHES Xcode)
	endif(CMAKE_GENERATOR MATCHES Visual*)

ENDMACRO(ADD_NATIVE_PRECOMPILED_HEADER)
