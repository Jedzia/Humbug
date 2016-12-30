# MACRO_BOOL_TO_01( VAR RESULT0 ... RESULTN )
# This macro evaluates its first argument
# and sets all the given vaiables either to 0 or 1
# depending on the value of the first one

# Copyright (c) 2006, Alexander Neundorf, <neundorf@kde.org>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.


macro(MACRO_BOOL_TO_01 FOUND_VAR )
   foreach (_current_VAR ${ARGN})
      if(${FOUND_VAR})
         set(${_current_VAR} 1)
      else(${FOUND_VAR})
         set(${_current_VAR} 0)
      endif(${FOUND_VAR})
   endforeach(_current_VAR)
endmacro(MACRO_BOOL_TO_01)
