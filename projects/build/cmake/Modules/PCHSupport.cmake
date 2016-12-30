
set( PCH_${PROJECT_NAME}_ENABLED TRUE CACHE BOOL "Enable precompiled header support for the $(PROJECT) project .")
mark_as_advanced(PCH_${PROJECT_NAME}_ENABLED)
add_definitions("-DPCH_${PROJECT_NAME}_ENABLED")

if(MSVC)
        # Disable ADD_PRECOMPILED_HEADER on MSVC
        macro(ADD_PRECOMPILED_HEADER _targetName _input _gch)        
        endmacro()
        if(PCH_${PROJECT_NAME}_ENABLED)
                include (PCHSupport_MSVC)
                if(NOT PCHSupport_FOUND)
                  # PCH usage not available. Blank out macro.
                  macro(ADD_PRECOMPILED_HEADER _targetName _input _gch)        
                  endmacro()
                endif(NOT PCHSupport_FOUND)
        else(PCH_${PROJECT_NAME}_ENABLED)
          # PCH usage turned off. Blank out macro.
          macro(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
          endmacro()
        endif(PCH_${PROJECT_NAME}_ENABLED)
elseif(CMAKE_COMPILER_IS_GNUCXX)
        # Disable ADD_MSVC_PRECOMPILED_HEADER on GCC
        macro(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
        endmacro()
        if(PCH_${PROJECT_NAME}_ENABLED)
                include (PCHSupport_26)
                if(NOT PCHSupport_FOUND)
                  # PCH usage not available. Blank out macro.
                  macro(ADD_PRECOMPILED_HEADER _targetName _input _gch)        
                  endmacro()
                endif(NOT PCHSupport_FOUND)
        else(PCH_${PROJECT_NAME}_ENABLED)
          # PCH usage turned off. Blank out macro.
          macro(ADD_PRECOMPILED_HEADER _targetName _input _gch)        
          endmacro()
        endif(PCH_${PROJECT_NAME}_ENABLED)
else()
          macro(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
          endmacro()

          macro(ADD_PRECOMPILED_HEADER _targetName _input _gch)        
          endmacro()
endif(MSVC)

