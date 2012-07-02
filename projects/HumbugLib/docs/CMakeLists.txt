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

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.2)
PROJECT( HumbugLibDocs )

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
add_doxygen(HumbugLib.doxygen
#   [INSTALL_DESTINATION <installdir>
#   [INSTALL_COMPONENT <installcomponent>]
#   [INSTALL_PDF_NAME <installpdfname>] ]
    DOC_TARGET ${PROJECT_NAME}
#   [PROJECT_NUMBER <versionnumber>]
#   [NO_WARNINGS]
   NO_PDF
)
