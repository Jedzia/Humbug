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

# local project settings
INCLUDE (bindings)

IF( ImageMagick_FOUND )

ADD_CUSTOM_TARGET(BI ALL DEPENDS ${IMAGES_SOURCE_FILES})

SET(IMAGES_SOURCE_FILES 
	    ${CMAKE_CURRENT_SOURCE_DIR}/footer.psd
)

#FILE(GLOB playground_SDL_headers ${PROJECT_SOURCE_DIR}/*.psd)
FOREACH(f ${IMAGES_SOURCE_FILES})
	GET_FILENAME_COMPONENT(_target_name  ${f} NAME_WE)
		SET(_target_name "SDL_${_target_name}")
		#ADD_EXECUTABLE(${_target_name} ${f})
		#TARGET_LINK_LIBRARIES(${_target_name} ${SDL_LIBRARY})
ENDFOREACH()

# ${IMAGEMAGICK_CONVERT_EXECUTABLE}

SET(Build_Image_OPTIONS -layers merge)
#SET(Build_Image_ARGUMENTS "${IMAGES_SOURCE_FILES} test.jpg")
SET(Build_Image_ARGUMENTS "${IMAGES_SOURCE_FILES}")
SEPARATE_ARGUMENTS(Build_Image_ARGUMENTS_LIST WINDOWS_COMMAND "${Build_Image_ARGUMENTS}")

ADD_CUSTOM_COMMAND(
	#OUTPUT ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${XSD_LIBRARY_DEBUG}
	TARGET BI
	POST_BUILD
	COMMAND ${IMAGEMAGICK_CONVERT_EXECUTABLE} ${Build_Image_OPTIONS} ${Build_Image_ARGUMENTS_LIST}
	# DEPENDS Humbug
	COMMENT "Convert Images." 
)
#ADD_DEPENDENCIES(BI BI_CV)








ELSE( ImageMagick_FOUND )
	MESSAGE(STATUS "Not using ImageMagick.")
ENDIF( ImageMagick_FOUND )
