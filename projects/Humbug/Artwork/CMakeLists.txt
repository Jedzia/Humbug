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
SET(${PROJECT_NAME}_WORKDIR "${CMAKE_CURRENT_BINARY_DIR}"  CACHE TYPE PATH)


SET(USE_MAGICK TRUE)
SET(USE_INKSCAPE TRUE)

# local project settings
INCLUDE (bindings)

IF( ImageMagick_FOUND OR INKSCAPE_EXECUTABLE_FOUND )

#ADD_CUSTOM_TARGET(BI ALL DEPENDS ${IMAGES_SOURCE_FILES})
#SET_TARGET_PROPERTIES(BI
#	PROPERTIES
#	EXCLUDE_FROM_DEFAULT_BUILD
#	#EXCLUDE_FROM_ALL_BUILD
#	TRUE
#)

ADD_CUSTOM_TARGET(Artwork ALL)

SET(ADDITIONAL_IMAGES_SOURCE_FILES 
	    ${CMAKE_CURRENT_SOURCE_DIR}/footer.psd
)


IF(NOT IMGCONVERSION_CMAKE_DEBUG)
	SET(IMGCONVERSION_CMAKE_DEBUG ON)
ENDIF()

FUNCTION(ADD_IMGCONVERSION_TARGET _targetname _image_source_file _format)

	GET_FILENAME_COMPONENT(_file_namef  ${_image_source_file} NAME)
	GET_FILENAME_COMPONENT(_file_ext  ${_image_source_file} EXT)
	GET_FILENAME_COMPONENT(_file_name  ${_image_source_file} NAME_WE)
	GET_FILENAME_COMPONENT(_file_path  ${_image_source_file} PATH)
	IF(IMGCONVERSION_CMAKE_DEBUG)
		MESSAGE(STATUS "[IMGCONV] processing ${_file_namef}")
	ENDIF()
	#SET(_file_fullpath "${_file_path}/${_file_name}.png")
	#MESSAGE(STATUS "[IMGCONV] ${_file_fullpath}")
	#SET(_out_file_fullpath  "${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${_file_name}.${_format}")
	SET(_out_file_fullpath  "${PROJECT_BINARY_DIR}/${_file_name}.${_format}")
	MESSAGE(STATUS "[IMGCONV] output ${_out_file_fullpath}")


	SET(_inkscape_exts ".svg")
	list(FIND _inkscape_exts ${_file_ext} _val_found)
	IF(${_val_found} GREATER -1 AND INKSCAPE_EXECUTABLE_FOUND)
		# Inkscape part
		# inkscape --without-gui --file=$$i --export-png=$$o
#		MESSAGE(STATUS "[IMGCONV] USING INKSCAPE")
		
		SET(Build_Image_CMD ${INKSCAPE_EXECUTABLE})
		SET(Build_Image_OPTIONS --without-gui)
		SET(Build_Image_ARGUMENTS --file=\"${_image_source_file}\" --export-png=\"${_file_name}.${_format}\")
	ELSE()
		# ImageMagick part
		# convert -layers merge infile.psd outfile.png
		SET(Build_Image_CMD ${IMAGEMAGICK_CONVERT_EXECUTABLE})
		SET(Build_Image_OPTIONS -layers merge)
		SET(Build_Image_ARGUMENTS "\"${_image_source_file}\" \"${_file_name}.${_format}\"")
		#SET(Build_Image_ARGUMENTS "${_image_source_file}")
	ENDIF()

	#SEPARATE_ARGUMENTS(Build_Image_ARGUMENTS_LIST WINDOWS_COMMAND "${Build_Image_ARGUMENTS}")
#	ADD_CUSTOM_COMMAND(
#		# OUTPUT ${_out_file_fullpath}
#		TARGET ${_targetname}
#		POST_BUILD
#		COMMAND ${Build_Image_CMD} ${Build_Image_OPTIONS} ${Build_Image_ARGUMENTS}
#		# DEPENDS Humbug
#		COMMENT "Convert Image." 
#	)

	MESSAGE(STATUS "[IMGCONV-X] DEPENDS ${_image_source_file}")
	MESSAGE(STATUS "[IMGCONV-X] OUTPUT ${_out_file_fullpath}")
	
	ADD_CUSTOM_COMMAND(
		OUTPUT "${_out_file_fullpath}"
		POST_BUILD
		COMMAND ${Build_Image_CMD} ${Build_Image_OPTIONS} ${Build_Image_ARGUMENTS}
		#MAIN_DEPENDENCY Artwork${_file_namef}
		DEPENDS "${_image_source_file}"
		COMMENT "Convert ${_file_name} Image to ${_file_name}.${_format}." 
	)
	ADD_CUSTOM_TARGET(Artwork${_file_namef} ALL DEPENDS "${_out_file_fullpath}")
	ADD_DEPENDENCIES(Artwork Artwork${_file_namef})

	IF(IMGCONVERSION_CMAKE_DEBUG)
		MESSAGE(STATUS "[IMGCONV] ${Build_Image_CMD} ${Build_Image_OPTIONS} ${Build_Image_ARGUMENTS}")
	ENDIF()
	#ADD_DEPENDENCIES(BI BI_CV)
ENDFUNCTION()

#ADD_IMGCONVERSION_TARGET(BI ${CMAKE_CURRENT_SOURCE_DIR}/footer.psd)

FILE(GLOB IMAGES_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.psd;${PROJECT_SOURCE_DIR}/*.svg)
FOREACH(f ${IMAGES_SOURCE_FILES})
#		GET_FILENAME_COMPONENT(_file_name  ${f} NAME_WE)
#		GET_FILENAME_COMPONENT(_file_path  ${f} PATH)
#		SET(_file_fullpath "${_file_path}/${_file_name}.png")
		ADD_IMGCONVERSION_TARGET(BI ${f} png)
#		MESSAGE(STATUS "IMG: ${f}")
		#ADD_EXECUTABLE(${_file_fullpath} ${f})
		#TARGET_LINK_LIBRARIES(${_file_fullpath} ${SDL_LIBRARY})
ENDFOREACH()

# ${IMAGEMAGICK_CONVERT_EXECUTABLE}




ELSE( ImageMagick_FOUND OR INKSCAPE_EXECUTABLE_FOUND )
	MESSAGE(STATUS "Not using ImageMagick.")
ENDIF( ImageMagick_FOUND OR INKSCAPE_EXECUTABLE_FOUND )
