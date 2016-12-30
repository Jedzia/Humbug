# Modules path (for searching FindXXX.cmake files)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../config" "${PROJECT_SOURCE_DIR}/config")

set(CMAKE_VERSION "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}")
message(STATUS "CMAKE_VERSION: ${CMAKE_VERSION}")


###########################################################
#                                                         #
# Some global options we need to set here                 #
#                                                         #
###########################################################
#
# STATIC or SHARED
#
option( BUILD_STATIC "Build as a static library." ${FORCE_BUILD_STATIC})
# Is modified by target selection below

# Disable line wrapping for gcc/g++ such that eclipse can parse the errors.
#
if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
endif(CMAKE_COMPILER_IS_GNUCC)
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
endif(CMAKE_COMPILER_IS_GNUCXX)

#
# If we're using gcc, make sure the version is OK.
#
if (CMAKE_COMPILER_IS_GNUCXX)
  # this is a workaround distcc:
  if ( CMAKE_CXX_COMPILER_ARG1 )
    string(REPLACE " " "" CMAKE_CXX_COMPILER_ARG1 ${CMAKE_CXX_COMPILER_ARG1} )
    #message("Invoking: '${CMAKE_CXX_COMPILER_ARG1} -dumpversion'")
    execute_process( COMMAND ${CMAKE_CXX_COMPILER_ARG1} -dumpversion RESULT_VARIABLE CXX_HAS_VERSION OUTPUT_VARIABLE CXX_VERSION)
  else ( CMAKE_CXX_COMPILER_ARG1 )
    #message("Invoking: ${CMAKE_CXX_COMPILER} -dumpversion")
    execute_process( COMMAND ${CMAKE_CXX_COMPILER} -dumpversion RESULT_VARIABLE CXX_HAS_VERSION OUTPUT_VARIABLE CXX_VERSION)
  endif ( CMAKE_CXX_COMPILER_ARG1 )

  if ( ${CXX_HAS_VERSION} EQUAL 0 )
    # We are assuming here that -dumpversion is gcc specific.
    if( CXX_VERSION MATCHES "4\\.[0-9](\\.[0-9])?" )
      message(STATUS "Detected gcc4: ${CXX_VERSION}")
      set(RTT_GCC_HASVISIBILITY TRUE)
    else(CXX_VERSION MATCHES "4\\.[0-9](\\.[0-9])?")
      if( CXX_VERSION MATCHES "3\\.[0-9](\\.[0-9])?" )
	message(STATUS "Detected gcc3: ${CXX_VERSION}")
      else( CXX_VERSION MATCHES "3\\.[0-9](\\.[0-9])?" )
	message("ERROR: You seem to be using gcc version:")
	message("${CXX_VERSION}")
	message( FATAL_ERROR "ERROR: For gcc, Orocos requires version 4.x or 3.x")
      endif( CXX_VERSION MATCHES "3\\.[0-9](\\.[0-9])?" )
    endif(CXX_VERSION MATCHES "4\\.[0-9](\\.[0-9])?")
  else ( ${CXX_HAS_VERSION} EQUAL 0)
    message("Could not determine gcc version: ${CXX_HAS_VERSION}")
  endif ( ${CXX_HAS_VERSION} EQUAL 0)
endif()

#
# Check for Doxygen and enable documentation building
#
find_package( Doxygen )
if ( DOXYGEN_EXECUTABLE )
  message( STATUS "Found Doxygen -- API documentation can be built" )
else ( DOXYGEN_EXECUTABLE )
  message( STATUS "Doxygen not found -- unable to build documentation" )
endif ( DOXYGEN_EXECUTABLE )

#
# Check for XSDe
#
find_package( XSDE REQUIRED XSDE_LIBRARY)
if ( XSDE_LIBRARY )
  message( STATUS "Found XSDe library -- parser/serializer can be built" )
else ( XSDE_LIBRARY )
  message( STATUS "XSDe library not found -- unable to build parser/serializer" )
endif ( XSDE_LIBRARY )

