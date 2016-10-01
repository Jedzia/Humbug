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

PROJECT( GuiLib )
ADD_SUBDIRECTORY( docs )

MESSAGE(STATUS         "!!!!!!!!!!!!!!!! CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME} !!!!!!!!!!")
INCLUDE (BoostExtensions)
INCLUDE (PCHSupport)
INCLUDE (helpers)
INCLUDE (library)

find_package(OpenGL)
find_package(GLUT)

SET(USE_LIB_BOOST_COMPONENTS "system;filesystem;signals;program_options;serialization")
# Use Boost libraries for this project.
SET(USE_LIB_BOOST TRUE)

	SET(USE_SDL TRUE)
	SET(USE_SDL_IMAGE TRUE)
	SET(USE_SDL_TTF TRUE)
#	SET(USE_SDL_GFX TRUE)

# local project settings
INCLUDE (bindings)

SET(GuiLib_GLOBAL_headers
		MathDefs.h
		TimingDefs.h
)

# User-Interface skeleton
SET(GuiLib_GUI_Data_headers
		GUI/Data/ColorData.h
)
SET(GuiLib_GUI_Data_sources
		GUI/Data/ColorData.cpp
)

SET(GuiLib_OTHER_headers
		Input/KeyboardHandler.h
)
SET(GuiLib_OTHER_sources
		Input/KeyboardHandler.cpp
)

SET(GuiLib_GUI_headers
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
SET(GuiLib_GUI_sources
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
SET(GuiLib_Component_headers
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
		GUI/Components/Canvas.h
		GUI/Components/CanvasRendererImpl.h
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
SET(GuiLib_Component_sources
		Timing.cpp
		TimingChain.cpp
		GUI/Disposable.cpp

		GUI/Components/Point.cpp
		GUI/Components/Rectangle.cpp
		GUI/Components/Color.cpp
		GUI/Components/Canvas.cpp
		GUI/Components/CanvasRendererImpl.cpp
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
SET(GuiLib_GuiConsole_headers
		GUI/Visual/DT_drawtext.h
		GUI/Visual/internal.h
		GUI/Visual/SDL_console.h
		GUI/Visual/split.h
)
SET(GuiLib_GuiConsole_sources
		GUI/Visual/DT_drawtext.c
		GUI/Visual/internal.c
		GUI/Visual/SDL_console.c
		GUI/Visual/split.c
)

# putting the sources together
SET(GuiLib_headers
		${GuiLib_OTHER_headers}
		${GuiLib_GUI_Data_headers}
		${GuiLib_GUI_headers}
		${GuiLib_Component_headers}

		Filesystem/FileLoader.h
)

SET(GuiLib_sources
		${GuiLib_OTHER_sources}
		${GuiLib_GUI_Data_sources}
		${GuiLib_GUI_sources}
		${GuiLib_Component_sources}

		Filesystem/FileLoader.cpp
)


INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${SDLIMAGE_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${SDLTTF_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${SDLGFX_INCLUDE_DIR})
#INCLUDE_DIRECTORIES(${HumbugGLShared_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${HumbugGLLib_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR})
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
INCLUDE_DIRECTORIES( ${glm_INCLUDE_DIR} )

# Move to bindings
IF(LINUX)
  INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
ENDIF(LINUX)


ADD_DEFINITIONS(${GuiLibShared_DEFINITIONS})
IF(SDLIMAGE_FOUND)
  ADD_DEFINITIONS("-DHAVE_SDLIMAGE")
ENDIF(SDLIMAGE_FOUND)

# Move to bindings
IF(LINUX)
  ADD_DEFINITIONS("-DLINUX")
ENDIF(LINUX)

#if(WIN32)
#endif(WIN32)

if(CMAKE_GENERATOR MATCHES Visual*)
	# disable warning C4996: 'std::_Uninitialized_copy0': Function call with parameters that may be unsafe
	ADD_DEFINITIONS("/wd4996")
	# error C3859: virtual memory range for PCH exceeded; please recompile with a command line option of '-Zm118' or greater
	# fatal error C1076: compiler limit : internal heap limit reached; use /Zm to specify a higher limit
	ADD_DEFINITIONS("-Zm118")
endif()


ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" GuiLib_sources)

SOURCE_GROUP(Generated FILES ${res_outfiles} ${moc_outfiles} ${ui_outfiles} )
SOURCE_GROUP(Resources FILES ${GuiLib_resfiles})
SOURCE_GROUP(GUI FILES ${GuiLib_uifiles})
SOURCE_GROUP(GlobalHeader FILES ${DEBUG_DEFINITION_INCLUDES})
SOURCE_GROUP(GlobalHeader FILES ${GuiLib_GLOBAL_headers})
SOURCE_GROUP(THeaders FILES ${GuiLib_headers})
SOURCE_GROUP(TSources FILES ${GuiLib_sources})
SOURCE_GROUP(GuiHeaders FILES ${GuiLib_GUI_headers})
SOURCE_GROUP(GuiSources FILES ${GuiLib_GUI_sources})
SOURCE_GROUP(CompHeaders FILES ${GuiLib_Component_headers})
SOURCE_GROUP(CompSources FILES ${GuiLib_Component_sources})

#SET(GuiLib_documents
#		Readme.md
#		docs/!DevelNotes.txt
#)
#SOURCE_GROUP(Docs FILES ${GuiLib_documents})
ENSURE_DOCS_ARE_PRESENT(GuiLib_documents)

SET(LIBRARY_TYPE STATIC)
ADD_DEFINITIONS("-DMYENGINE_EXPORTS")

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
TARGET_LINK_LIBRARIES(GuiLib HumbugGLLib)
#TARGET_LINK_LIBRARIES(GuiLib HumbugGLShared)
TARGET_LINK_LIBRARIES(GuiLib ${SDL_LIBRARY})
TARGET_LINK_LIBRARIES(GuiLib ${SDLIMAGE_LIBRARY})
TARGET_LINK_LIBRARIES(GuiLib ${SDLTTF_LIBRARY})
TARGET_LINK_LIBRARIES(GuiLib ${SDLGFX_LIBRARY})
TARGET_LINK_LIBRARIES(GuiLib ${OPENGL_gl_LIBRARY})
TARGET_LINK_LIBRARIES(GuiLib ${OPENGL_glu_LIBRARY}) # this works on windows with VC2013
#TARGET_LINK_LIBRARIES(GuiLib ${GLUT_LIBRARIES})

#D:/Program Files (x86)/Windows Kits/8.0/Lib/win8/um/x64/

# A) Target-centric: target, header-file, precompiled header, [ warn on invalid header(-Winvalid-pch) ]
# B) individual sources specified: target, header-file, precompiled header,
#    warn on invalid header(-Winvalid-pch), source files with header
ADD_PRECOMPILED_HEADER(GuiLib stdafx.h stdafx.h.gch TRUE "${GuiLib_sources}")

INSTALL(TARGETS GuiLib
	COMPONENT Application
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib/static
)
#INSTALL(FILES
#		${SDL_LIBRARY_DLL_RELEASE}
#		${SDLIMAGE_LIBRARY_DLL_RELEASE}
#		${SDLIMAGE_LIBRARY_DLLS_EXT}
#		${SDLTTF_LIBRARY_DLL_RELEASE}
#		${SDLGFX_LIBRARY_DLL_RELEASE}
#	DESTINATION bin
#	COMPONENT Libraries
#)

