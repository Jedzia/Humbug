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

project( HumbugGL )

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
set(HumbugGL_MyGUI_headers 
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
set(HumbugGL_MyGUI_sources 
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

set(HumbugGL_Level_headers 
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
set(HumbugGL_Level_sources 
		Levels/TestLevel.cpp
		Levels/LevelA.cpp
		Levels/Scroller/ScrollerLevelA.cpp
		Levels/Scroller/PlayerShip.cpp
		Levels/Scroller/EnemyWave.cpp
		Levels/Scroller/EnemyWaveSTM.cpp
		Levels/Scroller/EnemyShip.cpp
)

# putting the sources together
set(HumbugGL_headers 
		${HumbugGL_MyGUI_headers}
		${HumbugGL_Level_headers}

		HumbugGLFileLoader.h

		Input/PlayerKeys.h
		Input/PlayerKeys2.h
		Input/PlayerKeys3.h
		Input/PlayerKeys4.h

	    Project/ProjectModel.h
)

set(HumbugGL_sources 
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

set(HumbugGL_LUA_sources 
		Lua/funcret.lua
		Lua/globalclass.lua
		Lua/hello.lua
		Lua/iowrite.lua
		Lua/math.lua
		Lua/sequencer.lua
		Lua/sprite1.lua
)

set(HumbugGL_LUAsprite_sources 
		Lua/male_sprites.spr
		Lua/male_spritesA.spr
)


#set(CMAKE_BUILD_TYPE DEBUG)

#include_directories( ${CppStructz_INCLUDE_DIR} )
include_directories(${SDL_INCLUDE_DIR})
include_directories(${SDLIMAGE_INCLUDE_DIR})
include_directories(${SDLTTF_INCLUDE_DIR})
include_directories(${SDLGFX_INCLUDE_DIR})
include_directories(${HumbugGLShared_INCLUDE_DIR})
include_directories(${HumbugGLLib_INCLUDE_DIR})
include_directories(${GuiLib_INTERFACE_DIR})
include_directories(${HumbugGLSerialization_INTERFACE_DIR})
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


add_definitions(${HumbugGLShared_DEFINITIONS})
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

ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" HumbugGL_sources)

source_group(Generated FILES ${res_outfiles} ${moc_outfiles} ${ui_outfiles} )
source_group(Resources FILES ${HumbugGL_resfiles})
source_group(GUI FILES ${HumbugGL_uifiles})
source_group(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
source_group(THeaders FILES ${HumbugGL_headers})
source_group(TSources FILES ${HumbugGL_sources})
source_group(Lua FILES ${HumbugGL_LUA_sources})
source_group(LuaSprites FILES ${HumbugGL_LUAsprite_sources})


set(HumbugGL_documents
		../Readme.md
		../docs/!DevelNotes.txt
)
source_group(Docs FILES ${HumbugGL_documents})

# Move to bindings
set(_GUI_DEP )
if(WIN32)
  # Maybe here is the point for a HumbugGL_WINDOWS_CONSOLE subsystem switch.
  set(_GUI_DEP WIN32)
endif(WIN32)
add_executable(HumbugGL ${_GUI_DEP}
        stdafx.h
        ${DEBUG_DEFINITION_INCLUDES}
        defs.h 

        ${HumbugGL_headers}
        ${HumbugGL_sources} 
		${HumbugGL_documents}
		${HumbugGL_LUA_sources}
		${HumbugGL_LUAsprite_sources}
)



set(Pak01_PACKAGE_SOURCE_FILES 
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
#set(Pak01x_PACKAGE_SOURCE_FILES 
#	    ${HumbugGL_Artwork_DIR}/Tutor/Images
#)
#CREATEPACKAGE(HumbugGL MakeVFSx "${Pak01x_PACKAGE_SOURCE_FILES}" base_data Pak01.zip)
#add_dependencies(MakeVFS Artwork)

set(Pak02_PACKAGE_SOURCE_FILES 
	    ${HumbugGL_Artwork_WORKDIR}/Sprites/
	    ${HumbugGL_Artwork_DIR}/Hud/footer.psd
)
CREATEPACKAGE(MakeVFS MakeVFS01 "${Pak02_PACKAGE_SOURCE_FILES}" base_data Pak02.zip)

# copy to build dir based on language
set_source_files_properties( ${HumbugGL_LUA_sources} 
        PROPERTIES LANGUAGE LUA_Script
)
copy_language_to_build_tree(HumbugGL LUA_Script base_data)

# copy to build dir based on file list
copy_files_to_build_tree(HumbugGL "${HumbugGL_LUAsprite_sources}" base_data/Sprites)

#add_custom_target(generate_foo DEPENDS ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${XSD_LIBRARY_DEBUG})

Copy_DLL_To_Target(HumbugGL SDL_LIBRARY)
Copy_DLL_To_Target(HumbugGL SDLIMAGE_LIBRARY)
Copy_Files_To_Target(HumbugGL "${SDLIMAGE_LIBRARY_DLLS_EXT}")
Copy_DLL_To_Target(HumbugGL SDLTTF_LIBRARY)
Copy_Files_To_Target(HumbugGL "${SDLTTF_LIBRARY_DLLS_EXT}")
#Copy_ReleaseDLL_To_Target(HumbugGL ICU)

TargetLinkBoost(HumbugGL "filesystem;system;regex;signals;serialization")
target_link_libraries(HumbugGL HumbugGLLib)
target_link_libraries(HumbugGL HumbugGLShared)
target_link_libraries(HumbugGL GuiLib)
target_link_libraries(HumbugGL HumbugGLSerialization)
target_link_libraries(HumbugGL ${SDL_LIBRARY})
target_link_libraries(HumbugGL ${SDLMAIN_LIBRARY})
target_link_libraries(HumbugGL ${SDLIMAGE_LIBRARY})
target_link_libraries(HumbugGL ${SDLTTF_LIBRARY})
if(USE_SDL_GFX)
    target_link_libraries(HumbugGL ${SDLGFX_LIBRARY})
endif()


#TODO: without this does not compile under linux
if(LINUX)
	target_link_libraries(HumbugGL boost_serialization)
endif(LINUX)


#target_link_libraries(HumbugGL ${LUA_LIBRARY})
#target_link_libraries(HumbugGL ${LUABIND_LIBRARY})
#target_link_libraries(HumbugGL luabind)
#add_dependencies(HumbugGL luabind)
#target_link_libraries(HumbugGL ${LUABIND_LIBRARY})
# message(WARNING "LUABIND: ${LUABIND}")
# A) Target-centric: target, header-file, precompiled header, [ warn on invalid header(-Winvalid-pch) ]
# B) individual sources specified: target, header-file, precompiled header, 
#    warn on invalid header(-Winvalid-pch), source files with header
ADD_PRECOMPILED_HEADER(HumbugGL stdafx.h stdafx.h.gch TRUE "${HumbugGL_sources}")

#set_source_files_properties( main.cpp
#       PROPERTIES OBJECT_DEPENDS ${CppStructz_DLL_DEBUG}
#)

install(TARGETS HumbugGL 
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

# ===========================  HumbugGLConsole Executable  ===========================

set(HumbugGLConsole_headers 
#        HumbugGLConsole/GB.h
        HumbugGLConsole/ProgOptions.h 
		HumbugGLConsole/HumbugGLFileLoader.h
#        HumbugGLConsole/ProcessProject.h 
)

set(HumbugGLConsole_sources 
#        HumbugGLConsole/GB.cpp 
        HumbugGLConsole/ProgOptions.cpp 
		HumbugGLConsole/HumbugGLFileLoader.cpp
#        HumbugGLConsole/ProcessProject.cpp 
        HumbugGLConsole/main.cpp 
)

# see http://www.mail-archive.com/cmake@cmake.org/msg17661.html
add_definitions(-DUNICODE -D_UNICODE)
ADD_MSVC_PRECOMPILED_HEADER("HumbugGLConsole/stdafx.h" "HumbugGLConsole/stdafx.cpp" HumbugGLConsole_sources)
include_directories( ${PROJECT_SOURCE_DIR} )
include_directories( ${HumbugGLShared_INCLUDE_DIR})
include_directories(${HumbugGLSerialization_INTERFACE_DIR})
#include_directories( ${Crunchy_INCLUDE_DIR})

add_executable(HumbugGLConsole #WIN32
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
#target_link_libraries(HumbugGLConsole CppStructz)
target_link_libraries(HumbugGLConsole GuiLib)
target_link_libraries(HumbugGLConsole HumbugGLShared)
target_link_libraries(HumbugGLConsole HumbugGLSerialization)
#Copy_DLL_To_Target(HumbugGLConsole CppStructz)
if(USE_NLS)
  Copy_DLL_To_Target(HumbugGLConsole LIBINTL)
  Copy_DLL_To_Target(HumbugGLConsole ICONV)
endif(USE_NLS)


