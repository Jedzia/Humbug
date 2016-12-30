##---------------------------------------------------------------------------
## $RCSfile$
## $Source$
## $Revision$
## $Date$
##---------------------------------------------------------------------------
## Author:      Jedzia
## Copyright:   (c) Jedzia, 2011
## License:     GPL License
##---------------------------------------------------------------------------
##---------------------------------------------------
## 
##--------------------------------------------------- 

cmake_minimum_required(VERSION 2.8)

project( HumbugGL_Artwork )

set(${PROJECT_NAME}_DIR "${CMAKE_CURRENT_SOURCE_DIR}"  CACHE TYPE PATH)
#set(${PROJECT_NAME}_WORKDIR "${CMAKE_CURRENT_BINARY_DIR}"  CACHE TYPE PATH)
set(${PROJECT_NAME}_WORKDIR "${PROJECT_SOURCE_DIR}/Work"  CACHE TYPE PATH)
#set(HumbugGL_Artwork_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/Work)

set(HumbugGL_Artwork_Update_Target "Update_Artwork")

set(USE_MAGICK TRUE)
set(USE_INKSCAPE TRUE)

# local project settings
include (bindings)

if( ImageMagick_FOUND OR INKSCAPE_EXECUTABLE_FOUND )


if(NOT IMGCONVERSION_CMAKE_DEBUG)
	set(IMGCONVERSION_CMAKE_DEBUG OFF)
endif()

set(IMGCONVERSION_TARGETS)


function(ADD_IMGCONVERSION_TARGET _targetname _imgconv_output_dir _inp_image_source_file _format)

	#set(_imgconv_output_dir ${PROJECT_SOURCE_DIR}/Work)
	set(_additional_path ${ARGV4})

	get_filename_component(_image_source_file  ${_inp_image_source_file} ABSOLUTE)
	get_filename_component(_file_namef  ${_image_source_file} NAME)
	get_filename_component(_file_ext  ${_image_source_file} EXT)
	get_filename_component(_file_name  ${_image_source_file} NAME_WE)
	get_filename_component(_file_path  ${_inp_image_source_file} PATH)
	file(RELATIVE_PATH _file_rel "${PROJECT_SOURCE_DIR}" "${_image_source_file}")
	get_filename_component(_file_rel_path  ${_file_rel} PATH)
	if(IMGCONVERSION_CMAKE_DEBUG)
		message(STATUS "[IMGCONV] processing ${_file_namef}")
	endif()
	
	set(_imgconv_final_output_dir "${_imgconv_output_dir}/${_file_rel_path}")
	#message(STATUS "[IMGCONV] _imgconv_final_output_dir: ${_imgconv_final_output_dir}")
	#message(STATUS "[IMGCONV-XXX]  _additional_path=${_additional_path}")
	#message(STATUS "[IMGCONV-XXX]  _file_rel=${_file_rel} _file_path=${_file_path} _image_source_file=${_image_source_file}")
	#set(_out_file_fullpath  "${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${_file_name}.${_format}")
	#set(_out_file_fullpath  "${PROJECT_BINARY_DIR}/${_file_name}.${_format}")
	if(_additional_path)
		set(_out_file_fullpath  "${_imgconv_output_dir}/${_additional_path}/${_file_name}.${_format}")
		#message(STATUS "[IMGCONV] HAS _additional_path")
	else()
		set(_out_file_fullpath  "${_imgconv_output_dir}/${_file_rel_path}/${_file_name}.${_format}")
	endif()
	#message(STATUS "[IMGCONV] output ${_out_file_fullpath}")


	set(_inkscape_exts ".svg")
	list(FIND _inkscape_exts ${_file_ext} _val_found)
	if(${_val_found} GREATER -1 AND INKSCAPE_EXECUTABLE_FOUND)
		# Inkscape part
		# inkscape --without-gui --file=$$i --export-png=$$o
#		message(STATUS "[IMGCONV] USING INKSCAPE")
		
		set(Build_Image_CMD ${INKSCAPE_EXECUTABLE})
		set(Build_Image_OPTIONS --without-gui)
		#set(Build_Image_ARGUMENTS --file=\"${_image_source_file}\" --export-png=\"${_file_name}.${_format}\")
		set(Build_Image_ARGUMENTS --file=\"${_image_source_file}\" --export-png=\"${_out_file_fullpath}\")
	else()
		# ImageMagick part
		# convert -layers merge infile.psd outfile.png
		set(Build_Image_CMD ${IMAGEMAGICK_CONVERT_EXECUTABLE})
		#set(Build_Image_OPTIONS -layers merge)
		set(Build_Image_OPTIONS -background transparent -flatten)
		#set(Build_Image_ARGUMENTS "\"${_image_source_file}\" \"${_file_name}.${_format}\"")
		set(Build_Image_ARGUMENTS "\"${_image_source_file}\" \"${_out_file_fullpath}\"")
		#set(Build_Image_ARGUMENTS "${_image_source_file}")

		if(UNIX)
		  separate_arguments(Build_Image_ARGUMENTS UNIX_COMMAND "${Build_Image_ARGUMENTS}")
		endif(UNIX)
	endif()

	#separate_arguments(Build_Image_ARGUMENTS_LIST WINDOWS_COMMAND "${Build_Image_ARGUMENTS}")

#	message(STATUS "[IMGCONV-X] DEPENDS ${_image_source_file}")
#	message(STATUS "[IMGCONV-X] OUTPUT ${_out_file_fullpath}")
	
	add_custom_command(
		OUTPUT "${_out_file_fullpath}"
		POST_BUILD
		COMMAND ${Build_Image_CMD} ${Build_Image_OPTIONS} ${Build_Image_ARGUMENTS} && touch ${_imgconv_final_output_dir}
		DEPENDS "${_image_source_file}"
		COMMENT "Convert ${_file_namef} Image to ${_file_name}.${_format}." 
	)
	list(APPEND IMGCONVERSION_TARGETS "${_out_file_fullpath}")
	set(IMGCONVERSION_TARGETS ${IMGCONVERSION_TARGETS} PARENT_SCOPE)
	set_source_files_properties("${_out_file_fullpath}" PROPERTIES GENERATED 1)

	if(IMGCONVERSION_CMAKE_DEBUG)
		message(STATUS "[IMGCONV] ${Build_Image_CMD} ${Build_Image_OPTIONS} ${Build_Image_ARGUMENTS}")
	endif()
endfunction(ADD_IMGCONVERSION_TARGET) 

function(ADD_IMGCONVERSION_TARGET_MULTI _targetname _imgconv_output_dir _inp_image_source_file _tile _format )

	#set(_imgconv_output_dir ${PROJECT_SOURCE_DIR}/Work)
	set(_additional_path ${ARGV5})

	get_filename_component(_image_source_file  ${_inp_image_source_file} ABSOLUTE)
	get_filename_component(_file_namef  ${_image_source_file} NAME)
	get_filename_component(_file_ext  ${_image_source_file} EXT)
	get_filename_component(_file_name  ${_image_source_file} NAME_WE)
	get_filename_component(_file_path  ${_inp_image_source_file} PATH)
	file(RELATIVE_PATH _file_rel "${PROJECT_SOURCE_DIR}" "${_image_source_file}")
	get_filename_component(_file_rel_path  ${_file_rel} PATH)
	if(IMGCONVERSION_CMAKE_DEBUG)
		message(STATUS "[IMGCONV-MULTI] processing ${_file_namef}")
	endif()
	
	set(_imgconv_final_output_dir "${_imgconv_output_dir}/${_file_rel_path}")
	#message(STATUS "[IMGCONV] _imgconv_final_output_dir: ${_imgconv_final_output_dir}")
	#message(STATUS "[IMGCONV-XXX]  _additional_path=${_additional_path}")
	#message(STATUS "[IMGCONV-XXX]  _file_rel=${_file_rel} _file_path=${_file_path} _image_source_file=${_image_source_file}")
	#set(_out_file_fullpath  "${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${_file_name}.${_format}")
	#set(_out_file_fullpath  "${PROJECT_BINARY_DIR}/${_file_name}.${_format}")
	if(_additional_path)
		set(_out_file_fullpath      "${_imgconv_output_dir}/${_additional_path}/${_file_name}.${_format}")
		set(_out_sequence_dir  "${CMAKE_CURRENT_BINARY_DIR}/${_additional_path}")
		set(_out_sequence_fullpath  "${_out_sequence_dir}/${_file_name}-%%03d.${_format}")
		set(_in_Mfile_fullpath      "${_out_sequence_dir}/${_file_name}-*")
		set(_in_Mfirstfile_fullpath  "${_out_sequence_dir}/${_file_name}-000.${_format}")
		#message(STATUS "[IMGCONV] HAS _additional_path")
	else()
		set(_out_file_fullpath      "${_imgconv_output_dir}/${_file_rel_path}/${_file_name}.${_format}")
#		set(_out_sequence_fullpath  "${_imgconv_output_dir}/${_file_rel_path}/${_file_name}-%%03d.${_format}")
		set(_out_sequence_dir  "${CMAKE_CURRENT_BINARY_DIR}/${_file_rel_path}")
		set(_out_sequence_fullpath  "${_out_sequence_dir}/${_file_name}-%%03d.${_format}")
		set(_in_Mfile_fullpath      "${_out_sequence_dir}/${_file_name}-*")
		set(_in_Mfirstfile_fullpath  "${_out_sequence_dir}/${_file_name}-000.${_format}")
	endif()
	#message(STATUS "[IMGCONV] output ${_out_file_fullpath}")


	set(_inkscape_exts ".svg")
	list(FIND _inkscape_exts ${_file_ext} _val_found)
#	if(${_val_found} GREATER -1 AND INKSCAPE_EXECUTABLE_FOUND)
#		# Inkscape part
#		# inkscape --without-gui --file=$$i --export-png=$$o
#		message(STATUS "[IMGCONV] USING INKSCAPE")
		
#		set(Build_Image_CMD ${INKSCAPE_EXECUTABLE})
#		set(Build_Image_OPTIONS --without-gui)
#		#set(Build_Image_ARGUMENTS --file=\"${_image_source_file}\" --export-png=\"${_file_name}.${_format}\")
#		set(Build_Image_ARGUMENTS --file=\"${_image_source_file}\" --export-png=\"${_out_file_fullpath}\")
#	else()
		# ImageMagick part
		# convert -layers merge infile.psd outfile.png
		set(Build_Image_CMD ${IMAGEMAGICK_CONVERT_EXECUTABLE})
		set(Montage_Image_CMD ${IMAGEMAGICK_MONTAGE_EXECUTABLE})
		#set(Build_Image_OPTIONS -layers merge)
		set(Build_Image_OPTIONS "-background transparent")
#		set(Montage_Image_OPTIONS -background none -geometry 256x256)
#		set(Montage_Image_OPTIONS -background none -geometry 49x480)
		set(Montage_Image_OPTIONS -background none -geometry ${_tile})
		#set(Build_Image_ARGUMENTS "\"${_image_source_file}\" \"${_file_name}.${_format}\"")
		set(Build_Image_ARGUMENTS "\"${_image_source_file}\" \"${_out_sequence_fullpath}\"")
		set(Montage_Image_ARGUMENTS "\"${_in_Mfile_fullpath}\" \"${_out_file_fullpath}\"")
		#set(Build_Image_ARGUMENTS "${_image_source_file}")

		if(UNIX)
		 # separate_arguments(Build_Image_ARGUMENTS UNIX_COMMAND "${Build_Image_ARGUMENTS}")
		endif(UNIX)
#	endif()

	#separate_arguments(Build_Image_ARGUMENTS_LIST WINDOWS_COMMAND "${Build_Image_ARGUMENTS}")

#	message(STATUS "[IMGCONV-X] DEPENDS ${_image_source_file}")
#	message(STATUS "[IMGCONV-X] Montage_Image_ARGUMENTS ${Montage_Image_ARGUMENTS}")


	#file(MAKE_DIRECTORY ${directory})
	set(_out_file_buildcmd  "${_out_sequence_dir}/${_file_name}.${_format}.cmd")
#	message(STATUS "[IMGCONV-X] _out_file_buildcmd ${_out_file_buildcmd}")
	message(STATUS "[IMGCONV-X] _in_Mfirstfile_fullpath ${_in_Mfirstfile_fullpath}")
	file(WRITE ${_out_file_buildcmd} "\"${Build_Image_CMD}\" ${Build_Image_OPTIONS} ${Build_Image_ARGUMENTS}" )
	add_custom_command(
		OUTPUT "${_in_Mfirstfile_fullpath}"
		POST_BUILD
#		COMMAND ${Build_Image_CMD} ${Build_Image_OPTIONS} ${Build_Image_ARGUMENTS} && touch ${_imgconv_final_output_dir}
		COMMAND ${_out_file_buildcmd}
		DEPENDS "${_image_source_file}"
		COMMENT "Converting ${_file_namef} Artbooks to ${_file_name}-*.${_format}." 
	)
	#list(APPEND IMGCONVERSION_TARGETS "${_out_file_fullpath}")
	set_source_files_properties("${_out_file_fullpath}" PROPERTIES GENERATED 1)

	add_custom_command(
		OUTPUT "${_out_file_fullpath}"
		POST_BUILD
		COMMAND ${Montage_Image_CMD} ${Montage_Image_OPTIONS} ${Montage_Image_ARGUMENTS} && touch ${_imgconv_final_output_dir}
		DEPENDS "${_in_Mfirstfile_fullpath}"
		COMMENT "Montage ${_file_name}-* Images to ${_file_name}.${_format}." 
	)
	list(APPEND IMGCONVERSION_TARGETS "${_out_file_fullpath}")
	set_source_files_properties("${_out_file_fullpath}" PROPERTIES GENERATED 1)

	set(IMGCONVERSION_TARGETS ${IMGCONVERSION_TARGETS} PARENT_SCOPE)

	if(IMGCONVERSION_CMAKE_DEBUG)
		message(STATUS "[IMGCONV] ${Build_Image_CMD} ${Build_Image_OPTIONS} ${Build_Image_ARGUMENTS}")
	endif()
endfunction(ADD_IMGCONVERSION_TARGET_MULTI) 
#ADD_IMGCONVERSION_TARGET(BI ${CMAKE_CURRENT_SOURCE_DIR}/footer.psd)

#file(GLOB IMAGES_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.psd;${PROJECT_SOURCE_DIR}/*.svg)
file(GLOB_RECURSE IMAGES_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.psd;${PROJECT_SOURCE_DIR}/*.svg;${PROJECT_SOURCE_DIR}/*.ai)


set(ADDITIONAL_IMAGES_SOURCE_FILES 
	    #${CMAKE_CURRENT_SOURCE_DIR}/Icons/nase.psd
	    ${CMAKE_CURRENT_SOURCE_DIR}/Icons/nase.psd
)

#set(_und_const_match "(^D:/E/Projects/C\\+\\+/HumbugGL/projects/HumbugGL/Artwork/UnderConstruction/.*)")
set(_und_const_match "${PROJECT_SOURCE_DIR}/UnderConstruction/")
foreach(f ${IMAGES_SOURCE_FILES})
		string(FIND "${f}" "${_und_const_match}" _und_const_result)
		#message(STATUS "[IMGCONV] _und_const_result ${_und_const_result}.")
		#if("${f}" MATCHES ${_und_const_match})
		if(_und_const_result EQUAL 0)
			if(IMGCONVERSION_CMAKE_DEBUG)
				message(STATUS "[IMGCONV] Skipping ${f}.")
			endif()
			list(REMOVE_ITEM IMAGES_SOURCE_FILES ${f} )
		endif()
endforeach()


foreach(f ${IMAGES_SOURCE_FILES})
		#message(STATUS "IMG: ${f}")
		if("${f}" MATCHES "Artwork/Sprites/Ship")
			#message(STATUS "SKIP IMG: ${f}")
			#ADD_IMGCONVERSION_TARGET_MULTI(Artwork ${${PROJECT_NAME}_WORKDIR} ${f} png)
			continue()
		endif()
		ADD_IMGCONVERSION_TARGET(Artwork ${${PROJECT_NAME}_WORKDIR} ${f} png)
endforeach()

#set(MULTI_IMAGES_SOURCE_FILES 
#	    ${CMAKE_CURRENT_SOURCE_DIR}/Sprites/Ship/Laser/Laser01.ai
#)

#foreach(f ${MULTI_IMAGES_SOURCE_FILES})
#		#message(STATUS "IMG: ${f}")
#		ADD_IMGCONVERSION_TARGET_MULTI(Artwork ${${PROJECT_NAME}_WORKDIR} ${f} 49x480 png)
#endforeach()

ADD_IMGCONVERSION_TARGET_MULTI(Artwork ${${PROJECT_NAME}_WORKDIR} ${CMAKE_CURRENT_SOURCE_DIR}/Sprites/Ship/Laser/Bullet01.ai 32x32 png)
ADD_IMGCONVERSION_TARGET_MULTI(Artwork ${${PROJECT_NAME}_WORKDIR} ${CMAKE_CURRENT_SOURCE_DIR}/Sprites/Ship/Laser/Laser01.ai 49x480 png)

#ADD_IMGCONVERSION_TARGET(Artwork ${${PROJECT_NAME}_WORKDIR} Icons/nase.psd png AnotherFolder)

# ${IMAGEMAGICK_CONVERT_EXECUTABLE}
add_custom_target(Artwork ALL DEPENDS ${IMGCONVERSION_TARGETS})
set_target_properties(Artwork
	PROPERTIES
	#EXCLUDE_FROM_DEFAULT_BUILD
	EXCLUDE_FROM_ALL_BUILD
	TRUE
)

#add_custom_target(Artwork ALL DEPENDS "${PROJECT_BINARY_DIR}/footer.png" "${PROJECT_BINARY_DIR}/footer2.png")
#add_custom_target(Artwork ALL DEPENDS "${PROJECT_BINARY_DIR}/footer.png" )
#message(STATUS "[IMGCONV-AAAA] IMGCONVERSION_TARGETS: ${IMGCONVERSION_TARGETS}")
#add_custom_target(Artwork ALL DEPENDS "${PROJECT_BINARY_DIR}/footer.png" )
#add_dependencies(Artwork ${PROJECT_BINARY_DIR}/footer2.png)




else( ImageMagick_FOUND OR INKSCAPE_EXECUTABLE_FOUND )
	message(STATUS "Not using ImageMagick.")
endif( ImageMagick_FOUND OR INKSCAPE_EXECUTABLE_FOUND )
