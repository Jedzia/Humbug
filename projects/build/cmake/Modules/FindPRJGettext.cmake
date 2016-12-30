# - Slightly modified Find GNU gettext tools
# This module looks for the GNU gettext tools. This module defines the 
# following values:
#  GETTEXT_MSGMERGE_EXECUTABLE: the full path to the msgmerge tool.
#  GETTEXT_MSGFMT_EXECUTABLE: the full path to the msgfmt tool.
#  GETTEXT_FOUND: True if gettext has been found.
#
# Additionally it provides the following macros:
# GETTEXT_CREATE_TRANSLATIONS ( outputFile [ALL] file1 ... fileN )
#    This will create a target "translations" which will convert the 
#    given input po files into the binary output mo file. If the 
#    ALL option is used, the translations will also be created when
#    building the default target.

set(hints "HINTS ${GNUWIN32_DIR}/bin")
#message(FATAL_ERROR "   hints ${hints}")
find_program(GETTEXT_MSGMERGE_EXECUTABLE msgmerge  HINTS ${GNUWIN32_DIR}/bin )
find_program(GETTEXT_MSGFMT_EXECUTABLE   msgfmt    HINTS ${GNUWIN32_DIR}/bin )
find_program(GETTEXT_XGETTEXT_EXECUTABLE xgettext  HINTS ${GNUWIN32_DIR}/bin )
find_program(GETTEXT_MSGUNIQ_EXECUTABLE  msguniq   HINTS ${GNUWIN32_DIR}/bin )

macro(GETTEXT_CREATE_TRANSLATIONS _potFile _firstPoFile)

   set(_gmoFiles)
   # remove only the last extension e.g
   # 	LyX2.0.pot ==> LyX2.0
   # and not LyX2.0.pot ==> LyX2
   # as it would be with NAME_WE
   # get_filename_component(_potBasename ${_potFile} NAME_WE)
   get_filename_component(_potname ${_potFile} NAME)
   if (_potname MATCHES "^\(.+\)\\.[^\\.]+$")
       set(_potBasename ${CMAKE_MATCH_1})
   else()
       set(_potBasename ${_potname})
   endif()
   get_filename_component(_absPotFile ${_potFile} ABSOLUTE)

   set(_addToAll)
   if(${_firstPoFile} STREQUAL "ALL")
      set(_addToAll "ALL")
      set(_firstPoFile)
   endif(${_firstPoFile} STREQUAL "ALL")

   foreach (_currentPoFile ${ARGN})
      get_filename_component(_absFile ${_currentPoFile} ABSOLUTE)
      get_filename_component(_abs_PATH ${_absFile} PATH)
      get_filename_component(_lang ${_absFile} NAME_WE)
      set(_gmoFile ${CMAKE_CURRENT_BINARY_DIR}/${_lang}.gmo)

      add_custom_command( 
         OUTPUT ${_gmoFile} 
         COMMAND ${GETTEXT_MSGMERGE_EXECUTABLE} --quiet --update --backup=none ${_absFile} ${_absPotFile}
         COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} -o ${_gmoFile} ${_absFile}
         DEPENDS ${_absPotFile} ${_absFile} 
      )

      install(FILES ${_gmoFile} DESTINATION ${${_prj_name}_DATA_SUBDIR}${${_prj_name}_LOCALEDIR}/${_lang}/LC_MESSAGES RENAME ${_potBasename}.mo) 
      set(_gmoFiles ${_gmoFiles} ${_gmoFile})

   endforeach (_currentPoFile )

   add_custom_target(${PACKAGE}_translations ${_addToAll} DEPENDS ${_gmoFiles})

endmacro(GETTEXT_CREATE_TRANSLATIONS )

if (GETTEXT_MSGMERGE_EXECUTABLE AND GETTEXT_MSGFMT_EXECUTABLE )
   set(GETTEXT_FOUND TRUE)
else (GETTEXT_MSGMERGE_EXECUTABLE AND GETTEXT_MSGFMT_EXECUTABLE )
   set(GETTEXT_FOUND FALSE)
   if (GetText_REQUIRED)
      message(FATAL_ERROR "GetText not found")
   endif (GetText_REQUIRED)
endif (GETTEXT_MSGMERGE_EXECUTABLE AND GETTEXT_MSGFMT_EXECUTABLE )

mark_as_advanced(GETTEXT_MSGMERGE_EXECUTABLE GETTEXT_MSGFMT_EXECUTABLE GETTEXT_XGETTEXT_EXECUTABLE GETTEXT_MSGUNIQ_EXECUTABLE)

