 # HumbugGLLib #
HumbugGL Base Helper Library

Description here.

## Dependencies ## 

	none


	# HumbugGLShared #
HumbugGL Shared Library

Types that are specific for HumbugGL, like game objects or the virtual file system.

## Dependencies ## 

- TARGET_LINK Boost
	* program_options, filesystem, system, regex
- TARGET_LINK ZLIB_LIBRARY
- TARGET_LINK luabind


 # HumbugGL GuiLib #
SDL Gui Integration Library

Provides components and helpers for easy use of SDL.

## Dependencies ## 

- TARGET_LINK HumbugGLLib
    * provides debug helpers.
- TARGET_LINK SDL_LIBRARY
- TARGET_LINK SDLIMAGE_LIBRARY
- TARGET_LINK SDLTTF_LIBRARY
- TARGET_LINK SDLGFX_LIBRARY


 # HumbugGLConsole #
HumbugGL Helper Console-Application

Description here.

## Dependencies ## 

- TARGET_LINK Boost
	* program_options, filesystem, system, regex, serialization
- TARGET_LINK HumbugGLLib
    * provides debug helpers.
- TARGET_LINK HumbugGLShared
	* game objects, VFS
- TARGET_LINK GuiLib
- TARGET_LINK luabind


