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

project( GuiLib )
add_subdirectory( docs )

message(STATUS         "!!!!!!!!!!!!!!!! CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME} !!!!!!!!!!")
include (BoostExtensions)
include (PCHSupport)
include (helpers)
include (library)

find_package(OpenGL)
find_package(GLUT)

set(USE_LIB_BOOST_COMPONENTS "system;filesystem;signals;program_options;serialization")
# Use Boost libraries for this project.
set(USE_LIB_BOOST TRUE)

	set(USE_SDL TRUE)
	set(USE_SDL_IMAGE TRUE)
	set(USE_SDL_TTF TRUE)
#	set(USE_SDL_GFX TRUE)

# local project settings
include (bindings)

set(GuiLib_GLOBAL_headers
		MathDefs.h
		TimingDefs.h
)

# User-Interface skeleton
set(GuiLib_GUI_Data_headers
		GUI/Data/ColorData.h
)
set(GuiLib_GUI_Data_sources
		GUI/Data/ColorData.cpp
)

set(GuiLib_OTHER_headers
		Input/KeyboardHandler.h
)
set(GuiLib_OTHER_sources
		Input/KeyboardHandler.cpp
)

set(GuiLib_GUI_headers
		GUI/GuiFontMetrics.h

		GUI/Visual/Application.h
		GUI/Visual/EventHandler.h
		GUI/Visual/MessageHandler.h
		GUI/Visual/Thread.h
		GUI/Visual/Timer.h
		GUI/Visual/Hookable.h
		GUI/Visual/HookableManager.h
		GUI/Visual/SdlInfo.h
		GUI/Visual/Console.h
)
set(GuiLib_GUI_sources
		GUI/GuiFontMetrics.cpp

		GUI/Visual/Application.cpp
		GUI/Visual/EventHandler.cpp
		GUI/Visual/MessageHandler.cpp
		GUI/Visual/Thread.cpp
		GUI/Visual/Timer.cpp
		GUI/Visual/Hookable.cpp
		GUI/Visual/HookableManager.cpp
		GUI/Visual/SdlInfo.cpp
		GUI/Visual/Console.cpp
)

# Component set (Canvas, Controls, etc.)
set(GuiLib_Component_headers
		Timing.h
		TimingChain.h
		Timing2.h
		GUI/Disposable.h

		Animation.h
		Animation/AnimatedRectangle.h
		Animation/SinusoidWobbler.h
		
		GUI/Components/Point.h
		GUI/Components/Rectangle.h
		GUI/Components/Color.h
		GUI/Components/Blendmode.h
		GUI/Components/Canvas.h
		GUI/Components/CanvasRendererImpl.h
		GUI/Components/CanvasDisplayApi.h
		GUI/Components/Impl/BothDisplay.h
		GUI/Components/Impl/QuadRenderer.h
		GUI/Components/Image.h
		GUI/Components/SeamlessImage.h
		GUI/Components/MainCanvas.h
		GUI/Components/CoordSystem.h

		GUI/Components/Shape.h
		GUI/Components/Shapes/Line.h

		GUI/Components/BaseDrawable.h
		GUI/Components/Text.h
		GUI/Components/TextAnimator.h
		GUI/Components/TextAnimatorImpl.h
		GUI/Components/EasingFunctors.h
		GUI/Components/TextScroller.h

		GUI/Components/Screen.h

		GUI/Controls/Control.h
		GUI/Controls/Button.h
		GUI/Controls/Label.h
		GUI/Controls/LineMenu.h

		GUI/Sprite/Sprite.h
		GUI/Sprite/SpriteManager.h

		GUI/TileEngine/Tile.h
		GUI/TileEngine/TileImage.h
		GUI/TileEngine/TileSet.h
		GUI/TileEngine/TileMap.h
		GUI/TileEngine/TileEngine.h
)
set(GuiLib_Component_sources
		Timing.cpp
		TimingChain.cpp
		GUI/Disposable.cpp

		GUI/Components/Point.cpp
		GUI/Components/Rectangle.cpp
		GUI/Components/Color.cpp
		GUI/Components/Canvas.cpp
		GUI/Components/CanvasRendererImpl.cpp
		GUI/Components/Impl/BothDisplay.cpp
		GUI/Components/Impl/QuadRenderer.cpp
		GUI/Components/Image.cpp
		GUI/Components/SeamlessImage.cpp
		GUI/Components/MainCanvas.cpp
		GUI/Components/CoordSystem.cpp

		GUI/Components/Shape.cpp
		GUI/Components/Shapes/Line.cpp
		
		GUI/Components/BaseDrawable.cpp
		GUI/Components/Text.cpp
		GUI/Components/TextAnimator.cpp
		GUI/Components/TextAnimatorImpl.cpp
		GUI/Components/EasingFunctors.cpp
		GUI/Components/TextScroller.cpp

		GUI/Components/Screen.cpp

		GUI/Controls/Control.cpp
		GUI/Controls/Button.cpp
		GUI/Controls/Label.cpp
		GUI/Controls/LineMenu.cpp

		GUI/Sprite/Sprite.cpp
		GUI/Sprite/SpriteManager.cpp

		GUI/TileEngine/Tile.cpp
		GUI/TileEngine/TileImage.cpp
		GUI/TileEngine/TileSet.cpp
		GUI/TileEngine/TileMap.cpp
		GUI/TileEngine/TileEngine.cpp
)

# Console stuff
set(GuiLib_GuiConsole_headers
		GUI/Visual/DT_drawtext.h
		GUI/Visual/internal.h
		GUI/Visual/SDL_console.h
		GUI/Visual/split.h
)
set(GuiLib_GuiConsole_sources
		GUI/Visual/DT_drawtext.c
		GUI/Visual/internal.c
		GUI/Visual/SDL_console.c
		GUI/Visual/split.c
)

# putting the sources together
set(GuiLib_headers
		${GuiLib_OTHER_headers}
		${GuiLib_GUI_Data_headers}
		${GuiLib_GUI_headers}
		${GuiLib_Component_headers}

		Filesystem/FileLoader.h
)

set(GuiLib_sources
		${GuiLib_OTHER_sources}
		${GuiLib_GUI_Data_sources}
		${GuiLib_GUI_sources}
		${GuiLib_Component_sources}

		Filesystem/FileLoader.cpp
)


include_directories(${SDL_INCLUDE_DIR})
include_directories(${SDLIMAGE_INCLUDE_DIR})
include_directories(${SDLTTF_INCLUDE_DIR})
include_directories(${SDLGFX_INCLUDE_DIR})
#include_directories(${HumbugShared_INCLUDE_DIR})
include_directories(${HumbugLib_INCLUDE_DIR})
include_directories(${ZLIB_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR})
#include_directories(${GL3W_INCLUDE_DIRS})
include_directories(${glm_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})

#add_definitions("-DGL_VERSION_4_1")
include_directories(${OGLPLUS_INCLUDE_DIR})

# Move to bindings
if(LINUX)
  include_directories(${PROJECT_SOURCE_DIR})
endif(LINUX)


add_definitions(${GuiLibShared_DEFINITIONS})
if(SDLIMAGE_FOUND)
  add_definitions("-DHAVE_SDLIMAGE")
endif(SDLIMAGE_FOUND)

# Move to bindings
if(LINUX)
  add_definitions("-DLINUX")
endif(LINUX)

#if(WIN32)
#endif(WIN32)

if(CMAKE_GENERATOR MATCHES Visual*)
	# disable warning C4996: 'std::_Uninitialized_copy0': Function call with parameters that may be unsafe
	add_definitions("/wd4996")
	# error C3859: virtual memory range for PCH exceeded; please recompile with a command line option of '-Zm118' or greater
	# fatal error C1076: compiler limit : internal heap limit reached; use /Zm to specify a higher limit
	add_definitions("-Zm118")
endif()


ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" GuiLib_sources)

source_group(Generated FILES ${res_outfiles} ${moc_outfiles} ${ui_outfiles} )
source_group(Resources FILES ${GuiLib_resfiles})
source_group(GUI FILES ${GuiLib_uifiles})
source_group(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
source_group(GlobalHeader FILES ${GuiLib_GLOBAL_headers})
source_group(THeaders FILES ${GuiLib_headers})
source_group(TSources FILES ${GuiLib_sources})
source_group(GuiHeaders FILES ${GuiLib_GUI_headers})
source_group(GuiSources FILES ${GuiLib_GUI_sources})
source_group(CompHeaders FILES ${GuiLib_Component_headers})
source_group(CompSources FILES ${GuiLib_Component_sources})

#set(GuiLib_documents
#		Readme.md
#		docs/!DevelNotes.txt
#)
#source_group(Docs FILES ${GuiLib_documents})
ENSURE_DOCS_ARE_PRESENT(GuiLib_documents)

set(LIBRARY_TYPE STATIC)
add_definitions("-DMYENGINE_EXPORTS")
add_definitions("-DGLEW_STATIC")

# Move to bindings
ADD_LIBRARY_X(GuiLib ${LIBRARY_TYPE}
        stdafx.h
        ${DEBUG_DEFINITION_INCLUDES}
        defs.h

		${GuiLib_GLOBAL_headers}
        ${GuiLib_headers}
        ${GuiLib_sources}
		${GuiLib_GuiConsole_headers}
		${GuiLib_GuiConsole_sources}
		${GuiLib_documents}
)



TargetLinkBoost(GuiLib "filesystem;system;regex;signals")
target_link_libraries(GuiLib HumbugLib)
#target_link_libraries(GuiLib HumbugShared)
target_link_libraries(GuiLib ${SDL_LIBRARY})
target_link_libraries(GuiLib ${SDLIMAGE_LIBRARY})
target_link_libraries(GuiLib ${SDLTTF_LIBRARY})
target_link_libraries(GuiLib ${SDLGFX_LIBRARY})
target_link_libraries(GuiLib ${OPENGL_gl_LIBRARY})
target_link_libraries(GuiLib ${OPENGL_glu_LIBRARY}) # this works on windows with VC2013
#target_link_libraries(GuiLib ${GLUT_LIBRARIES})
target_link_libraries(GuiLib ${GLEW_LIBRARY})

#D:/Program Files (x86)/Windows Kits/8.0/Lib/win8/um/x64/

# A) Target-centric: target, header-file, precompiled header, [ warn on invalid header(-Winvalid-pch) ]
# B) individual sources specified: target, header-file, precompiled header,
#    warn on invalid header(-Winvalid-pch), source files with header
ADD_PRECOMPILED_HEADER(GuiLib stdafx.h stdafx.h.gch TRUE "${GuiLib_sources}")

install(TARGETS GuiLib
	COMPONENT Application
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib/static
)
#install(FILES
#		${SDL_LIBRARY_DLL_RELEASE}
#		${SDLIMAGE_LIBRARY_DLL_RELEASE}
#		${SDLIMAGE_LIBRARY_DLLS_EXT}
#		${SDLTTF_LIBRARY_DLL_RELEASE}
#		${SDLGFX_LIBRARY_DLL_RELEASE}
#	DESTINATION bin
#	COMPONENT Libraries
#)

