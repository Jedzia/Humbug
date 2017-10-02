# Locate Luabind library

find_path(LUABIND_INCLUDE_DIRS luabind/luabind.hpp
  HINTS $ENV{LUABIND_DIR}
  PATH_SUFFIXES include/luabind09 include/luabind include
)

find_library(_LUABIND_LIBRARY_RELEASE
  NAMES luabind09 luabind-0.9 luabind
  HINTS $ENV{LUABIND_DIR}
  PATH_SUFFIXES lib64 lib
)

find_library(_LUABIND_LIBRARY_DEBUG
  NAMES luabind09-d luabind-0.9-d luabind-d
  HINTS $ENV{LUABIND_DIR}
  PATH_SUFFIXES lib64 lib
)

if(_LUABIND_LIBRARY_RELEASE OR _LUABIND_LIBRARY_DEBUG)
    if(_LUABIND_LIBRARY_RELEASE AND _LUABIND_LIBRARY_DEBUG)
        set(_LUABIND_LIBRARY optimized ${_LUABIND_LIBRARY_RELEASE}
                             debug     ${_LUABIND_LIBRARY_DEBUG})
    elseif(_LUABIND_LIBRARY_RELEASE)
        set(_LUABIND_LIBRARY ${_LUABIND_LIBRARY_RELEASE})
    else()
        set(_LUABIND_LIBRARY ${_LUABIND_LIBRARY_DEBUG})
    endif()
endif()

if(_LUABIND_LIBRARY)
    set(LUABIND_LIBRARIES
        "${_LUABIND_LIBRARY}" CACHE STRING "Luabind Libraries")
endif(_LUABIND_LIBRARY)

include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
# handle the QUIETLY and REQUIRED arguments and set LUABIND_FOUND to TRUE if
# all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Luabind
    REQUIRED_VARS LUABIND_INCLUDE_DIRS LUABIND_LIBRARIES)

mark_as_advanced(LUABIND_INCLUDE_DIRS LUABIND_LIBRARIES)
