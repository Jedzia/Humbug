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

if(NOT PCHSUPPORT_CMAKE_DEBUG)
	set(PCHSUPPORT_CMAKE_DEBUG OFF)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)

    exec_program(
    	${CMAKE_CXX_COMPILER}  
        ARGS 	${CMAKE_CXX_COMPILER_ARG1} -dumpversion 
        OUTPUT_VARIABLE gcc_compiler_version)
    #message("GCC Version: ${gcc_compiler_version}")
    if(gcc_compiler_version MATCHES "4\\.[0-9]\\.[0-9]")
        set(PCHSupport_FOUND TRUE)
    else(gcc_compiler_version MATCHES "4\\.[0-9]\\.[0-9]")
        if(gcc_compiler_version MATCHES "3\\.4\\.[0-9]")
            set(PCHSupport_FOUND TRUE)
        endif(gcc_compiler_version MATCHES "3\\.4\\.[0-9]")
    endif(gcc_compiler_version MATCHES "4\\.[0-9]\\.[0-9]")
    
	set(_PCH_include_prefix "-I")

else(CMAKE_COMPILER_IS_GNUCXX)
#	if(WIN32)	
#		set(PCHSupport_FOUND TRUE) # for experimental msvc support
#		set(_PCH_include_prefix "/I")
#	else(WIN32)
#		set(PCHSupport_FOUND FALSE)
#	endif(WIN32)	
message(FATAL_ERROR "USE the PCHSupport_MSVC module for WIN32 support.")
endif(CMAKE_COMPILER_IS_GNUCXX)


macro(_PCH_GET_COMPILE_FLAGS _out_compile_flags)


  string(TOUPPER "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" _flags_var_name)
  set(${_out_compile_flags} ${${_flags_var_name}} )
  
  if(CMAKE_COMPILER_IS_GNUCXX)
    
    get_target_property(_targetType ${_PCH_current_target} TYPE)
    if(${_targetType} STREQUAL SHARED_LIBRARY)
      list(APPEND ${_out_compile_flags} "${${_out_compile_flags}} -fPIC")
    endif(${_targetType} STREQUAL SHARED_LIBRARY)
    
  else(CMAKE_COMPILER_IS_GNUCXX)
    ## TODO ... ? or does it work out of the box 
  endif(CMAKE_COMPILER_IS_GNUCXX)
  
  get_directory_property(DIRINC INCLUDE_DIRECTORIES )
  foreach(item ${DIRINC})
    list(APPEND ${_out_compile_flags} "${_PCH_include_prefix}${item}")
  endforeach(item)
  #message(STATUS "[PCHSupport_26] _out_compile_flags ${_out_compile_flags}: ${${_out_compile_flags}}" )
  
  get_directory_property(_directory_flags DEFINITIONS)
  #message("_directory_flags ${_directory_flags}" )
  list(APPEND ${_out_compile_flags} ${_directory_flags})
  list(APPEND ${_out_compile_flags} ${CMAKE_CXX_FLAGS} )
  
  separate_arguments(${_out_compile_flags})

endmacro(_PCH_GET_COMPILE_FLAGS)


macro(_PCH_WRITE_PCHDEP_CXX _targetName _include_file _dephelp)

  set(${_dephelp} ${CMAKE_CURRENT_BINARY_DIR}/${_targetName}_pch_dephelp.cxx)
  file(WRITE  ${${_dephelp}}
"#include \"${_include_file}\" 
int testfunction()
{
    return 0;
}
"
    ) 

endmacro(_PCH_WRITE_PCHDEP_CXX )

macro(_PCH_GET_COMPILE_COMMAND out_command _input _output)

	file(TO_NATIVE_PATH ${_input} _native_input)
	file(TO_NATIVE_PATH ${_output} _native_output)
	

	if(CMAKE_COMPILER_IS_GNUCXX)
          if(CMAKE_CXX_COMPILER_ARG1)
	    # remove leading space in compiler argument
            string(REGEX REPLACE "^ +" "" pchsupport_compiler_cxx_arg1 ${CMAKE_CXX_COMPILER_ARG1})

	    set(${out_command} 
	      ${CMAKE_CXX_COMPILER} ${pchsupport_compiler_cxx_arg1} ${_compile_FLAGS}	-x c++-header -o ${_output} ${_input} 
	      )
	  else(CMAKE_CXX_COMPILER_ARG1)
	    set(${out_command} 
	      ${CMAKE_CXX_COMPILER}  ${_compile_FLAGS}	-x c++-header -o ${_output} ${_input} 
	      )
          endif(CMAKE_CXX_COMPILER_ARG1)
	else(CMAKE_COMPILER_IS_GNUCXX)
		
		set(_dummy_str "#include <${_input}>")
		file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/pch_dummy.cpp ${_dummy_str})
	
		set(${out_command} 
			${CMAKE_CXX_COMPILER} ${_compile_FLAGS} /c /Fp${_native_output} /Yc${_native_input} pch_dummy.cpp
		)	
		#/out:${_output}

	endif(CMAKE_COMPILER_IS_GNUCXX)
	
  #message(STATUS "[PCHSupport_26] out_command ${out_command}: ${${out_command}}" )
endmacro(_PCH_GET_COMPILE_COMMAND )



macro(_PCH_GET_TARGET_COMPILE_FLAGS _cflags  _header_name _pch_path _outdir _dowarn )

  file(TO_NATIVE_PATH ${_pch_path} _native_pch_path)
  
  if(CMAKE_COMPILER_IS_GNUCXX)
    # for use with distcc and gcc >4.0.1 if preprocessed files are accessible
    # on all remote machines set
    # PCH_ADDITIONAL_COMPILER_FLAGS to -fpch-preprocess
    # if you want warnings for invalid header files (which is very inconvenient
    # if you have different versions of the headers for different build types
    # you may set _pch_dowarn
    if (_dowarn)
      set(${_cflags} "${PCH_ADDITIONAL_COMPILER_FLAGS} -include ${_outdir}/${_header_name} -Winvalid-pch " )
    else (_dowarn)
      set(${_cflags} "${PCH_ADDITIONAL_COMPILER_FLAGS} -include ${_outdir}/${_header_name} " )
    endif (_dowarn)
   #message("XX _outdir ${_outdir}")
   #message("XX _header_name ${_header_name}")
  else(CMAKE_COMPILER_IS_GNUCXX)
   
    set(${_cflags} "/Fp${_native_pch_path} /Yu${_header_name}" )	
    
  endif(CMAKE_COMPILER_IS_GNUCXX)	
  #message("_cflags  ${_cflags}")

endmacro(_PCH_GET_TARGET_COMPILE_FLAGS )

macro(GET_PRECOMPILED_HEADER_OUTPUT _targetName _input _output)
  get_filename_component(_name ${_input} NAME)
  get_filename_component(_path ${_input} PATH)
  set(_output "${CMAKE_CURRENT_BINARY_DIR}/${_name}.gch/${_targetName}_${CMAKE_BUILD_TYPE}.h++")
#  message(STATUS "[PCHSupport_26] _output ${_output}: ${${_output}}" )
endmacro(GET_PRECOMPILED_HEADER_OUTPUT _targetName _input)


macro(ADD_PRECOMPILED_HEADER_TO_TARGET _targetName _input _pch_output_to_use _outdir)
   
  # to do: test whether compiler flags match between target  _targetName
  # and _pch_output_to_use
  get_filename_component(_name ${_input} NAME)

  if( "${ARGN}" STREQUAL "0")
    set(_dowarn 0)
  else( "${ARGN}" STREQUAL "0")
    set(_dowarn 1)
  endif("${ARGN}" STREQUAL "0")


  _PCH_GET_TARGET_COMPILE_FLAGS(_target_cflags ${_name} ${_pch_output_to_use} ${_outdir} ${_dowarn})

  if(PCHSUPPORT_CMAKE_DEBUG)
	  message(STATUS "[PCHSupport_26] _PCH_GET_TARGET_COMPILE_FLAGS ${_target_cflags}=${_targetName} " )
	  message(STATUS "[PCHSupport_26] _PCH_GET_TARGET_COMPILE_FLAGS _name=${_name} " )
	  message(STATUS "[PCHSupport_26] _PCH_GET_TARGET_COMPILE_FLAGS _pch_output_to_use=${_pch_output_to_use} " )
	  message(STATUS "[PCHSupport_26] _PCH_GET_TARGET_COMPILE_FLAGS _outdir=${_outdir} " )
	  message(STATUS "[PCHSupport_26] _PCH_GET_TARGET_COMPILE_FLAGS _dowarn=${_dowarn} " )
  endif()
  
  set_target_properties(${_targetName} 
    PROPERTIES	
    COMPILE_FLAGS ${_target_cflags} 
    )
  #message(STATUS "[PCHSupport_26] COMPILE_FLAGS: ${_target_cflags}" )
  
  add_custom_target(pch_Generate_${_targetName}
    DEPENDS	${_pch_output_to_use} 
    )
  
  add_dependencies(${_targetName} pch_Generate_${_targetName} )
  
endmacro(ADD_PRECOMPILED_HEADER_TO_TARGET)

macro(ADD_PRECOMPILED_HEADER_TO_SOURCE _targetName _sourcefile _input _pch_output_to_use _outdir)
   
  # to do: test whether compiler flags match between target  _targetName
  # and _pch_output_to_use
  get_filename_component(_name ${_input} NAME)

  if( "${ARGN}" STREQUAL "0")
    set(_dowarn 0)
  else( "${ARGN}" STREQUAL "0")
    set(_dowarn 1)
  endif("${ARGN}" STREQUAL "0")


  _PCH_GET_TARGET_COMPILE_FLAGS(_target_cflags ${_name} ${_pch_output_to_use} ${_outdir} ${_dowarn})
  #   message("Add flags ${_target_cflags} to ${_targetName} " )
set_source_files_properties(${_sourcefile}
#							PROPERTIES COMPILE_FLAGS "MOOOO"
							PROPERTIES COMPILE_FLAGS ${_target_cflags} 
#									   OBJECT_OUTPUTS "${PrecompiledBinary}"
)

#  set_target_properties(${_targetName} 
#    PROPERTIES	
#    COMPILE_FLAGS ${_target_cflags} 
#    )
  #message(STATUS "[PCHSupport_26] COMPILE_FLAGS: ${_target_cflags}" )
  
  #add_custom_target(pch_Generate_${_targetName}
   # DEPENDS	${_pch_output_to_use} 
    #)
  
 # add_dependencies(${_targetName} pch_Generate_${_targetName} )
  
endmacro(ADD_PRECOMPILED_HEADER_TO_SOURCE)

macro(ADD_PRECOMPILED_HEADER_TARGET _targetName _input _pch_output_to_use _outdir)
   
 # to do: test whether compiler flags match between target  _targetName
  # and _pch_output_to_use
  get_filename_component(_name ${_input} NAME)

  if( "${ARGN}" STREQUAL "0")
    set(_dowarn 0)
  else( "${ARGN}" STREQUAL "0")
    set(_dowarn 1)
  endif("${ARGN}" STREQUAL "0")


  _PCH_GET_TARGET_COMPILE_FLAGS(_target_cflags ${_name} ${_pch_output_to_use} ${_outdir} ${_dowarn})
  if(PCHSUPPORT_CMAKE_DEBUG)
	  message(STATUS "[PCHSupport_26X] _PCH_GET_TARGET_COMPILE_FLAGS ${_target_cflags}=${_targetName} " )
	  message(STATUS "[PCHSupport_26X] _PCH_GET_TARGET_COMPILE_FLAGS _name=${_name} " )
	  message(STATUS "[PCHSupport_26X] _PCH_GET_TARGET_COMPILE_FLAGS _pch_output_to_use=${_pch_output_to_use} " )
	  message(STATUS "[PCHSupport_26X] _PCH_GET_TARGET_COMPILE_FLAGS _outdir=${_outdir} " )
	  message(STATUS "[PCHSupport_26X] _PCH_GET_TARGET_COMPILE_FLAGS _dowarn=${_dowarn} " )
  endif()
   
  add_custom_target(pch_Generate_${_targetName}
    DEPENDS	${_pch_output_to_use} 
  )
  
 add_dependencies(${_targetName} pch_Generate_${_targetName} )
  
endmacro(ADD_PRECOMPILED_HEADER_TARGET)

macro(ADD_PRECOMPILED_HEADER _targetName _inputx _gchx)

  if(IS_ABSOLUTE "${_inputx}")
    set( _input ${_inputx} )
  else()
    set( _input ${CMAKE_CURRENT_SOURCE_DIR}/${_inputx} )
  endif()

  if(IS_ABSOLUTE "${_gchx}")
    set( _gch ${_gchx} )
  else()
    set( _gch ${CMAKE_CURRENT_BINARY_DIR}/${_gchx} )
  endif()
  #message("_gch ${_gchx}")


  set(_PCH_current_target ${_targetName})
  
  if(NOT CMAKE_BUILD_TYPE)
    message(FATAL_ERROR 
      "This is the ADD_PRECOMPILED_HEADER macro. " 
      "You must set CMAKE_BUILD_TYPE!"
      )
  endif(NOT CMAKE_BUILD_TYPE)

  if( "${ARGN}" STREQUAL "0")
    set(_dowarn 0)
  else( "${ARGN}" STREQUAL "0")
    set(_dowarn 1)
  endif("${ARGN}" STREQUAL "0")


  get_filename_component(_name ${_input} NAME)
  get_filename_component(_path ${_input} PATH)
  GET_PRECOMPILED_HEADER_OUTPUT( ${_targetName} ${_input} _output)

  get_filename_component(_gchname ${_output} NAME)
  get_filename_component(_outdir ${_output} PATH )
  get_filename_component(_gchdir ${_gch} PATH )
  set(_pch_source ${_output})
  set(_pch_target "${_output}.gch")
  
  get_target_property(_targetType ${_PCH_current_target} TYPE)
   _PCH_WRITE_PCHDEP_CXX(${_targetName} ${_input} _pch_dephelp_cxx)

  if(${_targetType} STREQUAL SHARED_LIBRARY)
    add_library(${_targetName}_pch_dephelp SHARED ${_pch_dephelp_cxx} )
  else(${_targetType} STREQUAL SHARED_LIBRARY)
    add_library(${_targetName}_pch_dephelp STATIC ${_pch_dephelp_cxx})
  endif(${_targetType} STREQUAL SHARED_LIBRARY)



  file(MAKE_DIRECTORY ${_outdir})
  #file(MAKE_DIRECTORY ${_gchdir})
  #message("_gch ${_gch}")
  #message("_output ${_output}")
  #message("_outdir ${_outdir}")
  #message("_gchdir ${_gchdir}")
  #message("_pch_source_name ${_pch_source_name}")

  
  _PCH_GET_COMPILE_FLAGS(_compile_FLAGS)
  
  #message("_compile_FLAGS: ${_compile_FLAGS}")
  #message("COMMAND ${CMAKE_CXX_COMPILER}	${_compile_FLAGS} -x c++-header -o ${_output} ${_input}")
  #set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/${_name} PROPERTIES GENERATED 1)
  set_source_files_properties(${_output} PROPERTIES GENERATED 1)
  #set_source_files_properties(${_pch_target} PROPERTIES GENERATED 1)
  
  add_custom_command(
   OUTPUT	${_output} 
   COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${_input} ${_output} # ensure same directory! Required by gcc
   DEPENDS ${_input}
  )
  
  _PCH_GET_COMPILE_COMMAND(_command   ${_output} ${_pch_target} )
  
  
  #message("_command  ${_command}")
  #message("_input ${_input}" )
  #message("_output ${_output}")
  #message("DEPENDS ${_input}   ${CMAKE_CURRENT_BINARY_DIR}/${_name} ${_targetName}_pch_dephelp")

  add_custom_command(
    OUTPUT ${_pch_target} 	
    COMMAND ${_command}
    DEPENDS ${_output} ${_input} ${_targetName}_pch_dephelp
  )

#list(LENGTH "${ARGV4}" _list_length)
#if(_list_length GREATER 0)
if("${ARGV4}" STREQUAL "")
  # This is the old thingy

  message(STATUS "[PCHSupport_26] Using target-centric method on target ${_targetName}." )
  ADD_PRECOMPILED_HEADER_TO_TARGET(${_targetName} ${_output}  ${_pch_target} ${_outdir} ${_dowarn})
else()
	message(STATUS "[PCHSupport_26] Using file-centric method on target ${_targetName}." )
  
	set(SourcesVar ${ARGV4})
	#message(STATUS "[PCHSupport_26] SourcesVar: ${SourcesVar}" )

	foreach(file ${SourcesVar})
		get_filename_component(_abs_file ${file} ABSOLUTE)
		ADD_PRECOMPILED_HEADER_TO_SOURCE(${_targetName} ${_abs_file} ${_output}  ${_pch_target} ${_outdir} ${_dowarn})
		#get_source_file_property(_src_prop ${_abs_file} COMPILE_FLAGS)
		#message(STATUS "[PCHSupport_26] ${_abs_file}: ${_src_prop}" )
	endforeach()
	ADD_PRECOMPILED_HEADER_TARGET(${_targetName} ${_output}  ${_pch_target} ${_outdir} ${_dowarn})
endif()
  
endmacro(ADD_PRECOMPILED_HEADER)


# Generates the use of precompiled in a target,
# without using depency targets (2 extra for each target)
# Using Visual, must also add ${_targetName}_pch to sources
# Not needed by Xcode

macro(GET_NATIVE_PRECOMPILED_HEADER _targetName _input)

	if(CMAKE_GENERATOR MATCHES Visual*)

		set(_dummy_str "#include \"${_input}\"\n"
										"// This is required to suppress LNK4221.  Very annoying.\n"
										"void *g_${_targetName}Dummy = 0\;\n")

		# Use of cxx extension for generated files (as Qt does)
		set(${_targetName}_pch ${CMAKE_CURRENT_BINARY_DIR}/${_targetName}_pch.cxx)
		if(EXISTS ${${_targetName}_pch})
			# Check if contents is the same, if not rewrite
			# todo
		else(EXISTS ${${_targetName}_pch})
			file(WRITE ${${_targetName}_pch} ${_dummy_str})
		endif(EXISTS ${${_targetName}_pch})
	endif(CMAKE_GENERATOR MATCHES Visual*)

endmacro(GET_NATIVE_PRECOMPILED_HEADER)


macro(ADD_NATIVE_PRECOMPILED_HEADER _targetName _input)

	if( "${ARGN}" STREQUAL "0")
		set(_dowarn 0)
	else( "${ARGN}" STREQUAL "0")
		set(_dowarn 1)
	endif("${ARGN}" STREQUAL "0")
	
	if(CMAKE_GENERATOR MATCHES Visual*)
		# Auto include the precompile (useful for moc processing, since the use of 
		# precompiled is specified at the target level
		# and I don't want to specifiy /F- for each moc/res/ui generated files (using Qt)

		get_target_property(oldProps ${_targetName} COMPILE_FLAGS)
		if (${oldProps} MATCHES NOTFOUND)
			set(oldProps "")
		endif(${oldProps} MATCHES NOTFOUND)

		set(newProperties "${oldProps} /Yu\"${_input}\" /FI\"${_input}\"")
		set_target_properties(${_targetName} PROPERTIES COMPILE_FLAGS "${newProperties}")
		
		#also inlude ${oldProps} to have the same compile options 
		set_source_files_properties(${${_targetName}_pch} PROPERTIES COMPILE_FLAGS "${oldProps} /Yc\"${_input}\"")
		
	else(CMAKE_GENERATOR MATCHES Visual*)
	
		if (CMAKE_GENERATOR MATCHES Xcode)
			# For Xcode, cmake needs my patch to process
			# GCC_PREFIX_HEADER and GCC_PRECOMPILE_PREFIX_HEADER as target properties
			
			get_target_property(oldProps ${_targetName} COMPILE_FLAGS)
			if (${oldProps} MATCHES NOTFOUND)
				set(oldProps "")
			endif(${oldProps} MATCHES NOTFOUND)

			# When buiding out of the tree, precompiled may not be located
			# Use full path instead.
			get_filename_component(fullPath ${_input} ABSOLUTE)

			set_target_properties(${_targetName} PROPERTIES XCODE_ATTRIBUTE_GCC_PREFIX_HEADER "${fullPath}")
			set_target_properties(${_targetName} PROPERTIES XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER "YES")

		else (CMAKE_GENERATOR MATCHES Xcode)

			#Fallback to the "old" precompiled suppport
			#ADD_PRECOMPILED_HEADER(${_targetName} ${_input} ${_dowarn})
		endif(CMAKE_GENERATOR MATCHES Xcode)
	endif(CMAKE_GENERATOR MATCHES Visual*)

endmacro(ADD_NATIVE_PRECOMPILED_HEADER)
