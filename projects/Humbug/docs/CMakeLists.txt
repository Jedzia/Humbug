##---------------------------------------------------------------------------
## $RCSfile$
## $Source$
## $Revision$
## $Date$
##---------------------------------------------------------------------------
## Author:      Jedzia
## Copyright:   (c) Jedzia, 2011
## License:     GPL License
##---------------------------------------------------------------------------
##---------------------------------------------------
##
##---------------------------------------------------
## !!!!!! CMake Help: http://www.cmake.org/cmake/help/cmake-2-8-docs.html !!!!!

cmake_minimum_required(VERSION 2.8.2)
project( HumbugDocs )

# See http://www.stack.nl/~dimitri/doxygen/grouping.html and 
# http://www.stack.nl/~dimitri/doxygen/commands.html#cmdcode for 
# a doxygen manual.

include(DoxygenTargets)
#add_doxygen(<doxyfile> [OUTPUT_DIRECTORY <outputdir>]
#   [INSTALL_DESTINATION <installdir>
#   [INSTALL_COMPONENT <installcomponent>]
#   [INSTALL_PDF_NAME <installpdfname>] ]
#   [DOC_TARGET <targetname>]
#   [PROJECT_NUMBER <versionnumber>]
#   [NO_WARNINGS]
#   [NO_PDF]
#)
#${CMAKE_CURRENT_SOURCE_DIR}/
add_doxygen(Humbug.doxygen
#   [INSTALL_DESTINATION <installdir>
#   [INSTALL_COMPONENT <installcomponent>]
#   [INSTALL_PDF_NAME <installpdfname>] ]
    DOC_TARGET ${PROJECT_NAME}
#   [PROJECT_NUMBER <versionnumber>]
#   [NO_WARNINGS]
   NO_PDF
)
