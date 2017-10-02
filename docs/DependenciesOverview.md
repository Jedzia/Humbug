 # HumbugLib #
Humbug Base Helper Library

Description here.

## Dependencies ## 

	none


	# HumbugShared #
Humbug Shared Library

Types that are specific for Humbug, like game objects or the virtual file system.

## Dependencies ## 

- TARGET_LINK Boost
	* program_options, filesystem, system, regex
- TARGET_LINK ZLIB_LIBRARY
- TARGET_LINK luabind


 # Humbug GuiLib #
SDL Gui Integration Library

Provides components and helpers for easy use of SDL.

## Dependencies ## 

- TARGET_LINK HumbugLib
    * provides debug helpers.
- TARGET_LINK SDL_LIBRARY
- TARGET_LINK SDLIMAGE_LIBRARY
- TARGET_LINK SDLTTF_LIBRARY
- TARGET_LINK SDLGFX_LIBRARY


 # HumbugConsole #
Humbug Helper Console-Application

Description here.

## Dependencies ## 

- TARGET_LINK Boost
	* program_options, filesystem, system, regex, serialization
- TARGET_LINK HumbugLib
    * provides debug helpers.
- TARGET_LINK HumbugShared
	* game objects, VFS
- TARGET_LINK GuiLib
- TARGET_LINK luabind


