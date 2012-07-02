# This file is part of LyX, the document processor.
# Licence details can be found in the file COPYING.
#
# Copyright (c) 2008-2011 Peter Kümmel, <syntheticpp@gmx.net>
# Copyright (c) 2008-2011 Kornel Benko, <Kornel.Benko@berlin.de>
#

project(${PACKAGE}_Locale)

IF("${POTSRC}" STREQUAL "")
	SET(POTSRC ${CMAKE_CURRENT_SOURCE_DIR})
ENDIF()

#if(COMMAND cmake_policy)
#	cmake_policy(SET CMP0003 OLD)
#	cmake_policy(SET CMP0005 OLD)
#endif()

#set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)

# Supress regeneration
#set(CMAKE_SUPPRESS_REGENERATION FALSE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

SET(_lyxname ${PACKAGE})
MESSAGE(STATUS " Generating NLS Translations for ${PACKAGE}")

#SET(_lyxname ${PROJECT_NAME})
SET(_py_sources)
macro(add_gettext_python  _par _dir)
  set(_sources)
  foreach(_arg ${ARGN})
    file(GLOB _s1 ${CMAKE_CURRENT_SOURCE_DIR}/${_dir}/${_arg})
    list(SORT _s1)
    list(APPEND _sources ${_s1})
  endforeach(_arg)
  if (${_par} MATCHES "layouttranslations")
    SET(_dst "${CMAKE_CURRENT_BINARY_DIR}/${_par}")
  else ()
    SET(_dst "${CMAKE_CURRENT_BINARY_DIR}/${_par}_l10n.pot")
  endif()
  SET(_tmp_src_files "${CMAKE_CURRENT_BINARY_DIR}/${_par}_tmp_files")
  SET(_src_files "${CMAKE_CURRENT_BINARY_DIR}/${_par}_files")
  file(WRITE ${_tmp_src_files} "")
  foreach(_s ${_sources})
    FILE(APPEND ${_tmp_src_files} "${_s}\n")
  endforeach()
  if(${_par} MATCHES "^\(.*\)_[0-9]+$")
    set(_par1 ${CMAKE_MATCH_1})
  else()
    set(_par1 ${_par})
  endif()
  ADD_CUSTOM_COMMAND(
    OUTPUT ${_src_files}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${_tmp_src_files} ${_src_files}
    DEPENDS ${_tmp_src_files}
  )
  MESSAGE(STATUS " _src_files ${_src_files}")
  MESSAGE(STATUS " _tmp_src_files ${_tmp_src_files}")

  if (${_par} MATCHES "layouttranslations")
    ADD_CUSTOM_COMMAND(
      OUTPUT "${_dst}"
      PRE_BUILD
      COMMAND  ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/lib/layouttranslations" "${_dst}"
      COMMAND ${PYTHON_EXECUTABLE}
      ARGS "${P_PO_MODULES_PATH}/lyx_pot.py" -b "${CMAKE_CURRENT_SOURCE_DIR}" -o "${_dst}" -t ${_par1} "--src_file=${_src_files}"
      COMMAND  ${CMAKE_COMMAND} -E copy_if_different "${_dst}" "${CMAKE_CURRENT_SOURCE_DIR}/lib/layouttranslations"
      DEPENDS ${_sources} ${_src_files} "${CMAKE_CURRENT_SOURCE_DIR}/lib/layouttranslations"
      COMMENT "${PYTHON_EXECUTABLE} ${P_PO_MODULES_PATH}/lyx_pot.py -b ${CMAKE_CURRENT_SOURCE_DIR} -o  ${_dst} -t ${_par1} --src_file=${_src_files}"
      )
    ADD_CUSTOM_TARGET(${PACKAGE}_layouttranslations1 DEPENDS "${_dst}")
    if (${_prj_name}_DATA_SUBDIR STREQUAL "")
      install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/lib/layouttranslations" DESTINATION .)
    else()
      install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/lib/layouttranslations" DESTINATION ${${_prj_name}_DATA_SUBDIR})
    endif()
  else()
    ADD_CUSTOM_COMMAND(
      OUTPUT "${_dst}"
      PRE_BUILD
      COMMAND ${PYTHON_EXECUTABLE}
      ARGS "${P_PO_MODULES_PATH}/lyx_pot.py" -b "${CMAKE_CURRENT_SOURCE_DIR}" -o "${_dst}" -t ${_par1} "--src_file=${_src_files}"
      DEPENDS ${_sources} ${_src_files} 
      COMMENT "${PYTHON_EXECUTABLE} ${P_PO_MODULES_PATH}/lyx_pot.py -b ${CMAKE_CURRENT_SOURCE_DIR} -o  ${_dst} -t ${_par1} --src_file=${_src_files}"
      )
#    ADD_CUSTOM_TARGET(fuck_${_par} DEPENDS "${_dst}")
	    MESSAGE(STATUS "_dst ${_dst} ------  _sources ${_sources} ---- _src_files ${_src_files}")

    LIST(APPEND _py_sources "${_dst}")
  endif()
  SET_SOURCE_FILES_PROPERTIES("${_dst}" GENERATED)
  SET_SOURCE_FILES_PROPERTIES("${_src_files}" GENERATED)
endmacro(add_gettext_python)

SET_SOURCE_FILES_PROPERTIES("${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.cat.pot" GENERATED)
SET_SOURCE_FILES_PROPERTIES("${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.fmt.pot" GENERATED)
SET_SOURCE_FILES_PROPERTIES("${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.pot" GENERATED)

#add_gettext_python(qt4 src/frontends/qt4/ui *.ui)
#add_gettext_python(layouts lib/layouts *.layout *.inc *.module)
#add_gettext_python(languages lib languages)
#add_gettext_python(encodings lib encodings)
#add_gettext_python(ui lib/ui *.ui *.inc)
#add_gettext_python(external lib external_templates)
add_gettext_python(formats lib configure.py)
#add_gettext_python(layouttranslations lib/layouts *.layout *.inc *.module)
#add_gettext_python(fs ../FileSystem *.cpp)
#add_gettext_python(layouttranslations ../../../../Humbug *.ui)
#add_gettext_python(qt4 ../../../../Humbug *.ui)

MESSAGE(STATUS " _py_sources ${_py_sources}")

ADD_CUSTOM_COMMAND(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.cat.pot"
    COMMAND ${PYTHON_EXECUTABLE}
    ARGS   "${P_PO_MODULES_PATH}/cat.py" ${_py_sources} > "${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.cat.pot"
    DEPENDS ${_py_sources}
    )
#MESSAGE(STATUS " PYTHON_EXECUTABLE ${PYTHON_EXECUTABLE}")
#ADD_CUSTOM_TARGET(cat DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.cat.pot)

ADD_CUSTOM_COMMAND(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.fmt.pot"
    COMMAND ${GETTEXT_MSGUNIQ_EXECUTABLE}
    ARGS -o "${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.fmt.pot" "${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.cat.pot"
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.cat.pot"
    )
#ADD_CUSTOM_TARGET(uniq DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.fmt.pot)

SET(_potfiles_dep)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/POTFILES.in "")
file(GLOB_RECURSE _tmp_potfiles RELATIVE ${POTSRC} ${POTSRC}/*.h  ${POTSRC}/*.cpp  ${POTSRC}/*.cpp.in)
MESSAGE(STATUS " _tmp_potfiles ${_tmp_potfiles}")
list(SORT _tmp_potfiles)
list(REMOVE_ITEM _tmp_potfiles src/support/Package.cpp)

foreach(_f ${_tmp_potfiles})
  # we don't need to select only relevant files because the outcome of xgettext
  # will stay the same.
  # Relevant files are files containing the string '_(".*")'
  LIST(APPEND _potfiles_dep "${CMAKE_CURRENT_SOURCE_DIR}/${_f}")
  file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/POTFILES.in "${_f}\n")
endforeach(_f)

ADD_CUSTOM_COMMAND(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.pot"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.fmt.pot" "${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.pot"
    COMMAND ${GETTEXT_XGETTEXT_EXECUTABLE}
    ARGS --default-domain=${_lyxname} --directory=${POTSRC} --add-comments=TRANSLATORS: --language=C++ --join-existing --keyword=_ --keyword=N_ --keyword=B_ --keyword=qt_ --files-from="${CMAKE_CURRENT_BINARY_DIR}/POTFILES.in" --copyright-holder="LyX Developers" --msgid-bugs-address=lyx-devel@lists.lyx.org -o "${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.pot"
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.fmt.pot" ${_potfiles_dep}
    )
#ADD_CUSTOM_TARGET(vollpot DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.pot")

#
# We have to copy the po-files first,
# otherwise they would be modified (inside the macro GETTEXT_CREATE_TRANSLATIONS())
# This makes the "svn up" on po-files work again
#file(GLOB LYX_BASE_PO_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/po ${CMAKE_CURRENT_SOURCE_DIR}/po/*.po)
file(GLOB LYX_BASE_PO_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.po)
#MESSAGE(STATUS "LYX_BASE_PO_FILES ${LYX_BASE_PO_FILES}")
set(LYX_PO_FILES)
SET(LYX_UPDATED_PO_FILES)
SET(LYX_DEST_PO ${CMAKE_CURRENT_SOURCE_DIR})

foreach(_pofile ${LYX_BASE_PO_FILES})
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_pofile}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${_pofile} ${CMAKE_CURRENT_BINARY_DIR}/${_pofile}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${_pofile}
    )
  list(APPEND LYX_PO_FILES ${CMAKE_CURRENT_BINARY_DIR}/${_pofile})
endforeach(_pofile)

set(LYX_UPDATED_PO_FILES)
foreach(_pofile ${LYX_BASE_PO_FILES})
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_pofile}.copied
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/${_pofile} ${LYX_DEST_PO}/${_pofile}
    COMMAND ${CMAKE_COMMAND} -E touch ${_pofile}.copied
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${_pofile}
    )
  list(APPEND LYX_UPDATED_PO_FILES ${CMAKE_CURRENT_BINARY_DIR}/${_pofile}.copied)
endforeach(_pofile)

if(LYX_CPACK OR LYX_INSTALL)
  set(_addALLOption ALL)
endif()
#MESSAGE(FATAL_ERROR " CMAKE_CURRENT_BINARY_DIR/_lyxname.pot   ${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.pot  ")
#MESSAGE(FATAL_ERROR " _addALLOption - LYX_PO_FILES ${_addALLOption} - ${LYX_PO_FILES} ")
GETTEXT_CREATE_TRANSLATIONS(${CMAKE_CURRENT_BINARY_DIR}/${_lyxname}.pot ${_addALLOption} ${LYX_PO_FILES})

# Create a new target to remerge po files
# ALL omitted here, to prevent from automatic creation
MESSAGE(STATUS " LYX_UPDATED_PO_FILES ${LYX_UPDATED_PO_FILES}")
ADD_CUSTOM_TARGET(${PACKAGE}_update-po DEPENDS ${LYX_UPDATED_PO_FILES})
add_dependencies(${PACKAGE}_update-po translations)

