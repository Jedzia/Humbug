INCLUDE(InstallRequiredSystemLibraries)

# Components
set(CPACK_COMPONENTS_ALL Application Libraries Resources)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "This is Humbug, the Game!")
SET(CPACK_PACKAGE_VENDOR "Me, myself, and I")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${P_ROOT_PATH}/ReadMe")
SET(CPACK_RESOURCE_FILE_WELCOME "${P_ROOT_PATH}/Installer/Welcome.txt")
SET(CPACK_RESOURCE_FILE_README "${P_ROOT_PATH}/ReadMe")
SET(CPACK_RESOURCE_FILE_LICENSE "${P_ROOT_PATH}/Copyright")
SET(CPACK_PACKAGE_VERSION_MAJOR "1")
SET(CPACK_PACKAGE_VERSION_MINOR "3")
SET(CPACK_PACKAGE_VERSION_PATCH "2")
#SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "Humbug")
IF(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
#  SET(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
#  SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe")
  SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} My Famous Project")
  SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
  SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
  SET(CPACK_NSIS_CONTACT "me@my-personal-home-page.com")
#  SET(CPACK_NSIS_MODIFY_PATH ON)
ELSE(WIN32 AND NOT UNIX)
  SET(CPACK_STRIP_FILES "bin/MyExecutable")
  SET(CPACK_SOURCE_STRIP_FILES "")
ENDIF(WIN32 AND NOT UNIX)
SET(CPACK_PACKAGE_EXECUTABLES "Humbug" "Humbug Game")

INCLUDE(CPack)
