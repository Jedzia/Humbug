
set(PACKAGE Humbug)
set(HUMBUG_RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Resources)

add_subdirectory( Artwork )
#add_subdirectory( HumbugShared )
add_subdirectory( src )

#set(POTSRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
#add_subdirectory( po )
add_subdirectory( docs )
