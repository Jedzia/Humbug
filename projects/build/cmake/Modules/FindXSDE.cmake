#
# CMake script for finding XSDe.
# If the optional XSDE_ROOT_DIR environment variable exists, executable, header files and
# libraries will be searched in the XSDE_ROOT_DIR/bin XSDE_ROOT_DIR/include and XSDE_ROOT_DIR/libs
# directories, respectively. Otherwise the default CMake search process will be
# used.
#
# This script creates the following variables:
#  XSDE_FOUND: Boolean that indicates if the package was found
#  XSDE_EXECUTABLE: command to call the xsde executable
#  XSDE_INCLUDE_DIR: Path to include to use xsde
#  XSDE_LIBRARY_DIR: Path to link against if you included an xsde header 
#
################################################################################

include(FindPackageHandleStandardArgs)

# Get hint from environment variable (if any)
if(NOT XSDE_ROOT_DIR AND DEFINED ENV{XSDE_ROOT_DIR})
  set(XSDE_ROOT_DIR "$ENV{XSDE_ROOT_DIR}" CACHE PATH "XSDE base directory location (optional, used for nonstandard installation paths)")
  mark_as_advanced(XSDE_ROOT_DIR)
endif()

# Search path for nonstandard locations
if(XSDE_ROOT_DIR)
  set(XSDE_BIN_PATH PATHS "${XSDE_ROOT_DIR}/bin" NO_DEFAULT_PATH)
  set(XSDE_INCLUDE_PATH PATHS "${XSDE_ROOT_DIR}/include" NO_DEFAULT_PATH)
  set(XSDE_LIBRARY_PATH PATHS "${XSDE_ROOT_DIR}/lib" NO_DEFAULT_PATH)
else(XSDE_ROOT_DIR)
  set(XSDE_INCLUDE_PATH PATHS "/usr/include/libxsde" "/usr/local/include/libxsde")
  set(XSDE_LIBRARY_PATH PATHS "/usr/lib/libxsde/xsde"  "/usr/local/lib/libxsde/xsde")
endif(XSDE_ROOT_DIR)

# Find headers and libraries
find_program(XSDE_BIN            NAMES xsde          ${XSDE_BIN_PATH})
find_path(XSDE_INCLUDE_DR        NAMES xsde/config.h ${XSDE_INCLUDE_PATH})
find_path(XSDE_LIBRARY_DR        NAMES libxsde.a     ${XSDE_LIBRARY_PATH})

# Set XSDE_FOUND honoring the QUIET and REQUIRED arguments
find_package_handle_standard_args(XSDE DEFAULT_MSG XSDE_BIN XSDE_LIBRARY_DR XSDE_INCLUDE_DR)

# Output variables
if(XSDE_FOUND)
  MESSAGE("setting xsde vars")
  # Include dirs
  set(XSDE_EXECUTABLE ${XSDE_BIN})

  # Include dirs
  set(XSDE_INCLUDE_DIR ${XSDE_INCLUDE_DR})

  # Libraries
  set(XSDE_LIBRARY_DIR ${XSDE_LIBRARY_DR})
#  set(XSDE_LIBRARY "xsde")
  set(XSDE_LIBRARY "${XSDE_LIBRARY_DR}/xsde.lib")

endif(XSDE_FOUND)

# Advanced options for not cluttering the cmake UIs
mark_as_advanced(XSDE_BIN XSDE_INCLUDE_DR XSDE_LIBRARY_DR)
