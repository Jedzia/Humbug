ADD_SUBDIRECTORY( luabind )

SET_PROPERTY(TARGET luabind PROPERTY FOLDER "External Library")
#SET_PROPERTY(TARGET LuabindDoc PROPERTY FOLDER "External Library")

ADD_SUBDIRECTORY( glm )
SET(glm_INCLUDE_DIR "${glm_SOURCE_DIR}"  CACHE STRING "OpenGL Mathematics (GLM) Include Directory.")