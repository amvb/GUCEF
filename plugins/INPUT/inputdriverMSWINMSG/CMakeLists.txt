#-------------------------------------------------------------------
# This file was automatically generated by ProjectGenerator
# which is tooling part the build system designed for GUCEF
#     (Galaxy Unlimited Framework)
# For the latest info, see http://www.VanvelzenSoftware.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------
#

# Configuration for module: inputdriverMSWINMSG



if (WIN32)
  set( PLATFORM_HEADER_FILES 
    include/DLLMainInputDriverMSWINMSG.h
  )

  set( PLATFORM_HEADER_INSTALL "WIN32" )
  source_group( "Platform Header Files" FILES ${PLATFORM_HEADER_FILES} )

  set( PLATFORM_SOURCE_FILES 
    src/DLLMainInputDriverMSWINMSG.cpp
  )

  set( PLATFORM_SOURCE_INSTALL "WIN32" )
  source_group( "Platform Source Files" FILES ${PLATFORM_SOURCE_FILES} )

elseif (WIN64)
  set( PLATFORM_HEADER_FILES 
    include/DLLMainInputDriverMSWINMSG.h
  )

  set( PLATFORM_HEADER_INSTALL "WIN64" )
  source_group( "Platform Header Files" FILES ${PLATFORM_HEADER_FILES} )

  set( PLATFORM_SOURCE_FILES 
    src/DLLMainInputDriverMSWINMSG.cpp
  )

  set( PLATFORM_SOURCE_INSTALL "WIN64" )
  source_group( "Platform Source Files" FILES ${PLATFORM_SOURCE_FILES} )

endif ()

# For ease of use make a variable that has all files for this module
set( ALL_FILES ${HEADER_FILES} ${SOURCE_FILES} ${PLATFORM_HEADER_FILES} ${PLATFORM_SOURCE_FILES} )


if( WIN32 )
  set( MODULE_NAME "inputdriverMSWINMSG" )
elseif( WIN64 )
  set( MODULE_NAME "inputdriverMSWINMSG" )
endif()
if( WIN32 )
  add_library( ${MODULE_NAME} ${ALL_FILES} )
elseif( WIN64 )
  add_library( ${MODULE_NAME} ${ALL_FILES} )
endif()

if ( WIN32 )
  add_dependencies( ${MODULE_NAME} gucefCORE gucefINPUT gucefMT )
  set_property( TARGET ${MODULE_NAME} APPEND_STRING PROPERTY COMPILE_DEFINITIONS "BUILD_GUCEF_INPUT_PLUGIN_DLL;INPUTDRIVERMSWINMSG_BUILD_MODULE" )
endif( WIN32 )

if ( WIN64 )
  add_dependencies( ${MODULE_NAME} gucefCORE gucefINPUT gucefMT )
  set_property( TARGET ${MODULE_NAME} APPEND_STRING PROPERTY COMPILE_DEFINITIONS "BUILD_GUCEF_INPUT_PLUGIN_DLL;INPUTDRIVERMSWINMSG_BUILD_MODULE" )
endif( WIN64 )

include_directories( ../../../common/include ../../../platform/gucefCORE/include ../../../platform/gucefINPUT/include ../../../platform/gucefMT/include )

if ( WIN32 )
  include_directories( ../../../platform/gucefCORE/include/mswin include )
endif( WIN32 )

if ( WIN64 )
  include_directories( ../../../platform/gucefCORE/include/mswin include )
endif( WIN64 )



#******** START OF AUTOGENERATED TEMPLATED ADDITION CONTENT ********




if (WIN32)
GUCEF_config_lib( ${MODULE_NAME} )
elseif (WIN64)
GUCEF_config_lib( ${MODULE_NAME} )
endif()



#******** END OF AUTOGENERATED TEMPLATED ADDITION CONTENT ********


