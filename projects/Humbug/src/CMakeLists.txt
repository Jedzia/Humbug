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

project( Humbug )

message(STATUS         "!!!!!!!!!!!!!!!! CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME} !!!!!!!!!!")
include (BoostExtensions)
#include (PCHSupport_MSVC)
include (PCHSupport)
include (CopyResourcesToBuildTree)
include (helpers)
include (PackageCreate)

set(USE_LIB_BOOST_COMPONENTS "system;filesystem;signals;program_options;serialization")
#set(USE_LIB_BOOST TRUE CACHE BOOL "Use Boost libraries")
# Use Boost libraries for this project.
set(USE_LIB_BOOST TRUE)

set(USE_SDL TRUE)
set(USE_SDL_IMAGE TRUE)
set(USE_SDL_TTF TRUE)
#set(USE_SDL_GFX TRUE)

set(USE_LUA TRUE)

# local project settings
include (bindings)

# Link explicitely to Microsoft.VC90.CRT version=9.0.30729.1
#add_definitions("-D_BIND_TO_CURRENT_VCLIBS_VERSION=1")
# this does the same as above
#add_definitions("-D_BIND_TO_CURRENT_MFC_VERSION=2")
#add_definitions("-D_BIND_TO_CURRENT_CRT_VERSION=2")

# GUI implementation
set(Humbug_MyGUI_headers 
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
		Screens/ZoomInScreen2.h

		Screens/InfoText.h
		Screens/MenuScreen.h
		Screens/MenuScreen/SubmenuA.h
		Screens/MenuScreen/SubmenuB.h
		Screens/MenuScreen/TutorA1.h
		Screens/MenuScreen/TutorEasing.h

		Screens/WavyTextFloat.h
)
set(Humbug_MyGUI_sources 
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
		Screens/ZoomInScreen2.cpp

		Screens/MenuScreen.cpp
		Screens/MenuScreen/SubmenuA.cpp
		Screens/MenuScreen/SubmenuB.cpp
		Screens/MenuScreen/TutorA1.cpp
		Screens/MenuScreen/TutorEasing.cpp

		Screens/WavyTextFloat.cpp
)

set(Humbug_Level_headers 
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
set(Humbug_Level_sources 
		Levels/TestLevel.cpp
		Levels/LevelA.cpp
		Levels/Scroller/ScrollerLevelA.cpp
		Levels/Scroller/PlayerShip.cpp
		Levels/Scroller/EnemyWave.cpp
		Levels/Scroller/EnemyWaveSTM.cpp
		Levels/Scroller/EnemyShip.cpp
)

# putting the sources together
set(Humbug_headers 
		${Humbug_MyGUI_headers}
		${Humbug_Level_headers}

		HumbugFileLoader.h

		Input/PlayerKeys.h
		Input/PlayerKeys2.h
		Input/PlayerKeys3.h
		Input/PlayerKeys4.h

	    Project/ProjectModel.h
)

set(Humbug_sources 
		${Humbug_MyGUI_sources}
		${Humbug_Level_sources}

		Input/PlayerKeys.cpp
		Input/PlayerKeys2.cpp
		Input/PlayerKeys3.cpp
		Input/PlayerKeys4.cpp

		HumbugFileLoader.cpp
	    main.cpp 
	    Project/ProjectModel.cpp
)

set(Humbug_LUA_sources 
		Lua/funcret.lua
		Lua/globalclass.lua
		Lua/hello.lua
		Lua/iowrite.lua
		Lua/math.lua
		Lua/sequencer.lua
		Lua/sprite1.lua
)

set(Humbug_LUAsprite_sources 
		Lua/male_sprites.spr
		Lua/male_spritesA.spr
)


#set(CMAKE_BUILD_TYPE DEBUG)

#include_directories( ${CppStructz_INCLUDE_DIR} )
include_directories(${SDL_INCLUDE_DIR})
include_directories(${SDLIMAGE_INCLUDE_DIR})
include_directories(${SDLTTF_INCLUDE_DIR})
include_directories(${SDLGFX_INCLUDE_DIR})
include_directories(${HumbugShared_INCLUDE_DIR})
include_directories(${HumbugLib_INCLUDE_DIR})
include_directories(${GuiLib_INTERFACE_DIR})
include_directories(${HumbugSerialization_INTERFACE_DIR})
include_directories(${ZLIB_INCLUDE_DIR})
include_directories(${LUA_INCLUDE_DIR})
include_directories(${LUABIND_INCLUDE_DIR})
include_directories(${glm_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${OGLPLUS_INCLUDE_DIR})
# Move to bindings
if(LINUX)
  include_directories( ${PROJECT_SOURCE_DIR} )
endif(LINUX)


add_definitions(${HumbugShared_DEFINITIONS})
if(SDLIMAGE_FOUND)
  add_definitions("-DHAVE_SDLIMAGE")
endif(SDLIMAGE_FOUND)

# Move to bindings
if(LINUX)
  add_definitions("-DLINUX")
endif(LINUX)

if(CMAKE_GENERATOR MATCHES Visual*)
	# disable warning C4996: 'std::_Uninitialized_copy0': Function call with parameters that may be unsafe
	add_definitions("/wd4996")
	# error C3859: virtual memory range for PCH exceeded; please recompile with a command line option of '-Zm118' or greater
	# fatal error C1076: compiler limit : internal heap limit reached; use /Zm to specify a higher limit
	add_definitions("-Zm150")
endif()

ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" Humbug_sources)

source_group(Generated FILES ${res_outfiles} ${moc_outfiles} ${ui_outfiles} )
source_group(Resources FILES ${Humbug_resfiles})
source_group(GUI FILES ${Humbug_uifiles})
source_group(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
source_group(THeaders FILES ${Humbug_headers})
source_group(TSources FILES ${Humbug_sources})
source_group(Lua FILES ${Humbug_LUA_sources})
source_group(LuaSprites FILES ${Humbug_LUAsprite_sources})


set(Humbug_documents
		../Readme.md
		../docs/!DevelNotes.txt
)
source_group(Docs FILES ${Humbug_documents})

# Move to bindings
set(_GUI_DEP )
if(WIN32)
  # Maybe here is the point for a Humbug_WINDOWS_CONSOLE subsystem switch.
  set(_GUI_DEP WIN32)
endif(WIN32)
add_executable(Humbug ${_GUI_DEP}
        stdafx.h
        ${DEBUG_DEFINITION_INCLUDES}
        defs.h 

        ${Humbug_headers}
        ${Humbug_sources} 
		${Humbug_documents}
		${Humbug_LUA_sources}
		${Humbug_LUAsprite_sources}
)



set(Pak01_PACKAGE_SOURCE_FILES 
		${PROJECT_SOURCE_DIR}/Icons/
	    ${Humbug_Artwork_DIR}/data/
	    ${Humbug_Artwork_DIR}/Tutor/
#	    ${Humbug_Artwork_DIR}/Tutor/Images
		${HUMBUGGL_RESOURCES_DIR}/Fonts/
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
#set(Pak01x_PACKAGE_SOURCE_FILES 
#	    ${Humbug_Artwork_DIR}/Tutor/Images
#)
#CREATEPACKAGE(Humbug MakeVFSx "${Pak01x_PACKAGE_SOURCE_FILES}" base_data Pak01.zip)
#add_dependencies(MakeVFS Artwork)

set(Pak02_PACKAGE_SOURCE_FILES 
	    ${Humbug_Artwork_WORKDIR}/Sprites/
	    ${Humbug_Artwork_DIR}/Hud/footer.psd
)
CREATEPACKAGE(MakeVFS MakeVFS01 "${Pak02_PACKAGE_SOURCE_FILES}" base_data Pak02.zip)

# copy to build dir based on language
set_source_files_properties( ${Humbug_LUA_sources} 
        PROPERTIES LANGUAGE LUA_Script
)
copy_language_to_build_tree(Humbug LUA_Script base_data)

# copy to build dir based on file list
copy_files_to_build_tree(Humbug "${Humbug_LUAsprite_sources}" base_data/Sprites)

#add_custom_target(generate_foo DEPENDS ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${XSD_LIBRARY_DEBUG})

Copy_DLL_To_Target(Humbug SDL_LIBRARY)
Copy_DLL_To_Target(Humbug SDLIMAGE_LIBRARY)
Copy_Files_To_Target(Humbug "${SDLIMAGE_LIBRARY_DLLS_EXT}")
Copy_DLL_To_Target(Humbug SDLTTF_LIBRARY)
Copy_Files_To_Target(Humbug "${SDLTTF_LIBRARY_DLLS_EXT}")
#Copy_ReleaseDLL_To_Target(Humbug ICU)

TargetLinkBoost(Humbug "filesystem;system;regex;signals;serialization")
target_link_libraries(Humbug HumbugLib)
target_link_libraries(Humbug HumbugShared)
target_link_libraries(Humbug GuiLib)
target_link_libraries(Humbug HumbugSerialization)
target_link_libraries(Humbug ${SDL_LIBRARY})
target_link_libraries(Humbug ${SDLMAIN_LIBRARY})
target_link_libraries(Humbug ${SDLIMAGE_LIBRARY})
target_link_libraries(Humbug ${SDLTTF_LIBRARY})
if(USE_SDL_GFX)
    target_link_libraries(Humbug ${SDLGFX_LIBRARY})
endif()


#TODO: without this does not compile under linux
if(LINUX)
	target_link_libraries(Humbug boost_serialization)
endif(LINUX)


#target_link_libraries(Humbug ${LUA_LIBRARY})
#target_link_libraries(Humbug ${LUABIND_LIBRARY})
#target_link_libraries(Humbug luabind)
#add_dependencies(Humbug luabind)
#target_link_libraries(Humbug ${LUABIND_LIBRARY})
# message(WARNING "LUABIND: ${LUABIND}")
# A) Target-centric: target, header-file, precompiled header, [ warn on invalid header(-Winvalid-pch) ]
# B) individual sources specified: target, header-file, precompiled header, 
#    warn on invalid header(-Winvalid-pch), source files with header
ADD_PRECOMPILED_HEADER(Humbug stdafx.h stdafx.h.gch TRUE "${Humbug_sources}")

#set_source_files_properties( main.cpp
#       PROPERTIES OBJECT_DEPENDS ${CppStructz_DLL_DEBUG}
#)

install(TARGETS Humbug 
	COMPONENT Application
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib/static
)
install(FILES 
		${SDL_LIBRARY_DLL_RELEASE} 
		${SDLIMAGE_LIBRARY_DLL_RELEASE} 
		${SDLIMAGE_LIBRARY_DLLS_EXT} 
		${SDLTTF_LIBRARY_DLL_RELEASE} 
		${SDLGFX_LIBRARY_DLL_RELEASE} 
	DESTINATION bin
	COMPONENT Libraries
)

# ===========================  HumbugConsole Executable  ===========================

set(HumbugConsole_headers 
#        HumbugConsole/GB.h
        HumbugConsole/ProgOptions.h 
		HumbugConsole/HumbugFileLoader.h
#        HumbugConsole/ProcessProject.h 
)

set(HumbugConsole_sources 
#        HumbugConsole/GB.cpp 
        HumbugConsole/ProgOptions.cpp 
		HumbugConsole/HumbugFileLoader.cpp
#        HumbugConsole/ProcessProject.cpp 
        HumbugConsole/main.cpp 
)

# see http://www.mail-archive.com/cmake@cmake.org/msg17661.html
add_definitions(-DUNICODE -D_UNICODE)
ADD_MSVC_PRECOMPILED_HEADER("HumbugConsole/stdafx.h" "HumbugConsole/stdafx.cpp" HumbugConsole_sources)
include_directories( ${PROJECT_SOURCE_DIR} )
include_directories( ${HumbugShared_INCLUDE_DIR})
include_directories(${HumbugSerialization_INTERFACE_DIR})
#include_directories( ${Crunchy_INCLUDE_DIR})

add_executable(HumbugConsole #WIN32
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
TargetLinkBoost(HumbugConsole "filesystem;system;regex;serialization")
#target_link_libraries(HumbugConsole CppStructz)
target_link_libraries(HumbugConsole GuiLib)
target_link_libraries(HumbugConsole HumbugShared)
target_link_libraries(HumbugConsole HumbugSerialization)
#Copy_DLL_To_Target(HumbugConsole CppStructz)
if(USE_NLS)
  Copy_DLL_To_Target(HumbugConsole LIBINTL)
  Copy_DLL_To_Target(HumbugConsole ICONV)
endif(USE_NLS)


