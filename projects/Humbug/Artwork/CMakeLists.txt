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

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT( Humbug_Artwork )

SET(${PROJECT_NAME}_DIR "${CMAKE_CURRENT_SOURCE_DIR}"  CACHE TYPE PATH)
#SET(${PROJECT_NAME}_WORKDIR "${CMAKE_CURRENT_BINARY_DIR}"  CACHE TYPE PATH)
SET(${PROJECT_NAME}_WORKDIR "${PROJECT_SOURCE_DIR}/Work"  CACHE TYPE PATH)
#SET(Humbug_Artwork_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/Work)

SET(Humbug_Artwork_Update_Target "Update_Artwork")

SET(USE_MAGICK TRUE)
SET(USE_INKSCAPE TRUE)

# local project settings
INCLUDE (bindings)

IF( ImageMagick_FOUND OR INKSCAPE_EXECUTABLE_FOUND )


IF(NOT IMGCONVERSION_CMAKE_DEBUG)
	SET(IMGCONVERSION_CMAKE_DEBUG OFF)
ENDIF()

set(IMGCONVERSION_TARGETS)


FUNCTION(ADD_IMGCONVERSION_TARGET _targetname _imgconv_output_dir _inp_image_source_file _format)

	#SET(_imgconv_output_dir ${PROJECT_SOURCE_DIR}/Work)
	SET(_additional_path ${ARGV4})

	GET_FILENAME_COMPONENT(_image_source_file  ${_inp_image_source_file} ABSOLUTE)
	GET_FILENAME_COMPONENT(_file_namef  ${_image_source_file} NAME)
	GET_FILENAME_COMPONENT(_file_ext  ${_image_source_file} EXT)
	GET_FILENAME_COMPONENT(_file_name  ${_image_source_file} NAME_WE)
	GET_FILENAME_COMPONENT(_file_path  ${_inp_image_source_file} PATH)
	file(RELATIVE_PATH _file_rel "${PROJECT_SOURCE_DIR}" "${_image_source_file}")
	GET_FILENAME_COMPONENT(_file_rel_path  ${_file_rel} PATH)
	IF(IMGCONVERSION_CMAKE_DEBUG)
		MESSAGE(STATUS "[IMGCONV] processing ${_file_namef}")
	ENDIF()
	
	SET(_imgconv_final_output_dir "${_imgconv_output_dir}/${_file_rel_path}")
	#MESSAGE(STATUS "[IMGCONV] _imgconv_final_output_dir: ${_imgconv_final_output_dir}")
	#MESSAGE(STATUS "[IMGCONV-XXX]  _additional_path=${_additional_path}")
	#MESSAGE(STATUS "[IMGCONV-XXX]  _file_rel=${_file_rel} _file_path=${_file_path} _image_source_file=${_image_source_file}")
	#SET(_out_file_fullpath  "${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${_file_name}.${_format}")
	#SET(_out_file_fullpath  "${PROJECT_BINARY_DIR}/${_file_name}.${_format}")
	IF(_additional_path)
		SET(_out_file_fullpath  "${_imgconv_output_dir}/${_additional_path}/${_file_name}.${_format}")
		#MESSAGE(STATUS "[IMGCONV] HAS _additional_path")
	ELSE()
		SET(_out_file_fullpath  "${_imgconv_output_dir}/${_file_rel_path}/${_file_name}.${_format}")
	ENDIF()
	#MESSAGE(STATUS "[IMGCONV] output ${_out_file_fullpath}")


	SET(_inkscape_exts ".svg")
	list(FIND _inkscape_exts ${_file_ext} _val_found)
	IF(${_val_found} GREATER -1 AND INKSCAPE_EXECUTABLE_FOUND)
		# Inkscape part
		# inkscape --without-gui --file=$$i --export-png=$$o
#		MESSAGE(STATUS "[IMGCONV] USING INKSCAPE")
		
		SET(Build_Image_CMD ${INKSCAPE_EXECUTABLE})
		SET(Build_Image_OPTIONS --without-gui)
		#SET(Build_Image_ARGUMENTS --file=\"${_image_source_file}\" --export-png=\"${_file_name}.${_format}\")
		SET(Build_Image_ARGUMENTS --file=\"${_image_source_file}\" --export-png=\"${_out_file_fullpath}\")
	ELSE()
		# ImageMagick part
		# convert -layers merge infile.psd outfile.png
		SET(Build_Image_CMD ${IMAGEMAGICK_CONVERT_EXECUTABLE})
		SET(Build_Image_OPTIONS -layers merge)
		#SET(Build_Image_ARGUMENTS "\"${_image_source_file}\" \"${_file_name}.${_format}\"")
		SET(Build_Image_ARGUMENTS "\"${_image_source_file}\" \"${_out_file_fullpath}\"")
		#SET(Build_Image_ARGUMENTS "${_image_source_file}")
	ENDIF()

	#SEPARATE_ARGUMENTS(Build_Image_ARGUMENTS_LIST WINDOWS_COMMAND "${Build_Image_ARGUMENTS}")
#	MESSAGE(STATUS "[IMGCONV-X] DEPENDS ${_image_source_file}")
#	MESSAGE(STATUS "[IMGCONV-X] OUTPUT ${_out_file_fullpath}")
	
	ADD_CUSTOM_COMMAND(
		OUTPUT "${_out_file_fullpath}"
		POST_BUILD
		COMMAND ${Build_Image_CMD} ${Build_Image_OPTIONS} ${Build_Image_ARGUMENTS} && touch ${_imgconv_final_output_dir}
		DEPENDS "${_image_source_file}"
		COMMENT "Convert ${_file_namef} Image to ${_file_name}.${_format}." 
	)
	list(APPEND IMGCONVERSION_TARGETS "${_out_file_fullpath}")
	SET(IMGCONVERSION_TARGETS ${IMGCONVERSION_TARGETS} PARENT_SCOPE)
	SET_SOURCE_FILES_PROPERTIES("${_out_file_fullpath}" PROPERTIES GENERATED 1)

	IF(IMGCONVERSION_CMAKE_DEBUG)
		MESSAGE(STATUS "[IMGCONV] ${Build_Image_CMD} ${Build_Image_OPTIONS} ${Build_Image_ARGUMENTS}")
	ENDIF()
ENDFUNCTION()

#ADD_IMGCONVERSION_TARGET(BI ${CMAKE_CURRENT_SOURCE_DIR}/footer.psd)

#FILE(GLOB IMAGES_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.psd;${PROJECT_SOURCE_DIR}/*.svg)
FILE(GLOB_RECURSE IMAGES_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.psd;${PROJECT_SOURCE_DIR}/*.svg)


SET(ADDITIONAL_IMAGES_SOURCE_FILES 
	    #${CMAKE_CURRENT_SOURCE_DIR}/Icons/nase.psd
	    ${CMAKE_CURRENT_SOURCE_DIR}/Icons/nase.psd
)

#SET(_und_const_match "(^D:/E/Projects/C\\+\\+/Humbug/projects/Humbug/Artwork/UnderConstruction/.*)")
SET(_und_const_match "${PROJECT_SOURCE_DIR}/UnderConstruction/")
FOREACH(f ${IMAGES_SOURCE_FILES})
		string(FIND "${f}" "${_und_const_match}" _und_const_result)
		#MESSAGE(STATUS "[IMGCONV] _und_const_result ${_und_const_result}.")
		#IF("${f}" MATCHES ${_und_const_match})
		IF(_und_const_result EQUAL 0)
			IF(IMGCONVERSION_CMAKE_DEBUG)
				MESSAGE(STATUS "[IMGCONV] Skipping ${f}.")
			ENDIF()
			LIST(REMOVE_ITEM IMAGES_SOURCE_FILES ${f} )
		ENDIF()
ENDFOREACH()


FOREACH(f ${IMAGES_SOURCE_FILES})
#		MESSAGE(STATUS "IMG: ${f}")
		ADD_IMGCONVERSION_TARGET(Artwork ${${PROJECT_NAME}_WORKDIR} ${f} png)
ENDFOREACH()

#ADD_IMGCONVERSION_TARGET(Artwork ${${PROJECT_NAME}_WORKDIR} Icons/nase.psd png AnotherFolder)

# ${IMAGEMAGICK_CONVERT_EXECUTABLE}
ADD_CUSTOM_TARGET(Artwork ALL DEPENDS ${IMGCONVERSION_TARGETS})
SET_TARGET_PROPERTIES(Artwork
	PROPERTIES
	#EXCLUDE_FROM_DEFAULT_BUILD
	EXCLUDE_FROM_ALL_BUILD
	TRUE
)

#ADD_CUSTOM_TARGET(Artwork ALL DEPENDS "${PROJECT_BINARY_DIR}/footer.png" "${PROJECT_BINARY_DIR}/footer2.png")
#ADD_CUSTOM_TARGET(Artwork ALL DEPENDS "${PROJECT_BINARY_DIR}/footer.png" )
#MESSAGE(STATUS "[IMGCONV-AAAA] IMGCONVERSION_TARGETS: ${IMGCONVERSION_TARGETS}")
#ADD_CUSTOM_TARGET(Artwork ALL DEPENDS "${PROJECT_BINARY_DIR}/footer.png" )
#ADD_DEPENDENCIES(Artwork ${PROJECT_BINARY_DIR}/footer2.png)




ELSE( ImageMagick_FOUND OR INKSCAPE_EXECUTABLE_FOUND )
	MESSAGE(STATUS "Not using ImageMagick.")
ENDIF( ImageMagick_FOUND OR INKSCAPE_EXECUTABLE_FOUND )
