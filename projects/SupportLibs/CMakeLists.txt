ADD_SUBDIRECTORY( luabind )

SET_PROPERTY(TARGET luabind PROPERTY FOLDER "External Library")
#SET_PROPERTY(TARGET LuabindDoc PROPERTY FOLDER "External Library")

ADD_SUBDIRECTORY( glm )
SET(glm_INCLUDE_DIR "${glm_SOURCE_DIR}"  CACHE STRING "OpenGL Mathematics (GLM) Include Directory.")

ADD_SUBDIRECTORY( glew/build/cmake )
SET(GLEW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/glew/include"  CACHE STRING "OpenGL Extension Wrangler Library Include Directory.")
