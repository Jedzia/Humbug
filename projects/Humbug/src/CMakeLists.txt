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
## !!!!!! we should use the internal FindwxWidgets.cmake !!!!!

#cmake_policy(SET CMP0005 NEW) # 
cmake_minimum_required(VERSION 2.8)

PROJECT( Humbug )

MESSAGE(STATUS         "!!!!!!!!!!!!!!!! CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME} !!!!!!!!!!")
INCLUDE (BoostExtensions)
#INCLUDE (PCHSupport_MSVC)
INCLUDE (PCHSupport)
INCLUDE (CopyResourcesToBuildTree)
INCLUDE (helpers)
INCLUDE (PackageCreate)

SET(USE_LIB_BOOST_COMPONENTS "system;filesystem;signals;program_options;serialization")
#SET(USE_LIB_BOOST TRUE CACHE BOOL "Use Boost libraries")
# Use Boost libraries for this project.
SET(USE_LIB_BOOST TRUE)

SET(USE_SDL TRUE)
SET(USE_SDL_IMAGE TRUE)
SET(USE_SDL_TTF TRUE)
#SET(USE_SDL_GFX TRUE)

SET(USE_LUA TRUE)

# local project settings
INCLUDE (bindings)

# Link explicitely to Microsoft.VC90.CRT version=9.0.30729.1
#ADD_DEFINITIONS("-D_BIND_TO_CURRENT_VCLIBS_VERSION=1")
# this does the same as above
#ADD_DEFINITIONS("-D_BIND_TO_CURRENT_MFC_VERSION=2")
#ADD_DEFINITIONS("-D_BIND_TO_CURRENT_CRT_VERSION=2")

# GUI implementation
SET(Humbug_MyGUI_headers 
		GUI/Hud.h
		GUI/DebugOverlay.h

		TestEventHandler.h
		TestThread.h
		TestTimer.h

		Screens/HopperScreen.h
		Screens/LuaScreen.h
		Screens/BlaScreen.h
		Screens/StartScreen.h
		Screens/TestScreen.h
		Screens/HighscoreScreen.h
		Screens/TileScreen.h
		Screens/SimpleScreen.h
		Screens/MenuScreen.h
		Screens/WavyTextFloat.h
)
SET(Humbug_MyGUI_sources 
		GUI/Hud.cpp
		GUI/DebugOverlay.cpp

		TestEventHandler.cpp
		TestThread.cpp
		TestTimer.cpp

		Screens/HopperScreen.cpp
		Screens/LuaScreen.cpp
		Screens/BlaScreen.cpp
		Screens/StartScreen.cpp
		Screens/TestScreen.cpp
		Screens/HighscoreScreen.cpp
		Screens/TileScreen.cpp
		Screens/SimpleScreen.cpp
		Screens/MenuScreen.cpp
		Screens/WavyTextFloat.cpp
)

SET(Humbug_Level_headers 
		Levels/TestLevel.h
		Levels/LevelA.h
)
SET(Humbug_Level_sources 
		Levels/TestLevel.cpp
		Levels/LevelA.cpp
)

# putting the sources together
SET(Humbug_headers 
		${Humbug_MyGUI_headers}
		${Humbug_Level_headers}

		HumbugFileLoader.h

		Input/PlayerKeys.h
		Input/PlayerKeys2.h
		Input/PlayerKeys3.h

	    Project/ProjectModel.h
)

SET(Humbug_sources 
		${Humbug_MyGUI_sources}
		${Humbug_Level_sources}

		Input/PlayerKeys.cpp
		Input/PlayerKeys2.cpp
		Input/PlayerKeys3.cpp

		HumbugFileLoader.cpp
	    main.cpp 
	    Project/ProjectModel.cpp
)


#SET(CMAKE_BUILD_TYPE DEBUG)

#INCLUDE_DIRECTORIES( ${CppStructz_INCLUDE_DIR} )
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${SDLIMAGE_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${SDLTTF_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${SDLGFX_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${HumbugShared_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${HumbugLib_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${GuiLib_INTERFACE_DIR})
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${LUABIND_INCLUDE_DIR})
# Move to bindings
IF(LINUX)
  INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
ENDIF(LINUX)


ADD_DEFINITIONS(${HumbugShared_DEFINITIONS})
IF(SDLIMAGE_FOUND)
  ADD_DEFINITIONS("-DHAVE_SDLIMAGE")
ENDIF(SDLIMAGE_FOUND)

# Move to bindings
IF(LINUX)
  ADD_DEFINITIONS("-DLINUX")
ENDIF(LINUX)

ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" Humbug_sources)

SOURCE_GROUP(Generated FILES ${res_outfiles} ${moc_outfiles} ${ui_outfiles} )
SOURCE_GROUP(Resources FILES ${Humbug_resfiles})
SOURCE_GROUP(GUI FILES ${Humbug_uifiles})
SOURCE_GROUP(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
SOURCE_GROUP(THeaders FILES ${Humbug_headers})
SOURCE_GROUP(TSources FILES ${Humbug_sources})

SET(Humbug_documents
		../Readme.md
		../docs/!DevelNotes.txt
)
SOURCE_GROUP(Docs FILES ${Humbug_documents})

# Move to bindings
SET(_GUI_DEP )
IF(WIN32)
  # Maybe here is the point for a Humbug_WINDOWS_CONSOLE subsystem switch.
  SET(_GUI_DEP WIN32)
ENDIF(WIN32)
ADD_EXECUTABLE(Humbug ${_GUI_DEP}
        stdafx.h
        ${DEBUG_DEFINITION_INCLUDES}
        defs.h 

        ${Humbug_headers}
        ${Humbug_sources} 
		${Humbug_documents}
)



SET(Pak01_PACKAGE_SOURCE_FILES 
		${PROJECT_SOURCE_DIR}/Icons/
	    ${Humbug_Artwork_DIR}/data/
		${HUMBUG_RESOURCES_DIR}/Fonts/
	    ${Humbug_Artwork_WORKDIR}/Hud/
	    ${Humbug_Artwork_WORKDIR}/Intro/
	    #${Humbug_Artwork_WORKDIR}/Screens/
	    ${Humbug_Artwork_WORKDIR}/Images/
	    ${Humbug_Artwork_WORKDIR}/Text/
		#${PROJECT_SOURCE_DIR}/Icons/blue.png
	    #${P_ROOT_PATH}/Artwork/footer.png
	    #${Humbug_Artwork_WORKDIR}/footer.png
	    ${Humbug_Artwork_DIR}/Sprites/Sprites/
	    ${Humbug_Artwork_DIR}/Moo.png
	    ${Humbug_Artwork_DIR}/Tiles/gfx/Tiles1.bmp
)
CREATEPACKAGE(Humbug MakeVFS "${Pak01_PACKAGE_SOURCE_FILES}" base_data Pak01.zip)
#ADD_DEPENDENCIES(MakeVFS Artwork)

SET(Pak02_PACKAGE_SOURCE_FILES 
	    ${Humbug_Artwork_DIR}/Hud/footer.psd
)
CREATEPACKAGE(MakeVFS MakeVFS01 "${Pak02_PACKAGE_SOURCE_FILES}" base_data Pak02.zip)

#ADD_CUSTOM_TARGET(generate_foo DEPENDS ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${XSD_LIBRARY_DEBUG})

Copy_DLL_To_Target(Humbug SDL_LIBRARY)
Copy_DLL_To_Target(Humbug SDLIMAGE_LIBRARY)
Copy_Files_To_Target(Humbug "${SDLIMAGE_LIBRARY_DLLS_EXT}")
Copy_DLL_To_Target(Humbug SDLTTF_LIBRARY)
Copy_Files_To_Target(Humbug "${SDLTTF_LIBRARY_DLLS_EXT}")
#Copy_ReleaseDLL_To_Target(Humbug ICU)

TargetLinkBoost(Humbug "filesystem;system;regex;signals;serialization")
TARGET_LINK_LIBRARIES(Humbug HumbugLib)
TARGET_LINK_LIBRARIES(Humbug HumbugShared)
TARGET_LINK_LIBRARIES(Humbug GuiLib)
TARGET_LINK_LIBRARIES(Humbug ${SDL_LIBRARY})
TARGET_LINK_LIBRARIES(Humbug ${SDLMAIN_LIBRARY})
TARGET_LINK_LIBRARIES(Humbug ${SDLIMAGE_LIBRARY})
TARGET_LINK_LIBRARIES(Humbug ${SDLTTF_LIBRARY})
IF(USE_SDL_GFX)
    TARGET_LINK_LIBRARIES(Humbug ${SDLGFX_LIBRARY})
ENDIF()


#TODO: without this does not compile under linux
IF(LINUX)
	TARGET_LINK_LIBRARIES(Humbug boost_serialization)
ENDIF(LINUX)


#TARGET_LINK_LIBRARIES(Humbug ${LUA_LIBRARY})
#TARGET_LINK_LIBRARIES(Humbug ${LUABIND_LIBRARY})
#TARGET_LINK_LIBRARIES(Humbug luabind)
#ADD_DEPENDENCIES(Humbug luabind)
#TARGET_LINK_LIBRARIES(Humbug ${LUABIND_LIBRARY})
# Message(WARNING "LUABIND: ${LUABIND}")
# A) Target-centric: target, header-file, precompiled header, [ warn on invalid header(-Winvalid-pch) ]
# B) individual sources specified: target, header-file, precompiled header, 
#    warn on invalid header(-Winvalid-pch), source files with header
ADD_PRECOMPILED_HEADER(Humbug stdafx.h stdafx.h.gch TRUE "${Humbug_sources}")

#SET_SOURCE_FILES_PROPERTIES( main.cpp
#       PROPERTIES OBJECT_DEPENDS ${CppStructz_DLL_DEBUG}
#)

#SET_SOURCE_FILES_PROPERTIES( ${Humbug_sources} #main.cpp
#       PROPERTIES OBJECT_DEPENDS "d:/Eigene Dateien/Projects/C++/Humbug/src/CppStructz/TestClass.cpp"
#)
#copy_resources_to_build_tree(Humbug)

INSTALL(TARGETS Humbug 
	COMPONENT Application
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib/static
)
INSTALL(FILES 
		${SDL_LIBRARY_DLL_RELEASE} 
		${SDLIMAGE_LIBRARY_DLL_RELEASE} 
		${SDLIMAGE_LIBRARY_DLLS_EXT} 
		${SDLTTF_LIBRARY_DLL_RELEASE} 
		${SDLGFX_LIBRARY_DLL_RELEASE} 
	DESTINATION bin
	COMPONENT Libraries
)

# ===========================  HumbugConsole Executable  ===========================

SET(HumbugConsole_headers 
#        HumbugConsole/GB.h
        HumbugConsole/ProgOptions.h 
#        HumbugConsole/ProcessProject.h 
)

SET(HumbugConsole_sources 
#        HumbugConsole/GB.cpp 
        HumbugConsole/ProgOptions.cpp 
#        HumbugConsole/ProcessProject.cpp 
        HumbugConsole/main.cpp 
)

# see http://www.mail-archive.com/cmake@cmake.org/msg17661.html
ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
ADD_MSVC_PRECOMPILED_HEADER("HumbugConsole/stdafx.h" "HumbugConsole/stdafx.cpp" HumbugConsole_sources)
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
INCLUDE_DIRECTORIES( ${HumbugShared_INCLUDE_DIR})
#INCLUDE_DIRECTORIES( ${Crunchy_INCLUDE_DIR})

ADD_EXECUTABLE(HumbugConsole #WIN32
        HumbugConsole/stdafx.h
        ${DEBUG_DEFINITION_INCLUDES}
        #defs.h 

        ${HumbugConsole_sources} 
        ${HumbugConsole_headers}
        ${HumbugConsole_XSD_sources}
        ${HumbugConsole_mocfiles} 
        ${HumbugConsole_res_outfiles} 
        ${HumbugConsole_moc_outfiles} 
        ${HumbugConsole_ui_outfiles}
)

TargetLinkBoost(HumbugConsole "program_options")
TargetLinkBoost(HumbugConsole "filesystem;system;regex")
#TARGET_LINK_LIBRARIES(HumbugConsole CppStructz)
TARGET_LINK_LIBRARIES(HumbugConsole HumbugShared)
#Copy_DLL_To_Target(HumbugConsole CppStructz)
IF(USE_NLS)
  Copy_DLL_To_Target(HumbugConsole LIBINTL)
  Copy_DLL_To_Target(HumbugConsole ICONV)
ENDIF(USE_NLS)


