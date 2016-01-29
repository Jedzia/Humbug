#SET(ZIPPCKG_ZIP_COMMAND )
  
IF( NOT ZIPPCKG_ZIP_COMMAND)  
#	FIND_PROGRAM(ZIPPCKG_EXECUTABLE wzzip PATHS "$ENV{ProgramFiles}/WinZip" "C:/Program Files/WinZip")
#	IF(ZIPPCKG_EXECUTABLE)
##	  SET(ZIPPCKG_ZIP_COMMAND "\"${ZIPPCKG_EXECUTABLE}\" -P \"<ARCHIVE>\" @<FILELIST>"  CACHE TYPE STRING FORCE)
#	  SET(ZIPPCKG_ZIP_COMMAND "-P \"<ARCHIVE>\" @<FILELIST>"  CACHE TYPE STRING FORCE)
#	  SET(ZIPPCKG_ZIP_NEED_QUOTES TRUE  CACHE TYPE BOOL FORCE)
#	ENDIF(ZIPPCKG_EXECUTABLE)

	IF(NOT ZIPPCKG_EXECUTABLE)
	  FIND_PROGRAM(ZIPPCKG_EXECUTABLE 7z PATHS "D:/Program Files (x86)/7-ZIP_64_bit" "$ENV{ProgramFiles}/7-Zip" "$ENV{ProgramFiles(x86)}/7-ZIP_64_bit" "$ENV{ProgramW6432}/7-ZIP_64_bit") 
	  IF(ZIPPCKG_EXECUTABLE)
#		SET(ZIPPCKG_ZIP_COMMAND "\"${ZIPPCKG_EXECUTABLE}\" a -tzip \"<ARCHIVE>\" @<FILELIST>" CACHE TYPE STRING FORCE)
		IF(LINUX OR UNIX)
			SET(ZIPPCKG_ZIP_COMMAND "a -tzip <ARCHIVE> @<FILELIST>" CACHE TYPE STRING FORCE)
			SET(ZIPPCKG_ZIP_NEED_QUOTES TRUE CACHE TYPE BOOL FORCE)
		ELSE()
			SET(ZIPPCKG_ZIP_COMMAND "a -tzip \"<ARCHIVE>\" @<FILELIST>" CACHE TYPE STRING FORCE)
			SET(ZIPPCKG_ZIP_NEED_QUOTES TRUE CACHE TYPE BOOL FORCE)
		#MESSAGE(FATAL_ERROR "UNIX")
		ENDIF()
	  ENDIF(ZIPPCKG_EXECUTABLE)
	ENDIF(NOT ZIPPCKG_EXECUTABLE)

	IF(NOT ZIPPCKG_EXECUTABLE)
	  FIND_PACKAGE(Cygwin)
	  FIND_PROGRAM(ZIPPCKG_EXECUTABLE zip PATHS "${CYGWIN_INSTALL_PATH}/bin")
	  IF(ZIPPCKG_EXECUTABLE)
#		SET(ZIPPCKG_ZIP_COMMAND "\"${ZIPPCKG_EXECUTABLE}\" -r \"<ARCHIVE>\" . -i@<FILELIST>" CACHE TYPE STRING FORCE)
		SET(ZIPPCKG_ZIP_COMMAND "-r \"<ARCHIVE>\" . -i@<FILELIST>" CACHE TYPE STRING FORCE)
		SET(ZIPPCKG_ZIP_NEED_QUOTES FALSE CACHE TYPE BOOL FORCE)
	  ENDIF(ZIPPCKG_EXECUTABLE)
	ENDIF(NOT ZIPPCKG_EXECUTABLE)

#SET(ZIPPCKG_EXECUTABLE "${ZIPPCKG_EXECUTABLE}"  CACHE STRING "ZIPPCKG_EXECUTABLE" )

ENDIF( NOT ZIPPCKG_ZIP_COMMAND)  

# CREATEPACKAGE(PACKAGENAME MakeVFS ${VFS_PACKAGE_SOURCE_FILES} base_data dingens.zip)
FUNCTION(CREATEPACKAGE root_target target VFS_PACKAGE_SOURCE_FILES VFS_PACKAGE_DIR VFS_PACKAGE_NAME)

	#string(REGEX MATCHALL "[a-zA-Z]+\ |[a-zA-Z]+$" VFS_PACKAGE_SOURCE_FILES "${VFS_PACKAGE_SOURCE_FILES}")
IF(WIN32)
	separate_arguments(VFS_PACKAGE_SOURCE_FILES_L WINDOWS_COMMAND "${VFS_PACKAGE_SOURCE_FILES}")
ELSE()
	separate_arguments(VFS_PACKAGE_SOURCE_FILES_L UNIX_COMMAND "${VFS_PACKAGE_SOURCE_FILES}")
	string(REPLACE ";" " " VFS_PACKAGE_SOURCE_FILES_L ${VFS_PACKAGE_SOURCE_FILES_L})
ENDIF()

	SET(VFS_PACKAGE_PATH ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${VFS_PACKAGE_DIR} )
	SET(VFS_PACKAGE_INSTALL_FILE ${PROJECT_BINARY_DIR}/Release/${VFS_PACKAGE_DIR}/${VFS_PACKAGE_NAME} )
	SET(VFS_PACKAGE_FILE ${VFS_PACKAGE_PATH}/${VFS_PACKAGE_NAME} )
	execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${VFS_PACKAGE_PATH})

	#set(ZIPPCKG_ARGUMENTS "Drecksau")
	string(REPLACE "@<FILELIST>" "${VFS_PACKAGE_SOURCE_FILES_L}" ZIPPCKG_ARGUMENTS ${ZIPPCKG_ZIP_COMMAND})
	string(REPLACE "<ARCHIVE>" "${VFS_PACKAGE_FILE}" ZIPPCKG_ARGUMENTS ${ZIPPCKG_ARGUMENTS})
	#message(STATUS "ZIPPCKG_ARGUMENTS = ${ZIPPCKG_ARGUMENTS}")
IF(WIN32)
	#separate_arguments(ZIPPCKG_ARGUMENTS_LIST WINDOWS_COMMAND "${ZIPPCKG_ARGUMENTS}")
	SET(ZIPPCKG_ARGUMENTS_LIST "${ZIPPCKG_ARGUMENTS}")
ELSE()
	separate_arguments(ZIPPCKG_ARGUMENTS_LIST UNIX_COMMAND "${ZIPPCKG_ARGUMENTS}")
ENDIF()
	#message(STATUS "ZIPPCKG_ARGUMENTS_LIST = ${ZIPPCKG_ARGUMENTS_LIST}")

	# POST_BUILD TARGET Build package file. 
	#ADD_CUSTOM_TARGET(${target} ALL DEPENDS ${VFS_PACKAGE_SOURCE_FILES})
	ADD_CUSTOM_TARGET(${target} ALL DEPENDS ${VFS_PACKAGE_FILE})
	ADD_CUSTOM_COMMAND(
		OUTPUT ${VFS_PACKAGE_FILE}
		POST_BUILD
		COMMAND ${ZIPPCKG_EXECUTABLE} ${ZIPPCKG_ARGUMENTS_LIST}
		DEPENDS ${VFS_PACKAGE_SOURCE_FILES}
		COMMENT "Build ${VFS_PACKAGE_FILE} package-file." 
	)

	ADD_DEPENDENCIES(${root_target} ${target})

	MESSAGE(STATUS "[CREATEPACKAGE] VFS_PACKAGE_SOURCE_FILES: ${VFS_PACKAGE_SOURCE_FILES}")

	INSTALL(FILES 
			${VFS_PACKAGE_INSTALL_FILE}
		DESTINATION bin/${VFS_PACKAGE_DIR}
		COMPONENT Resources
	)


ENDFUNCTION(CREATEPACKAGE)
