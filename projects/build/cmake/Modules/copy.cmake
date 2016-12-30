# copy.cmake 													   16:27 17.11.2010
# Copy with conditional debug/release switch 
# by Jedzia (c) 2010
#
# Call with:
# ---------------------------------------------------------------------------------
# COMMAND ${CMAKE_COMMAND} --debug-output -Dconfig=${CMAKE_CFG_INTDIR} -Dtgt=${tgt} 
# -Dreleasesrc=${_boost_my_releasedll} -Ddebugsrc=${_boost_my_debugdll} 
# -P "${CMAKE_SOURCE_DIR}/build/cmake/Modules/copy.cmake"
# 
# Arguments:
# ---------------------------------------------------------------------------------
# * config 			debug/release switch
# * tgt				base target directory
# * releasesrc		source to use when the release switch is triggered
# * debugsrc		source to use when the debug switch is triggered
#
# Description:
# ---------------------------------------------------------------------------------
# This little script can be used to copy dll's from their library folder into the
# target folder of a built executable that depends on those libraries.
#
# When the build is in the state of debug output "debug/" is added to the -Dtgt 
# target destination directory and -Ddebugsrc file is copied to it.
# All other -Dconfig settings add a "release/" to -Dtgt as the destination for
# the file specified with -Dreleasesrc. 
# ---------------------------------------------------------------------------------

#message( STATUS "*COPY* config: ${config}")
if(no_intdir)
	set(target "${tgt}")
else()
	set(target "${tgt}${config}/")
endif()

if(${config} STREQUAL "Debug")
  set(src ${debugsrc})
else()
  set(src ${releasesrc})
endif()

#message( STATUS "*COPY* copy src: ${src} to target: ${target}   ")

execute_process(
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${src} ${target}
 )
