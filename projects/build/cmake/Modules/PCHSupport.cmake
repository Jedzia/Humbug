
SET( PCH_${PROJECT_NAME}_ENABLED TRUE CACHE BOOL "Enable precompiled header support for the $(PROJECT) project .")
MARK_AS_ADVANCED(PCH_${PROJECT_NAME}_ENABLED)
ADD_DEFINITIONS("-DPCH_${PROJECT_NAME}_ENABLED")

IF(MSVC)
        # Disable ADD_PRECOMPILED_HEADER on MSVC
        MACRO(ADD_PRECOMPILED_HEADER _targetName _input _gch)        
        ENDMACRO()
        IF(PCH_${PROJECT_NAME}_ENABLED)
                INCLUDE (PCHSupport_MSVC)
                IF(NOT PCHSupport_FOUND)
                  # PCH usage not available. Blank out macro.
                  MACRO(ADD_PRECOMPILED_HEADER _targetName _input _gch)        
                  ENDMACRO()
                ENDIF(NOT PCHSupport_FOUND)
        ELSE(PCH_${PROJECT_NAME}_ENABLED)
          # PCH usage turned off. Blank out macro.
          MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
          ENDMACRO()
        ENDIF(PCH_${PROJECT_NAME}_ENABLED)
ELSEIF(CMAKE_COMPILER_IS_GNUCXX)
        # Disable ADD_MSVC_PRECOMPILED_HEADER on GCC
        MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
        ENDMACRO()
        IF(PCH_${PROJECT_NAME}_ENABLED)
                INCLUDE (PCHSupport_26)
                IF(NOT PCHSupport_FOUND)
                  # PCH usage not available. Blank out macro.
                  MACRO(ADD_PRECOMPILED_HEADER _targetName _input _gch)        
                  ENDMACRO()
                ENDIF(NOT PCHSupport_FOUND)
        ELSE(PCH_${PROJECT_NAME}_ENABLED)
          # PCH usage turned off. Blank out macro.
          MACRO(ADD_PRECOMPILED_HEADER _targetName _input _gch)        
          ENDMACRO()
        ENDIF(PCH_${PROJECT_NAME}_ENABLED)
ELSE()
          MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
          ENDMACRO()

          MACRO(ADD_PRECOMPILED_HEADER _targetName _input _gch)        
          ENDMACRO()
ENDIF(MSVC)

