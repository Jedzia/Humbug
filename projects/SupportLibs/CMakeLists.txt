add_subdirectory( luabind )

set_property(TARGET luabind PROPERTY FOLDER "External Library")
#set_property(TARGET LuabindDoc PROPERTY FOLDER "External Library")

add_subdirectory( glm )
set(glm_INCLUDE_DIR "${glm_SOURCE_DIR}"  CACHE STRING "OpenGL Mathematics (GLM) Include Directory.")

add_subdirectory( glew/build/cmake )
set(GLEW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glew/include"  CACHE STRING "OpenGL Extension Wrangler Library Include Directory.")

option(FREEGLUT_BUILD_SHARED_LIBS "Build FreeGLUT shared library." OFF)
option(FREEGLUT_BUILD_STATIC_LIBS "Build FreeGLUT static library." ON)
option(FREEGLUT_BUILD_DEMOS "Build FreeGLUT demos." OFF )
add_subdirectory( FreeGLUT )

#add_subdirectory( gl3w )
#set(GL3W_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/gl3w/include"  CACHE STRING "OpenGL Extension Wrangler Library Include Directory.")
#set(GL3W_LIBRARIES "${CMAKE_CURRENT_BINARY_DIR}/gl3w/Debug/dings.lib"  CACHE STRING "OpenGL Extension Wrangler Library Include Directory.")

set(OGLPLUS_DEP_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/FreeGLUT/include")
option(OGLPLUS_NO_EXAMPLES "Don't build examples and textures." On)
option(OGLPLUS_NO_SCREENSHOTS "Don't make example screenshots for the docs." On)
option(OGLPLUS_NO_DOCS "Don't build and install the documentation." On)
add_subdirectory( oglplus )
set(OGLPLUS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/oglplus/include;${CMAKE_CURRENT_SOURCE_DIR}/oglplus/implement;${CMAKE_CURRENT_BINARY_DIR}/oglplus/include"  CACHE STRING "OpenGL Extension Wrangler Library Include Directory.")
