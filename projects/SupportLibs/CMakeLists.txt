ADD_SUBDIRECTORY( luabind )

SET_PROPERTY(TARGET luabind PROPERTY FOLDER "External Library")
#SET_PROPERTY(TARGET LuabindDoc PROPERTY FOLDER "External Library")

ADD_SUBDIRECTORY( glm )
SET(glm_INCLUDE_DIR "${glm_SOURCE_DIR}"  CACHE STRING "OpenGL Mathematics (GLM) Include Directory.")

ADD_SUBDIRECTORY( glew/build/cmake )
SET(GLEW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glew/include"  CACHE STRING "OpenGL Extension Wrangler Library Include Directory.")

OPTION(FREEGLUT_BUILD_SHARED_LIBS "Build FreeGLUT shared library." OFF)
OPTION(FREEGLUT_BUILD_STATIC_LIBS "Build FreeGLUT static library." ON)
OPTION(FREEGLUT_BUILD_DEMOS "Build FreeGLUT demos." OFF )
ADD_SUBDIRECTORY( FreeGLUT )

#ADD_SUBDIRECTORY( gl3w )
#SET(GL3W_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/gl3w/include"  CACHE STRING "OpenGL Extension Wrangler Library Include Directory.")
#SET(GL3W_LIBRARIES "${CMAKE_CURRENT_BINARY_DIR}/gl3w/Debug/dings.lib"  CACHE STRING "OpenGL Extension Wrangler Library Include Directory.")

SET(OGLPLUS_DEP_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/FreeGLUT/include")
option(OGLPLUS_NO_EXAMPLES "Don't build examples and textures." On)
option(OGLPLUS_NO_SCREENSHOTS "Don't make example screenshots for the docs." On)
option(OGLPLUS_NO_DOCS "Don't build and install the documentation." On)
ADD_SUBDIRECTORY( oglplus )
SET(OGLPLUS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/oglplus/include;${CMAKE_CURRENT_SOURCE_DIR}/oglplus/implement;${CMAKE_CURRENT_BINARY_DIR}/oglplus/include"  CACHE STRING "OpenGL Extension Wrangler Library Include Directory.")
