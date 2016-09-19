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

PROJECT( HumbugGL )

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
SET(HumbugGL_MyGUI_headers 
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
		Screens/ZoomInScreen.h

		Screens/InfoText.h
		Screens/MenuScreen.h
		Screens/MenuScreen/SubmenuA.h
		Screens/MenuScreen/SubmenuB.h
		Screens/MenuScreen/TutorA1.h
		Screens/MenuScreen/TutorEasing.h

		Screens/WavyTextFloat.h
)
SET(HumbugGL_MyGUI_sources 
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
		Screens/ZoomInScreen.cpp

		Screens/MenuScreen.cpp
		Screens/MenuScreen/SubmenuA.cpp
		Screens/MenuScreen/SubmenuB.cpp
		Screens/MenuScreen/TutorA1.cpp
		Screens/MenuScreen/TutorEasing.cpp

		Screens/WavyTextFloat.cpp
)

SET(HumbugGL_Level_headers 
		Levels/TestLevel.h
		Levels/LevelA.h
		Levels/Scroller/ScrollerLevelA.h
		Levels/Scroller/ScrollerLevelATestStuff.h
		Levels/Scroller/MoverStuff.h
		Levels/Scroller/PlayerShip.h
		Levels/Scroller/EnemyWave.h
		Levels/Scroller/EnemyWaveSTM.h
		Levels/Scroller/EnemyShip.h
)
SET(HumbugGL_Level_sources 
		Levels/TestLevel.cpp
		Levels/LevelA.cpp
		Levels/Scroller/ScrollerLevelA.cpp
		Levels/Scroller/PlayerShip.cpp
		Levels/Scroller/EnemyWave.cpp
		Levels/Scroller/EnemyWaveSTM.cpp
		Levels/Scroller/EnemyShip.cpp
)

# putting the sources together
SET(HumbugGL_headers 
		${HumbugGL_MyGUI_headers}
		${HumbugGL_Level_headers}

		HumbugGLFileLoader.h

		Input/PlayerKeys.h
		Input/PlayerKeys2.h
		Input/PlayerKeys3.h
		Input/PlayerKeys4.h

	    Project/ProjectModel.h
)

SET(HumbugGL_sources 
		${HumbugGL_MyGUI_sources}
		${HumbugGL_Level_sources}

		Input/PlayerKeys.cpp
		Input/PlayerKeys2.cpp
		Input/PlayerKeys3.cpp
		Input/PlayerKeys4.cpp

		HumbugGLFileLoader.cpp
	    main.cpp 
	    Project/ProjectModel.cpp
)

SET(HumbugGL_LUA_sources 
		Lua/funcret.lua
		Lua/globalclass.lua
		Lua/hello.lua
		Lua/iowrite.lua
		Lua/math.lua
		Lua/sequencer.lua
		Lua/sprite1.lua
)

SET(HumbugGL_LUAsprite_sources 
		Lua/male_sprites.spr
		Lua/male_spritesA.spr
)


#SET(CMAKE_BUILD_TYPE DEBUG)

#INCLUDE_DIRECTORIES( ${CppStructz_INCLUDE_DIR} )
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${SDLIMAGE_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${SDLTTF_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${SDLGFX_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${HumbugGLShared_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${HumbugGLLib_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${GuiLib_INTERFACE_DIR})
INCLUDE_DIRECTORIES(${HumbugGLSerialization_INTERFACE_DIR})
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${LUABIND_INCLUDE_DIR})
# Move to bindings
IF(LINUX)
  INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
ENDIF(LINUX)


ADD_DEFINITIONS(${HumbugGLShared_DEFINITIONS})
IF(SDLIMAGE_FOUND)
  ADD_DEFINITIONS("-DHAVE_SDLIMAGE")
ENDIF(SDLIMAGE_FOUND)

# Move to bindings
IF(LINUX)
  ADD_DEFINITIONS("-DLINUX")
ENDIF(LINUX)

if(CMAKE_GENERATOR MATCHES Visual*)
	# disable warning C4996: 'std::_Uninitialized_copy0': Function call with parameters that may be unsafe
	ADD_DEFINITIONS("/wd4996")
	# error C3859: virtual memory range for PCH exceeded; please recompile with a command line option of '-Zm118' or greater
	# fatal error C1076: compiler limit : internal heap limit reached; use /Zm to specify a higher limit
	ADD_DEFINITIONS("-Zm150")
endif()

ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" HumbugGL_sources)

SOURCE_GROUP(Generated FILES ${res_outfiles} ${moc_outfiles} ${ui_outfiles} )
SOURCE_GROUP(Resources FILES ${HumbugGL_resfiles})
SOURCE_GROUP(GUI FILES ${HumbugGL_uifiles})
SOURCE_GROUP(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
SOURCE_GROUP(THeaders FILES ${HumbugGL_headers})
SOURCE_GROUP(TSources FILES ${HumbugGL_sources})
SOURCE_GROUP(Lua FILES ${HumbugGL_LUA_sources})
SOURCE_GROUP(LuaSprites FILES ${HumbugGL_LUAsprite_sources})


SET(HumbugGL_documents
		../Readme.md
		../docs/!DevelNotes.txt
)
SOURCE_GROUP(Docs FILES ${HumbugGL_documents})

# Move to bindings
SET(_GUI_DEP )
IF(WIN32)
  # Maybe here is the point for a HumbugGL_WINDOWS_CONSOLE subsystem switch.
  SET(_GUI_DEP WIN32)
ENDIF(WIN32)
ADD_EXECUTABLE(HumbugGL ${_GUI_DEP}
        stdafx.h
        ${DEBUG_DEFINITION_INCLUDES}
        defs.h 

        ${HumbugGL_headers}
        ${HumbugGL_sources} 
		${HumbugGL_documents}
		${HumbugGL_LUA_sources}
		${HumbugGL_LUAsprite_sources}
)



SET(Pak01_PACKAGE_SOURCE_FILES 
		${PROJECT_SOURCE_DIR}/Icons/
	    ${HumbugGL_Artwork_DIR}/data/
	    ${HumbugGL_Artwork_DIR}/Tutor/
#	    ${HumbugGL_Artwork_DIR}/Tutor/Images
		${HUMBUGGL_RESOURCES_DIR}/Fonts/
	    ${HumbugGL_Artwork_WORKDIR}/Hud/
	    ${HumbugGL_Artwork_WORKDIR}/Intro/
	    #${HumbugGL_Artwork_WORKDIR}/Screens/
	    ${HumbugGL_Artwork_WORKDIR}/Images/
	    ${HumbugGL_Artwork_WORKDIR}/Text/
		#${PROJECT_SOURCE_DIR}/Icons/blue.png
	    #${P_ROOT_PATH}/Artwork/footer.png
	    #${HumbugGL_Artwork_WORKDIR}/footer.png
	    ${HumbugGL_Artwork_DIR}/Sprites/Sprites/
	    ${HumbugGL_Artwork_DIR}/Moo.png
	    ${HumbugGL_Artwork_DIR}/Tiles/gfx/Tiles1.bmp
)
CREATEPACKAGE(HumbugGL MakeVFS "${Pak01_PACKAGE_SOURCE_FILES}" base_data Pak01.zip)
#SET(Pak01x_PACKAGE_SOURCE_FILES 
#	    ${HumbugGL_Artwork_DIR}/Tutor/Images
#)
#CREATEPACKAGE(HumbugGL MakeVFSx "${Pak01x_PACKAGE_SOURCE_FILES}" base_data Pak01.zip)
#ADD_DEPENDENCIES(MakeVFS Artwork)

SET(Pak02_PACKAGE_SOURCE_FILES 
	    ${HumbugGL_Artwork_WORKDIR}/Sprites/
	    ${HumbugGL_Artwork_DIR}/Hud/footer.psd
)
CREATEPACKAGE(MakeVFS MakeVFS01 "${Pak02_PACKAGE_SOURCE_FILES}" base_data Pak02.zip)

# copy to build dir based on language
SET_SOURCE_FILES_PROPERTIES( ${HumbugGL_LUA_sources} 
        PROPERTIES LANGUAGE LUA_Script
)
copy_language_to_build_tree(HumbugGL LUA_Script base_data)

# copy to build dir based on file list
copy_files_to_build_tree(HumbugGL "${HumbugGL_LUAsprite_sources}" base_data/Sprites)

#ADD_CUSTOM_TARGET(generate_foo DEPENDS ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${XSD_LIBRARY_DEBUG})

Copy_DLL_To_Target(HumbugGL SDL_LIBRARY)
Copy_DLL_To_Target(HumbugGL SDLIMAGE_LIBRARY)
Copy_Files_To_Target(HumbugGL "${SDLIMAGE_LIBRARY_DLLS_EXT}")
Copy_DLL_To_Target(HumbugGL SDLTTF_LIBRARY)
Copy_Files_To_Target(HumbugGL "${SDLTTF_LIBRARY_DLLS_EXT}")
#Copy_ReleaseDLL_To_Target(HumbugGL ICU)

TargetLinkBoost(HumbugGL "filesystem;system;regex;signals;serialization")
TARGET_LINK_LIBRARIES(HumbugGL HumbugGLLib)
TARGET_LINK_LIBRARIES(HumbugGL HumbugGLShared)
TARGET_LINK_LIBRARIES(HumbugGL GuiLib)
TARGET_LINK_LIBRARIES(HumbugGL HumbugGLSerialization)
TARGET_LINK_LIBRARIES(HumbugGL ${SDL_LIBRARY})
TARGET_LINK_LIBRARIES(HumbugGL ${SDLMAIN_LIBRARY})
TARGET_LINK_LIBRARIES(HumbugGL ${SDLIMAGE_LIBRARY})
TARGET_LINK_LIBRARIES(HumbugGL ${SDLTTF_LIBRARY})
IF(USE_SDL_GFX)
    TARGET_LINK_LIBRARIES(HumbugGL ${SDLGFX_LIBRARY})
ENDIF()


#TODO: without this does not compile under linux
IF(LINUX)
	TARGET_LINK_LIBRARIES(HumbugGL boost_serialization)
ENDIF(LINUX)


#TARGET_LINK_LIBRARIES(HumbugGL ${LUA_LIBRARY})
#TARGET_LINK_LIBRARIES(HumbugGL ${LUABIND_LIBRARY})
#TARGET_LINK_LIBRARIES(HumbugGL luabind)
#ADD_DEPENDENCIES(HumbugGL luabind)
#TARGET_LINK_LIBRARIES(HumbugGL ${LUABIND_LIBRARY})
# Message(WARNING "LUABIND: ${LUABIND}")
# A) Target-centric: target, header-file, precompiled header, [ warn on invalid header(-Winvalid-pch) ]
# B) individual sources specified: target, header-file, precompiled header, 
#    warn on invalid header(-Winvalid-pch), source files with header
ADD_PRECOMPILED_HEADER(HumbugGL stdafx.h stdafx.h.gch TRUE "${HumbugGL_sources}")

#SET_SOURCE_FILES_PROPERTIES( main.cpp
#       PROPERTIES OBJECT_DEPENDS ${CppStructz_DLL_DEBUG}
#)

INSTALL(TARGETS HumbugGL 
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

# ===========================  HumbugGLConsole Executable  ===========================

SET(HumbugGLConsole_headers 
#        HumbugGLConsole/GB.h
        HumbugGLConsole/ProgOptions.h 
		HumbugGLConsole/HumbugGLFileLoader.h
#        HumbugGLConsole/ProcessProject.h 
)

SET(HumbugGLConsole_sources 
#        HumbugGLConsole/GB.cpp 
        HumbugGLConsole/ProgOptions.cpp 
		HumbugGLConsole/HumbugGLFileLoader.cpp
#        HumbugGLConsole/ProcessProject.cpp 
        HumbugGLConsole/main.cpp 
)

# see http://www.mail-archive.com/cmake@cmake.org/msg17661.html
ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
ADD_MSVC_PRECOMPILED_HEADER("HumbugGLConsole/stdafx.h" "HumbugGLConsole/stdafx.cpp" HumbugGLConsole_sources)
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
INCLUDE_DIRECTORIES( ${HumbugGLShared_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${HumbugGLSerialization_INTERFACE_DIR})
#INCLUDE_DIRECTORIES( ${Crunchy_INCLUDE_DIR})

ADD_EXECUTABLE(HumbugGLConsole #WIN32
        HumbugGLConsole/stdafx.h
        ${DEBUG_DEFINITION_INCLUDES}
        #defs.h 

        ${HumbugGLConsole_sources} 
        ${HumbugGLConsole_headers}
        ${HumbugGLConsole_XSD_sources}
        ${HumbugGLConsole_mocfiles} 
        ${HumbugGLConsole_res_outfiles} 
        ${HumbugGLConsole_moc_outfiles} 
        ${HumbugGLConsole_ui_outfiles}
)

TargetLinkBoost(HumbugGLConsole "program_options")
TargetLinkBoost(HumbugGLConsole "filesystem;system;regex;serialization")
#TARGET_LINK_LIBRARIES(HumbugGLConsole CppStructz)
TARGET_LINK_LIBRARIES(HumbugGLConsole GuiLib)
TARGET_LINK_LIBRARIES(HumbugGLConsole HumbugGLShared)
TARGET_LINK_LIBRARIES(HumbugGLConsole HumbugGLSerialization)
#Copy_DLL_To_Target(HumbugGLConsole CppStructz)
IF(USE_NLS)
  Copy_DLL_To_Target(HumbugGLConsole LIBINTL)
  Copy_DLL_To_Target(HumbugGLConsole ICONV)
ENDIF(USE_NLS)


